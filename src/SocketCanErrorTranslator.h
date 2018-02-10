#ifndef SRC_SOCKETCANERRORTRANSLATOR_H
#define SRC_SOCKETCANERRORTRANSLATOR_H

#include "CANMessage.h"
#include "CANError.h"

#include <string>

namespace CanSocket 
{
  
CANErrorFlag getErrorType( const CANMessage& msg );
  
std::string getErrorString( const CANMessage& msg );
  
} /* namespace CanSocket */

#endif // SRC_SOCKETCANERRORTRANSLATOR_H
