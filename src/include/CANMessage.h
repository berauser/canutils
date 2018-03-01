/*
 * CANMessage.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_CANMESSAGE_H_
#define SRC_INCLUDE_CANMESSAGE_H_

#include <cstdint>

namespace CanSocket
{

#define CAN_MAX_DATA_LENGTH 8

/* ****************************************************************************
 *
 * CANFlag: definition and operator functions
 *
 * ***************************************************************************/
enum struct CANFlag : uint32_t
{
	Extended = 0x80000000U, //!< Extended
	Remote = 0x40000000U, //!< Remote
	Error = 0x20000000U //!< Error
};

inline constexpr CANFlag
operator~(CANFlag x)
{
	return static_cast<CANFlag>(~static_cast<uint32_t>(x));
}

inline constexpr CANFlag
operator&(CANFlag f1, CANFlag f2)
{
	return static_cast<CANFlag>(static_cast<uint32_t>(f1)&static_cast<uint32_t>(f2));
}

inline constexpr uint32_t
operator&(uint32_t f1, CANFlag f2)
{
	return (f1&static_cast<uint32_t>(f2));
}

inline constexpr CANFlag
operator|(CANFlag f1, CANFlag f2)
{
	return static_cast<CANFlag>(static_cast<uint32_t>(f1)|static_cast<uint32_t>(f2));
}

inline constexpr uint32_t
operator|(uint32_t f1, CANFlag f2)
{
	return (f1|static_cast<uint32_t>(f2));
}

inline constexpr bool
operator==(uint32_t f1, CANFlag f2)
{
	return (f1==static_cast<uint32_t>(f2));
}

inline constexpr bool
operator!=(uint32_t f1, CANFlag f2)
{
	return (f1!=static_cast<uint32_t>(f2));
}

/* ****************************************************************************
 *
 * CANMask: definition and operator functions
 *
 * ***************************************************************************/
enum struct CANMask : uint32_t
{
	Standard = 0x000007FFU,
	Extended = 0x1FFFFFFFU,
	Error = 0x1FFFFFFFU
};

inline constexpr CANMask
operator~(CANMask x)
{
	return static_cast<CANMask>(~static_cast<uint32_t>(x));
}

inline constexpr CANMask
operator&(CANMask f1, CANMask f2)
{
	return static_cast<CANMask>(static_cast<uint32_t>(f1)&static_cast<uint32_t>(f2));
}

inline constexpr uint32_t
operator&(uint32_t f1, CANMask f2)
{
	return (f1&static_cast<uint32_t>(f2));
}

inline constexpr CANMask
operator|(CANMask f1, CANMask f2)
{
	return static_cast<CANMask>(static_cast<uint32_t>(f1)|static_cast<uint32_t>(f2));
}

inline constexpr uint32_t
operator|(uint32_t f1, CANMask f2)
{
	return (f1|static_cast<uint32_t>(f2));
}

inline constexpr bool
operator==(uint32_t f1, CANMask f2)
{
	return (f1==static_cast<uint32_t>(f2));
}

inline constexpr bool
operator!=(uint32_t f1, CANMask f2)
{
	return (f1!=static_cast<uint32_t>(f2));
}

/* ****************************************************************************
 *
 * CANMessage: definition, functions and operator functions
 *
 * ***************************************************************************/
struct CANMessage final
{
	enum struct CANFrameType : uint32_t
	{
		Standard = 0x01, //!< Standard
		Extended = 0x02, //!< Extended
		Remote   = 0x04, //!< Remote
		Error    = 0x08  //!< Error

	};

	CANMessage(uint32_t id = 0, CANFrameType type = CANFrameType::Standard, uint8_t dlc = 0x00,
			uint8_t data0 = 0, uint8_t data1 = 0, uint8_t data2 = 0,
			uint8_t data3 = 0, uint8_t data4 = 0, uint8_t data5 = 0,
			uint8_t data6 = 0, uint8_t data7 = 0)
	{
		if     ( type == CANFrameType::Extended ) can_id = ( id & CANMask::Extended ) | CANFlag::Extended;
		else if( type == CANFrameType::Remote   ) can_id = ( id & CANMask::Extended ) | CANFlag::Remote;
		else if( type == CANFrameType::Error    ) can_id = ( id & CANMask::Error )    | CANFlag::Error;
		else /* SFF */ can_id = ( id & CANMask::Standard );

		can_dlc = dlc > 8 ? CAN_MAX_DATA_LENGTH : dlc;

		data[0] = data0;
		data[1] = data1;
		data[2] = data2;
		data[3] = data3;

		data[4] = data4;
		data[5] = data5;
		data[6] = data6;
		data[7] = data7;
	}

