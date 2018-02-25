

#ifndef SRC_BUFFER_H
#define SRC_BUFFER_H

#include "Base.h"

#include <string>

namespace CanSocket
{

template<typename T>
class Buffer : public Base<T>
{
public:
    virtual ~Buffer() {}
    
    virtual int read(T& msg) override = 0;
    virtual int write(const T& msg) override = 0;
    
    virtual unsigned int size() const = 0;
    virtual int resize( unsigned int size ) = 0;
    
    virtual bool hasNext() const = 0;
    virtual bool isFull()  const = 0;
    virtual bool isEmpty() const = 0;
    
    virtual std::string implementation() const = 0;
    
protected:
    Buffer() {};
};

} /* namespace CanSocket */

#endif /* SRC_BUFFER_H */
