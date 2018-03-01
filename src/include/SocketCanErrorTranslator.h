#ifndef SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_
#define SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_

#include "CANMessage.h"
#include "CANError.h"

#include <string>

namespace CanUtils
{

CANErrorFlag getErrorType( const CANMessage& msg );

std::string getErrorString( const CANMessage& msg );

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_ */
