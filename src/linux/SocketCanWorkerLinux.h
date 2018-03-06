/*
 * SocketCanWorkerLinux.h
 *
 *  Created on: 04.03.2017
 *      Author: rauser
 */

#ifndef SRC_LINUX_SOCKETCANWORKERLINUX_H_
#define SRC_LINUX_SOCKETCANWORKERLINUX_H_

#include "SocketCanWorkerImpl.h"
#include "LinuxThread.h"

namespace CanUtils
{

class SocketCanWorkerLinux final : public SocketCanWorkerImpl
{    
public:
    SocketCanWorkerLinux();
    virtual ~SocketCanWorkerLinux();
    
protected:
    virtual int startWorker( WorkerFunc worker ) override;
    virtual int stopWorker() override;
    virtual bool isStarted() const override;
    
protected:
    ThreadPtr _thread;
};

} /* namespace CanUtils */

#endif /* SRC_LINUX_SOCKETCANWORKERLINUX_H_ */
