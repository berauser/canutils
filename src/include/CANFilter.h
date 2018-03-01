/*
 * CANFilter.h
 *
 *  Created on: 26.09.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_CANFILTER_H_
#define SRC_INCLUDE_CANFILTER_H_

namespace CanSocket
{

struct CANFilter
{
	enum struct CANFilterFlags
	{
		Invert = 0x20000000U
	};

	CANFilter(uint32_t id = 0, uint32_t mask = 0x1FFFFFFFU)
	{
		can_id = id;
		can_mask = mask;
	}

	void invert()
	{
		can_id = can_id | static_cast<uint32_t>(CANFilterFlags::Invert);
	}

	bool isInverted()
	{
		return ( ( can_id & static_cast<uint32_t>(CANFilterFlags::Invert) )
				== static_cast<uint32_t>(CANFilterFlags::Invert) );
	}

	CANFilter& operator=(const CANFilter& f1)
	{
		can_id = f1.can_id;
		can_mask = f1.can_mask;
		return *this;
	}

	bool operator==(const CANFilter& f1) const
	{
		return (this->can_id == f1.can_id && this->can_mask == f1.can_mask);
	}

	bool operator!=(const CANFilter& f1) const
	{
		return (this->can_id != f1.can_id || this->can_mask != f1.can_mask);
	}

	CANFilter& operator&=(const CANFilterFlags& flag)
	{
		can_id &= static_cast<uint32_t>(flag);
		return *this;
	}

	CANFilter& operator|=(const CANFilterFlags& flag)
	{
		can_id |= static_cast<uint32_t>(flag);
		return *this;
	}

	CANFilter operator&(const CANFilterFlags& flag) const
	{
		return CANFilter(can_id & static_cast<uint32_t>(flag), can_mask);
	}

	CANFilter operator|(const CANFilterFlags& flag) const
	{
		return CANFilter(can_id | static_cast<uint32_t>(flag), can_mask);
	}

	uint32_t can_id;
	uint32_t can_mask;
};

} /* namespace CanSocket */

#endif /* SRC_INCLUDE_CANFILTER_H_ */
