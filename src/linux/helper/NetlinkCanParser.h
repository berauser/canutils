#ifndef CANSOCKET_NETLINKCANPARSER_H
#define CANSOCKET_NETLINKCANPARSER_H

#include "Netlink.h"
#include "NetlinkParser.h"

namespace CanSocket 
{

class NetlinkCanParser : public NetlinkParser
{
public:
	enum struct ControlMode {
		LOOPBACK,
		LISTEN_ONLY,
		TRIPEL_SAMPLING,
		ONE_SHOT,
		BERR_REPORTING,
		FD,
		PRESUME_ACK,
		FD_NON_ISO,
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
	
	struct BusErrorCounter
	{
		uint16_t tx_error;
		uint16_t rx_error;
	};
	
	struct CanBittiming
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
	
	struct CanBittimingConst
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
	  
	struct CanDeviceDetails
	{ 
		CanState state;
		uint32_t clock_freq;
		uint32_t restart_ms;
		std::vector<ControlMode> mode;
		BusErrorCounter berr;
		CanBittiming bittiming;
		CanBittimingConst const_bittiming;
	};
  
public:
	NetlinkCanParser();
	~NetlinkCanParser();
	
	static CanDeviceDetails*    parseCanDetails   (Netlink::Data* data);
	
	static std::string canStateToString   (CanState state  );
	static std::string controlModeToString(ControlMode mode);
	
protected:
	static CanState canState(unsigned int data);
	
	static int parseCanClock         (Netlink::Data* data, CanDeviceDetails* details);
	static int parseControlMode      (Netlink::Data* data, CanDeviceDetails* details);
	static int parseBerrCounter      (Netlink::Data* data, CanDeviceDetails* details);
	static int parseCanBittiming     (Netlink::Data* data, CanDeviceDetails* details);
	static int parseCanBittimingConst(Netlink::Data* data, CanDeviceDetails* details);
};

} /* namespace CanSocket */

#endif // CANSOCKET_NETLINKCANPARSER_H
