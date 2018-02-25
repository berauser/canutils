

#ifndef SRC_CANBUFFERREGISTRY_H
#define SRC_CANBUFFERREGISTRY_H

#include "Registry.h"
#include "CanBuffer.h"

namespace CanSocket
{

#define CAN_BUFFER_REGISTRATION registrationCanBuffer
extern Registry<CanBuffer, std::string, unsigned int>* CAN_BUFFER_REGISTRATION;

#define REGISTER_CANBUFFER(   type, key ) REGISTER_TYPE(   type, key, CAN_BUFFER_REGISTRATION );
#define UNREGISTER_CANBUFFER( type, key ) UNREGISTER_TYPE( type, key, CAN_BUFFER_REGISTRATION );

} /* namespace CanSocket */

#endif /* SRC_CANBUFFERREGISTRY_H */
