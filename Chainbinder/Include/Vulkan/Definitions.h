#ifndef CHAINBINDER_VULKAN_DEFINITIONS_H
#define CHAINBINDER_VULKAN_DEFINITIONS_H

#include <vulkan/vulkan.h>

#define CHECK_RESULT(expression, message, ...)                            \
    {                                                                     \
        VkResult result = expression;                                     \
        if (result != VK_SUCCESS)                                         \
        {                                                                 \
            Chainbinder_Log(CHAINBINDER_ERROR, message,                   \
                            result __VA_OPT__(, ) __VA_ARGS__);           \
            return false;                                                 \
        }                                                                 \
    }

#endif // CHAINBINDER_VULKAN_DEFINITIONS_H
