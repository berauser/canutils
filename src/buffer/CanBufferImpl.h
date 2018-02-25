
#ifndef SRC_CANBUFFER_IMPL_H
#define SRC_CANBUFFER_IMPL_H

#include "CanBuffer.h"

namespace CanSocket
{

class CanBufferImpl : public CanBuffer
{
public:
    CanBufferImpl() = delete;
    CanBufferImpl( unsigned int size );
    virtual ~CanBufferImpl();
        
    virtual int read(CANMessage& msg) override = 0;
    virtual int write(const CANMessage& msg) override = 0;
    
    virtual unsigned int size() const override;
    virtual int resize( unsigned int size ) override = 0;
    
    virtual bool hasNext() const override = 0;
    virtual bool isFull()  const override = 0;
    virtual bool isEmpty() const override = 0;
    
    virtual std::string implementation() const override = 0;
        
protected:
        unsigned int _size;
};

} /* namespace CanSocket */

#endif /* SRC_CANBUFFER_IMPL_h */
