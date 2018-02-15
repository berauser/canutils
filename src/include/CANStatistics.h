
#ifndef _SRC_CANSTATISTICS_H
#define _SRC_CANSTATISTICS_H

#include <cstdint>

namespace CanSocket
{

struct CANStatistics final {
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

} /* namespace CanSocket */

#endif /* _SRC_CANSTATISTICS_H */