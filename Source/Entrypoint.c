#include <Vulkan.h>
#include <Window.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    stormsinger_createWindow();
    stormsinger_vulkanInitialize();

    stormsinger_runWindow();

    return 0;
}
