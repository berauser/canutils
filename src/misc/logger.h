/*
 * logger.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#define DEBUG_CONSOLE

#ifdef DEBUG_CONSOLE
	#include <stdio.h>
	#define FTRACE( buf, format, ... ) fprintf ( stdout, buf " " format "\x1B[0m\n", ##__VA_ARGS__ )
	#define STRACE( buf, format, ... ) fprintf ( stdout, buf " " format "\x1B[0m\n", ##__VA_ARGS__ )
	#define ITRACE( buf, format, ... ) fprintf ( stdout, buf " " format "\x1B[0m\n", ##__VA_ARGS__ )
	#define FFDC_SOCKETCAN_ERROR "\x1B[31mSOCKETCAN_ERROR"
	#define FFDC_SOCKETCAN_INFO  "\x1B[33mSOCKETCAN_INFO "
	#define FFDC_SOCKETCAN_DEBUG "\x1B[37mSOCKETCAN_DEBUG"
#else
	#define FTRACE( buf, format, ... )
	#define STRACE( buf, format, ... )
	#define ITRACE( buf, format, ... )
#endif // DEBUG_CONSOLE



#endif /* SRC_LOGGER_H_ */
