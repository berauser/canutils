
#ifndef SRC_CANBUFFER_QUEUE_H
#define SRC_CANBUFFER_QUEUE_H

#include "BufferImpl.h"

#include <queue>

namespace CanSocket
{

template<typename T>
class GrowingQueue : public BufferImpl<T>
{
public:
    GrowingQueue( unsigned int size );
    ~GrowingQueue();
    
    virtual int read(T& msg) override;
    virtual int write(const T& msg) override;
    
    virtual int resize( unsigned int size ) override;
    
    virtual bool hasNext() const override;
    virtual bool isFull()  const override;
    virtual bool isEmpty() const override;
    
    virtual std::string implementation() const override;
    
protected:
    std::queue<T> _queue;
    
};

} /* namespace CanSocket */

#endif /* SRC_CANBUFFER_QUEUE_H */
