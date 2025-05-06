#include <Config/Parser.h>
#include <Reporting.h>
#include <stdio.h>
#include <string.h>

bool Chainbinder_ParseConfig(chainbinder_config_type_t type,
                             chainbinder_config_t *config)
{
    *config = (chainbinder_config_t){0};
    config->type = type;

    FILE *configFile = fopen(configPaths[type], "rb");
    if (configFile == nullptr)
    {
        Chainbinder_Log(CHAINBINDER_ERROR,
                        "Failed to find config file of type '%d'.", type);
        return false;
    }
    Chainbinder_Log(CHAINBINDER_VERBOSE,
                    "Opened config file of type '%d'.", type);

    chainbinder_config_section_t *currentSection = nullptr;

    char line[CHAINBINDER_CONFIG_MAX_LINE_LENGTH];
    while (fgets(line, CHAINBINDER_CONFIG_MAX_LINE_LENGTH, configFile))
    {
        if (line[0] == '[')
        {
            config->sections = realloc(
                config->sections, sizeof(chainbinder_config_section_t) *
                                      (config->sectionCount + 1));
            currentSection = &config->sections[config->sectionCount];

            if (strcmp(line, "[splashscreen]\n") == 0)
            {
                currentSection->splashscreen.type =
                    CHAINBINDER_SPLASHSCREEN_SECTION;
                currentSection->splashscreen.title =
                    strdup(fgets(line, CHAINBINDER_CONFIG_MAX_LINE_LENGTH,
                                 configFile) +
                           6);
                currentSection->splashscreen.image =
                    strdup(fgets(line, CHAINBINDER_CONFIG_MAX_LINE_LENGTH,
                                 configFile) +
                           6);
            }

            config->sectionCount++;
            continue;
        }

        if (currentSection == nullptr || line[0] == '#') continue;
    }

    fclose(configFile);

    return config;
}
