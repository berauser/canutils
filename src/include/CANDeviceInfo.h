/*
 * CANDeviceInfo.h
 *
 *  Created on: 17.02.2018
 *      Author: rauser
 */

#ifndef SRC_CANDEVICEINFO_H_
#define SRC_CANDEVICEINFO_H_

#include <string>
#include <memory>
#include <vector>
#include <cstdint>

namespace CanSocket
{

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

enum struct ControlMode {
	LOOPBACK,
	LISTEN_ONLY,
	TRIPLE_SAMPLING,
	ONE_SHOT,
	BERR_REPORTING,
	FD,
	PRESUME_ACK,
	FD_NON_ISO,
	UNKNOWN,
};

enum struct CanState {
	ERROR_ACTIVE,
	ERROR_WARNING,
	ERROR_PASSIV,
	BUS_OFF,
	STOPPED,
	SLEEPING,
	UNKNOWN,
};

struct DeviceDetails final
{
	int ifindex         = 0;
	std::string ifname  = "";
	std::string iftype  = "";
	std::string ifalias = "";
	std::vector<DeviceFlags> flags;
	int mtu             = 0;
	int tx_qlen         = 0;
	std::string qdisc   = "";;
	DeviceState state   = DeviceState::UNKNOWN;
};  

struct CanDeviceDetails final
{ 
	CanState state      = CanState::UNKNOWN;
	uint32_t clock_freq = 0;
	uint32_t restart_ms = 0;;
	std::vector<ControlMode> mode;
};

struct BusErrorCounter final
{
	uint16_t tx_error = 0; /* Bus error transmit */
	uint16_t rx_error = 0; /* Bus error receive */
};
typedef std::shared_ptr<BusErrorCounter> BusErrorCounterPtr;

struct CanBittiming final
{
	uint32_t bitrate      = 0; /* Bit-rate in bits/second */
	uint32_t sample_point = 0; /* Sample point in one-tenth of a percent */
	uint32_t tq           = 0; /* Time quanta (TQ) in nanoseconds */
	uint32_t prop_seg     = 0; /* Propagation segment in TQs */
	uint32_t phase_seg1   = 0; /* Phase buffer segment 1 in TQs */
	uint32_t phase_seg2   = 0; /* Phase buffer segment 2 in TQs */
	uint32_t sjw          = 0; /* Synchronisation jump width in TQs */
	uint32_t brp          = 0; /* Bit-rate prescaler */
};
typedef std::shared_ptr<CanBittiming> CanBittimingPtr;

struct CanBittimingConst final
{
	std::string name   = ""; /* Name of the CAN controller hardware */
	uint32_t tseg1_min = 0;  /* Time segement 1 = prop_seg + phase_seg1 */
	uint32_t tseg1_max = 0;
	uint32_t tseg2_min = 0;  /* Time segement 2 = phase_seg2 */
	uint32_t tseg2_max = 0;
	uint32_t sjw_max   = 0;  /* Synchronisation jump width */
	uint32_t brp_min   = 0;  /* Bit-rate prescaler */
	uint32_t brp_max   = 0;
	uint32_t brp_inc   = 0;
};
typedef std::shared_ptr<CanBittimingConst> CanBittimingConstPtr;

struct CANDeviceInfo final 
{
	DeviceDetails     device_details;
	CanDeviceDetails  can_device_details;
	BusErrorCounter   berr_counter;
	CanBittiming      bittiming;
	CanBittimingConst bittiming_const;
};
typedef std::shared_ptr<CANDeviceInfo> CANDeviceInfoPtr;

} /* namespace CanSocket */

#endif /* SRC_CANDEVICEINFO_H_ */