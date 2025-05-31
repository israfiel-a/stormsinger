/**
 * @file Vulkan/Definitions.h
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides utility definitions for Vulkan, like error
 * checking procedures.
 *
 * @since 0.1.1
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
#ifndef CHAINBINDER_VULKAN_DEFINITIONS_H
#define CHAINBINDER_VULKAN_DEFINITIONS_H

#include <vulkan/vulkan.h>

/**
 * @brief Check the result of a given Vulkan function/expression, and
 * output the given message should it fail. The message should have a
 * formatter (%d) for the result code.
 *
 * @since 0.1.1
 * @updated 0.1.1
 */
#define CHAINBINDER_CHECK_RESULT(expression, message, ...)                \
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
