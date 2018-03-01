#ifndef SRC_BASIC_SOCKETCANINFOIMPL_H_
#define SRC_BASIC_SOCKETCANINFOIMPL_H_

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
	
	virtual CANDeviceInfoPtr read() override final;
	
protected:
	virtual int  openDevice() = 0;
	virtual int  closeDevice() = 0;
	virtual bool deviceIsOpen() = 0;
	virtual CANDeviceInfoPtr  readDevice() = 0;
	
private:
	std::string device;
};

} /* namespace CanSocket */

#endif /* SRC_BASIC_SOCKETCANINFOIMPL_H_ */
