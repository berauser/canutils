/*
 * CANMessage.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_CANMESSAGE_H_
#define SRC_CANMESSAGE_H_

#include <cstdint>

namespace CanSocket
{

#define CAN_MAX_DATA_LENGTH 8

struct CANMessage final
{
	enum struct CANFlag : uint32_t
	{
		Extended = 0x80000000U, //!< Extended
		Remote = 0x40000000U, //!< Remote
		Error = 0x20000000U //!< Error
	};

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

	enum struct CANMask : uint32_t
	{
		Standard = 0x000007FFU,
		Extended = 0x1FFFFFFFU,
		Error = 0x1FFFFFFFU

		/* TODO implement operator~ ( const CANMask& mask ) const */
	};

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

	CANMessage(uint32_t id = 0, bool extended = false, uint8_t dlc = 0x00,
			uint8_t data0 = 0, uint8_t data1 = 0, uint8_t data2 = 0,
			uint8_t data3 = 0, uint8_t data4 = 0, uint8_t data5 = 0,
			uint8_t data6 = 0, uint8_t data7 = 0)
	{
		if( extended ) can_id = ( id & static_cast<uint32_t>( CANMask::Extended ) ) | static_cast<uint32_t>( CANFlag::Extended );
		else /* SFF */ can_id = ( id & static_cast<uint32_t>( CANMask::Standard ) );

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
	uint8_t padding;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t data[CAN_MAX_DATA_LENGTH];
};

inline constexpr CANMessage::CANFlag
operator~(CANMessage::CANFlag x)
{
	return static_cast<CANMessage::CANFlag>(~static_cast<uint32_t>(x));
}

inline constexpr CANMessage::CANFlag
operator&(CANMessage::CANFlag f1, CANMessage::CANFlag f2)
{
	return static_cast<CANMessage::CANFlag>(static_cast<uint32_t>(f1)&static_cast<uint32_t>(f2));
}

inline constexpr CANMessage::CANFlag
operator|(CANMessage::CANFlag f1, CANMessage::CANFlag f2)
{
	return static_cast<CANMessage::CANFlag>(static_cast<uint32_t>(f1)|static_cast<uint32_t>(f2));
}

inline constexpr CANMessage::CANMask
operator~(CANMessage::CANMask x)
{
	return static_cast<CANMessage::CANMask>(~static_cast<uint32_t>(x));
}

inline constexpr CANMessage::CANMask
operator&(CANMessage::CANMask f1, CANMessage::CANMask f2)
{
	return static_cast<CANMessage::CANMask>(static_cast<uint32_t>(f1)&static_cast<uint32_t>(f2));
}

inline constexpr CANMessage::CANMask
operator|(CANMessage::CANMask f1, CANMessage::CANMask f2)
{
	return static_cast<CANMessage::CANMask>(static_cast<uint32_t>(f1)|static_cast<uint32_t>(f2));
}

} /* namespace CanSocket */

#endif /* SRC_CANMESSAGE_H_ */
