/**
 * @file Reporting.h
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides the logging/reporting interface for the
 * engine. This interface is basically empty in release mode, but in debug
 * provides ample information for debugging purposes.
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
#ifndef CHAINBINDER_REPORTING_H
#define CHAINBINDER_REPORTING_H

#include <Chainbinder.h>

/**
 * @brief An enumerator specifying what kind of log you're trying to send.
 * This mostly affects log styling, but in the case of warnings and errors,
 * STDERR is used instead of STDOUT.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
CHAINBINDER_ENUM(chainbinder_log_type_t, CHAINBINDER_VERBOSE,
                 CHAINBINDER_LOG, CHAINBINDER_SUCCESS, CHAINBINDER_NOTICE,
                 CHAINBINDER_WARNING, CHAINBINDER_ERROR);

/**
 * @brief The internal log function. This is not called directly, instead
 * the macro wrapper is used, for metadata reasons.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @see Chainbinder_Log(type, format, ...) The macro wrapper for this
 * function that allows for easy invocation and metadata gathering.
 *
 * @param filename The name of the file the log came from.
 * @param line The line the log came from.
 * @param type The type of log this is.
 * @param format The format string for the log.
 * @param ... An arguments to be inserted into the format string,
 * printf-style.
 */
CHAINBINDER_NONNULL(4)
CHAINBINDER_PRINTF(4, 5)
CHAINBINDER_HOT
CHAINBINDER_NULL_TERMINATED(1, 4)
void(Chainbinder_Log)(const char *const filename, chainbinder_u16_t line,
                      chainbinder_log_type_t type,
                      const char *const format, ...);

#if STORMSINGER_DISABLE_LOGS
    #define Chainbinder_Log(...)
#elif STORMSINGER_STRIP_LOG_METADATA
    // We have to define a case for this to prevent the storage of unneeded
    // strings and value (filenames, line numbers).

    /**
     * @brief A macro wrapper for the internal logging function that allows
     * for ease-of-invocation and extra metadata grabbing.
     *
     * @since 0.1.1
     * @updated 0.1.1
     *
     * @param type The type of log this is.
     * @param format The format string for the log.
     * @param ... An arguments to be inserted into the format string,
     * printf-style.
     */
    #define Chainbinder_Log(type, format, ...)                            \
        Chainbinder_Log(NULL, 0, type, format __VA_OPT__(, ) __VA_ARGS__)
#else
    /**
     * @brief A macro wrapper for the internal logging function that allows
     * for ease-of-invocation and extra metadata grabbing.
     *
     * @since 0.1.1
     * @updated 0.1.1
     *
     * @param type The type of log this is.
     * @param format The format string for the log.
     * @param ... An arguments to be inserted into the format string,
     * printf-style.
     */
    #define Chainbinder_Log(type, format, ...)                            \
        Chainbinder_Log(FILENAME, __LINE__, type,                         \
                        format __VA_OPT__(, ) __VA_ARGS__)
#endif // STORMSINGER_DISABLE_LOGS

#endif // CHAINBINDER_REPORTING_H
