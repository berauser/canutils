
#ifndef SRC_BUFFER_QUEUE_H
#define SRC_BUFFER_QUEUE_H

#include "BufferImpl.h"

#include <queue>

namespace Buffer
{

template<typename T>
class BufferQueue : public BufferImpl<T>
{
public:
    BufferQueue( unsigned int size ) : BufferImpl<T>(size)
    {
        
    }
    ~BufferQueue()
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
        return "Queue";
    }
    
protected:
    std::queue<T> _queue;
    
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_QUEUE_H */
