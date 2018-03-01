
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

using namespace CanUtils;

int main()
{
	SocketCanFactory factory;
	SocketCanInfoPtr socketcan = factory.createSocketCanInfo( "vcan0" );
	
	CANDeviceInfoPtr info = socketcan->read();
	
	std::cout << CLR_SCREEN << std::endl; /* clear screen */
	
	// Device details
	std::cout << GREEN << "Device details ------------------------------------------------" << NO_COLOR << std::endl;
	std::cout << "Interface index: " <<   info->device_details.ifindex                                                << std::endl;
	std::cout << "Interface name:  " << ( info->device_details.ifname.size()  ? info->device_details.ifname : "\"\"" ) << std::endl;
	std::cout << "Interface type:  " << ( info->device_details.iftype.size()  ? info->device_details.iftype : "\"\"" ) << std::endl;
	std::cout << "Interface alias: " << ( info->device_details.ifalias.size() ? info->device_details.ifalias: "\"\"" ) << std::endl;
	std::cout << "Device flags:    ";
		for( DeviceFlags flag : info->device_details.flags )
		{
			std::cout << SocketCanInfo::toString(flag) << " ";
		}
		std::cout << std::endl;
	std::cout << "Settings:        " << "mtu:    "           << info->device_details.mtu     << std::endl
	          << "                 " << "tx_len: "           << info->device_details.tx_qlen << std::endl
	          << "                 " << "qdisc:  "           << info->device_details.qdisc   << std::endl;
	std::cout << "Device state:    " << SocketCanInfo::toString(info->device_details.state)  << std::endl;
	std::cout << std::endl;
	
	// Can Device details
	std::cout << GREEN << "CAN Device details: -------------------------------------------" << NO_COLOR << std::endl;
	std::cout << "CAN state:           " << SocketCanInfo::toString(info->can_device_details.state) << std::endl;
	std::cout << "CAN clock frequency: " << info->can_device_details.clock_freq << std::endl;
	std::cout << "CAN restart (ms):    " << info->can_device_details.restart_ms << std::endl;
	std::cout << "CAN mode:            ";
		for( ControlMode mode : info->can_device_details.mode )
		{
			std::cout << SocketCanInfo::toString(mode) << " ";
		}
	std::cout << std::endl;
	std::cout << std::endl;
	
	// CAN timming (current)
	std::cout << GREEN << "Bittiming (current): ------------------------------------------" << NO_COLOR << std::endl;
	std::cout << "Bitrate:                    " << info->bittiming.bitrate      << std::endl;
	std::cout << "Sample-point:               " << info->bittiming.sample_point << std::endl;
	std::cout << "Time quanta (ns):           " << info->bittiming.tq           << std::endl;
	std::cout << "Propagation segment (tq):   " << info->bittiming.prop_seg     << std::endl;
	std::cout << "Phase buffer seq 1 (tq):    " << info->bittiming.phase_seg1   << std::endl;
	std::cout << "Phase buffer seq 2 (tq):    " << info->bittiming.phase_seg2   << std::endl;
	std::cout << "Synchornisation jump width: " << info->bittiming.sjw          << std::endl;
	std::cout << "Bitrate prescaler:          " << info->bittiming.brp          << std::endl;
	std::cout << std::endl;
	
	// CAN timming maximum/minimum
	std::cout << GREEN << "Bittiming (const): ------------------------------------------" << NO_COLOR << std::endl;
	std::cout << "Controller name:                  " << info->bittiming_const.name      << std::endl;
	std::cout << "Time seqment 1 (min,max):         " << info->bittiming_const.tseg1_min
	                                           << "," << info->bittiming_const.tseg1_max << std::endl;
	std::cout << "Time seqment 2 (min,max):         " << info->bittiming_const.tseg2_min
	                                           << "," << info->bittiming_const.tseg2_max << std::endl;
	std::cout << "Synchornisation jump width (max): " << info->bittiming_const.sjw_max   << std::endl;
	std::cout << "Bitrate prescaler (min,max,inc):  " << info->bittiming_const.brp_min
	                                           << "," << info->bittiming_const.brp_max
	                                           << "," << info->bittiming_const.brp_inc   << std::endl;
	std::cout << std::endl;
	   
	// Bus error counter
	std::cout << GREEN << "Bus error counter: ------------------------------------------" << NO_COLOR << std::endl;
	std::cout << "TX bus error: " << std::setw(7) << info->berr_counter.tx_error << std::endl; 
	std::cout << "RX bus error: " << std::setw(7) << info->berr_counter.rx_error << std::endl;
	std::cout << std::endl;
}
