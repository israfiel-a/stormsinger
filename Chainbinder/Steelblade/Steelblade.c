#include "Steelblade.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static steelblade_arena_t arena = {0};
steelblade_allocation_mode_t allocationMode = STEELBLADE_EXPLICIT;

static char *GetArenaBlock(size_t size, steelblade_error_t *error)
{
    size_t trueSize = size + 1;
    if (trueSize > arena.end && allocationMode == STEELBLADE_EXPLICIT)
    {
        *error = STEELBLADE_BUFFER_OVERFLOW;
        return 0;
    }
    else if (trueSize > arena.end)
    {
        Steelblade_StretchArena(trueSize - arena.end, error);
        if (*error != STEELBLADE_OKAY) return 0;
    }
    char *block = arena.offset;
    arena.offset += trueSize;
    arena.end -= trueSize;

    *error = STEELBLADE_OKAY;
    return block;
}

static char *CopyIntoArena(const char *const string, size_t length,
                           steelblade_error_t *error)
{
    char *stringBlock = GetArenaBlock(length, error);
    if (stringBlock == 0) return 0;
    char *stringBlockPointer = stringBlock;

    char *tempString = (char *)string;
    char currentChar = 0;
    while ((currentChar = *tempString++) != 0)
    {
        *stringBlockPointer = currentChar;
        stringBlockPointer++;
    }
    *stringBlockPointer = 0;
    return stringBlock;
}

steelblade_error_t SteelbladeBegin(size_t size)
{
    steelblade_error_t error;
    Steelblade_FreeArena(&error);
    (void)error;

    arena.size = size;
    arena.end = size;
    arena.buffer = malloc(arena.size);
    if (arena.buffer == 0) return STEELBLADE_FAILED_ALLOCATION;
    arena.offset = arena.buffer;
    return STEELBLADE_OKAY;
}

void SteelbladeCleanup(void)
{
    steelblade_error_t error;
    Steelblade_FreeArena(&error);
    (void)error;
}

void SteelbladeSetAllocationMode(steelblade_allocation_mode_t mode)
{
    allocationMode = mode;
}

steelblade_string_t SteelbladeCreate(const char *const string,
                                     steelblade_error_t *error)
{
    size_t length = strlen(string);
    return (steelblade_string_t){
        .value = CopyIntoArena(string, length, error), .length = length};
}

void Steelblade_StretchArena(size_t amount, steelblade_error_t *error)
{
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_NO_ARENA;
        return;
    }

    arena.buffer = realloc(arena.buffer, arena.size += amount);
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_FAILED_ALLOCATION;
        return;
    }
    arena.end += amount;
    arena.offset = arena.buffer + arena.size - arena.end;
    *error = STEELBLADE_OKAY;
}

void Steelblade_ShrinkArena(size_t amount, steelblade_error_t *error)
{
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_NO_ARENA;
        return;
    }

    if (amount > arena.end)
    {
        *error = STEELBLADE_DATA_INTERSECTION;
        return;
    }
    arena.end -= amount;
    arena.buffer = realloc(arena.buffer, arena.size -= amount);
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_FAILED_ALLOCATION;
        return;
    }
    arena.offset = arena.buffer + arena.size - arena.end;
    *error = STEELBLADE_OKAY;
}

void Steelblade_TrimArena(steelblade_error_t *error)
{
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_NO_ARENA;
        return;
    }

    const size_t trimmedSize = arena.size -= arena.end;
    arena.buffer = realloc(arena.buffer, trimmedSize);
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_FAILED_ALLOCATION;
        return;
    }
    arena.end = 0;
    *error = STEELBLADE_OKAY;
}

void Steelblade_ResetArena(steelblade_error_t *error)
{
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_NO_ARENA;
        return;
    }

    arena.offset = arena.buffer;
    arena.end = arena.size;
    *error = STEELBLADE_OKAY;
}

void Steelblade_FreeArena(steelblade_error_t *error)
{
    if (arena.buffer == 0)
    {
        *error = STEELBLADE_NO_ARENA;
        return;
    }

    free(arena.buffer);
    arena = (steelblade_arena_t){0};
    *error = STEELBLADE_OKAY;
}
