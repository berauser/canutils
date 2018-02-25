
#include <iostream>
#include <iomanip>

#include <unistd.h>

#include "SocketCanFactory.h"

/**
 * Normaly a uint64_t has 0 to 20 digits,
 * here we print only 7
 */
#define DIGITS 7
/**
 * The time to relaod the statistics in seconds
 */
#define RELOAD_TIME 1

/**
 * Clear screen command (Depends on shell!)
 */
#define CLR_SCREEN "\33[H\33[2J"
#define RED        "\33[0;31m"
#define GREEN      "\33[0;32m"
#define NO_COLOR   "\33[0;0m"

using namespace CanSocket;

int main()
{
	SocketCanFactory factory;
	
	CanBufferPtr buffer_default_default = factory.createCanBuffer();
	std::cout << "Buffer: " << buffer_default_default->implementation() << " has size: " << buffer_default_default->size() << std::endl;
	
	CanBufferPtr buffer_ring_buffer_32 = factory.createCanBuffer("RingBuffer", 32);
	std::cout << "Buffer: " << buffer_ring_buffer_32->implementation() << " has size: " << buffer_ring_buffer_32->size() << std::endl;
	
	CanBufferPtr buffer_priority_queue_default = factory.createCanBuffer("PriorityQueue");
	std::cout << "Buffer: " << buffer_priority_queue_default->implementation() << " has size: " << buffer_priority_queue_default->size() << std::endl;
	
	CanBufferPtr buffer_growing_queue_default = factory.createCanBuffer("GrowingQueue");
	std::cout << "Buffer: " << buffer_growing_queue_default->implementation() << " has size: " << buffer_growing_queue_default->size() << std::endl;
	
	
	try 
	{
		CanBufferPtr buffer_undefind_default = factory.createCanBuffer("undefined");
		(void)buffer_undefind_default;
		
	} catch( const std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
	
}
