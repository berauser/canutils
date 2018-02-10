#include "CANErrorTranslatorTest.h"

#include "SocketCanErrorTranslator.h"

namespace CanSocket
{
namespace Test
{

void CANErrorTranslatorTest::SetUp()
{
}

void CANErrorTranslatorTest::TearDown()
{
}

TEST_F( CANErrorTranslatorTest, no_error )
{
	/* standard frame */
	CANMessage unknownError1( 0x007, \
		CANMessage::CANFrameType::Standard, \
		3, \
		0x01, 0x02, 0x03 ); 
	 /* to short, wrong dlc */
	CANMessage unknownError2( static_cast<uint32_t>(CANErrorFlag::NoError), \
		CANMessage::CANFrameType::Error, \
		7, \
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 );
		/* error message with NoError flag and the correct size */
	CANMessage unknownError3( static_cast<uint32_t>(CANErrorFlag::UnknownError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 );
	/* error message with NoError flag and the correct size */
	CANMessage noError( static_cast<uint32_t>(CANErrorFlag::NoError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::UnknownError      ,  getErrorType(unknownError1)   );
	EXPECT_EQ( std::string("Unknown CAN Error"),  getErrorString(unknownError1) );
	
	EXPECT_EQ( CANErrorFlag::UnknownError      ,  getErrorType(unknownError2) );
	EXPECT_EQ( std::string("Unknown CAN Error"),  getErrorString(unknownError2) );
	
	EXPECT_EQ( CANErrorFlag::UnknownError      ,  getErrorType(unknownError3) );
	EXPECT_EQ( std::string("Unknown CAN Error"),  getErrorString(unknownError3) );
	
	EXPECT_EQ( CANErrorFlag::NoError  ,  getErrorType(noError) );
	EXPECT_EQ( std::string("No Error"),  getErrorString(noError) );
}

TEST_F( CANErrorTranslatorTest, transmission_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::TransmissionTimoutError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::TransmissionTimoutError   ,  getErrorType(error)   );
	EXPECT_EQ( std::string("TX timeout (by netdriver)"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, arbitration_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::LostArbitrationError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::LostArbitrationError         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Lost arbitration: unspecific"),  getErrorString(error) );
	
	error.data[0] = static_cast<uint8_t>(LostArbitrationErrorBits::LOSTARB_UNSPECIFIC);
	EXPECT_EQ( CANErrorFlag::LostArbitrationError         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Lost arbitration: unspecific"),  getErrorString(error) );
	
	error.data[0] = static_cast<uint8_t>(LostArbitrationErrorBits::LOSTARB_UNSPECIFIC) + 1;
	EXPECT_EQ( CANErrorFlag::LostArbitrationError         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Lost arbitration: in bit"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, controller_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::ControllerError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::ControllerError           ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: unknown"),  getErrorString(error) );
	
	error.data[1] = static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_UNSPECIFIC);
	EXPECT_EQ( CANErrorFlag::ControllerError              ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: unspecific"),  getErrorString(error) );
	
	error.data[1] = static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_RX_OVERFLOW);
	EXPECT_EQ( CANErrorFlag::ControllerError                      ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: RX buffer overflow"),  getErrorString(error) );
	
	error.data[1] = static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_TX_OVERFLOW);
	EXPECT_EQ( CANErrorFlag::ControllerError                      ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: TX buffer overflow"),  getErrorString(error) );
	
	error.data[1] = static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_RX_WARNING);
	EXPECT_EQ( CANErrorFlag::ControllerError                                       ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: reached warning level for RX errors"),  getErrorString(error) );
	
	error.data[1] = static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_TX_WARNING);
	EXPECT_EQ( CANErrorFlag::ControllerError                                       ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: reached warning level for TX errors"),  getErrorString(error) );
	
	error.data[1] = static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_RX_PASSIVE);
	EXPECT_EQ( CANErrorFlag::ControllerError                                       ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: reached error passive status for RX"),  getErrorString(error) );
	
	error.data[1] = static_cast<uint8_t>(ControllerErrorBits::CONTROLLER_TX_PASSIVE);
	EXPECT_EQ( CANErrorFlag::ControllerError                                       ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller error: reached error passive status for TX"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, protocol_type_error )
{
	/* test only types (less test cases) */
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::ProtocolViolationError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                 ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unknown at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_UNSPECIFIC);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                    ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_SINGLE_BIT);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: single bit error at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_FORMAT);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                            ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: frame format error at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_BIT_STUFFING);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                            ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: bit stuffing error at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_DOMINAT_BIT);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                    ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unable to send dominat bit at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_RECESSIVE_BIT);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                      ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unable to send recessive bit at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_BUS_OVERLOAD);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                      ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: bus overload at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_ERR_ANNOUNCEMENT);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                   ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: active error announcement at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_ERR_TRANSMISSION);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                       ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: error occured on transmission at unknown"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, protocol_location_error )
{
	/* test only location (less test cases) */
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::ProtocolViolationError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                 ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unknown at unknown"),  getErrorString(error) );
	
	error.data[2] = static_cast<uint8_t>(ProtocolViolationErrorTypeBits::PROTOCOL_UNSPECIFIC);
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_UNSPECIFIC);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                       ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at unspecific"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_START_OF_FRAME);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                           ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at start of frame"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_28_21);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                          ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at ID bits 28 - 21 (SFF: 10 - 3)"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_20_18);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at ID bits 20 - 18 (SFF: 2 - 0)"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_SUBSTITUTE_RTR);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                      ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at substitute RTR (SFF: RTR)"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_IDENTIFIER_EXT);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                                 ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at identifier extension"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_17_13);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                            ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at ID bits 17 - 13"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_12_05);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                           ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at ID bits 12 - 5"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ID_04_00);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                          ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at ID bits 4 - 0"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_REMOTE);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at RTR"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_RESERVED_BIT_1);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                           ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at reserved bit 1"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_RESERVED_BIT_0);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                           ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at reserved bit 0"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_DATA_LENGTH_CODE);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                             ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at data length code"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_DATA_SECTION);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at data section"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_CRC_SEQUENCE);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at CRC sequence"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_CRC_DELIMITER);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                          ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at CRC delimiter"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ACKNOWNLEDGE);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                     ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at ACK slot"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_ACKNOWNLEDGE_DELIMITER);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                          ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at ACK delimiter"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_END_OF_FRAME);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at end of frame"),  getErrorString(error) );
	
	error.data[3] = static_cast<uint8_t>(ProtocolViolationErrorLocationBits::PROTOCOL_INTERMISSION);
	EXPECT_EQ( CANErrorFlag::ProtocolViolationError                         ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Protocol vialotion: unspecific at intermission"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, transceive_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::TransceiveError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::TransceiveError           ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: unknown"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_UNSPECIFIC);
	EXPECT_EQ( CANErrorFlag::TransceiveError                      ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: unspecific"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_NO_WIRE);
	EXPECT_EQ( CANErrorFlag::TransceiveError                          ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: no wire on CANH"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_SHORT_TO_BAT);
	EXPECT_EQ( CANErrorFlag::TransceiveError                                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: CANH shortage to BAT"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_SHORT_TO_VCC);
	EXPECT_EQ( CANErrorFlag::TransceiveError                                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: CANH shortage to VCC"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANH_SHORT_TO_GND);
	EXPECT_EQ( CANErrorFlag::TransceiveError                                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: CANH shortage to GND"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_NO_WIRE);
	EXPECT_EQ( CANErrorFlag::TransceiveError                          ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: no wire on CANL"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_BAT);
	EXPECT_EQ( CANErrorFlag::TransceiveError                                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: CANL shortage to BAT"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_VCC);
	EXPECT_EQ( CANErrorFlag::TransceiveError                                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: CANL shortage to VCC"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_GND);
	EXPECT_EQ( CANErrorFlag::TransceiveError                                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: CANL shortage to GND"),  getErrorString(error) );
	
	error.data[4] = static_cast<uint8_t>(TransceiveErrorBits::TRANSCEIVE_CANL_SHORT_TO_CANH);
	EXPECT_EQ( CANErrorFlag::TransceiveError                                ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Transceiver error status: CANL shortage to CANH"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, acknowledge_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::MissingAcknowledgeError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::MissingAcknowledgeError   ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Received no ACK on transmission"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, bus_off_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::BusOffError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::BusOffError   ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Bus off"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, bus_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::BusError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::BusError   ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Bus error (may flood!)"),  getErrorString(error) );
}

TEST_F( CANErrorTranslatorTest, restart_error )
{
	CANMessage error( static_cast<uint32_t>(CANErrorFlag::ControllerRestartError), \
		CANMessage::CANFrameType::Error, \
		static_cast<uint8_t>(CANErrorLength::CANErrorDataLengthCode), \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
	
	EXPECT_EQ( CANErrorFlag::ControllerRestartError   ,  getErrorType(error)   );
	EXPECT_EQ( std::string("Controller restarted"),  getErrorString(error) );
}

} /* namespace Test */
} /* namespace CanSocket */