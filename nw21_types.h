#ifndef __NW21_TYPES
#define __NW21_TYPES

#if defined WIN32
    typedef unsigned char uint8_t;
    typedef char int8_t;
    typedef short int16_t;
    typedef unsigned short uint16_t;
    typedef short int16_t;
    typedef unsigned long uint32_t;
    typedef long int32_t;
#else
    #include <stdint.h>
#endif

#endif

