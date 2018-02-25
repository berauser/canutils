

#ifndef SRC_CANBUFFER_H
#define SRC_CANBUFFER_H

#include "Buffer.h"
#include "CANMessage.h"

#include <memory>

namespace CanSocket
{

typedef Buffer::Buffer<CANMessage> CanBuffer;
typedef std::shared_ptr<CanBuffer> CanBufferPtr;

} /* namespace CanSocket */

#endif /* SRC_CANBUFFER_H */
