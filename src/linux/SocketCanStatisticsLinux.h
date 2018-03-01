#ifndef SRC_LINUX_SOCKETCANSTATISTICSLINUX_H_
#define SRC_LINUX_SOCKETCANSTATISTICSLINUX_H_

#include "SocketCanStatisticsImpl.h"
#include "helper/Netlink.h"
#include "helper/NetlinkParser.h"

#include <stdexcept>

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
	virtual CANStatisticsPtr readDevice() override final;
	virtual int  resetStatistics() override final;
	
private:
	static int copyStatistics( CANStatisticsPtr stats, Netlink::NetlinkParser::DeviceStatisticsPtr nstats );
	
protected:
	std::string device;
	
	Netlink::Netlink *netlink;
};

} /* namespace CanSocket */

#endif // SRC_LINUX_SOCKETCANSTATISTICSLINUX_H_
