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

    char sectionName[CHAINBINDER_CONFIG_MAX_KEY_LENGTH] = {0};
    struct pair_t
    {
        bool set;
        char key[CHAINBINDER_CONFIG_MAX_KEY_LENGTH];
        char value[CHAINBINDER_CONFIG_MAX_VALUE_LENGTH];
    } sectionPairs[CHAINBINDER_CONFIG_MAX_SECTION_PAIRS] = {0};
    struct pair_t *currentPair = &sectionPairs[0];

    char *keyNameChar = (char *)currentPair->key;
    char *valueNameChar = (char *)currentPair->value;

    bool suspendedUntilNewline = false;
    char currentChar = 0;
    while ((currentChar = fgetc(configFile)) != EOF)
    {
        if (currentChar == '\\' &&
            (currentChar = fgetc(configFile)) == 'n')
        {
            suspendedUntilNewline = false;

            currentPair++;
            keyNameChar = (char *)currentPair->key;
            valueNameChar = (char *)currentPair->value;
            continue;
        }
        else if (suspendedUntilNewline) continue;

        if (currentChar == '#')
        {
            suspendedUntilNewline = true;
            continue;
        }

        if (currentChar == '[')
        {
            config->sections = realloc(
                config->sections, sizeof(chainbinder_config_section_t) *
                                      (config->sectionCount++));

            if (sectionName[0] != 0)
            {
                if (strcmp(sectionName, "splashscreen") == 0)
                {
                    currentSection->splashscreen.type =
                        CHAINBINDER_SPLASHSCREEN_SECTION;

                    struct pair_t pair;
                    struct pair_t *pairs = (struct pair_t *)sectionPairs;
                    while ((pair = *pairs++).set)
                    {
                        if (strcmp(pair.key, "title") == 0)
                            currentSection->splashscreen.title =
                                pair.value;
                        else if (strcmp(pair.key, "image") == 0)
                            currentSection->splashscreen.image =
                                pair.value;
                        pair.set = false;
                    }
                    printf("%s\n", currentSection->splashscreen.title);
                }
                sectionName[0] = 0;

                currentSection =
                    &config->sections[config->sectionCount - 1];
            }

            char *sectionNameChar = (char *)sectionName;
            while ((currentChar = fgetc(configFile)) != EOF &&
                   currentChar != ']')
            {
                if (sectionNameChar - (char *)sectionName >=
                    CHAINBINDER_CONFIG_MAX_KEY_LENGTH - 1)
                {
                    *sectionNameChar = 0;
                    break;
                }
                *sectionNameChar = currentChar;
                sectionNameChar++;
            }
        }

        if (currentPair->key[0] == 0)
        {
            currentPair->set = true;
            while ((currentChar = fgetc(configFile)) != EOF &&
                   currentChar != '=')
            {
                if (keyNameChar - (char *)currentPair->key >=
                    CHAINBINDER_CONFIG_MAX_KEY_LENGTH - 1)
                {
                    *keyNameChar = 0;
                    break;
                }
                *keyNameChar = currentChar;
                keyNameChar++;
            }
        }

        if (valueNameChar - (char *)currentPair->value >=
            CHAINBINDER_CONFIG_MAX_KEY_LENGTH - 1)
        {
            *valueNameChar = 0;
            continue;
        }
        *valueNameChar = currentChar;
        valueNameChar++;
    }

    config->sections =
        realloc(config->sections, sizeof(chainbinder_config_section_t) *
                                      (config->sectionCount + 1));
    currentSection = &config->sections[config->sectionCount];

    if (sectionName[0] != 0)
    {
        if (strcmp(sectionName, "splashscreen") == 0)
        {
            currentSection->splashscreen.type =
                CHAINBINDER_SPLASHSCREEN_SECTION;

            struct pair_t pair;
            struct pair_t *pairs = (struct pair_t *)sectionPairs;
            while ((pair = *pairs++).set)
            {
                printf("%s\n", pair.key);
                if (strcmp(pair.key, "\ntitle") == 0)
                    currentSection->splashscreen.title =
                        strdup(pair.value);
                else if (strcmp(pair.key, "\nimage") == 0)
                    currentSection->splashscreen.image =
                        strdup(pair.value);
                pair.set = false;
            }
            printf("%s\n", currentSection->splashscreen.title);
        }
        sectionName[0] = 0;
    }
    config->sectionCount++;

    printf("%s\n", currentSection->splashscreen.title);

    fclose(configFile);

    return true;
}
