
#ifndef SRC_BUFFER_BUFFERIMPL_H_
#define SRC_BUFFER_BUFFERIMPL_H_

#include "Buffer.h"

namespace Buffer
{

template<typename T>
class BufferImpl : public Buffer<T>
{
public:
    BufferImpl() = delete;
    BufferImpl( unsigned int size )  : _size(size)
    {
        
    }
    virtual ~BufferImpl()
    {
        
    }
        
    virtual int read(T& msg) override = 0;
    virtual int write(const T& msg) override = 0;
    
    virtual unsigned int size() const override
    {
        return _size;
    }
    virtual int resize( unsigned int size ) override = 0;
    
    virtual bool hasNext() const override = 0;
    virtual bool isFull()  const override = 0;
    virtual bool isEmpty() const override = 0;
    
    virtual void clear() override = 0;
    
    virtual std::string implementation() const override = 0;
        
protected:
        unsigned int _size;
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_BUFFERIMPL_H_ */
