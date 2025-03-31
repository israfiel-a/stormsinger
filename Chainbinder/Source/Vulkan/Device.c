#include <Reporting.h>
#include <Vulkan/Context.h>
#include <Vulkan/Definitions.h>
#include <Vulkan/Device.h>

static VkPhysicalDevice physical = CHAINBINDER_NULLPTR;

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
                            "Found suitable graphics device with name %s.",
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
