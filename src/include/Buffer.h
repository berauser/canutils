

#ifndef SRC_INCLUDE_BUFFER_H_
#define SRC_INCLUDE_BUFFER_H_

#include "Base.h"

#include <string>

namespace Buffer
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
    
    virtual void clear() = 0;
    
    virtual std::string implementation() const = 0;
    
protected:
    Buffer() {};
};

} /* namespace Buffer */

#endif /* SRC_INCLUDE_BUFFER_H_ */
