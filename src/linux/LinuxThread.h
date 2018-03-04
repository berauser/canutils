/*
 * Thread.h
 *
 *  Created on: 25.09.2017
 *      Author: rauser
 */

#ifndef SRC_MISC_THREAD_H_
#define SRC_MISC_THREAD_H_

#include <thread>
#include <memory>
#include <pthread.h>

namespace CanUtils
{

class Thread : public std::thread
{
public:
	Thread()
	{
	}

	Thread& operator=(Thread&& __t) noexcept
	{
		std::thread::operator=( std::forward<std::thread>(__t) );
		return *this;
	}

	Thread(Thread&& __t) noexcept : std::thread( std::forward<std::thread>(__t) )
	{
		pthread_setname_np( this->native_handle(), "SocketCanWorker" );
	}

	template<typename _Callable, typename... _Args>
	explicit
	Thread(_Callable&& __f, _Args&&... __args) : std::thread( __f, (__args)... )
	{
		pthread_setname_np( this->native_handle(), "SocketCanWorker" );
	}

	virtual ~Thread()
	{
		cancel();
	}

	/**
	 * Send cancelling request to thread
	 * @return On success 0
	 */
	int cancel()
	{
		if( this->joinable() )
		{
			return pthread_cancel( this->native_handle() );   
		}
		return 0;
    }
};
typedef std::shared_ptr<Thread> ThreadPtr;

} /* namespace CanUtils */

#endif /* SRC_MISC_THREAD_H_ */
