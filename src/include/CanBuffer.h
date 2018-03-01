

#ifndef SRC_INCLUDE_CANBUFFER_H_
#define SRC_INCLUDE_CANBUFFER_H_

#include "Buffer.h"
#include "CANMessage.h"

#include <memory>

namespace CanSocket
{

typedef Buffer::Buffer<CANMessage> CanBuffer;
typedef std::shared_ptr<CanBuffer> CanBufferPtr;

} /* namespace CanSocket */

#endif /* SRC_INCLUDE_CANBUFFER_H_ */
