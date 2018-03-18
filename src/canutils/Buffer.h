

#ifndef SRC_INCLUDE_BUFFER_H_
#define SRC_INCLUDE_BUFFER_H_

#include "canutils/Base.h"

#include <string>

namespace Buffer
{

/*!
 * Buffer < T > is the Base class for all buffer implementations
 * @tparam T Template parameter
 */
template<typename T>
class Buffer : public Base<T>
{
public:
	/*!
	 * Destructor for Buffer
	 */
	virtual ~Buffer()  noexcept(false)
	{
	}
	
	/*!
	* Reads T from Buffer
	 * Read is blocking when the buffer is empty.
	 * @param msg A reference to store the readed value.
	 * @return 0 on success, -1 on error
	 */
	virtual int read(T& msg) override = 0;
	/*!
	 * Write T to the Buffer
	 * Write is blocking, when the buffer is full.
	 * @tparam msg A reference with the value to store in the Buffer
	 * @return 0 on success, -1 on error
	 */
	virtual int write(const T& msg) override = 0;
	
	/*!
	 * Returns the size of the buffer
	 * @return Size of the buffer
	 */
	virtual unsigned int size() const = 0;
	/*!
	 * Resizes the buffer
	 * @param size New size of the buffer
	 * @return 0 on success, -1 on error
	 */
	virtual int resize( unsigned int size ) = 0;
	
	/*!
	 * Check if an element is availabel for reading
	 * @return false if the buffer is empty, otherwise true
	 */
	virtual bool hasNext() const = 0;
	/*!
	 * Check if the buffer is full
	 * @return true if the buffer is full, otherwise false
	 */
	virtual bool isFull()  const = 0;
	/*!
	 * Check if the buffer is empty
	 * @return true if the buffer is empty, otherwise false
	 */
	virtual bool isEmpty() const = 0;
	
	/*!
	 * Clears the buffer content
	 */
	virtual void clear() = 0;
	
	/*!
	 * Get the implementation of the buffer
	 * @return The implementation of the buffer
	 */
	virtual std::string implementation() const = 0;
	
protected:
    Buffer() {};
};

} /* namespace Buffer */

#endif /* SRC_INCLUDE_BUFFER_H_ */
