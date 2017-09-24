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

enum struct CANMask : uint32_t
{
	Standard = 0x000007FFU,
	Extended = 0x1FFFFFFFU,
	Error    = 0x1FFFFFFFU
};

struct CANMessage final
{
	uint32_t can_id;
	uint8_t can_dlc;
	uint8_t padding;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t data[MAX_DATA_LENGTH];
};

} /* namespace CanSocket */

#endif /* SRC_CANMESSAGE_H_ */
