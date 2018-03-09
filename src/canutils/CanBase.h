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

/*!
 * Defines the CanBase.
 * CanBase is a specilization of Base< T >
 */
typedef Base<CANMessage> CanBase;
/*!
 * Defines the Pointer type for CanBase
 */
typedef std::shared_ptr<CanBase> CanBasePtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_CANBASE_H_ */
