
#ifndef SRC_BUFFER_GROWINGQUEUE_H
#define SRC_BUFFER_GROWINGQUEUE_H

#include "BufferImpl.h"

#include <queue>

namespace Buffer
{

template<typename T>
class GrowingQueue : public BufferImpl<T>
{
public:
    GrowingQueue( unsigned int size ) : BufferImpl<T>(size)
    {
        
    }
    ~GrowingQueue()
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
        return "GrowingQueue";
    }
    
protected:
    std::queue<T> _queue;
    
};

} /* namespace Buffer */

#endif /* SRC_CANBUFFER_GROWINGQUEUE_H */
