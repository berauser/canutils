
#ifndef _SRC_CANSTATISTICS_H
#define _SRC_CANSTATISTICS_H

#include <memory>
#include <cstdint>

namespace CanSocket
{

struct CANStatistics final 
{
	// Receive
	std::uint64_t rx_bytes          = 0;
	std::uint64_t rx_packets        = 0;
	std::uint64_t rx_errors         = 0;
	std::uint64_t rx_dropped        = 0;
	std::uint64_t rx_overrun_errors = 0;
	std::uint64_t rx_multicast      = 0;
	std::uint64_t rx_compressed     = 0;
	std::uint64_t rx_length_errors  = 0;
	std::uint64_t rx_crc_errors     = 0;
	std::uint64_t rx_frame_errors   = 0;
	std::uint64_t rx_fifo_errors    = 0;
	std::uint64_t rx_missed_errors  = 0;
	// Transmit
	std::uint64_t tx_bytes          = 0;
	std::uint64_t tx_packets        = 0;
	std::uint64_t tx_errors         = 0;
	std::uint64_t tx_dropped        = 0;
	std::uint64_t tx_carrier_errors = 0;
	std::uint64_t tx_collisions     = 0;
	std::uint64_t tx_compressed     = 0;
	std::uint64_t tx_aborted_errors = 0;
	std::uint64_t tx_fifo_errors    = 0;
	std::uint64_t tx_window_errors  = 0;
	std::uint64_t tx_heartbeat_errors = 0;
};
typedef std::shared_ptr<CANStatistics> CANStatisticsPtr;

} /* namespace CanSocket */

#endif /* _SRC_CANSTATISTICS_H */