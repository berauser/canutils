/*
 * SocketCanImpl.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANIMPL_H_
#define SRC_SOCKETCANIMPL_H_

#include "SocketCan.h"

namespace SocketCan {

class SocketCanImpl : public SocketCan
{
	SocketCanImpl() = delete;
	SocketCanImpl( const std::string& device_arg );
	virtual ~SocketCanImpl();

	virtual bool open() override final;
	virtual bool close() override final;

	virtual int write( const CANMessage& msg ) = 0;
	virtual int registerListener( SocketCanListener& listener );

	virtual SocketCanImpl& operator=( const SocketCanImpl& src ) = 0;
	virtual SocketCanImpl& operator=( SocketCanImpl&& src ) = 0;

	virtual const int getFiledescriptor() const override final;
	virtual const std::string& getDevice() const override final;

	virtual int addFilter   ( const SocketCan::CANFilter& filter ) override final;
	virtual int removeFilter( const SocketCan::CANFilter& filter ) override final;
	virtual std::list<SocketCan::CANFilter> getFilterList() override final;

protected:

	virtual bool openDevice ( const std::string& device ) = 0;
	virtual bool closeDevice() = 0;;

	virtual int setFilter( const std::list<CANFilter>& filterList ) = 0;
protected:
	std::string device;
	std::list<SocketCan::CANFilter> filterList;
};

} /* namespace SocketCan */

#endif /* SRC_SOCKETCANIMPL_H_ */
