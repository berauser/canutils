
#ifndef SRC_INCLUDE_BASE_H_
#define SRC_INCLUDE_BASE_H_

/*!
 * The Base class is the base for all read and write operations.
 * @tparam T The type for the Base class
 */
template < typename T >
class Base
{
public:
	/*!
	 * Write the < T > to Base< T >
	 * @param msg The value to write to Base<T>
	 * @return The written bytes or -1 on error
	 */
	virtual int  write( const  T& msg ) = 0;
	/*!
	 * Read < T > from Base< T >
	 * @param msg A reference to < T > to store the readed value in
	 * @return The readed bytes or -1 on error
	 */
	virtual int  read ( T& msg ) = 0;
};

#endif /* SRC_INCLUDE_BASE_H_ */
