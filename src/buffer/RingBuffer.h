
#ifndef SRC_BUFFER_QUEUE_H
#define SRC_BUFFER_QUEUE_H

#include "BufferImpl.h"

#include <vector>

namespace CanSocket
{

template<typename T>
class RingBuffer : public BufferImpl<T>
{
public:
    RingBuffer( unsigned int size );
    ~RingBuffer();
    
    virtual int read(T& msg) override;
    virtual int write(const T& msg) override;
    
    virtual int resize( unsigned int size ) override;
    
    virtual bool hasNext() const override;
    virtual bool isFull()  const override;
    virtual bool isEmpty() const override;
    
    virtual std::string implementation() const override;
    
protected:
    std::vector<T> _ring_buffer;
    std::size_t _read;
    std::size_t _write;
};

} /* namespace CanSocket */

#endif /* SRC_BUFFER_QUEUE_H */
