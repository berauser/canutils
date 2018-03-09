/*
 * SocketCan.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCAN_H_
#define SRC_INCLUDE_SOCKETCAN_H_

#include <list>
#include <string>
#include <memory>

#include "canutils/CanBase.h"

#include "canutils/CANMessage.h"
#include "canutils/CANFilter.h"
#include "canutils/CANError.h"

namespace CanUtils
{

/*!
 * Interface definition for CAN sockets
 */
class SocketCan : public CanBase
{

public:
	SocketCan() = delete;
	/*!
	 * Construtor for CAN socket
	 * @param device_arg The name of the CAN interface
	 */
	explicit SocketCan(const std::string& device_arg)
	{
		(void)device_arg;
	}
	/*!
	 * Destructor for CAN socket
	 */
	virtual ~SocketCan() noexcept(false)
	{
	}
	
	/*!
	 * Opens the CAN socket
	 * @return 0 on succes, -1 on error
	 */
	virtual int open() = 0;
	/*!
	 * Closes the CAN socket
	 * @return 0 on succes, -1 on error
	 */
	virtual int close() = 0;
	/*!
	 * Check if the CAN socket is opened
	 * @return true if open, false if closed
	 */
	virtual bool isOpen() = 0;
	
	/*!
	 * Writes a CANMessage to the CAN socket
	 * @note Blocking when the internal socket buffers are full
	 * @param message The CANMessage that should be written to the CAN socket
	 * @return The written bytes, -1 on error
	 */
	virtual int write(const CANMessage& message) = 0;
	/*!
	 * Reads a CANMessage from the CAN socket
	 * @note Blocking when no CANMessage available
	 * @param message A refernce to store the read CANMessage in it
	 */
	virtual int read(CANMessage& message) = 0;
	
	/*!
	 * Returns the name of the CAN device
	 * @return The CAN device name
	 */
	virtual const std::string& getDevice() const = 0;
	
	/*!
	 * Adds a single CANMessage filter
	 * The reception of CANMessage can be controlled.
	 * @see CANFilter for filter description
	 * @param filter The CANMessage filter to add to the device
	 * @return 0 on success, -1 on error
	 */
	virtual int addFilter(const CANFilter& filter) = 0;
	/*!
	 * Removes a single CANMessage filter
	 * The reception of CANMessage can be controlled.
	 * @param filter The CANMessage filter that should be removed from the device
	 * @return 0 on success, -1 on error
	 */
	virtual int removeFilter(const CANFilter& filter) = 0;
	/*!
	 * Removes all CANMessage filters
	 * @return 0 on succes, -1 on error
	 */
	virtual int clearFilter() = 0;
	/*!
	 * Returns a list with all CANMessage filters set
	 * @return List with CANMessage filters
	 */
	virtual std::list<CANFilter> getFilterList() = 0;
	
	/*!
	 * Enable or disable local CANMessage loopback on this CAN device.
	 * @param enable True to enable loopback (default), false to disable loopback
	 * @return 0 on success, -1 on error
	 */
	virtual int enableLoopback(bool enable) = 0;
	/*!
	 * Check if the local loopback is enabled
	 * @return true if enabled, false if disabled
	 */
	virtual bool loopbackEnabled() const = 0;
	
	/*!
	 * Enable receiving of the CANMessages sent
	 * @note Local loopback must be enabled.
	 * @param enable Trie to enable receiving, false to disable (default)
	 * @return 0 on success, -1 on error
	 */
	virtual int receiveOwnMessage(bool enable) = 0;
	/*!
	 * Check if the receiving of own CANMessage is enabled
	 * @return True if enabled, false if disabled
	 */
	virtual bool receiveOwnMessageEnabled() const = 0;
	
	/*!
	 * Add a CANError mask.
	 * Defines the errors that should be received on this CAN socket
	 * @param mask The CANErrorMask to define the CANErros that should be received
	 * @return 0 on success, -1 on error
	 */
	virtual int setErrorFilterMask( CANErrorMask mask ) = 0;
	/*!
	 * Get the currently set CANErrorMask
	 * @return The CANErrorMask that is set on this CAN socket
	 */
	virtual CANErrorMask getErrorFilterMask() const = 0;
	/*!
	 * Clears the currently set CANErrorMask
	 * @return 0 on success, -1 on error
	 */
	virtual int clearErrorFilterMask() = 0;
};
typedef std::shared_ptr<SocketCan> SocketCanPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCAN_H_ */
