#include <Logging.h>
#include <stdarg.h>
#include <stdio.h>

#include <assert.h>

static const chainbinder_u8_t color_codes[] = {90, 0, 32, 93, 33, 31};
static const char *const string_descriptors[] = {"VERB", "INFO", " OK ",
                                                 "NOTE", "WARN", "FAIL"};

inline static void LogPrefix(const char *const filename,
                             chainbinder_u16_t line,
                             chainbinder_log_type_t type)
{
    fprintf(stdout,
            "[\033[%hhum%s\033[0m] %-12s @ ln. %.04u: ", color_codes[type],
            string_descriptors[type], filename, line);
}

void _Chainbinder_Log_INTERNAL(const char *const filename,
                               chainbinder_u16_t line,
                               chainbinder_log_type_t type,
                               const char *const format, ...)
{
    LogPrefix(filename, line, type);
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fputc('\n', stdout);
}

void _Chainbinder_LogString_INTERNAL(const char *const filename,
                                     chainbinder_u16_t line,
                                     chainbinder_log_type_t type,
                                     const char *const message)
{
    LogPrefix(filename, line, type);
    fputs(message, stdout);
    fputc('\n', stdout);
}
