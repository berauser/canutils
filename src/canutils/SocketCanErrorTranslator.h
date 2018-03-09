#ifndef SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_
#define SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_

#include "canutils/CANMessage.h"
#include "canutils/CANError.h"

#include <string>

namespace CanUtils
{

/*!
 * Returns the CANErroFlag of the given CANMessage
 * @see CANErroFlag
 * @param message The CANMessage from which the CANErroFlag should be read
 * @return The associated CANErroFlag
 */
CANErrorFlag getErrorType( const CANMessage& message );

/*!
 * Return the corresponding error message to the given CANMessage
 * @param message The CANMessage form which the error should be read
 * @return The associated error message
 */
std::string getErrorString( const CANMessage& message );

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANERRORTRANSLATOR_H_ */
