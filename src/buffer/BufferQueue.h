
#ifndef SRC_BUFFER_QUEUE_H_
#define SRC_BUFFER_QUEUE_H_

#include "BufferImpl.h"

#include <queue>
#include <mutex>
#include <condition_variable>

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
        std::unique_lock<std::mutex> lock(_mutex);
        while( _queue.empty() )
        {
            _condition_rx.wait( lock );
        }
        msg = _queue.front();
        _queue.pop();
        lock.unlock();
        _condition_tx.notify_one();
        return 0;
    }
    
    virtual int write(const T& msg) override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        while( _queue.size() >= this->size() )
        {
            _condition_tx.wait( lock );
        }
        _queue.push( msg );
        lock.unlock();
        _condition_rx.notify_one();
        return 0;
    }
    
    virtual int resize( unsigned int size ) override
    {
        if( size == 0 )
        {
                throw std::invalid_argument("Null is not a valid buffer size");
        }
        if( size == this->size() )
        {
                return 0;
        }
        /* do not delete messages if the new buffer size is smaller then the older one */
        /* wait until the enough messages have been read */
        std::unique_lock<std::mutex> lock(_mutex);
        this->_size = size;
        return 0;
    }
    
    virtual bool hasNext() const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return (_queue.size() > 0);
    }
    virtual bool isFull()  const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return ( _queue.size() >= this->size() );
    }
    virtual bool isEmpty() const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.empty();
    }
    
    virtual void clear() override
    {
        std::unique_lock<std::mutex> lock(_mutex);   
        std::queue<T> empty;
        std::swap( _queue, empty );
    }
    
    virtual std::string implementation() const override
    {
        return "Queue";
    }
    
protected:
    std::queue<T> _queue;
    mutable std::mutex _mutex;
    std::condition_variable _condition_rx;
    std::condition_variable _condition_tx;
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_QUEUE_H_ */
