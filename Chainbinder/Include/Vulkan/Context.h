/**
 * @file Vulkan/Context.h
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides the mechanisms needed to create the Vulkan
 * context for the engine.
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
#ifndef CHAINBINDER_VULKAN_CONTEXT_H
#define CHAINBINDER_VULKAN_CONTEXT_H

#include <Chainbinder.h>
#include <Vulkan/Definitions.h>

#if !STORMSINGER_DISABLE_VALIDATION_LAYERS

// u32 for a reason, otherwise msvc complains about converting implicitly
// to u32
static const chainbinder_u32_t chainbinderValidationCount = 1;

static CHAINBINDER_STRING_ARRAY(ValidationLayers,
                                "VK_LAYER_KHRONOS_validation");

#else

static const chainbinder_u32_t chainbinderValidationCount = 0;

static CHAINBINDER_STRING_ARRAY(ValidationLayers, CHAINBINDER_NULLPTR);

#endif

/**
 * @brief Create the Vulkan instance.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @see Chainbinder_DestroyVulkanInstance(void) To destroy this created
 * instance.
 *
 * @returns A boolean value representing whether or not the instance
 * was created successfully.
 */
CHAINBINDER_NOIGNORE bool Chainbinder_CreateVulkanInstance(void);

/**
 * @brief Destroy the Vulkan instance.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @see Chainbinder_CreateVulkanInstance(void) To (re)create the instance.
 *
 * @note This does not clean up other Vulkan data, like the swapchain. That
 * has to be destroyed manually.
 */
void Chainbinder_DestroyVulkanInstance(void);

VkInstance Chainbinder_GetVulkanInstance(void);

#endif // CHAINBINDER_VULKAN_CONTEXT_H
