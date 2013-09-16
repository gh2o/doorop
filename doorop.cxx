#define F_CPU 8000000

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

class UART
{
	private:
	UART() {}

	public:
	static uint8_t read()
	{
		while (true)
			if (UCSR0A & (1 << RXC0))
				break;
		return UDR0;
	}

	static void write(uint8_t c)
	{
		while (1)
			if (UCSR0A & (1 << UDRE0))
				break;
		UDR0 = c;
	}

	static int get(FILE *s)
	{
		(void) s;
		return read();
	}

	static int put(char c, FILE *s)
	{
		(void) s;
		write(c);
		return 0;
	}

	static void init()
	{
		// setup UART
#define BAUD 9600
#include <util/setbaud.h>
		UBRR0 = UBRR_VALUE;
#if USE_2X
		UCSR0A = (1 << U2X0);
#endif
		UCSR0B = (1 << TXEN0) | (1 << RXEN0);

		// setup stdio
		static FILE uart;
		uart.get = UART::get;
		uart.put = UART::put;
		uart.flags = _FDEV_SETUP_RW;
		stdin = &uart;
		stdout = &uart;
		stderr = &uart;
	}
};

class SPI
{
	private:
	SPI() {}

	public:
	static void init()
	{
		// setup SPI
		DDRB |= 1 << 2;
		DDRB |= 1 << 3;
		DDRB |= 1 << 5;
		PORTB |= 1 << 2;
		PORTB &= ~(1 << 3);
		PORTB &= ~(1 << 5);
		SPCR = (1 << SPE) | (1 << MSTR) | 0x03;
	}

	static uint8_t transfer(uint8_t x)
	{
		SPDR = x;
		while (true)
			if (SPSR & (1 << SPIF))
				break;
		return SPDR;
	}

	static uint8_t transfer()
	{
		return transfer(0x00);
	}
};

class SPIGuard
{
	private:
	volatile uint8_t &port;
	uint8_t bit;

	public:
	SPIGuard(volatile uint8_t &port, uint8_t bit) : port(port), bit(bit)
	{
		port &= ~(1 << bit);
	}

	~SPIGuard()
	{
		port |= (1 << bit);
	}
};

class MFRC522
{
	public:
	static uint8_t readRegister(uint8_t reg)
	{
		SPIGuard guard(PORTB, 2);
		SPI::transfer(0x80 | (reg << 1));
		uint8_t value = SPI::transfer();
		return value;
	}

	static void writeRegister(uint8_t reg, uint8_t value)
	{
		SPIGuard guard(PORTB, 2);
		SPI::transfer(reg << 1);
		SPI::transfer(value);
	}

	public:
	static void init()
	{
		// setup MFRC522
		PORTB |= 1 << 2;
		DDRB |= 1 << 2;
	}
};

int main()
{
	UART::init();
	SPI::init();
	MFRC522::init();

	puts_P(PSTR("doing register dump:"));
	for (uint8_t i = 0; i < 0x40; i++)
		printf_P(PSTR("0x%02x: 0x%02x\n"), i, MFRC522::readRegister(i));
}
