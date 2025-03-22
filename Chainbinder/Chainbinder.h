/**
 * @file Chainbinder.h
 * @author Israfiel Argos (israfiel-a)
 * @brief The public interface file of the Chainbinder library. This
 * provides all functionality one needs to properly use Chainbinder.
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
#ifndef CHAINBINDER_ROOT_H
#define CHAINBINDER_ROOT_H

#include <inttypes.h>
#include <stdint.h>

// Define cross-platform attributes for functions, variables, and
// structures. I really, really wish that MS supported the full C23 spec,
// but alas.
#ifdef _MSC_VER
    // MSVC yet does not ship built-in boolean literals.
    #include <stdbool.h>

    /**
     * @brief A directive that results in whatever structure it's applied
     * to being packed into as little memory as possible.
     *
     * @since 0.1.0
     * @updated 0.1.1
     *
     * @note This has zero effect on this platform (Windows).
     */
    #define CHAINBINDER_PACKED

    /**
     * @brief A value corresponding a pointer "to nowhere" of sorts.
     * Defined because Microsoft is lazy and refused to support the C23
     * specification in its entirety.
     *
     * @since 0.1.0
     * @updated 0.1.1
     */
    #define CHAINBINDER_NULLPTR NULL
#else
    /**
     * @brief A directive that results in whatever structure it's applied
     * to being packed into as little memory as possible.
     *
     * @since 0.1.0
     * @updated 0.1.1
     */
    #define CHAINBINDER_PACKED __attribute__((__packed__))

    /**
     * @brief A value corresponding a pointer "to nowhere" of sorts.
     * Defined because Microsoft is lazy and refused to support the C23
     * specification in its entirety.
     *
     * @since 0.1.0
     * @updated 0.1.1
     */
    #define CHAINBINDER_NULLPTR nullptr
#endif

/**
 * @brief An enumerator blueprint to create (potentially) packed
 * enumerators. Nearly all enums throughout the engine have less than 255
 * values, so this comes in handy.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
#define CHAINBINDER_ENUM(name, ...)                                       \
    typedef enum CHAINBINDER_PACKED                                       \
    {                                                                     \
        __VA_ARGS__                                                       \
    } name

/**
 * @brief The unsigned 8-bit integer type the engine uses. This works out
 * to being the fastest unsigned integer type greater than or equal to 8
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef uint_fast8_t chainbinder_u8_t;

/**
 * @brief The unsigned 16-bit integer type the engine uses. This works out
 * to being the fastest unsigned integer type greater than or equal to 16
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef uint_fast16_t chainbinder_u16_t;

/**
 * @brief The unsigned 32-bit integer type the engine uses. This works out
 * to being the fastest unsigned integer type greater than or equal to 32
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef uint_fast32_t chainbinder_u32_t;

/**
 * @brief The unsigned 64-bit integer type the engine uses. This works out
 * to being the fastest unsigned integer type greater than or equal to 64
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef uint_fast64_t chainbinder_u64_t;

/**
 * @brief The signed 8-bit integer type the engine uses. This works out
 * to being the fastest signed integer type greater than or equal to 8
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef int_fast8_t chainbinder_i8_t;

/**
 * @brief The signed 16-bit integer type the engine uses. This works out
 * to being the fastest signed integer type greater than or equal to 16
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef int_fast16_t chainbinder_i16_t;

/**
 * @brief The signed 32-bit integer type the engine uses. This works out
 * to being the fastest signed integer type greater than or equal to 32
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef int_fast32_t chainbinder_i32_t;

/**
 * @brief The signed 64-bit integer type the engine uses. This works out
 * to being the fastest signed integer type greater than or equal to 64
 * bits long.
 *
 * @since 0.1.0
 * @updated 0.1.1
 */
typedef int_fast64_t chainbinder_i64_t;

/**
 * @brief An enumerator describing all the various error codes a function
 * can throw. If an engine function returns a false-evaluating value
 * (false, NULL, etc.), an error code will have been recorded.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @see Chainbinder_GetError(void) You can retrieve a recorded error code
 * via this function.
 */
CHAINBINDER_ENUM(chainbinder_error_t, CHAINBINDER_FAILED_NONE,
                 CHAINBINDER_FAILED_VULKAN, CHAINBINDER_FAILED_VMA);

/**
 * @brief Initialize the Chainbinder engine, and all of its subprocesses.
 * Because of the architecture of the engine, unless this function returns
 * an error, the game is fully loaded by the end of this function.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @see Chainbinder_CleanUp(void) To clean up the engine and reset all
 * engine processes, call this function.
 *
 * @param argc The count of arguments supplied to the process via command
 * line.
 * @param argv The array of arguments supplied to the process via command
 * line.
 *
 * @returns A boolean value expressing whether or not the initialization
 * succeeded.
 */
bool Chainbinder_Initialize(int argc, char **argv);

/**
 * @brief Chean up the Chainbinder engine and all of its data. Past the
 * return of this function, the engine is completely inert, and is
 * functionally unusable until the initialization function is called again.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @see Chainbinder_Initialize(int, char**) To (re)initialize the engine,
 * call this function.
 */
void Chainbinder_CleanUp(void);

/**
 * @brief Run the engine. Past this point, nothing but a fatal error or
 * exit event will end the main loop, so all affairs should be in order by
 * this call.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @see Chainbinder_Initialize(int, char**) To (re)initialize the engine,
 * call this function.
 * @see Chainbinder_CleanUp(void) To clean up the engine and reset all
 * engine processes, call this function.
 */
void Chainbinder_Run(void);

/**
 * @brief Get the most recently recorded error value. This is cleared after
 * every successful Chainbinder function call.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @returns The most recently recorded error code.
 */
chainbinder_error_t Chainbinder_GetError(void);

#endif // CHAINBINDER_ROOT_H
