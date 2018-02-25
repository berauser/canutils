
#include "RingBuffer.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

template class RingBuffer<CANMessage>;
typedef RingBuffer<CANMessage> CanRingBuffer;
	
REGISTER_CANBUFFER  ( CanRingBuffer, "RingBuffer" );
UNREGISTER_CANBUFFER( CanRingBuffer, "RingBuffer" );

template<typename T>
RingBuffer<T>::RingBuffer( unsigned int size ) : BufferImpl<T>(size)
{
	
}

template<typename T>
RingBuffer<T>::~RingBuffer()
{
}
 
template<typename T> 
int RingBuffer<T>::read(T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int RingBuffer<T>::write(const T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int RingBuffer<T>::resize( unsigned int size )
{
	(void)size;
	return -1;
}

template<typename T>
bool RingBuffer<T>::hasNext() const
{
	return false;
}

template<typename T>
bool RingBuffer<T>::isFull()  const
{
	return false;
}

template<typename T>
bool RingBuffer<T>::isEmpty() const
{
	return false;
}

template<typename T>
std::string RingBuffer<T>::implementation() const
{
	return "RingBuffer";
}
 
} /* namespace CanSocket */
