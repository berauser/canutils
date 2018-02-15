#ifndef SOCKETCANSTATISTICSIMPL_H
#define SOCKETCANSTATISTICSIMPL_H

#include "SocketCanStatistics.h"

namespace CanSocket
{

class SocketCanStatisticsImpl :  public SocketCanStatistics
{
public:
	SocketCanStatisticsImpl() = delete;
	explicit SocketCanStatisticsImpl(const std::string& device_arg);
	virtual ~SocketCanStatisticsImpl();
	
	virtual const std::string& getDevice() const override final;
	
	virtual int read(CANStatistics* stats) override final;
	virtual int reset() override final;
	
protected:
	virtual int  openDevice() = 0;
	virtual int  closeDevice() = 0;
	virtual bool deviceIsOpen() = 0;
	virtual int  readDevice(CANStatistics* stats) = 0;
	virtual int  resetStatistics() = 0;
	
private:
	std::string device;
};

} /* namespace CanSocket */

#endif // SOCKETCANSTATISTICSIMPL_H
