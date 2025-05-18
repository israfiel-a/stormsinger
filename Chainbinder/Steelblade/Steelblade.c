#include "Steelblade.h"
#include <stdlib.h>
#include <string.h>

steelblade_string_t SteelbladeCreate(const char *const string)
{
    return (steelblade_string_t){._ = strdup(string),
                                 .length = strlen(string)};
}

void SteelbladeDestroy(steelblade_string_t *string)
{
    free(string->_);
    string->_ = 0;
    string->length = 0;
}

steelblade_string_t
SteelbladeDuplicate(const steelblade_string_t *const string)
{
    return (steelblade_string_t){._ = strdup(string->_),
                                 .length = string->length};
}
