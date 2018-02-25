
#ifndef SRC_BUFFER_PRIORITYQUEUE_H
#define SRC_BUFFER_PRIORITYQUEUE_H

#include "BufferImpl.h"

#include <queue>

namespace Buffer
{

template<typename T>
class PriorityQueue : public BufferImpl<T>
{
public:
    PriorityQueue( unsigned int size )  : BufferImpl<T>(size)
    {
        
    }
    ~PriorityQueue()
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
        return "PriorityQueue";
    }
    
protected:
    std::priority_queue<T> _priority_queue;
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_PRIORITYQUEUE_H */
