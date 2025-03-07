#ifndef CHAINBINDER_LOGGING_H
#define CHAINBINDER_LOGGING_H

#include <Definitions.h>
#include <stdint.h>

CHAINBINDER_ENUM(chainbinder_log_type_t, CHAINBINDER_VERBOSE,
                 CHAINBINDER_LOG, CHAINBINDER_SUCCESS, CHAINBINDER_NOTICE,
                 CHAINBINDER_WARNING, CHAINBINDER_ERROR);

void Chainbinder_Log_INTERNAL(const char *const filename,
                              chainbinder_u16_t line,
                              chainbinder_log_type_t type,
                              const char *const format, ...);

void Chainbinder_LogString_INTERNAL(const char *const filename,
                                    chainbinder_u16_t line,
                                    chainbinder_log_type_t type,
                                    const char *const message);

#define Chainbinder_Log(type, format, ...)                                \
    Chainbinder_Log_INTERNAL(FILENAME, __LINE__, type, format, __VA_ARGS__)

#define Chainbinder_LogString(type, message)                              \
    Chainbinder_LogString_INTERNAL(FILENAME, __LINE__, type, message)

#endif // CHAINBINDER_LOGGING_H
