
#include "BufferImpl.h"
#include "CANMessage.h"

namespace CanSocket
{

template<typename T>
BufferImpl<T>::BufferImpl( unsigned int size ) : _size(size)
{
	
}

template<typename T>
BufferImpl<T>::~BufferImpl()
{
	
}

template<typename T>
unsigned int BufferImpl<T>::size() const
{
	return _size;
}

template class BufferImpl<CANMessage> ;

} /* namespace CanSocket */
