/*
 * CanBase.h
 *
 *  Created on: 01.03.2018
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_CANBASE_H_
#define SRC_INCLUDE_CANBASE_H_

#include "canutils/Base.h"
#include "canutils/CANMessage.h"

#include <memory>

namespace CanUtils
{

typedef Base<CANMessage> CanBase;
typedef std::shared_ptr<CanBase> CanBasePtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_CANBASE_H_ */
