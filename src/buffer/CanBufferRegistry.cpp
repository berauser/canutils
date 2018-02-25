
#include "CanBufferRegistry.h"

#include "PriorityQueue.h"

namespace CanSocket
{

Registry<CanBuffer, std::string, unsigned int>* CAN_BUFFER_REGISTRATION;
 
CONSTRUCTOR( FACTORY_PRIORITY )
static void create_registry(void)
{
        CAN_BUFFER_REGISTRATION = new Registry<CanBuffer, std::string, unsigned int>;
}

DESTRUCTOR( FACTORY_PRIORITY )
static void destroy_registry(void)
{
        delete CAN_BUFFER_REGISTRATION;
}




} /* namespace CanSocket */
