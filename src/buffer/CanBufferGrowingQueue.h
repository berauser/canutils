
#ifndef SRC_CANBUFFER_QUEUE_H
#define SRC_CANBUFFER_QUEUE_H

#include "CanBufferImpl.h"

#include <queue>

namespace CanSocket
{

class CanBufferGrowingQueue : public CanBufferImpl
{
public:
    CanBufferGrowingQueue( unsigned int size );
    ~CanBufferGrowingQueue();
    
    virtual int read(CANMessage& msg) override;
    virtual int write(const CANMessage& msg) override;
    
    virtual int resize( unsigned int size ) override;
    
    virtual bool hasNext() const override;
    virtual bool isFull()  const override;
    virtual bool isEmpty() const override;
    
    virtual std::string implementation() const override;
    
protected:
    std::queue<CANMessage> _queue;
    
};

} /* namespace CanSocket */

#endif /* SRC_CANBUFFER_QUEUE_H */
