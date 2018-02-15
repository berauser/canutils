#ifndef SRC_SOCKETCANSTATISTICSLINUX_H
#define SRC_SOCKETCANSTATISTICSLINUX_H

#include "SocketCanStatisticsImpl.h"
#include "helper/Netlink.h"

#include <fstream>

namespace CanSocket 
{

class SocketCanStatisticsLinux final :  public SocketCanStatisticsImpl
{
public:
	SocketCanStatisticsLinux() = delete;
	explicit SocketCanStatisticsLinux(const std::string& device_arg);
	virtual ~SocketCanStatisticsLinux();
	
protected:
	virtual int  openDevice() override final;
	virtual int  closeDevice() override final;
	virtual bool deviceIsOpen() override final;
	virtual int  readDevice(CANStatistics* stats) override final;
	virtual int  resetStatistics() override final;
	
protected:
	std::string device;
	
	Netlink *netlink;
};

} /* namespace CanSocket */

#endif // SRC_SOCKETCANSTATISTICSLINUX_H
