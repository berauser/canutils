#ifndef SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_
#define SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_

#include "CANMessage.h"
#include "CANError.h"

#include <string>

namespace CanSocket
{

CANErrorFlag getErrorType( const CANMessage& msg );

std::string getErrorString( const CANMessage& msg );

} /* namespace CanSocket */

#endif /* SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_ */
