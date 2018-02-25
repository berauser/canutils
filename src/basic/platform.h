
#ifndef SRC_PLATFORM_H
#define SRC_PLATFORM_H


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

#endif /* SRC_PLATFORM_H */
