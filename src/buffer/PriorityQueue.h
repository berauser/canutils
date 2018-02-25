
#ifndef SRC_BUFFER_PRIORITYQUEUE_H
#define SRC_BUFFER_PRIORITYQUEUE_H

#include "BufferImpl.h"

#include <queue>

namespace CanSocket
{

template<typename T>
class PriorityQueue : public BufferImpl<T>
{
public:
    PriorityQueue( unsigned int size );
    ~PriorityQueue();
    
    virtual int read(T& msg) override;
    virtual int write(const T& msg) override;
    
    virtual int resize( unsigned int size ) override;
    
    virtual bool hasNext() const override;
    virtual bool isFull()  const override;
    virtual bool isEmpty() const override;
    
    virtual std::string implementation() const override;
    
protected:
    std::priority_queue<T> _priority_queue;
};

} /* namespace CanSocket */

#endif /* SRC_BUFFER_PRIORITYQUEUE_H */
