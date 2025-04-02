/**
 * @file Reporting.c
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides the implementation for the logging/reporting
 * interface for Chainbinder.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @copyright (c) 2024-2025 - Israfil Argos
 * This document is under the GNU Affero General Public License v3.0. It
 * can be modified and distributed (commercially or otherwise) freely, and
 * can be used privately and within patents. No liability or warranty is
 * guaranteed. However, on use, the user must state license and copyright,
 * any changes made, and disclose the source of the document. For more
 * information see the @file LICENSE.md file included with this
 * distribution of the source code, or https://www.gnu.org/licenses/agpl.
 */

#include <Reporting.h>
#include <stdarg.h>
#include <stdio.h>

#if !STORMSINGER_STRIP_LOG_METADATA

/**
 * @brief ANSI color escape codes for each of the log types.
 *
 * @since 0.1.1
 * @updated 0.1.1
 */
static chainbinder_u8_t color_codes[] = {90, 0, 32, 93, 33, 31};

/**
 * @brief Decoration strings for each of the log types. All are four
 * characters long.
 *
 * @since 0.1.1
 * @updated 0.1.1
 */
static const char *const string_descriptors[] = {"VERB", "INFO", " OK ",
                                                 "NOTE", "WARN", "FAIL"};

/**
 * @brief Log the decoration bit of the log message. This is a string in
 * the format of [decoration string] [filename] [line number].
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @param output The output stream to log to.
 * @param filename The file the log originated from.
 * @param line The line the log orignated from.
 * @param type The type of log we're sending. This decides the decoration
 * prefix.
 */
CHAINBINDER_FLATTEN CHAINBINDER_ALWAYSINLINE
CHAINBINDER_NONNULL(1, 2) inline static void
LogPrefix(FILE *const output, const char *const filename,
          chainbinder_u16_t line, chainbinder_log_type_t type)
{
    fprintf(output,
            "[\033[%" PRIuFAST8 "m%s\033[0m] %-12s @ ln. %.04" PRIuFAST16
            ": ",
            color_codes[type], string_descriptors[type], filename, line);
}

#endif // !STORMSINGER_STRIP_LOG_METADATA

void(Chainbinder_Log)(const char *const filename, chainbinder_u16_t line,
                      chainbinder_log_type_t type,
                      const char *const format, ...)
{
    // Be a good little process and send error output to, well, the error
    // stream.
    FILE *output = stdout;
    if (type == CHAINBINDER_WARNING || type == CHAINBINDER_ERROR)
        output = stderr;

#if !STORMSINGER_STRIP_LOG_METADATA
    LogPrefix(output, filename, line, type);
#else
    (void)filename;
    (void)line;
    (void)type;
#endif // !STORMSINGER_STRIP_LOG_METADATA

    va_list args;
    va_start(args, format);
    vfprintf(output, format, args);
    va_end(args);
    fputc('\n', output);
}
