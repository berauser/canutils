#ifndef SRC_LINUX_SOCKETCANSTATISTICSLINUX_H_
#define SRC_LINUX_SOCKETCANSTATISTICSLINUX_H_

#include "SocketCanStatisticsImpl.h"
#include "netlink_wrapper.h"

#include <stdexcept>

namespace CanUtils 
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
	virtual CANStatisticsPtr readDevice() override final;
	virtual int  resetStatistics() override final;
	
protected:
	std::string device;
	
	Netlink::NetlinkWrapperPtr netlink;
};

} /* namespace CanUtils */

#endif // SRC_LINUX_SOCKETCANSTATISTICSLINUX_H_
