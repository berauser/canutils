

#ifndef SRC_INCLUDE_CANBUFFER_H_
#define SRC_INCLUDE_CANBUFFER_H_

#include "canutils/Buffer.h"
#include "canutils/CANMessage.h"

#include <memory>

namespace CanUtils
{

/*!
 * Defines the Buffer base for CANMessages
 */
typedef Buffer::Buffer<CANMessage> CanBuffer;
/*!
 * Pointer definition to Buffer< CANMessage >
 */
typedef std::shared_ptr<CanBuffer> CanBufferPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_CANBUFFER_H_ */
