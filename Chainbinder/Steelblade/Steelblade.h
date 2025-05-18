#ifndef STEELBLADE_H
#define STEELBLADE_H

#define __need_size_t
#include <stddef.h>

typedef struct
{
    char *_;
    size_t length;
} steelblade_string_t;

void SteelbladeSetArenaSize(size_t size);

steelblade_string_t SteelbladeCreate(const char *const string);

void SteelbladeDestroy(steelblade_string_t *string);

steelblade_string_t
SteelbladeDuplicate(const steelblade_string_t *const string);

#endif // STEELBLADE_H
