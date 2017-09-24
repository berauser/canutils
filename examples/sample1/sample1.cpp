
#include <iostream>

#include <unistd.h>

#include "SocketCanFactory.h"

using namespace CanSocket;
class Recevier : public SocketCanListener
{
	void recvMessage( const CANMessage& message )
	{
		std::cout << std::hex << message.can_id << " ";
		std::cout << std::dec << "[" << message.can_dlc << "] ";

		for( int i = 0; (i < message.can_dlc) && (i < MAX_DATA_LENGTH) ; ++i )
		{
			std::cout << std::hex << message.data[i] << " ";
		}
		std::cout << std::dec << std::endl;
	}
};

int main()
{
	SocketCanFactory factory;
	SocketCan* socketcan = factory.createSocketCan( "vcan0" );

	Recevier receiver;

	socketcan->addListener( receiver );
	socketcan->open();

	sleep( 15 );

	socketcan->close();
	delete socketcan;
}
