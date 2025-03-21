#include <Reporting.h>
#include <stdarg.h>
#include <stdio.h>

#if STRIP_LOG_METADATA == false

static const chainbinder_u8_t color_codes[] = {90, 0, 32, 93, 33, 31};
static const char *const string_descriptors[] = {"VERB", "INFO", " OK ",
                                                 "NOTE", "WARN", "FAIL"};

inline static void LogPrefix(const char *const filename,
                             chainbinder_u16_t line,
                             chainbinder_log_type_t type)
{
    fprintf(stdout,
            "[\033[%" PRIuFAST8 "m%s\033[0m] %-12s @ ln. %.04" PRIuFAST16
            ": ",
            color_codes[type], string_descriptors[type], filename, line);
}

#endif

void(Chainbinder_Log)(const char *const filename, chainbinder_u16_t line,
                      chainbinder_log_type_t type,
                      const char *const format, ...)
{
#if STRIP_LOG_METADATA == false
    LogPrefix(filename, line, type);
#else
    (void)filename;
    (void)line;
    (void)type;
#endif

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fputc('\n', stdout);
}
