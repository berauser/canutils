
#ifndef SRC_BUFFER_QUEUE_H
#define SRC_BUFFER_QUEUE_H

#include "BufferImpl.h"

#include <queue>

namespace CanSocket
{

template<typename T>
class BufferQueue : public BufferImpl<T>
{
public:
    BufferQueue( unsigned int size );
    ~BufferQueue();
    
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

#endif /* SRC_BUFFER_QUEUE_H */
