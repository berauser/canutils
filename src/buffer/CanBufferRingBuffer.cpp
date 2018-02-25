
#include "CanBufferRingBuffer.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

REGISTER_CANBUFFER  ( CanBufferRingBuffer, "RingBuffer" );
UNREGISTER_CANBUFFER( CanBufferRingBuffer, "RingBuffer" );

CanBufferRingBuffer::CanBufferRingBuffer( unsigned int size ) : CanBufferImpl(size)
{
	
}

CanBufferRingBuffer::~CanBufferRingBuffer()
{
}
 
int CanBufferRingBuffer::read(CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferRingBuffer::write(const CANMessage& msg)
{
	(void)msg;
	return -1;
}
int CanBufferRingBuffer::resize( unsigned int size )
{
	(void)size;
	return -1;
}
    
bool CanBufferRingBuffer::hasNext() const
{
	return false;
}
bool CanBufferRingBuffer::isFull()  const
{
	return false;
}
bool CanBufferRingBuffer::isEmpty() const
{
	return false;
}
    
std::string CanBufferRingBuffer::implementation() const
{
	return "RingBuffer";
}
 
} /* namespace CanSocket */
