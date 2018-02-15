#ifndef CANSOCKET_NETLINKPARSER_H
#define CANSOCKET_NETLINKPARSER_H

#include "Netlink.h"

#include <cstdint>
#include <string>
#include <vector>

namespace CanSocket {

class NetlinkParser
{
public:
	enum struct DeviceState {
		UNKNOWN        = 0,
		NOTPRESENT     = 1,
		DOWN           = 2,
		LOWERLAYERDOWN = 3,
		TESTING        = 4,
		DORMANT        = 5,
		UP             = 6,
		STATE_SIZE
	};
	
	enum struct DeviceFlags {
		NOCARRIER,
		LOOPBACK,
		BROADCAST,
		POINTOPOINT,
		MULTICAST,
		NOARP,
		ALLMULTI,
		PROMISC,
		MASTER,
		SLAVE,
		DEBUG,
		DYNAMIC,
		AUTOMEDIA,
		PORTSEL,
		NOTRAILERS,
		UP,
		LOWERUP,
		DORMANT,
		ECHO
	};
	
	struct DeviceStatistics {
		// Receive
		uint64_t rx_bytes;
		uint64_t rx_packets;
		uint64_t rx_errors;
		uint64_t rx_dropped;
		uint64_t rx_overrun_errors;
		uint64_t rx_multicast;
		uint64_t rx_compressed;
		uint64_t rx_length_errors;
		uint64_t rx_crc_errors;
		uint64_t rx_frame_errors;
		uint64_t rx_fifo_errors;
		uint64_t rx_missed_errors;
		// Transmit
		uint64_t tx_bytes;
		uint64_t tx_packets;
		uint64_t tx_errors;
		uint64_t tx_dropped;
		uint64_t tx_carrier_errors;
		uint64_t tx_collisions;
		uint64_t tx_compressed;
		uint64_t tx_aborted_errors;
		uint64_t tx_fifo_errors;
		uint64_t tx_window_errors;
		uint64_t tx_heartbeat_errors;
	};
	
	struct DeviceDetails {
		// General
		int ifindex;
		std::string ifname;
		std::string iftype;
		std::string ifalias;
		std::vector<DeviceFlags> flags;
		int mtu;
		int tx_qlen;
		std::string qdisc;
		DeviceState state;
	};  
  
public:
	NetlinkParser();
	~NetlinkParser();
	
	static DeviceStatistics* parseStatistics( Netlink::Data* data );
	static DeviceDetails*    parseDetails   ( Netlink::Data* data );
	
	static std::string deviceStateToString( const DeviceState& state );
	static std::string deviceFlagsToString( const DeviceFlags& flags );
	
protected:
	static DeviceState operationState( uint8_t state );
	
	static int parseStatistics32( Netlink::Data* data, DeviceStatistics* );
	static int parseStatistics64( Netlink::Data* data, DeviceStatistics* );
};

} /* namespace CanSocket */

#endif // CANSOCKET_NETLINKPARSER_H
