
#ifndef SRC_INCLUDE_BASE_H_
#define SRC_INCLUDE_BASE_H_

template < typename T >
class Base
{
public:
	virtual int  write( const  T& msg ) = 0;
	virtual int  read ( T& msg ) = 0;
};

#endif /* SRC_INCLUDE_BASE_H_ */
