
#ifndef SRC_BASE_H
#define SRC_BASE_H

template < typename T >
class Base
{
public:
	virtual bool isOpen() = 0;
	virtual int  write( const  T& msg ) = 0;
	virtual int  read ( T& msg ) = 0;
};

#endif /* SRC_BASE_H */
