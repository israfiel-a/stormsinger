#include <Vulkan.h>
#include <Windowing.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    stormsinger_createWindow();
    stormsinger_initializeVulkan();

    return 0;
}
