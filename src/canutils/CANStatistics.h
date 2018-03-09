
#ifndef SRC_INCLUDE_CANSTATISTICS_H_
#define SRC_INCLUDE_CANSTATISTICS_H_

#include <memory>
#include <cstdint>

namespace CanUtils
{

struct CANStatistics final
{
	// Receive
	std::uint64_t rx_bytes          = 0;   //< total received bytes
	std::uint64_t rx_packets        = 0;   //< total received CAN packets
	std::uint64_t rx_errors         = 0;   //< total bad CAN Messages
	std::uint64_t rx_dropped        = 0;   //< dropped receive packets (e.g buffer full)
	std::uint64_t rx_overrun_errors = 0;   //< total receive buffer overflow
	std::uint64_t rx_multicast      = 0;   //< total received mutlicast packets
	std::uint64_t rx_compressed     = 0;   //<
	std::uint64_t rx_length_errors  = 0;   //<
	std::uint64_t rx_crc_errors     = 0;   //< received packets with CRC error
	std::uint64_t rx_frame_errors   = 0;   //< received frame alignment error
	std::uint64_t rx_fifo_errors    = 0;   //< receiver fifo overrun
	std::uint64_t rx_missed_errors  = 0;   //< receiver missed packets
	// Transmit
	std::uint64_t tx_bytes          = 0;   //< total transmitted bytes
	std::uint64_t tx_packets        = 0;   //< total transmitted pakctes
	std::uint64_t tx_errors         = 0;   //< total packets transmit errors
	std::uint64_t tx_dropped        = 0;   //< dropped transmit packets (e.g buffer full)
	std::uint64_t tx_carrier_errors = 0;   //<
	std::uint64_t tx_collisions     = 0;   //<
	std::uint64_t tx_compressed     = 0;   //<
	std::uint64_t tx_aborted_errors = 0;   //<
	std::uint64_t tx_fifo_errors    = 0;   //<
	std::uint64_t tx_window_errors  = 0;   //<
	std::uint64_t tx_heartbeat_errors = 0; //<
};
typedef std::shared_ptr<CANStatistics> CANStatisticsPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_CANSTATISTICS_H_ */
