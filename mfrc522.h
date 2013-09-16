static constexpr uint8_t
	kCommandReg = 0x01,
	kComIEnReg = 0x02,
	kDivIEnReg = 0x03,
	kComIrqReg = 0x04,
	kDivIrqReg = 0x05,
	kErrorReg = 0x06,
	kStatus1Reg = 0x07,
	kStatus2Reg = 0x08,
	kFIFODataReg = 0x09,
	kFIFOLevelReg = 0x0A,
	kWaterLevelReg = 0x0B,
	kControlReg = 0x0C,
	kBitFramingReg = 0x0D,
	kCollReg = 0x0E;

static constexpr uint8_t
	kCommandIdle = 0,
	kCommandMem = 1,
	kCommandGenerateRandomID = 2,
	kCommandCalcCRC = 3,
	kCommandTransmit = 4,
	kCommandNoCmdChange = 7,
	kCommandReceive = 8,
	KCommandTransceive = 12,
	kCommandMFAuthent = 14,
	kCommandSoftReset = 15;

static constexpr uint8_t
	kCommandRegRcvOff = 1 << 5,
	kCommandRegPowerDown = 1 << 4,
	kCommandRegCommand = 0x0F,

	kFIFOLevelRegFlushBuffer = 1 << 7,
	kFIFOLevelRegFIFOLevelMask = 0x7F,
	kFIFOLevelRegFIFOLevelShift = 0,

	kBitFramingRegStartSend = 1 << 7,
	kBitFramingRegRxAlignMask = 0x70,
	kBitFramingRegRxAlignShift = 4,
	kBitFramingRegTxLastBitsMask = 0x07,
	kBitFramingRegTxLastBitsShift = 0;
