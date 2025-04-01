#include <Reporting.h>
#include <Vulkan/Context.h>
#include <Vulkan/Definitions.h>
#include <Vulkan/Device.h>

static VkPhysicalDevice physical = CHAINBINDER_NULLPTR;
static VkDevice logical = CHAINBINDER_NULLPTR;
static VkQueue graphicsQueue = CHAINBINDER_NULLPTR;

chainbinder_size_t GetSuitableIndex(const VkPhysicalDevice *devices,
                                    uint32_t deviceCount)
{
    // Really, REALLY unlikely that the user is running a machine with
    // SIZE_MAX graphics devices.
    chainbinder_size_t bestIndex = -1;
    chainbinder_u8_t bestScore = 0;
    for (chainbinder_size_t i = 0; i < deviceCount; i++)
    {
        VkPhysicalDevice device = devices[i];

        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);

        chainbinder_u8_t score = 0;
        switch (properties.deviceType)
        {
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: score += 4; break;
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   score += 5; break;
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    score += 3; break;
            case VK_PHYSICAL_DEVICE_TYPE_CPU:            score += 2; break;
            default:                                     score += 1; break;
        }

        if (score >= bestScore)
        {
            bestIndex = i;
            bestScore = score;
            Chainbinder_Log(CHAINBINDER_VERBOSE,
                            "Found suitable graphics device %s.",
                            properties.deviceName);
        }
    }
    return bestIndex;
}

bool Chainbinder_FindPhysicalDevice(void)
{
    uint32_t deviceCount = 0;
    CHAINBINDER_CHECK_RESULT(
        vkEnumeratePhysicalDevices(Chainbinder_GetVulkanInstance(),
                                   &deviceCount, CHAINBINDER_NULLPTR),
        "Failed to enumerate physical devices. Code: %d.");

    if (deviceCount == 0)
    {
        Chainbinder_Log(CHAINBINDER_ERROR,
                        "Failed to find Vulkan-compatible devices.");
        return false;
    }

    VkPhysicalDevice *devices;
    CHAINBINDER_ALLOCATE(devices, sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(Chainbinder_GetVulkanInstance(),
                               &deviceCount, devices);

    chainbinder_size_t deviceIndex =
        GetSuitableIndex(devices, deviceCount);
    if (deviceIndex == (chainbinder_size_t)-1) return false;
    physical = devices[deviceIndex];

    return true;
}

static chainbinder_u32_t Chainbinder_FindGraphicsQueue(void)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &queueFamilyCount,
                                             CHAINBINDER_NULLPTR);
    VkQueueFamilyProperties *queueFamilies;
    CHAINBINDER_ALLOCATE(queueFamilies, sizeof(VkQueueFamilyProperties) *
                                            queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &queueFamilyCount,
                                             queueFamilies);

    for (chainbinder_size_t i = 0; i < queueFamilyCount; i++)
        if (queueFamilies->queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            Chainbinder_Log(CHAINBINDER_VERBOSE,
                            "Found graphics queue at index %zu.", i);
            return (chainbinder_u32_t)i;
        }
    return (chainbinder_u32_t)-1;
}

bool Chainbinder_CreateLogicalDevice(void)
{
    chainbinder_u32_t graphicsIndex = Chainbinder_FindGraphicsQueue();

    VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
    deviceQueueCreateInfo.sType =
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.pNext = CHAINBINDER_NULLPTR;
    deviceQueueCreateInfo.queueFamilyIndex = graphicsIndex;
    deviceQueueCreateInfo.queueCount = 1;

    float priority = 1.0f;
    deviceQueueCreateInfo.pQueuePriorities = &priority;

    // We don't use any device features as of right now.
    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext = CHAINBINDER_NULLPTR;
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.ppEnabledExtensionNames = CHAINBINDER_NULLPTR;
    deviceCreateInfo.enabledExtensionCount = 0;

    // Only relevant for older implementations, but still a good idea to
    // set them.
    deviceCreateInfo.ppEnabledLayerNames = chainbinderValidationLayers;
    deviceCreateInfo.enabledLayerCount = chainbinderValidationCount;

    CHAINBINDER_CHECK_RESULT(
        vkCreateDevice(physical, &deviceCreateInfo, CHAINBINDER_NULLPTR,
                       &logical),
        "Failed to create logical graphics device. Code: %d.");
    vkGetDeviceQueue(logical, graphicsIndex, 0, &graphicsQueue);

    return true;
}
