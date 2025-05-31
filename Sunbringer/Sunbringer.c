#include <Chainbinder.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char *args[] = {CHAINBINDER_NULLPTR};
    int shaderCompilation = Chainbinder_Execute(GLSL, args);
    if (shaderCompilation == -1) return -1;

    return 0;
}
