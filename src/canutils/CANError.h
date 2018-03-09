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
	NoError                 =  0x00,   //< No CAN error
	TransmissionTimoutError = (1<<0),  //< Transmission timeout
	LostArbitrationError    = (1<<1),  //< Lost arbitration
	ControllerError         = (1<<2),  //< Controller problems
	ProtocolViolationError  = (1<<3),  //< Protocol violations
	TransceiveError         = (1<<4),  //< Transceiver status
	MissingAcknowledgeError = (1<<5),  //< Received no ACK on transmission
	BusOffError             = (1<<6),  //< Bus off
	BusError                = (1<<7),  //< Bus error
	ControllerRestartError  = (1<<8),  //< Controller restarted
	UnknownError            = (1<<9)   //< Unknown error
};

enum struct CANErrorLength : uint8_t
{
	CANErrorDataLengthCode = 8,        //< Data length code for error messages
};

/* arbitration lost in bit ... / data[0] */
enum struct LostArbitrationErrorBits : uint8_t
{
	LOSTARB_UNSPECIFIC      = 0x00,    //< unspecified
                                       //< else in bit
};

/* error status of CAN-controller / data[1] */
enum struct ControllerErrorBits : uint8_t
{
	CONTROLLER_UNSPECIFIC   = 0x00,    //< unspecified
	CONTROLLER_RX_OVERFLOW  = 0x01,    //< RX buffer overflow
	CONTROLLER_TX_OVERFLOW  = 0x02,    //< TX buffer overflow
	CONTROLLER_RX_WARNING   = 0x04,    //< reached warning level for RX errors
	CONTROLLER_TX_WARNING   = 0x08,    //< reached warning level for TX errors
	CONTROLLER_RX_PASSIVE   = 0x10,    //< reached error passive status RX
	CONTROLLER_TX_PASSIVE   = 0x20,    //< reached error passive status TX
};

/* error in CAN protocol (type) / data[2] */
enum struct ProtocolViolationErrorTypeBits : uint8_t
{
	PROTOCOL_UNSPECIFIC       = 0x00,  //< unspecified
	PROTOCOL_SINGLE_BIT       = 0x01,  //< single bit error
	PROTOCOL_FORMAT           = 0x02,  //< frame format error
	PROTOCOL_BIT_STUFFING     = 0x04,  //< bit stuffing error
	PROTOCOL_DOMINAT_BIT      = 0x08,  //< unable to send dominat bits
	PROTOCOL_RECESSIVE_BIT    = 0x10,  //< unable to send recessive bits
	PROTOCOL_BUS_OVERLOAD     = 0x20,  //< bus overload
	PROTOCOL_ERR_ANNOUNCEMENT = 0x40,  //< active error announcement
	PROTOCOL_ERR_TRANSMISSION = 0x80,  //< error occured on transmission
};

/* error in CAN protocol (location) / data[3] */
enum struct ProtocolViolationErrorLocationBits : uint8_t
{
	PROTOCOL_UNSPECIFIC             = 0x00,    //< unspecified
	PROTOCOL_START_OF_FRAME         = 0x03,    //< start of frame
	PROTOCOL_ID_28_21               = 0x02,    //< ID bits 28 - 21 (SFF: 10 - 3)
	PROTOCOL_ID_20_18               = 0x06,    //< ID bits 20 - 18 (SFF:  2 - 0)
	PROTOCOL_SUBSTITUTE_RTR         = 0x04,    //< substitute RTR (SFF: RTR)
	PROTOCOL_IDENTIFIER_EXT         = 0x05,    //< Identifier extension
	PROTOCOL_ID_17_13               = 0x07,    //< ID bits 17-13
	PROTOCOL_ID_12_05               = 0x0F,    //< ID bits 12- 5
	PROTOCOL_ID_04_00               = 0x0E,    //< ID bits  4- 0
	PROTOCOL_REMOTE                 = 0x0C,    //< RTR
	PROTOCOL_RESERVED_BIT_1         = 0x0D,    //< reserved bit 1
	PROTOCOL_RESERVED_BIT_0         = 0x09,    //< reserved bit 0
	PROTOCOL_DATA_LENGTH_CODE       = 0x0B,    //< data length code
	PROTOCOL_DATA_SECTION           = 0x0A,    //< data section
	PROTOCOL_CRC_SEQUENCE           = 0x08,    //< CRC sequence
	PROTOCOL_CRC_DELIMITER          = 0x18,    //< CRC delimiter
	PROTOCOL_ACKNOWNLEDGE           = 0x19,    //< ACK slot
	PROTOCOL_ACKNOWNLEDGE_DELIMITER = 0x1B,    //< ACK delimiter
	PROTOCOL_END_OF_FRAME           = 0x1A,    //< end of frame
	PROTOCOL_INTERMISSION           = 0x12,    //< intermission
};

/* error status of CAN-transceiver / data[4] */
enum struct TransceiveErrorBits : uint8_t
{
	TRANSCEIVE_UNSPECIFIC         = 0x00,  //< unspecified
	TRANSCEIVE_CANH_NO_WIRE       = 0x04,  //< CAN high no wire
	TRANSCEIVE_CANH_SHORT_TO_BAT  = 0x05,  //<
	TRANSCEIVE_CANH_SHORT_TO_VCC  = 0x06,  //<
	TRANSCEIVE_CANH_SHORT_TO_GND  = 0x07,  //<
	TRANSCEIVE_CANL_NO_WIRE       = 0x40,  //< CAN low no wire
	TRANSCEIVE_CANL_SHORT_TO_BAT  = 0x50,  //<
	TRANSCEIVE_CANL_SHORT_TO_VCC  = 0x60,  //<
	TRANSCEIVE_CANL_SHORT_TO_GND  = 0x70,  //<
	TRANSCEIVE_CANL_SHORT_TO_CANH = 0x80,  //<
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
