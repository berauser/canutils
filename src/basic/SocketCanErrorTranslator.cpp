
#include "SocketCanErrorTranslator.h"

namespace CanSocket
{

std::string decodeLostArbitartionError( const CANMessage& msg )
{
	if ( msg.data[0] == static_cast<uint8_t>(LostArbitrationErrorBits::LOSTARB_UNSPECIFIC) ) 
		return "unspecific";
	else
		return "in bit";
}

std::string decodeControllerError( const CANMessage& msg )
{
	switch ( msg.data[1] )
	{
	case static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_UNSPECIFIC):
		return "unspecific";
	case static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_RX_OVERFLOW):
		return "RX buffer overflow";
	case static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_TX_OVERFLOW):
		return "TX buffer overflow";
	case static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_RX_WARNING):
		return "reached warning level for RX errors";
	case static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_TX_WARNING):
		return "reached warning level for TX errors";
	case static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_RX_PASSIVE):
		return "reached error passive status for RX";
	case static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_TX_PASSIVE):
		return "reached error passive status for TX";
	default:
		return "unknown";
	}
}

std::string decodeProtocolViolationError( const CANMessage& msg )
{
	std::string error;
	switch( msg.data[2] )
	{
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_UNSPECIFIC):
		error = "unspecific";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_SINGLE_BIT):
		error = "single bit error";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_FORMAT):
		error = "frame format error";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_BIT_STUFFING):
		error = "bit stuffing error";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_DOMINAT_BIT):
		error = "unable to send dominat bit";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_RECESSIVE_BIT):
		error = "unable to send recessive bit";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_BUS_OVERLOAD):
		error = "bus overload";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_ERR_ANNOUNCEMENT):
		error = "active error announcement";
		break;
	case static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_ERR_TRANSMISSION):
		error = "error occured on transmission";
		break;
	default:
		error = "unknown";
		break;
	}
	
	error += " at ";
	
	switch( msg.data[3] )
	{
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_UNSPECIFIC):
		return error += "unspecific";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_START_OF_FRAME):
		return error += "start of frame";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_28_21):
		return error += "ID bits 28 - 21 (SFF: 10 - 3)";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_20_18):
		return error += "ID bits 20 - 18 (SFF: 2 - 0)";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_SUBSTITUTE_RTR):
		return error += "substitute RTR (SFF: RTR)";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_IDENTIFIER_EXT):
		return error += "identifier extension";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_17_13):
		return error += "ID bits 17 - 13";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_12_05):
		return error += "ID bits 12 - 5";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_04_00):
		return error += "ID bits 4 - 0";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_REMOTE):
		return error += "RTR";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_RESERVED_BIT_1):
		return error += "reserved bit 1";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_RESERVED_BIT_0):
		return error += "reserved bit 0";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_DATA_LENGTH_CODE):
		return error += "data length code";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_DATA_SECTION):
		return error += "data section";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_CRC_SEQUENCE):
		return error += "CRC sequence";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_CRC_DELIMITER):
		return error += "CRC delimiter";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ACKNOWNLEDGE):
		return error += "ACK slot";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ACKNOWNLEDGE_DELIMITER):
		return error += "ACK delimiter";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_END_OF_FRAME):
		return error += "end of frame";
	case static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_INTERMISSION):
		return error += "intermission";
	default:
		return error += "unknown";
	}
}

std::string decodeTransceiveError( const CANMessage& msg )
{
	switch( msg.data[4] )
	{
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_UNSPECIFIC):
		return "unspecific";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_NO_WIRE):
		return "no wire on CANH";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_SHORT_TO_BAT):
		return "CANH shortage to BAT";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_SHORT_TO_VCC):
		return "CANH shortage to VCC";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_SHORT_TO_GND):
		return "CANH shortage to GND";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_NO_WIRE):
		return "no wire on CANL";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_BAT):
		return "CANL shortage to BAT";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_VCC):
		return "CANL shortage to VCC";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_GND):
		return "CANL shortage to GND";
	case static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_CANH):
		return "CANL shortage to CANH";
	default:
		return "unknown";
	}
}

std::string getErrorString( const CANMessage& msg )
{	
	switch(  getErrorType(msg) )
	{
	case CANErrorFlag::NoError:
		return std::string("No Error");
	case CANErrorFlag::TransmissionTimoutError:
		return std::string("TX timeout (by netdriver)");
	case CANErrorFlag::LostArbitrationError:
		return std::string("Lost arbitration: ") += decodeLostArbitartionError(msg);
	case CANErrorFlag::ControllerError:
		return std::string("Controller error: ") += decodeControllerError(msg);
	case CANErrorFlag::ProtocolViolationError:
		return std::string("Protocol vialotion: ") += decodeProtocolViolationError(msg);
	case CANErrorFlag::TransceiveError:
		return std::string("Transceiver error status: ") += decodeTransceiveError(msg);
	case CANErrorFlag::MissingAcknowledgeError:
		return std::string("Received no ACK on transmission");
	case CANErrorFlag::BusOffError:
		return std::string("Bus off");
	case CANErrorFlag::BusError:
		return std::string("Bus error (may flood!)");
	case CANErrorFlag::ControllerRestartError:
		return std::string("Controller restarted");
	case CANErrorFlag::UnknownError:
	default:
		return std::string("Unknown CAN Error");
	}
}

CANErrorFlag getErrorType( const CANMessage& msg )
{
	if ( msg.type()  != CANMessage::CANFrameType::Error
	  || msg.can_dlc != static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode) )
	{
		return CANErrorFlag::UnknownError;
	}
	
	switch(  msg.id() )
	{
	case static_cast<uint32_t>(CANErrorFlag::NoError):
		return CANErrorFlag::NoError;
	case static_cast<uint32_t>(CANErrorFlag::TransmissionTimoutError):
		return CANErrorFlag::TransmissionTimoutError;
	case static_cast<uint32_t>(CANErrorFlag::LostArbitrationError):
		return CANErrorFlag::LostArbitrationError;
	case static_cast<uint32_t>(CANErrorFlag::ControllerError):
		return CANErrorFlag::ControllerError;
	case static_cast<uint32_t>(CANErrorFlag::ProtocolViolationError):
		return CANErrorFlag::ProtocolViolationError;
	case static_cast<uint32_t>(CANErrorFlag::TransceiveError):
		return CANErrorFlag::TransceiveError;
	case static_cast<uint32_t>(CANErrorFlag::MissingAcknowledgeError):
		return CANErrorFlag::MissingAcknowledgeError;
	case static_cast<uint32_t>(CANErrorFlag::BusOffError):
		return CANErrorFlag::BusOffError;
	case static_cast<uint32_t>(CANErrorFlag::BusError):
		return CANErrorFlag::BusError;
	case static_cast<uint32_t>(CANErrorFlag::ControllerRestartError):
		return CANErrorFlag::ControllerRestartError;
	case static_cast<uint32_t>(CANErrorFlag::UnknownError):
	default:
		return CANErrorFlag::UnknownError;
	}
}

} /* namespace CanSocket */