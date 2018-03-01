

#ifndef SRC_BUFFER_CANBUFFERREGISTRY_H_
#define SRC_BUFFER_CANBUFFERREGISTRY_H_

#include "Registry.h"
#include "CanBuffer.h"

namespace CanUtils
{

#define CAN_BUFFER_REGISTRATION registrationCanBuffer
extern Registry<CanBuffer, std::string, unsigned int>* CAN_BUFFER_REGISTRATION;

#define REGISTER_CANBUFFER(   type, key ) REGISTER_TYPE(   type, key, CAN_BUFFER_REGISTRATION );
#define UNREGISTER_CANBUFFER( type, key ) UNREGISTER_TYPE( type, key, CAN_BUFFER_REGISTRATION );

} /* namespace CanUtils */

#endif /* SRC_BUFFER_CANBUFFERREGISTRY_H_ */
