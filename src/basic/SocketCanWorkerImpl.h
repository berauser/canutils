/*
 * SocketCanWorkerImpl.h
 *
 *  Created on: 01.03.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCANWORKERIMPL_H_
#define SRC_INCLUDE_SOCKETCANWORKERIMPL_H_

#include "SocketCanWorker.h"

#include <functional>
#include <map>

namespace CanUtils
{

class SocketCanWorkerImpl : public SocketCanWorker
{
public:    
    typedef std::function<void(void)> WorkerFunc;
    
public:
    SocketCanWorkerImpl();
    virtual ~SocketCanWorkerImpl();
    
    virtual int  start() override final;
    virtual int  stop()  override final;
    
    virtual int setInput ( CanBasePtr input ) override final;
    virtual int delInput ( CanBasePtr input ) override final;
    virtual int addOutput( CanBasePtr output ) override final;
    virtual int addOutput( CanBasePtr output, const CANFilter& filter ) override final;
    virtual int addOutput( CanBasePtr output, const std::vector<CANFilter>& filters ) override final;
    virtual int delOutput( CanBasePtr output ) override final;
    
protected:
    virtual int  startWorker( WorkerFunc worker ) = 0;
    virtual int  stopWorker()  = 0;
    virtual bool isStarted() const override = 0;
    virtual void workerLoop() final;

private:
    CanBasePtr _input;
    std::multimap<CANFilter,CanBasePtr> _output;
};

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANWORKERIMPL_H_ */
