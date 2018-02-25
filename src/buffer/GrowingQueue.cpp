
#include "GrowingQueue.h"

#include "CanBufferRegistry.h"

namespace CanSocket
{

template class GrowingQueue<CANMessage>;
typedef GrowingQueue<CANMessage> CanGrowingQueue;

REGISTER_CANBUFFER  ( CanGrowingQueue, "GrowingQueue" );
UNREGISTER_CANBUFFER( CanGrowingQueue, "GrowingQueue" );

template<typename T>
GrowingQueue<T>::GrowingQueue( unsigned int size ) : BufferImpl<T>(size)
{
	
}

template<typename T>
GrowingQueue<T>::~GrowingQueue()
{
}

template<typename T>
int GrowingQueue<T>::read(T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int GrowingQueue<T>::write(const T& msg)
{
	(void)msg;
	return -1;
}

template<typename T>
int GrowingQueue<T>::resize( unsigned int size )
{
	(void)size;
	return -1;
}

template<typename T>
bool GrowingQueue<T>::hasNext() const
{
	return false;
}

template<typename T>
bool GrowingQueue<T>::isFull()  const
{
	return false;
}

template<typename T>
bool GrowingQueue<T>::isEmpty() const
{
	return false;
}

template<typename T>
std::string GrowingQueue<T>::implementation() const
{
	return "GrowingQueue";
}

} /* namespace CanSocket */
