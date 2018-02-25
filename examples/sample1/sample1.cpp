
#include <iostream>

#include <unistd.h>

#include "SocketCanFactory.h"

using namespace CanSocket;

int main()
{
	SocketCanFactory factory;
	SocketCanPtr socketcan = factory.createSocketCan( "vcan0" );

	socketcan->open();

	CANMessage message;
	while( socketcan->isOpen() )
	{
		socketcan->read( message );
		std::cout << std::hex << message.can_id << " ";
		std::cout << std::dec << "[" << static_cast<uint32_t>(message.can_dlc) << "] ";
		for( int i = 0; (i < message.can_dlc) && (i < CAN_MAX_DATA_LENGTH) ; ++i )
		{
			std::cout << std::hex << static_cast <uint32_t>(message.data[i]) << " ";
		}
		std::cout << std::dec << std::endl;
	}

	sleep( 15 );

	socketcan->close();
}
