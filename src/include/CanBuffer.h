

#ifndef SRC_CANBUFFER_H
#define SRC_CANBUFFER_H

#include "Base.h"
#include "CANMessage.h"

#include <string>
#include <memory>

namespace CanSocket
{
    
class CanBuffer : public Base<CANMessage>
{
public:
    virtual ~CanBuffer() {}
    
    virtual int read(CANMessage& msg) override = 0;
    virtual int write(const CANMessage& msg) override = 0;
    
    virtual unsigned int size() const = 0;
    virtual int resize( unsigned int size ) = 0;
    
    virtual bool hasNext() const = 0;
    virtual bool isFull()  const = 0;
    virtual bool isEmpty() const = 0;
    
    virtual std::string implementation() const = 0;
    
protected:
    CanBuffer() {};
};
typedef std::shared_ptr<CanBuffer> CanBufferPtr;

} /* namespace CanSocket */

#endif /* SRC_CANBUFFER_H */
