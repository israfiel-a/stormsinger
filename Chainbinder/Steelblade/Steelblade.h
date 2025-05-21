/**
 * @file Steelblade.h
 * @authors Israfil Argos (israfiel-a)
 * @brief The public interface for the Steelblade module of the Chainbinder
 * engine. This provides a string wrapper, and several helpful string
 * manipulation functions.
 * @since 0.1.2
 * @updated 0.1.2
 *
 * @copyright (c) 2024-2025 - the Stormsinger Project
 * This document is under the GNU Affero General Public License v3.0. It
 * can be modified and distributed (commercially or otherwise) freely, and
 * can be used privately and within patents. No liability or warranty is
 * guaranteed. However, on use, the user must state license and copyright,
 * any changes made, and disclose the source of the document. For more
 * information see the @file LICENSE.md file included with this
 * distribution of the source code, or https://www.gnu.org/licenses/agpl.
 */
#ifndef STEELBLADE_H
#define STEELBLADE_H

#define __need_size_t
#include <stddef.h>

/**
 * @brief A very simple string wrapper class. You may construct these
 * yourself, but to take advantage of Steelblade's faster allocation and
 * cleanup functionality please use the Steelblade string creation
 * functions.
 * @since 0.1.2
 *
 * @see Steelblade_Create
 * @see Steelblade_Destroy
 */
typedef struct
{
    /**
     * @brief The value of the string. If allocated properly this is a
     * slice of the allocated space within the Steelblade allocation arena.
     * @since 0.1.2
     */
    char *value;
    /**
     * @brief The length of the string value detailed in the `value` member
     * of this structure.
     * @since 0.1.2
     */
    size_t length;
} steelblade_string_t;

/**
 * @brief An incredibly simple string arena structure. This contains a
 * pointer to the string buffer and some other various positioning
 * information. This structure is provided for transparency, and is not
 * meant to be used by the user in any capacity.
 * @since 0.1.2
 */
typedef struct
{
    /**
     * @brief The buffer itself, that which holds the strings. This only
     * changes after the arena is allocated or freed, offset manipulations
     * happen to the `offset` member of this structure.
     * @since 0.1.2
     */
    char *buffer;
    /**
     * @brief The offset pointer into the buffer. This is manipulated with
     * each string that enters or leaves the arena.
     * @since 0.1.2
     */
    char *offset;
    /**
     * @brief The size of the arena as a whole, in bytes.
     * @since 0.1.2
     */
    size_t size;
    /**
     * @brief The number of bytes left free-floating at the end of the
     * arena.
     * @since 0.1.2
     */
    size_t end;
} steelblade_arena_t;

/**
 * @brief An enumerator describing the different routes Steelblade can take
 * towards allocating memory. This can be changed during runtime.
 * @since 0.1.2
 */
typedef enum
{
    /**
     * @brief Only expand or contract the pool when the user demands it.
     * If space is exceeded, a buffer overflow error will be thrown and
     * nothing will be done--no exceptions.
     * @since 0.1.2
     */
    STEELBLADE_EXPLICIT,
    /**
     * @brief Expand or contract the pool whenever the runtime sees fit, be
     * it contracting the arena to save memory after a long period of
     * inactivity, or defragmenting the arena after several removals have
     * been done.
     * @since 0.1.2
     */
    STEELBLADE_IMPLICIT
} steelblade_allocation_mode_t;

/**
 * @brief An enumerator describing the possible issues Steelblade could run
 * into during its lifetime. Steelblade is a very one-dimensional library,
 * these errors are simply returned and NOT corrected.
 * @since 0.1.2
 */
typedef enum
{
    /**
     * @brief No error has occurred.
     * @since 0.1.2
     */
    STEELBLADE_OKAY,
    /**
     * @brief An allocation failed somewhere, typically while trying to
     * expand or set up the string arena. This error being thrown typically
     * means something is very, very wrong.
     * @since 0.1.2
     */
    STEELBLADE_FAILED_ALLOCATION,
    /**
     * @brief Steelblade has overflowed its arena while trying to allocate
     * a new string object. This can be rectified by increasing the size of
     * the pool, but one should try to allocate enough arena for the
     * strings required from the beginning.
     * @since 0.1.2
     */
    STEELBLADE_BUFFER_OVERFLOW,
    STEELBLADE_DATA_INTERSECTION,
    STEELBLADE_NO_ARENA
} steelblade_error_t;

steelblade_error_t SteelbladeBegin(size_t size);
void SteelbladeCleanup(void);
void SteelbladeSetAllocationMode(steelblade_allocation_mode_t mode);

steelblade_string_t SteelbladeCreate(const char *const string,
                                     steelblade_error_t *error);

void Steelblade_StretchArena(size_t amount, steelblade_error_t *error);

void Steelblade_ShrinkArena(size_t amount, steelblade_error_t *error);

/**
 * @brief Trim off any unused space within the arena. In implicit mode,
 * this is called after a specific cooldown of inactivity, after which
 * strings must be allocated manually once more. In explicit mode, this is
 * only ever called by the user.
 * @since 0.1.2
 *
 * @param error Should the arena not exist, this will be
 * STEELBLADE_NO_ARENA. If an allocation failed, this will be
 * STEELBLADE_FAILED_ALLOCATION. Otherwise, this will be always be
 * STEELBLADE_OKAY.
 *
 * @see Steelblade_StretchArena
 * @see Steelblade_ShrinkArena
 */
void Steelblade_TrimArena(steelblade_error_t *error);

/**
 * @brief Reset the arena as a whole by resetting position and offset
 * counters. This does not immediately erase data within the area, nor does
 * it change the arena's size, it simply allows for strings to be written
 * without care for overwriting.
 * @since 0.1.2
 *
 * @param error The error thrown by the operation. Should there not be an
 * arena setup to reset, this will be STEELBLADE_NO_ARENA. Otherwise, this
 * will always be STEELBLADE_OKAY.
 *
 * @see Steelblade_FreeArena
 */
void Steelblade_ResetArena(steelblade_error_t *error);

/**
 * @brief Free the arena, and reset all positioning counters. This
 * immediately invalidates all previously allocated strings, and should
 * likely only ever be called at the end of the program.
 * @since 0.1.2
 *
 *
 * @param error The error thrown by the operation. Should there not be an
 * arena setup to reset, this will be STEELBLADE_NO_ARENA. Otherwise, this
 * will always be STEELBLADE_OKAY.
 *
 * @see Steelblade_ResetArena
 */
void Steelblade_FreeArena(steelblade_error_t *error);

#endif // STEELBLADE_H
