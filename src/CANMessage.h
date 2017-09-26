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

#define MAX_DATA_LENGTH 8

enum struct CANFlag : uint32_t
{
	Extended = 0x80000000U, //!< Extended
	Remote   = 0x40000000U, //!< Remote
	Error    = 0x20000000U //!< Error
};

inline uint32_t operator| ( const CANFlag& flag, const uint32_t data )
{
	return data & static_cast<uint32_t>(flag);
}

inline uint32_t operator| ( const uint32_t data, const CANFlag& flag )
{
	return static_cast<uint32_t>(flag) & data;
}

enum struct CANMask : uint32_t
{
	Standard = 0x000007FFU,
	Extended = 0x1FFFFFFFU,
	Error    = 0x1FFFFFFFU
};

inline uint32_t operator& ( const CANMask& mask, const uint32_t data )
{
	return data & static_cast<uint32_t>(mask);
}

inline uint32_t operator& ( const uint32_t data, const CANMask& mask )
{
	return static_cast<uint32_t>(mask) & data;
}

struct CANMessage final
{
	uint32_t can_id;
	uint8_t can_dlc;
	uint8_t padding;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t data[MAX_DATA_LENGTH];

	bool operator==( const CANMessage& m1 ) const
	{
		return ( can_id == m1.can_id && can_dlc == m1.can_dlc
				&& data[0] == m1.data[0] && data[1] == m1.data[1]
				&& data[2] == m1.data[2] && data[3] == m1.data[3]
				&& data[4] == m1.data[4] && data[5] == m1.data[5]
				&& data[6] == m1.data[6] && data[7] == m1.data[7]);
	}
};

} /* namespace CanSocket */

#endif /* SRC_CANMESSAGE_H_ */
