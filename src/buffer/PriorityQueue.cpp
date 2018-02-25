
#include "PriorityQueue.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

template class PriorityQueue<CANMessage>;
typedef PriorityQueue<CANMessage> CanPriorityQueue;

REGISTER_CANBUFFER  ( CanPriorityQueue, "PriorityQueue" );
UNREGISTER_CANBUFFER( CanPriorityQueue, "PriorityQueue" );

template<typename T>
PriorityQueue<T>::PriorityQueue( unsigned int size ) : BufferImpl<T>(size)
{
	
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

template<typename T>
int PriorityQueue<T>::read(T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int PriorityQueue<T>::write(const T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int PriorityQueue<T>::resize( unsigned int size )
{
	(void)size;
	return -1;
}

template<typename T>
bool PriorityQueue<T>::hasNext() const
{
	return false;
}

template<typename T>
bool PriorityQueue<T>::isFull()  const
{
	return false;
}

template<typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return false;
}

template<typename T>
std::string PriorityQueue<T>::implementation() const
{
	return "PriorityQueue";
}
 
} /* namespace CanSocket */
