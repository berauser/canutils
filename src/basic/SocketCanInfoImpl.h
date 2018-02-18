#ifndef SOCKETCANINFOIMPL_H
#define SOCKETCANINFOIMPL_H

#include "SocketCanInfo.h"

namespace CanSocket
{

class SocketCanInfoImpl :  public SocketCanInfo
{
public:
	SocketCanInfoImpl() = delete;
	explicit SocketCanInfoImpl(const std::string& device_arg);
	virtual ~SocketCanInfoImpl();
	
	virtual const std::string& getDevice() const override final;
	
	virtual int read(CANDeviceInfo* info) override final;
	
protected:
	virtual int  openDevice() = 0;
	virtual int  closeDevice() = 0;
	virtual bool deviceIsOpen() = 0;
	virtual int  readDevice(CANDeviceInfo* info) = 0;
	
private:
	std::string device;
};

} /* namespace CanSocket */

#endif // SOCKETCANINFOIMPL_H
