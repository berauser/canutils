#ifndef SRC_BASIC_SOCKETCANSTATISTICSIMPL_H_
#define SRC_BASIC_SOCKETCANSTATISTICSIMPL_H_

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
	
	virtual CANStatisticsPtr read() override final;
	virtual int reset() override final;
	
protected:
	virtual int  openDevice() = 0;
	virtual int  closeDevice() = 0;
	virtual bool deviceIsOpen() = 0;
	virtual CANStatisticsPtr  readDevice() = 0;
	virtual int  resetStatistics() = 0;
	
private:
	std::string device;
};

} /* namespace CanSocket */

#endif /* SRC_BASIC_SOCKETCANSTATISTICSIMPL_H_ */
