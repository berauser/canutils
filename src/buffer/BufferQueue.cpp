
#include "BufferQueue.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

template class BufferQueue<CANMessage>;
typedef BufferQueue<CANMessage> CanBufferQueue;

REGISTER_CANBUFFER  ( CanBufferQueue, "Queue" );
UNREGISTER_CANBUFFER( CanBufferQueue, "Queue" );

template<typename T>
BufferQueue<T>::BufferQueue( unsigned int size ) : BufferImpl<T>(size)
{
	
}

template<typename T>
BufferQueue<T>::~BufferQueue()
{
}
 
 template<typename T>
int BufferQueue<T>::read(T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int BufferQueue<T>::write(const T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int BufferQueue<T>::resize( unsigned int size )
{
	(void)size;
	return -1;
}

template<typename T>
bool BufferQueue<T>::hasNext() const
{
	return false;
}

template<typename T>
bool BufferQueue<T>::isFull()  const
{
	return false;
}

template<typename T>
bool BufferQueue<T>::isEmpty() const
{
	return false;
}

template<typename T>
std::string BufferQueue<T>::implementation() const
{
	return "Queue";
}
 
} /* namespace CanSocket */
