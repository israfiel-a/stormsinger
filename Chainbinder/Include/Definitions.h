#ifndef CHAINBINDER_DEFINITIONS_H
#define CHAINBINDER_DEFINITIONS_H

#ifdef _MSC_VER
    // MSVC yet does not ship built-in boolean literals.
    #include <stdbool.h>

    #define CHAINBINDER_PACKED
    #define CHAINBINDER_NULLPTR NULL
#else
    #define CHAINBINDER_PACKED [[packed]]
    #define CHAINBINDER_NULLPTR nullptr
#endif

#define CHAINBINDER_ENUM(name, ...)                                       \
    typedef enum CHAINBINDER_PACKED                                       \
    {                                                                     \
        __VA_ARGS__                                                       \
    } name

#include <stdint.h>

typedef uint_fast8_t chainbinder_u8_t;
typedef uint_fast16_t chainbinder_u16_t;
typedef uint_fast32_t chainbinder_u32_t;
typedef uint_fast64_t chainbinder_u64_t;

typedef int_fast8_t chainbinder_i8_t;
typedef int_fast16_t chainbinder_i16_t;
typedef int_fast32_t chainbinder_i32_t;
typedef int_fast64_t chainbinder_i64_t;

#endif // CHAINBINDER_DEFINITIONS_H
