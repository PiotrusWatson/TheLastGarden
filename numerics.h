#ifndef _numerics_h
#define _numerics_h

#include <stdint.h>

typedef unsigned int Ui;
typedef int Si;

typedef uint8_t Ui8;
typedef uint16_t Ui16;
typedef uint32_t Ui32;
typedef uint64_t Ui64;

constexpr Ui32 UI8_MAX  =  UINT8_MAX;
constexpr Ui32 UI16_MAX = UINT16_MAX;
constexpr Ui32 UI32_MAX = UINT32_MAX;

typedef int8_t  Si8;
typedef int16_t  Si16;
typedef int32_t  Si32;
typedef int64_t  Si64;

#endif /* _numerics_h */