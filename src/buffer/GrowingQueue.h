
#ifndef SRC_BUFFER_GROWINGQUEUE_H
#define SRC_BUFFER_GROWINGQUEUE_H

#include "BufferImpl.h"

#include <queue>
#include <mutex>
#include <condition_variable>

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
        std::unique_lock<std::mutex> lock(_mutex);
        while( _queue.empty() )
        {
                _condition.wait( lock );
        }
        msg = _queue.front();
        _queue.pop();
        return 0;
    }
    
    virtual int write(const T& msg) override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _queue.push( msg );
        lock.unlock();
        _condition.notify_one();
        return 0;
    }
    
    virtual int resize( unsigned int size ) override
    {
        (void)size;
        return -1; /* not possible */
    }
    
    virtual bool hasNext() const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return ( !_queue.empty() );
    }
    
    virtual bool isFull()  const override
    {
        return false; /* not possible */
    }
    
    virtual bool isEmpty() const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return ( _queue.empty() );
    }
    
    virtual unsigned int size() const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.size();
    }
    
    virtual void clear() override
    {
        std::unique_lock<std::mutex> lock(_mutex);   
        std::queue<T> empty;
        std::swap( _queue, empty );
    }
    
    virtual std::string implementation() const override
    {
        return "GrowingQueue";
    }
    
protected:
    std::queue<T> _queue;
    mutable std::mutex _mutex;
    std::condition_variable _condition;
    
};

} /* namespace Buffer */

#endif /* SRC_CANBUFFER_GROWINGQUEUE_H */
