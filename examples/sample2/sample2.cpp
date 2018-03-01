
#include <iostream>

#include <unistd.h>

#include "SocketCanFactory.h"

using namespace CanUtils;

int main()
{
	SocketCanFactory factory;
	SocketCanPtr socketcan = factory.createSocketCan( "vcan0" );

	socketcan->open();

	CANMessage msg;
	msg.can_id = 0x123;
	msg.can_dlc = 4;
	msg.data[0] = 0x12;
	msg.data[1] = 0x34;
	msg.data[2] = 0x56;
	msg.data[3] = 0x78;

	socketcan->write( msg );

	socketcan->close();
}
