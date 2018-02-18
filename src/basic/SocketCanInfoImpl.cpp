
#include "SocketCanInfoImpl.h"

namespace CanSocket
{

SocketCanInfoImpl::SocketCanInfoImpl(const std::string& device_arg): SocketCanInfo(device_arg), device(device_arg)
{
	
}

SocketCanInfoImpl::~SocketCanInfoImpl()
{
	
}

const std::string& SocketCanInfoImpl::getDevice() const
{
	return device;
}

int SocketCanInfoImpl::read(CANDeviceInfo* info)
{
	openDevice();
	readDevice(info);
	return closeDevice();
}

} /* namespace CanSocket */