
#ifndef SRC_BUFFER_RINGBUFFER_H_
#define SRC_BUFFER_RINGBUFFER_H_

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
                _condition_rx.wait( lock );
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
        /* create a new vector, swap it with the old one */
        /* and write all entries to empty _ring_buffer */
        /* the oldest messages are lost, if the new buffer is smaller */
        std::unique_lock<std::mutex> lock(_mutex);
        
        std::vector<T> tmp( size );
        std::size_t  old_head = this->_head;
        std::size_t  old_tail = this->_tail;
        unsigned int old_size = this->_size;
        
        tmp.swap( _ring_buffer );
        this->_size = size;
        this->_head = 0;
        this->_tail = 0;
        
        while( old_tail != old_head )
        {
            _ring_buffer[_head] = tmp[old_tail];
            
            _head = ( (_head + 1) % this->_size );
            if( _head == _tail )
            {
                _tail = ( (_tail + 1) % this->_size );
            }
            
            old_tail = (old_tail + 1) % old_size;
        }
        return 0;
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
    std::condition_variable _condition_rx;
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_RINGBUFFER_H_ */
