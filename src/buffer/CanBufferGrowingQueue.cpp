
#include "CanBufferGrowingQueue.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

REGISTER_CANBUFFER  ( CanBufferGrowingQueue, "GrowingQueue" );
UNREGISTER_CANBUFFER( CanBufferGrowingQueue, "GrowingQueue" );

CanBufferGrowingQueue::CanBufferGrowingQueue( unsigned int size ) : CanBufferImpl(size)
{
	
}

CanBufferGrowingQueue::~CanBufferGrowingQueue()
{
}
 
int CanBufferGrowingQueue::read(CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferGrowingQueue::write(const CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferGrowingQueue::resize( unsigned int size )
{
	(void)size;
	return -1;
}
    
bool CanBufferGrowingQueue::hasNext() const
{
	return false;
}
bool CanBufferGrowingQueue::isFull()  const
{
	return false;
}
bool CanBufferGrowingQueue::isEmpty() const
{
	return false;
}
    
std::string CanBufferGrowingQueue::implementation() const
{
	return "GrowingQueue";
}
 
} /* namespace CanSocket */
