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

namespace CanUtils
{

int Thread::cancel()
{
	LOGGER( SOCKETCAN_DEBUG, "Thread::cancel()" );
#ifdef __linux__
	if( ! joinable() ) return 0;
	return pthread_cancel( this->native_handle() );
#else
	#error "Threads not implemented";
#endif
}

} /* namespace CanUtils */
