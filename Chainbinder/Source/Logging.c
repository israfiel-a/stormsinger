#include <Logging.h>
#include <stdarg.h>
#include <stdio.h>

void _Chainbinder_Log_INTERNAL(const char *filename, uint32_t line,
                               chainbinder_log_type_t type,
                               const char *format, ...)
{
    fputc('[', stdout);
    switch (type)
    {
        case CHAINBINDER_VERBOSE: fputs("\033[90m VERB ", stdout); break;
        case CHAINBINDER_LOG:     fputs(" INFO ", stdout); break;
        case CHAINBINDER_SUCCESS: fputs("\033[32m  OK  ", stdout); break;
        case CHAINBINDER_NOTICE:  fputs("\033[93m NOTE ", stdout); break;
        case CHAINBINDER_WARNING: fputs("\033[33m WARN ", stdout); break;
        case CHAINBINDER_ERROR:   fputs("\033[31m ERR! ", stdout); break;
        default:                  break;
    }
    fprintf(stdout, "\033[0m] %s @ ln. %.04d: ", filename, line);

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fputc('\n', stdout);
}

void _Chainbinder_LogString_INTERNAL(const char *filename, uint32_t line,
                                     chainbinder_log_type_t type,
                                     const char *message)
{
    fputc('[', stdout);
    switch (type)
    {
        case CHAINBINDER_VERBOSE: fputs("\033[90m VERB ", stdout); break;
        case CHAINBINDER_LOG:     fputs(" INFO ", stdout); break;
        case CHAINBINDER_SUCCESS: fputs("\033[32m  OK  ", stdout); break;
        case CHAINBINDER_NOTICE:  fputs("\033[93m NOTE ", stdout); break;
        case CHAINBINDER_WARNING: fputs("\033[33m WARN ", stdout); break;
        case CHAINBINDER_ERROR:   fputs("\033[31m ERR! ", stdout); break;
        default:                  break;
    }
    fprintf(stdout, "\033[0m] %s @ ln. %.04d: %s\n", filename, line,
            message);
}
