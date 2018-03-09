/*
 * CanUtilsFactory.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCANFACTORY_H_
#define SRC_INCLUDE_SOCKETCANFACTORY_H_

#include "canutils/CanBuffer.h"
#include "canutils/SocketCan.h"
#include "canutils/SocketCanInfo.h"
#include "canutils/SocketCanWorker.h"
#include "canutils/SocketCanStatistics.h"

namespace CanUtils
{
const unsigned int DEFAULT_BUFFER_SIZE = 16;        //< Default size for all CAN buffers
const std::string  DEFAULT_BUFFER_TYPE = "default"; //< Definition for the default CAN buffer implementation

/*!
 * Factory to create the platform independ CAN socket, buffer and device information
 */
class SocketCanFactory
{
public:
	/*!
	 * Constructor for SocketCanFactory
	 */
	SocketCanFactory();
	/*!
	 * Destructor for SocketCanFactory
	 */
	virtual ~SocketCanFactory() noexcept(false);
	
	/*!
	 * Get the version of the can utils implementation
	 * @return The version string
	 */
	static std::string version();
	
	/*!
	 * Creates a CanBuffer
	 * @param type Implementation of the Buffer
	 * @param size Initial buffer size
	 * @exception runtime_error When the internel buffer registration is not initialized
	 * @exception invalid_argument When the buffer implementation is not known
	 * @return Pointer to the created CAN buffer
	 */
	CanBufferPtr createCanBuffer(const std::string& type = DEFAULT_BUFFER_TYPE, const unsigned int size = DEFAULT_BUFFER_SIZE );
	/*!
	 * Create a CAN socket
	 * @param device The interface name of the CAN device
	 * @exception invalid_argument When the device name is empty
	 * @return Pointer to the created CAN socket
	 */
	SocketCanPtr createSocketCan(const std::string& device);
	
	/*!
	 * Create a worker to connect CAN buffer and CAN sockets
	 * @return Pointer to the created CAN worker
	 */
	SocketCanWorkerPtr createSocketCanWorker();
	/*!
	 * Creates CANInfo to query CAN device information given CAN device
	 * @param device The name of the CAN device
	 * @exception invalid_argument When the device name is empty
	 * @return Pointer to the created CANInfo
	 */
	SocketCanInfoPtr createSocketCanInfo( const std::string& device);
	/*!
	 * Creates CANStatistics to query the CAN statistics of the given CAN device
	 * @param device The name of the CAN device
	 * @exception invalid_argument When the device name is empty
	 * @return Pointer to the created CANStatistics
	 */
	SocketCanStatisticsPtr createSocketCanStatistics(const std::string& device);
};

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANFACTORY_H_ */
