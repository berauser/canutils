
#include "CanBufferRegistry.h"

#include "BufferImpl.h"
#include "RingBuffer.h"
#include "BufferQueue.h"
#include "GrowingQueue.h"
#include "PriorityQueue.h"

/*************************************************************************//***
 *
 * Explicit declaration of template classes
 * 
 * ***************************************************************************/
template class Buffer::BufferImpl<CanUtils::CANMessage>;
template class Buffer::RingBuffer<CanUtils::CANMessage>;
template class Buffer::BufferQueue<CanUtils::CANMessage>;
template class Buffer::GrowingQueue<CanUtils::CANMessage>;
template class Buffer::PriorityQueue<CanUtils::CANMessage>;

/*************************************************************************//***
 *
 * CanBuffer registration
 * 
 * ***************************************************************************/
namespace CanUtils
{

/*************************************************************************//***
 *
 * Define Registration and constructor/destructor function
 * 
 * ***************************************************************************/
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

/*************************************************************************//***
 *
 * Define and register buffer types
 * 
 * ***************************************************************************/
typedef Buffer::RingBuffer<CANMessage> CanRingBuffer;
REGISTER_CANBUFFER  ( CanRingBuffer, "RingBuffer" );
UNREGISTER_CANBUFFER( CanRingBuffer, "RingBuffer" );

typedef Buffer::BufferQueue<CANMessage> CanBufferQueue;
REGISTER_CANBUFFER  ( CanBufferQueue, "Queue" );
UNREGISTER_CANBUFFER( CanBufferQueue, "Queue" );

typedef Buffer::GrowingQueue<CANMessage> CanGrowingQueue;
REGISTER_CANBUFFER  ( CanGrowingQueue, "GrowingQueue" );
UNREGISTER_CANBUFFER( CanGrowingQueue, "GrowingQueue" );

typedef Buffer::PriorityQueue<CANMessage> CanPriorityQueue;
REGISTER_CANBUFFER  ( CanPriorityQueue, "PriorityQueue" );
UNREGISTER_CANBUFFER( CanPriorityQueue, "PriorityQueue" );

} /* namespace CanUtils */
