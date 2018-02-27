
#ifndef SRC_BUFFER_RINGBUFFER_H
#define SRC_BUFFER_RINGBUFFER_H

#include "BufferImpl.h"

#include <vector>
#include <mutex>
#include <condition_variable>

namespace Buffer
{

template<typename T>
class RingBuffer : public BufferImpl<T>
{
public:
    RingBuffer( unsigned int size ) : BufferImpl<T>(size), _head(0), _tail(0)
    {
        _ring_buffer = std::vector<T>( size );
    }
    ~RingBuffer()
    {
        
    }
    
    virtual int read(T& msg) override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        while( ( _head == _tail ) )
        {
                _condition.wait( lock );
        }
        
        msg = _ring_buffer[_tail];
        
        _tail = (_tail + 1) % this->size();
        
        return 0;
    }
    virtual int write(const T& msg) override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _ring_buffer[_head] = msg;
        _head = ( (_head + 1) % this->size() );
        
        if( _head == _tail )
        {
            _tail = ( (_tail + 1) % this->size() );
        }
        
        lock.unlock();
        _condition.notify_one();
        
        return 0;
    }
    
    virtual int resize( unsigned int size ) override
    {
        (void)size;
        return -1; /* TODO currently not implemented */
        
//         std::unique_lock<std::mutex> lock(_mutex);
//         _ring_buffer.resize( size );
//         // FIXME copy to another vector, replace _head and _tail
//         this->_size = size;
//         return 0;
    }
    
    virtual bool hasNext() const override
    {
        return ( !this->isEmpty() );
    }
    
    virtual bool isFull()  const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return ( ( (_head + 1) % this->size() ) == _tail );
    }
    
    virtual bool isEmpty() const override
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return ( _head == _tail );
    }
    
    virtual void clear() override 
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _ring_buffer.clear();
        _head = 0;
        _tail = 0;
    }
    
    virtual std::string implementation() const override
    {
        return "RingBuffer";
    }
    
protected:
    std::vector<T> _ring_buffer;
    std::size_t _head;
    std::size_t _tail;
    mutable std::mutex _mutex;
    std::condition_variable _condition;
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_RINGBUFFER_H */
