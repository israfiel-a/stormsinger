#include <Reporting.h>
#include <Vulkan/Context.h>
#include <Vulkan/Definitions.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static VkInstance instance = CHAINBINDER_NULLPTR;

static inline bool GetGLFWSupport(uint32_t *extensionCount,
                                  const char ***extensions)
{
    int supportFlag = glfwVulkanSupported();
    if (supportFlag != GLFW_TRUE) return false;
    *extensions = glfwGetRequiredInstanceExtensions(extensionCount);
    if (extensions == CHAINBINDER_NULLPTR) return false;

    return true;
}

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
