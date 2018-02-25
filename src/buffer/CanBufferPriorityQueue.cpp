
#include "CanBufferPriorityQueue.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

REGISTER_CANBUFFER  ( CanBufferPriorityQueue, "PriorityQueue" );
UNREGISTER_CANBUFFER( CanBufferPriorityQueue, "PriorityQueue" );

CanBufferPriorityQueue::CanBufferPriorityQueue( unsigned int size ) : CanBufferImpl(size)
{
	
}

CanBufferPriorityQueue::~CanBufferPriorityQueue()
{
}
 
int CanBufferPriorityQueue::read(CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferPriorityQueue::write(const CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferPriorityQueue::resize( unsigned int size )
{
	(void)size;
	return -1;
}
    
bool CanBufferPriorityQueue::hasNext() const
{
	return false;
}
bool CanBufferPriorityQueue::isFull()  const
{
	return false;
}
bool CanBufferPriorityQueue::isEmpty() const
{
	return false;
}
    
std::string CanBufferPriorityQueue::implementation() const
{
	return "PriorityQueue";
}
 
} /* namespace CanSocket */
