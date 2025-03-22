#ifndef CHAINBINDER_LOGGING_H
#define CHAINBINDER_LOGGING_H

#include <Chainbinder.h>

CHAINBINDER_ENUM(chainbinder_log_type_t, CHAINBINDER_VERBOSE,
                 CHAINBINDER_LOG, CHAINBINDER_SUCCESS, CHAINBINDER_NOTICE,
                 CHAINBINDER_WARNING, CHAINBINDER_ERROR);

void(Chainbinder_Log)(const char *const filename, chainbinder_u16_t line,
                      chainbinder_log_type_t type,
                      const char *const format, ...);

#if STORMSINGER_DISABLE_LOGS
    #define Chainbinder_Log(...)
#elif STORMSINGER_STRIP_LOG_METADATA
    #define Chainbinder_Log(type, format, ...)                            \
        Chainbinder_Log(NULL, 0, type, format __VA_OPT__(, ) __VA_ARGS__)
#else
    #define Chainbinder_Log(type, format, ...)                            \
        Chainbinder_Log(FILENAME, __LINE__, type,                         \
                        format __VA_OPT__(, ) __VA_ARGS__)
#endif

#endif // CHAINBINDER_LOGGING_H
