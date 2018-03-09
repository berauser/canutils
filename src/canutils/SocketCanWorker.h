/*
 * SocketCanWorker.h
 *
 *  Created on: 01.03.2018
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCANWORKER_H_
#define SRC_INCLUDE_SOCKETCANWORKER_H_

#include "canutils/CanBase.h"

#include "canutils/CANMessage.h"
#include "canutils/CANFilter.h"
#include "canutils/CANError.h"

#include <memory>
#include <vector>

namespace CanUtils
{

class SocketCanWorker
{
public:
	virtual ~SocketCanWorker() noexcept(false)
	{
	}
	
	virtual int  start() = 0;
	virtual int  stop()  = 0;
	virtual bool isStarted() const = 0;
	
	virtual int setInput ( CanBasePtr input ) = 0;
	virtual int delInput ( CanBasePtr input ) = 0;
	virtual int addOutput( CanBasePtr output ) = 0;
	virtual int addOutput( CanBasePtr output, const CANFilter& filter ) = 0;
	virtual int addOutput( CanBasePtr output, const std::vector<CANFilter>& filters ) = 0;
	virtual int delOutput( CanBasePtr output ) = 0;
};
typedef std::shared_ptr<SocketCanWorker> SocketCanWorkerPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANWORKER_H_ */
