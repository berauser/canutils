#ifndef SRC_SOCKETCANINFOLINUX_H
#define SRC_SOCKETCANINFOLINUX_H

#include "SocketCanInfoImpl.h"
#include "helper/Netlink.h"
#include "helper/NetlinkCanParser.h"

#include <fstream>

namespace CanSocket 
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
	static int copyDetails   (CANDeviceInfoPtr info, Netlink::NetlinkParser::DeviceDetailsPtr dev);
	static int copyCanDetails(CANDeviceInfoPtr info, Netlink::NetlinkCanParser::CanDeviceDetailsPtr cdev);
	
	static std::vector<DeviceFlags> copyDeviceFlags(std::vector<Netlink::NetlinkParser::DeviceFlags>&    vec);
	static std::vector<ControlMode> copyControlMode(std::vector<Netlink::NetlinkCanParser::ControlMode>& vec);
	
protected:
	std::string device;
	
	Netlink::Netlink *netlink;
};

} /* namespace CanSocket */

#endif // SRC_SOCKETCANINFOLINUX_H
