#include <Vulkan.h>
#include <Window.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    stormsinger_windowCreate();
    stormsinger_vulkanInitialize();

    stormsinger_windowRun();

    return 0;
}
