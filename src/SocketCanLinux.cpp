/*
 * SocketCan.cpp
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#include "SocketCanLinux.h"

namespace SocketCan {

SocketCanLinux::SocketCanLinux(const std::string& device_arg ) : SocketCan( device_arg ), socketfd( -1 )
{
}

SocketCanLinux::~SocketCanLinux() {
}

bool SocketCanLinux::open() {
}

bool SocketCanLinux::close() {
}

int SocketCanLinux::write(const CANMessage& msg) {
}

int SocketCanLinux::registerListener(SocketCanListener& listener) {
}

SocketCanLinux& SocketCanLinux::operator =(const SocketCanLinux& src) {
}

SocketCanLinux& SocketCanLinux::operator =(SocketCanLinux&& src) {
}

const int SocketCanLinux::getFiledescriptor() const {
}

const std::string& SocketCanLinux::getDevice() const {
}

} /* namespace SocketCan */
