#ifndef CHAINBINDER_CONFIG_PARSER_H
#define CHAINBINDER_CONFIG_PARSER_H

#define __need_size_t
#include <stddef.h>

#define CHAINBINDER_CONFIG_MAX_LINE_LENGTH 255
#define CHAINBINDER_CONFIG_MAX_KEY_LENGTH 32
#define CHAINBINDER_CONFIG_MAX_VALUE_LENGTH 128
#define CHAINBINDER_CONFIG_MAX_SECTION_PAIRS 16

typedef enum
{
    CHAINBINDER_ENGINE_CONFIG
} chainbinder_config_type_t;

typedef enum
{
    CHAINBINDER_SPLASHSCREEN_SECTION
} chainbinder_config_section_type_t;

typedef union
{
    struct
    {
        chainbinder_config_section_type_t type;
        const char *title;
        const char *image;
    } splashscreen;
} chainbinder_config_section_t;

typedef struct
{
    chainbinder_config_type_t type;
    size_t sectionCount;
    chainbinder_config_section_t *sections;
} chainbinder_config_t;

static const char *const configPaths[] = {
    [CHAINBINDER_ENGINE_CONFIG] = "Chainbinder.cfg",
};

bool Chainbinder_ParseConfig(chainbinder_config_type_t type,
                             chainbinder_config_t *config);

void Chainbinder_FreeConfig(chainbinder_config_t *config);

#endif // CHAINBINDER_CONFIG_PARSER_H
