
#include "CanBufferImpl.h"

namespace CanSocket
{

CanBufferImpl::CanBufferImpl( unsigned int size ) : _size(size)
{
	
}

CanBufferImpl::~CanBufferImpl()
{
	
}

unsigned int CanBufferImpl::size() const
{
	return _size;
}

} /* namespace CanSocket */
