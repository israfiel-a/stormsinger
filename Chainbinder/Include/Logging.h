#ifndef CHAINBINDER_LOGGING_H
#define CHAINBINDER_LOGGING_H

#include <stdint.h>

typedef enum chainbinder_log_type
{
    CHAINBINDER_VERBOSE,
    CHAINBINDER_LOG,
    CHAINBINDER_SUCCESS,
    CHAINBINDER_NOTICE,
    CHAINBINDER_WARNING,
    CHAINBINDER_ERROR
} chainbinder_log_type_t;

void _Chainbinder_Log_INTERNAL(const char *filename, uint32_t line,
                               chainbinder_log_type_t type,
                               const char *format, ...);

void _Chainbinder_LogString_INTERNAL(const char *filename, uint32_t line,
                                     chainbinder_log_type_t type,
                                     const char *message);

#define _Chainbinder_Log(type, format, ...)                               \
    _Chainbinder_Log_INTERNAL(FILENAME, __LINE__, type, format,           \
                              __VA_ARGS__)

#define _Chainbinder_LogString(type, message)                             \
    _Chainbinder_LogString_INTERNAL(FILENAME, __LINE__, type, message)

#endif // CHAINBINDER_LOGGING_H
