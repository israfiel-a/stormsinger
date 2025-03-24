/**
 * @file Vulkan/Context.c
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides the implementation of the Vulkan instance
 * creation interface.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @copyright (c) 2024-2025 - Israfil Argos
 * This document is under the GNU Affero General Public License v3.0. It
 * can be modified and distributed (commercially or otherwise) freely, and
 * can be used privately and within patents. No liability or warranty is
 * guaranteed. However, on use, the user must state license and copyright,
 * any changes made, and disclose the source of the document. For more
 * information see the @file LICENSE.md file included with this
 * distribution of the source code, or https://www.gnu.org/licenses/agpl.
 */

#include <Reporting.h>
#include <Vulkan/Context.h>
#include <Vulkan/Definitions.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

/**
 * @brief The Vulkan instance currently created.
 */
static VkInstance instance = CHAINBINDER_NULLPTR;

/**
 * @brief Get the GLFW support details for Vulkan on this machine.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @param extensionCount The place to store the count of instance
 * extensions GLFW requires.
 * @param extensions The place to store the array of extension names that
 * we'll use to enable all GLFW-required instance extensions.
 *
 * @returns A boolean flag representing whether or not Vulkan is supported
 * on this system. Unless this is truthy, any data within the
 * extensionCount and extensions parameters is not guaranteed to mean
 * anything.
 */
static inline bool GetGLFWSupport(uint32_t *extensionCount,
                                  const char ***extensions)
{
    int supportFlag = glfwVulkanSupported();
    if (supportFlag != GLFW_TRUE) return false;

    const char **reported_extensions =
        glfwGetRequiredInstanceExtensions(extensionCount);
    if (reported_extensions == CHAINBINDER_NULLPTR) return false;
    *extensions = reported_extensions;

    return true;
}

/**
 * @brief Assemble the application information structure to be sent off to
 * Vulkan.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @param applicationInfo The storage place for the created application
 * info.
 */
static inline void AssembleApplication(VkApplicationInfo *applicationInfo)
{
    VkApplicationInfo applicationCreateInfo = {0};
    applicationCreateInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationCreateInfo.pNext = CHAINBINDER_NULLPTR;

    applicationCreateInfo.apiVersion = VK_API_VERSION_1_0;
    applicationCreateInfo.applicationVersion = VK_MAKE_VERSION(
        STORMSINGER_VERSION_MAJOR, STORMSINGER_VERSION_MINOR,
        STORMSINGER_VERSION_PATCH);
    applicationCreateInfo.engineVersion =
        applicationCreateInfo.applicationVersion;

    applicationCreateInfo.pApplicationName = "Stormbringer";
    applicationCreateInfo.pEngineName = "Chainbinder";
    *applicationInfo = applicationCreateInfo;
    Chainbinder_Log(CHAINBINDER_VERBOSE,
                    "Assembled application information (%s, v%d.%d.%d).",
                    applicationCreateInfo.pApplicationName,
                    STORMSINGER_VERSION_MAJOR, STORMSINGER_VERSION_MINOR,
                    STORMSINGER_VERSION_PATCH);
}

/**
 * @brief Assemble the instance creation information structure. This also
 * decides what validation layers and extensions our instance is going to
 * have.
 *
 * @since 0.1.1
 * @updated 0.1.1
 *
 * @param applicationInfo The application information structure.
 * @param instanceInfo The place to store the created instance information
 * structure.
 *
 * @returns A boolean representing the success of polling GLFW for
 * extensions.
 */
static inline bool
AssembleInstance(const VkApplicationInfo *applicationInfo,
                 VkInstanceCreateInfo *instanceInfo)
{
    VkInstanceCreateInfo instanceCreateInfo = {0};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = CHAINBINDER_NULLPTR;

    instanceCreateInfo.pApplicationInfo = applicationInfo;
    instanceCreateInfo.flags = 0;

    uint32_t glfwExtensionCount;
    const char **glfwExtensionNames;
    if (!GetGLFWSupport(&glfwExtensionCount, &glfwExtensionNames))
    {
        Chainbinder_Log(CHAINBINDER_ERROR, "Invalid Vulkan installation.");
        return false;
    }
    Chainbinder_Log(CHAINBINDER_LOG,
                    "GLFW reported %d required extensions.",
                    glfwExtensionCount);

    instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledExtensionNames = glfwExtensionNames;
    instanceCreateInfo.ppEnabledLayerNames = CHAINBINDER_NULLPTR;
    *instanceInfo = instanceCreateInfo;
    Chainbinder_Log(CHAINBINDER_VERBOSE,
                    "Assembled instance information.");

    return true;
}

bool Chainbinder_CreateVulkanInstance(void)
{
    VkApplicationInfo applicationInfo;
    VkInstanceCreateInfo createInfo;

    AssembleApplication(&applicationInfo);
    bool assembled = AssembleInstance(&applicationInfo, &createInfo);
    if (!assembled) return false;

    CHECK_RESULT(
        vkCreateInstance(&createInfo, CHAINBINDER_NULLPTR, &instance),
        "Failed to create Vulkan instance. Code: %d.");
    Chainbinder_Log(CHAINBINDER_SUCCESS, "Created Vulkan instance.");

    return true;
}

void Chainbinder_DestroyVulkanInstance(void)
{
    vkDestroyInstance(instance, CHAINBINDER_NULLPTR);
    Chainbinder_Log(CHAINBINDER_NOTICE, "Destroyed Vulkan instance.");
}
