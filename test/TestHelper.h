/*
 * TestHelper.h
 *
 *  Created on: 16.11.2017
 *      Author: rauser
 */

#ifndef TEST_TESTHELPER_H_
#define TEST_TESTHELPER_H_

#include <future>

// http://antonlipov.blogspot.de/2015/08/how-to-timeout-tests-in-gtest.html
#define TEST_TIMEOUT_BEGIN                             \
	std::promise<bool> promisedFinished;               \
    auto futureResult = promisedFinished.get_future(); \
    std::thread([](std::promise<bool>& finished) {

#define TEST_TIMEOUT_FAIL_END(X)             \
	finished.set_value(true);                \
    }, std::ref(promisedFinished)).detach(); \
    EXPECT_TRUE(futureResult.wait_for(std::chrono::milliseconds(X)) != std::future_status::timeout);

#define TEST_TIMEOUT_SUCCESS_END(X)          \
	finished.set_value(true);                \
    }, std::ref(promisedFinished)).detach(); \
    EXPECT_FALSE(futureResult.wait_for(std::chrono::milliseconds(X)) != std::future_status::timeout);


//#include <sys/select.h>
//#include <sys/time.h>
//#include <sys/types.h>
//#include <unistd.h>

//#define WAIT_FOR( fd, cmd, tout )   					
//		do {							
//			int result;					
//			fd_set rdfs;					
//			FD_ZERO(&rdfs);					
//			FD_SET(fd, &rdfs);				
//			result = select(fd + 1, &rdfs, NULL, NULL, &tout);
//			if ( result == 0 ) /* timeout */		
//			{						
//				EXPECT_TRUE(false) << "timeout";	
//			}						
//			else if ( result > 0 && FD_ISSET(fd, &rdfs))
//			{						
//				cmd;					
//			}						
//		} while(0)


//#define WAIT_FOR( scan, tout )
//		do { 
//			std::promise<bool> promisedFinished;
//			auto futureResult = promisedFinished.get_future();
//			std::thread([](std::promise<bool>& finished, SocketCan & obj) { 
//				CANMessage message;
//				obj.read( &message );
//				finished.set_value(true);
//			}, std::ref(promisedFinished), std::ref(scan)).detach();
//			EXPECT_TRUE(futureResult.wait_for(std::chrono::milliseconds(tout))== std::future_status::timeout) << "timeout";
//		} while(0)


#endif /* TEST_TESTHELPER_H_ */
