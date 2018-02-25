
#include "CanBufferQueue.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

REGISTER_CANBUFFER  ( CanBufferQueue, "Queue" );
UNREGISTER_CANBUFFER( CanBufferQueue, "Queue" );

CanBufferQueue::CanBufferQueue( unsigned int size ) : CanBufferImpl(size)
{
	
}

CanBufferQueue::~CanBufferQueue()
{
}
 
int CanBufferQueue::read(CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferQueue::write(const CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferQueue::resize( unsigned int size )
{
	(void)size;
	return -1;
}
    
bool CanBufferQueue::hasNext() const
{
	return false;
}
bool CanBufferQueue::isFull()  const
{
	return false;
}
bool CanBufferQueue::isEmpty() const
{
	return false;
}
    
std::string CanBufferQueue::implementation() const
{
	return "Queue";
}
 
} /* namespace CanSocket */
