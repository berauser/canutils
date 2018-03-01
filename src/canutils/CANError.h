/*
 * CANError.h
 *
 *  Created on: 01.10.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_CANERROR_H_
#define SRC_INCLUDE_CANERROR_H_

#include <cstdint>

namespace CanUtils
{

typedef uint32_t CANErrorMask;

enum struct CANErrorFlag : uint32_t 
{
	NoError                 =  0x00,
	TransmissionTimoutError = (1<<0),
	LostArbitrationError    = (1<<1),
	ControllerError         = (1<<2),
	ProtocolViolationError  = (1<<3),
	TransceiveError         = (1<<4),
	MissingAcknowledgeError = (1<<5),
	BusOffError             = (1<<6),
	BusError                = (1<<7),
	ControllerRestartError  = (1<<8),
	UnknownError            = (1<<9)
};

enum struct CANErrorLength : uint8_t 
{
	CANErrorDataLengthCode = 8,
};

/* arbitration lost in bit ... / data[0] */
enum struct LostArbitrationErrorBits : uint8_t 
{
	LOSTARB_UNSPECIFIC      = 0x00,
};

/* error status of CAN-controller / data[1] */
enum struct ControllerErrorBits : uint8_t 
{
	CONTROLLER_UNSPECIFIC   = 0x00,
	CONTROLLER_RX_OVERFLOW  = 0x01,
	CONTROLLER_TX_OVERFLOW  = 0x02,
	CONTROLLER_RX_WARNING   = 0x04,
	CONTROLLER_TX_WARNING   = 0x08,
	CONTROLLER_RX_PASSIVE   = 0x10,
	CONTROLLER_TX_PASSIVE   = 0x20,
};

/* error in CAN protocol (type) / data[2] */
enum struct ProtocolViolationErrorTypeBits : uint8_t 
{
	PROTOCOL_UNSPECIFIC       = 0x00,
	PROTOCOL_SINGLE_BIT       = 0x01,
	PROTOCOL_FORMAT           = 0x02,
	PROTOCOL_BIT_STUFFING     = 0x04,
	PROTOCOL_DOMINAT_BIT      = 0x08,
	PROTOCOL_RECESSIVE_BIT    = 0x10,
	PROTOCOL_BUS_OVERLOAD     = 0x20,
	PROTOCOL_ERR_ANNOUNCEMENT = 0x40,
	PROTOCOL_ERR_TRANSMISSION = 0x80,
};

/* error in CAN protocol (location) / data[3] */
enum struct ProtocolViolationErrorLocationBits : uint8_t 
{
	PROTOCOL_UNSPECIFIC             = 0x00,
	PROTOCOL_START_OF_FRAME         = 0x03,
	PROTOCOL_ID_28_21               = 0x02,
	PROTOCOL_ID_20_18               = 0x06,
	PROTOCOL_SUBSTITUTE_RTR         = 0x04,
	PROTOCOL_IDENTIFIER_EXT         = 0x05,
	PROTOCOL_ID_17_13               = 0x07,
	PROTOCOL_ID_12_05               = 0x0F,
	PROTOCOL_ID_04_00               = 0x0E,
	PROTOCOL_REMOTE                 = 0x0C,
	PROTOCOL_RESERVED_BIT_1         = 0x0D,
	PROTOCOL_RESERVED_BIT_0         = 0x09,
	PROTOCOL_DATA_LENGTH_CODE       = 0x0B,
	PROTOCOL_DATA_SECTION           = 0x0A,
	PROTOCOL_CRC_SEQUENCE           = 0x08,
	PROTOCOL_CRC_DELIMITER          = 0x18,
	PROTOCOL_ACKNOWNLEDGE           = 0x19,
	PROTOCOL_ACKNOWNLEDGE_DELIMITER = 0x1B,
	PROTOCOL_END_OF_FRAME           = 0x1A,
	PROTOCOL_INTERMISSION           = 0x12,
};

/* error status of CAN-transceiver / data[4] */
enum struct TransceiveErrorBits : uint8_t 
{
	TRANSCEIVE_UNSPECIFIC         = 0x00,
	TRANSCEIVE_CANH_NO_WIRE       = 0x04,
	TRANSCEIVE_CANH_SHORT_TO_BAT  = 0x05,
	TRANSCEIVE_CANH_SHORT_TO_VCC  = 0x06,
	TRANSCEIVE_CANH_SHORT_TO_GND  = 0x07,
	TRANSCEIVE_CANL_NO_WIRE       = 0x40,
	TRANSCEIVE_CANL_SHORT_TO_BAT  = 0x50,
	TRANSCEIVE_CANL_SHORT_TO_VCC  = 0x60,
	TRANSCEIVE_CANL_SHORT_TO_GND  = 0x70,
	TRANSCEIVE_CANL_SHORT_TO_CANH = 0x80,
};

inline constexpr CANErrorFlag
operator ~(CANErrorFlag &f)
{
	return static_cast<CANErrorFlag>(~static_cast<uint32_t>(f));
}

inline constexpr CANErrorFlag
operator &(CANErrorFlag &f1, CANErrorFlag &f2)
{
	return static_cast<CANErrorFlag>(static_cast<uint32_t>(f1)&static_cast<uint32_t>(f2));
}

inline constexpr CANErrorFlag
operator |(CANErrorFlag &f1, CANErrorFlag &f2)
{
	return static_cast<CANErrorFlag>(static_cast<uint32_t>(f1)|static_cast<uint32_t>(f2));
}

inline constexpr CANErrorMask
operator &=(CANErrorMask &data, const CANErrorFlag &f)
{
	return ( data & static_cast<uint32_t>(f) );
}

inline constexpr CANErrorMask
operator |=(CANErrorMask &data, const CANErrorFlag &f)
{
	return ( data | static_cast<uint32_t>(f) );
}

inline constexpr CANErrorMask
operator |(CANErrorMask &data, CANErrorFlag &f)
{
	return ( data | static_cast<CANErrorMask>(f) );
}

inline constexpr CANErrorMask
operator &(CANErrorMask &data, CANErrorFlag &f)
{
	return ( data & static_cast<CANErrorMask>(f) );
}

inline constexpr bool
operator ==(const CANErrorMask &data, const CANErrorFlag &f)
{
	return ( data == static_cast<uint32_t>(f));
}

inline constexpr bool
operator !=(const CANErrorMask &data, const CANErrorFlag &f)
{
	return ( data != static_cast<uint32_t>(f));
}


} /* namespace CanUtils */

#endif /* SRC_INCLUDE_CANERROR_H_ */
