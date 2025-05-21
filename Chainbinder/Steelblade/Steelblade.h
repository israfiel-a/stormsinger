#ifndef STEELBLADE_H
#define STEELBLADE_H

#define __need_size_t
#include <stddef.h>

typedef struct
{
    char *value;
    size_t length;
} steelblade_string_t;

typedef enum
{
    STEELBLADE_OKAY,
    STEELBLADE_FAILED_ALLOCATION,
    STEELBLADE_BUFFER_OVERFLOW
} steelblade_error_t;

typedef enum
{
    STEELBLADE_EXPLICIT,
    STEELBLADE_IMPLICIT
} steelblade_allocation_mode_t;

steelblade_error_t SteelbladeBegin(size_t size);
void SteelbladeCleanup(void);
void SteelbladeSetAllocationMode(steelblade_allocation_mode_t mode);

steelblade_string_t SteelbladeCreate(const char *const string,
                                     steelblade_error_t *error);

// void SteelbladeDestroy(steelblade_string_t *string);

// steelblade_string_t
// SteelbladeDuplicate(const steelblade_string_t *const string);

#endif // STEELBLADE_H
