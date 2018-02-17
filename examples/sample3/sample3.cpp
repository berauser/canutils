
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

using namespace CanSocket;

int main()
{
	SocketCanFactory factory;
	SocketCanStatistics* socketcan = factory.createSocketCanStatistics( "vcan0" );
	
	CANStatistics stats;
	
	while( !socketcan->read( &stats ) )
	{
		std::cout << CLR_SCREEN << std::endl; /* clear screen */
		std::cout << "RX bytes          " << std::setw(DIGITS) << stats.rx_bytes          << " | " << std::setw(DIGITS) << stats.tx_bytes            << "            bytes TX" << std::endl;
		std::cout << "RX packets        " << std::setw(DIGITS) << stats.rx_packets        << " | " << std::setw(DIGITS) << stats.tx_packets          << "          packets TX" << std::endl;
		std::cout << "RX errors         " << std::setw(DIGITS) << stats.rx_errors         << " | " << std::setw(DIGITS) << stats.tx_errors           << "           errors TX" << std::endl;
		std::cout << "RX dropped        " << std::setw(DIGITS) << stats.rx_dropped        << " | " << std::setw(DIGITS) << stats.tx_dropped          << "         droppped TX" << std::endl;
		std::cout << "RX overrun errors " << std::setw(DIGITS) << stats.rx_overrun_errors << " | " << std::setw(DIGITS) << stats.tx_carrier_errors   << "   carrier errors TX" << std::endl;
		std::cout << "RX multicast      " << std::setw(DIGITS) << stats.rx_multicast      << " | " << std::setw(DIGITS) << stats.tx_collisions       << "        collisons TX" << std::endl;
		std::cout << "RX compressed     " << std::setw(DIGITS) << stats.rx_compressed     << " | " << std::setw(DIGITS) << stats.tx_compressed       << "       compressed TX" << std::endl;
		std::cout << "RX length errors  " << std::setw(DIGITS) << stats.rx_length_errors  << " | " << std::setw(DIGITS) << stats.tx_aborted_errors   << "   aborted errors TX" << std::endl;
		std::cout << "RX crc errors     " << std::setw(DIGITS) << stats.rx_crc_errors     << " | " << std::setw(DIGITS) << stats.tx_window_errors    << "    window errors TX" << std::endl;
		std::cout << "RX frame errors   " << std::setw(DIGITS) << stats.rx_frame_errors   << " | " << std::setw(DIGITS) << stats.tx_heartbeat_errors << " heartbeat errors TX" << std::endl;
		std::cout << "RX fifo errors    " << std::setw(DIGITS) << stats.rx_fifo_errors    << " | " << std::setw(DIGITS) << stats.tx_fifo_errors      << "      fifo errors TX" << std::endl;
		std::cout << "RX missed errors  " << std::setw(DIGITS) << stats.rx_missed_errors  << std::endl;
		std::cout << std::flush;
		sleep(RELOAD_TIME);
	}
	
	delete socketcan;
}
