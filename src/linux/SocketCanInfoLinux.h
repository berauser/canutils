#ifndef SRC_LINUX_SOCKETCANINFOLINUX_H_
#define SRC_LINUX_SOCKETCANINFOLINUX_H_

#include "SocketCanInfoImpl.h"

#include "netlink_wrapper.h"

namespace CanUtils
{

class SocketCanInfoLinux final :  public SocketCanInfoImpl
{
public:
	SocketCanInfoLinux() = delete;
	explicit SocketCanInfoLinux(const std::string& device_arg);
	virtual ~SocketCanInfoLinux();
	
protected:
	virtual int  openDevice() override final;
	virtual int  closeDevice() override final;
	virtual bool deviceIsOpen() override final;
	virtual CANDeviceInfoPtr  readDevice() override final;
	
private:
	static bool isCanDevice(struct rtnl_link* link);
	static CanState getCanState(struct rtnl_link* link);
	static uint32_t getClockFrequency(struct rtnl_link* link);
	static uint32_t getRestartMS(struct rtnl_link* link);
	static uint16_t getBerrCountTxErr(struct rtnl_link* link);
	static uint16_t getBerrCountRxErr(struct rtnl_link* link);
	static void getBittiming(struct rtnl_link* link, CanBittiming* bittiming);
	static void getBittimingConst(struct rtnl_link* link, CanBittimingConst* bittiming_const);
	static std::vector<DeviceFlags> getDeviceFlags(struct rtnl_link* link);
	static std::vector<ControlMode> getControlMode(struct rtnl_link* link);
	
protected:
	std::string device;
	
    Netlink::NetlinkWrapperPtr netlink;
};

} /* namespace CanUtils */

#endif // SRC_LINUX_SOCKETCANINFOLINUX_H_
