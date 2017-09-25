/*
 * Thread.cpp
 *
 *  Created on: 25.09.2017
 *      Author: rauser
 */

#include "Thread.h"

#include "logger.h"

#ifdef __linux__
#include <pthread.h>
#else
	/* windows */
#endif

namespace CanSocket
{

int Thread::cancel()
{
	FTRACE( FFDC_SOCKETCAN_DEBUG, "Thread::cancel()" );
#ifdef __linux__
	return pthread_cancel( this->native_handle() );
#else
	#error "Threads not implemented";
#endif
}

} /* namespace CanSocket */
