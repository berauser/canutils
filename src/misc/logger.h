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
	#define LOGGER( buf, format, ... ) fprintf ( stdout, buf " " format "\x1B[0m\n", ##__VA_ARGS__ )
	#define SOCKETCAN_ERROR "\x1B[31m[ERROR]"
	#define SOCKETCAN_INFO  "\x1B[33m[INFO ]"
	#define SOCKETCAN_DEBUG "\x1B[37m[DEBUG]"
#else
	#define LOGGER( buf, format, ... )
#endif // DEBUG_CONSOLE

#endif /* SRC_LOGGER_H_ */