	uint32_t id() const
	{
		if     ( (can_id & CANFlag::Extended) == CANFlag::Extended ) return ( can_id & CANMask::Extended );
		else if( (can_id & CANFlag::Remote  ) == CANFlag::Remote   ) return ( can_id & CANMask::Extended );
		else if( (can_id & CANFlag::Error   ) == CANFlag::Error    ) return ( can_id & CANMask::Error );
		else return ( can_id & CANMask::Standard );
	}

	CANFrameType type() const
	{
		if     ( (can_id & CANFlag::Extended) == CANFlag::Extended ) return CANFrameType::Extended;
		else if( (can_id & CANFlag::Remote  ) == CANFlag::Remote   ) return CANFrameType::Remote;
		else if( (can_id & CANFlag::Error   ) == CANFlag::Error    ) return CANFrameType::Error;
		else return CANFrameType::Standard;
	}

	CANMessage& operator= ( const CANMessage& m1 )
	{
		can_id  = m1.can_id;
		can_dlc = m1.can_dlc;

		data[0] = m1.data[0];
		data[1] = m1.data[1];
		data[2] = m1.data[2];
		data[3] = m1.data[3];

		data[4] = m1.data[4];
		data[5] = m1.data[5];
		data[6] = m1.data[6];
		data[7] = m1.data[7];
		return *this;
	}

	CANMessage& operator&=(const CANFlag& flag)
	{
		can_id = can_id & static_cast<uint32_t>(flag);
		return *this;
	}

	CANMessage& operator|=(const CANFlag& flag)
	{
		can_id = can_id | static_cast<uint32_t>(flag);
		return *this;
	}

	CANMessage operator&(const CANFlag& flag) const
	{
		/* FIXME */
		CANMessage m = *this;
		m.can_id &= static_cast<uint32_t>(flag);
		return m;
	}

	CANMessage operator|(const CANFlag& flag) const
	{
		/* FIXME */
		CANMessage m = *this;
		m.can_id |= static_cast<uint32_t>(flag);
		return m;
	}

	CANMessage& operator&=(const CANMask& mask)
	{
		can_id = can_id & static_cast<uint32_t>(mask);
		return *this;
	}

	CANMessage& operator|=(const CANMask& mask)
	{
		can_id = can_id | static_cast<uint32_t>(mask);
		return *this;
	}

	CANMessage operator&(const CANMask& mask) const
	{
		/* FIXME */
		CANMessage m = *this;
		m.can_id &= static_cast<uint32_t>(mask);
		return m;
	}

	CANMessage operator|(const CANMask& mask) const
	{
		/* FIXME */
		CANMessage m = *this;
		m.can_id |= static_cast<uint32_t>(mask);
		return m;
	}

	/**
	 * Compares the priority of the CAN message
	 * 0x001 is the highest CAN message priority
	 * 0x7FF (SFF) is the lowest priority
	 * (0x002 < 0x001 should returns true) 
	 */
	bool operator<(const CANMessage& m1) const
	{
		/* FIXME check for error and RTR flag */
		return (this->can_id > m1.can_id);
	}

	/**
	 * Compares the priority of the CAN message
	 * 0x001 is the highest CAN message priority
	 * 0x7FF (SFF) is the lowest priority
	 * (0x001 > 0x002 should returns true) 
	 */
	bool operator>(const CANMessage& m1) const
	{
		/* FIXME check for error and RTR flag */
		return (this->can_id < m1.can_id);
	}

	bool operator==(const CANMessage& m1) const
	{
		return (can_id == m1.can_id && can_dlc == m1.can_dlc
				&& data[0] == m1.data[0] && data[1] == m1.data[1]
				&& data[2] == m1.data[2] && data[3] == m1.data[3]
				&& data[4] == m1.data[4] && data[5] == m1.data[5]
				&& data[6] == m1.data[6] && data[7] == m1.data[7]);
	}

	uint32_t can_id;
	uint8_t can_dlc;
	uint8_t padding   = 0;
	uint8_t reserved1 = 0;
	uint8_t reserved2 = 0;
	uint8_t data[CAN_MAX_DATA_LENGTH];
};

} /* namespace CanSocket */

#endif /* SRC_INCLUDE_CANMESSAGE_H_ */
