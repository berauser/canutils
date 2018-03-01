

#ifndef SRC_INCLUDE_CANBUFFER_H_
#define SRC_INCLUDE_CANBUFFER_H_

#include "canutils/Buffer.h"
#include "canutils/CANMessage.h"

#include <memory>

namespace CanUtils
{

typedef Buffer::Buffer<CANMessage> CanBuffer;
typedef std::shared_ptr<CanBuffer> CanBufferPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_CANBUFFER_H_ */
