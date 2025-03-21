#include <Reporting.h>
#include <Vulkan/Context.h>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static VkInstance instance = CHAINBINDER_NULLPTR;

bool Chainbinder_CreateVulkanInstance(void)
{
    VkApplicationInfo applicationInfo = {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pNext = CHAINBINDER_NULLPTR;

    applicationInfo.apiVersion = VK_API_VERSION_1_0;
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 1);
    applicationInfo.engineVersion = applicationInfo.applicationVersion;

    applicationInfo.pApplicationName = "Stormbringer";
    applicationInfo.pEngineName = "Chainbinder";

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = CHAINBINDER_NULLPTR;

    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.flags = 0;

    chainbinder_u32_t glfwExtensionCount = 0;
    const char **glfwExtensionNames =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledExtensionNames = glfwExtensionNames;
    instanceCreateInfo.ppEnabledLayerNames = CHAINBINDER_NULLPTR;

    VkResult instanceCreateFlag = vkCreateInstance(
        &instanceCreateInfo, CHAINBINDER_NULLPTR, &instance);
    if (instanceCreateFlag != VK_SUCCESS)
    {
        Chainbinder_Log(CHAINBINDER_ERROR,
                        "Failed to create Vulkan instance. Code: %d.",
                        instanceCreateFlag);
        return false;
    }

    return true;
}

void Chainbinder_DestroyVulkanInstance(void) {}
