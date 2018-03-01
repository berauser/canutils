
#ifndef SRC_BASIC_PLATFORM_H_
#define SRC_BASIC_PLATFORM_H_


/*************************************************************************//***
 *
 * Construtor/Destructor macro to execute a function on library loading
 * Dependencies: Depends on the compiler
 * 
 * ***************************************************************************/
#ifdef __GNUG__
    /* g++ */
    #define CONSTRUCTOR(p) __attribute__(( constructor ((p)) ))
    #define DESTRUCTOR(p)  __attribute__(( destructor  ((p)) ))
#else
    #define CONSTRUCTOR(p) (void)
    #define DESTRUCTOR(p)  (void)
#endif

#endif /* SRC_BASIC_PLATFORM_H_ */
