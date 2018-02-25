
#ifndef SRC_BUFFER_RINGBUFFER_H
#define SRC_BUFFER_RINGBUFFER_H

#include "BufferImpl.h"

#include <vector>

namespace Buffer
{

template<typename T>
class RingBuffer : public BufferImpl<T>
{
public:
    RingBuffer( unsigned int size ) : BufferImpl<T>(size)
    {
        
    }
    ~RingBuffer()
    {
        
    }
    
    virtual int read(T& msg) override
    {
        (void)msg;
        return -1;
    }
    virtual int write(const T& msg) override
    {
        (void)msg;
        return -1;
    }
    
    virtual int resize( unsigned int size ) override
    {
        (void)size;
        return -1;
    }
    
    virtual bool hasNext() const override
    {
        return false;
    }
    
    virtual bool isFull()  const override
    {
        return false;
    }
    
    virtual bool isEmpty() const override
    {
        return false;
    }
    
    virtual std::string implementation() const override
    {
        return "RingBuffer";
    }
    
protected:
    std::vector<T> _ring_buffer;
    std::size_t _read;
    std::size_t _write;
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_RINGBUFFER_H */
