/*
 * CANDeviceInfo.h
 *
 *  Created on: 17.02.2018
 *      Author: rauser
 */

#ifndef SRC_CANDEVICEINFO_H_
#define SRC_CANDEVICEINFO_H_

#include <string>
#include <vector>
#include <cstdint>

namespace CanSocket
{

enum struct DeviceState {
	UNKNOWN        = 0,
	NOTPRESENT     = 1,
	DOWN           = 2,
	LOWERLAYERDOWN = 3,
	TESTING        = 4,
	DORMANT        = 5,
	UP             = 6,
	STATE_SIZE     = 7,
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
	ECHO,
	UNKNOWN,
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
	ERROR_ACTIVE  = 0,
	ERROR_WARNING = 1,
	ERROR_PASSIV  = 2,
	BUS_OFF       = 3,
	STOPPED       = 4,
	SLEEPING      = 5,
	UNKNOWN,
};

struct DeviceDetails final
{
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

struct CanDeviceDetails final
{ 
	CanState state;
	uint32_t clock_freq;
	uint32_t restart_ms;
	std::vector<ControlMode> mode;
};

struct BusErrorCounter final
{
	uint16_t tx_error; /* Bus error transmit */
	uint16_t rx_error; /* Bus error receive */
};

struct CanBittiming final
{
	uint32_t bitrate;      /* Bit-rate in bits/second */
	uint32_t sample_point; /* Sample point in one-tenth of a percent */
	uint32_t tq;           /* Time quanta (TQ) in nanoseconds */
	uint32_t prop_seg;     /* Propagation segment in TQs */
	uint32_t phase_seg1;   /* Phase buffer segment 1 in TQs */
	uint32_t phase_seg2;   /* Phase buffer segment 2 in TQs */
	uint32_t sjw;          /* Synchronisation jump width in TQs */
	uint32_t brp;          /* Bit-rate prescaler */
};
	
struct CanBittimingConst final
{
	std::string name;   /* Name of the CAN controller hardware */
	uint32_t tseg1_min; /* Time segement 1 = prop_seg + phase_seg1 */
	uint32_t tseg1_max;
	uint32_t tseg2_min; /* Time segement 2 = phase_seg2 */
	uint32_t tseg2_max;
	uint32_t sjw_max;   /* Synchronisation jump width */
	uint32_t brp_min;   /* Bit-rate prescaler */
	uint32_t brp_max;
	uint32_t brp_inc;
};
	  
struct CANDeviceInfo final 
{
	DeviceDetails     device_details;
	CanDeviceDetails  can_device_details;
	BusErrorCounter   berr_counter;
	CanBittiming      bittiming;
	CanBittimingConst bittiming_const;
};

} /* namespace CanSocket */

#endif /* SRC_CANDEVICEINFO_H_ */