/*
 * Thread.h
 *
 *  Created on: 25.09.2017
 *      Author: rauser
 */

#ifndef SRC_MISC_THREAD_H_
#define SRC_MISC_THREAD_H_

#include <thread>

namespace CanSocket
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
	}

	template<typename _Callable, typename... _Args>
	explicit
	Thread(_Callable&& __f, _Args&&... __args) : std::thread( __f, (__args)... )
	{
	}

	virtual ~Thread() {}

	/**
	 * Send cancelling request to thread
	 * @return On success 0
	 */
	int cancel();
};

} /* namespace CanSocket */

#endif /* SRC_MISC_THREAD_H_ */
