#include "Steelblade.h"
#include <stdlib.h>
#include <string.h>

char *stringArena = 0;
char *stringArenaOffset = 0;
size_t stringArenaSize = 0;
size_t stringArenaLeft = 0;

static char *GetArenaBlock(size_t size, steelblade_error_t *error)
{
    if (size > stringArenaLeft)
    {
        *error = STEELBLADE_BUFFER_OVERFLOW;
        return 0;
    }
    char *block = stringArenaOffset;
    stringArenaOffset += size;

    *error = STEELBLADE_OKAY;
    return block;
}

static char *CopyIntoArena(const char *const string, size_t length,
                           steelblade_error_t *error)
{
    char *stringBlock = GetArenaBlock(length + 1, error);
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

static void FreeArena(void)
{
    if (stringArena == 0) return;

    free(stringArena);
    stringArena = 0;
    stringArenaOffset = 0;
    stringArenaSize = 0;
    stringArenaLeft = 0;
}

steelblade_error_t SteelbladeBegin(size_t size)
{
    FreeArena();
    stringArenaSize = size;
    stringArenaLeft = size;
    stringArena = calloc(stringArenaSize, 1);
    stringArenaOffset = stringArena;
    if (stringArena == 0) return STEELBLADE_FAILED_ALLOCATION;
    return STEELBLADE_OKAY;
}

void SteelbladeCleanup(void) { FreeArena(); }

steelblade_string_t SteelbladeCreate(const char *const string,
                                     steelblade_error_t *error)
{
    size_t length = strlen(string);
    return (steelblade_string_t){
        .value = CopyIntoArena(string, length, error), .length = length};
}

// void SteelbladeDestroy(steelblade_string_t *string)
// {
//     free(string->_);
//     string->_ = 0;
//     string->length = 0;
// }

// steelblade_string_t
// SteelbladeDuplicate(const steelblade_string_t *const string)
// {
//     return (steelblade_string_t){._ = strdup(string->_),
//                                  .length = string->length};
// }
