/*
 * SocketCanWorkerLinux.cpp
 *
 *  Created on: 04.03.2017
 *      Author: rauser
 */

#include "SocketCanWorkerLinux.h"

namespace CanUtils
{

SocketCanWorkerLinux::SocketCanWorkerLinux()
{
    _thread = ThreadPtr(new Thread);
}

SocketCanWorkerLinux::~SocketCanWorkerLinux()
{
    
}
    
int SocketCanWorkerLinux::startWorker( WorkerFunc worker )
{
    _thread = ThreadPtr(new Thread( worker ));
    return 0;
}

int SocketCanWorkerLinux::stopWorker()
{
    if( !_thread )
    {
        return -1;
    }
    
    _thread->cancel();
    if( isStarted() ) _thread->join();
    _thread.reset();

    return 0;
}

bool SocketCanWorkerLinux::isStarted() const
{
    if( !_thread ) return false;
    return ( _thread->joinable() );
}

} /* namespace CanUtils */
