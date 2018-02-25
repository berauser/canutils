
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

CANStatisticsPtr SocketCanStatisticsImpl::read()
{
	openDevice();
	CANStatisticsPtr stats = readDevice();
	closeDevice();
	
	return stats;
}

int SocketCanStatisticsImpl::reset()
{
	return -1;
}

} /* namespace CanSocket */