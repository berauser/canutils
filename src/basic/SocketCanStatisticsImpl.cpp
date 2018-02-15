
#include "SocketCanStatisticsImpl.h"

namespace CanSocket
{

SocketCanStatisticsImpl::SocketCanStatisticsImpl(const std::string& device_arg): SocketCanStatistics(device_arg), device(device_arg)
{
	
}

SocketCanStatisticsImpl::~SocketCanStatisticsImpl()
{
	
}

const std::string& SocketCanStatisticsImpl::getDevice() const
{
	return device;
}

int SocketCanStatisticsImpl::read(CANStatistics* stats)
{
	openDevice();
	readDevice(stats);
	return closeDevice();
}

int SocketCanStatisticsImpl::reset()
{
	return -1;
}

} /* namespace CanSocket */