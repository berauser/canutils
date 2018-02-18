#ifndef NETLINK_NETLINKPARSER_H
#define NETLINK_NETLINKPARSER_H

#include "Netlink.h"

#include <cstdint>
#include <string>
#include <vector>

namespace Netlink {

class NetlinkParser
{
public:
	enum struct DeviceState {
		UNKNOWN,
		NOTPRESENT,
		DOWN,
		LOWERLAYERDOWN,
		TESTING,
		DORMANT,
		UP,
		STATE_SIZE,
	};
	
	enum struct DeviceFlags {
		UP,
		BROADCAST,
		DEBUG,
		LOOPBACK,
		POINTOPOINT,
		NOTRAILERS,
		RUNNING,
		NOARP,
		PROMISC,
		ALLMULTI,
		MASTER,
		SLAVE,
		MULTICAST,
		PORTSEL,
		AUTOMEDIA,
		DYNAMIC,
		LOWERUP,
		DORMANT,
		ECHO,
		UNKNOWN
	};
	
	struct DeviceStatistics {
		// Receive
		std::uint64_t rx_bytes;
		std::uint64_t rx_packets;
		std::uint64_t rx_errors;
		std::uint64_t rx_dropped;
		std::uint64_t rx_overrun_errors;
		std::uint64_t rx_multicast;
		std::uint64_t rx_compressed;
		std::uint64_t rx_length_errors;
		std::uint64_t rx_crc_errors;
		std::uint64_t rx_frame_errors;
		std::uint64_t rx_fifo_errors;
		std::uint64_t rx_missed_errors;
		// Transmit
		std::uint64_t tx_bytes;
		std::uint64_t tx_packets;
		std::uint64_t tx_errors;
		std::uint64_t tx_dropped;
		std::uint64_t tx_carrier_errors;
		std::uint64_t tx_collisions;
		std::uint64_t tx_compressed;
		std::uint64_t tx_aborted_errors;
		std::uint64_t tx_fifo_errors;
		std::uint64_t tx_window_errors;
		std::uint64_t tx_heartbeat_errors;
	};
	
	struct DeviceDetails {
		// General
		int ifindex;
		std::string ifname;
		std::string iftype;
		std::string ifalias;
		std::vector<DeviceFlags> flags;
		// Settings
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
	static DeviceState operationState( unsigned int state );
	
	static int parseDeviceFlags ( Netlink::Data* data, DeviceDetails* details );
	
	static int parseStatistics32( Netlink::Data* data, DeviceStatistics* stats );
	static int parseStatistics64( Netlink::Data* data, DeviceStatistics* stats );
};

} /* namespace Netlink */

#endif // NETLINK_NETLINKPARSER_H
