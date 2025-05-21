/**
 * @file Chainbinder.c
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides the implementation of the public interface for
 * Chainbinder.
 *
 * @since 0.1.0
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

#include <Chainbinder.h>
#include <Reporting.h>
#include <Steelblade.h>
#include <Vulkan/Context.h>
#include <Window.h>
#include <stdio.h>

/**
 * @brief A flag representing whether or not the engine is initialized and
 * ready to be used.
 *
 * @since 0.1.1
 * @updated 0.1.1
 */
static bool initialized = false;

bool Chainbinder_Initialize(int argc, char **argv)
{
    if (initialized)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Tried to initialize engine twice.");
        return true;
    }

    (void)argc;
    (void)argv;

    SteelbladeBegin(256);
    SteelbladeSetAllocationMode(STEELBLADE_IMPLICIT);
    steelblade_error_t error;
    steelblade_string_t string = SteelbladeCreate(
        "y4iu2bwncrbut8diyc2c1gb6phmg21yruop08h1wm2vi4mev9pr463fzm0cx5sdl8"
        "hpuwxxusft438k1fkfj713hgeyknir1yb5lzjyez01hyh7k2wle645z9vndj2wzbd"
        "7ptj4t4vf5b70phebkrv1ubhhwch6piyjd64vgxhm5pfbion388b86bxqc01d1h0e"
        "kldkvu49oloyu73ukqooxiye1otlq2a1ml0h2y9o2pxifk5stdgrb3znujhcohrew"
        "ouhiohfewihfwohfewiofhewiofhe0",
        &error);
    if (error != STEELBLADE_OKAY) printf("%d\n", error);
    else printf("%s\n", string.value);
    SteelbladeCleanup();

    if (!Chainbinder_CreateWindow(CHAINBINDER_SPLASHSCREEN)) return false;
    // I would like to do this before creating the window, but GLFW
    // requires some extensions and in order to grab them, we need to have
    // the library initialized.
    if (!Chainbinder_CreateVulkanInstance()) return false;

    initialized = true;
    return true;
}

void Chainbinder_CleanUp(void)
{
    if (!initialized)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Tried to cleanup uninitialized engine.");
        return;
    }

    Chainbinder_DestroyWindow();
    Chainbinder_CleanupWindows();
    Chainbinder_DestroyVulkanInstance();
    initialized = false;
}

void Chainbinder_Run(void)
{
    if (!initialized)
    {
        Chainbinder_Log(CHAINBINDER_WARNING,
                        "Tried to run uninitialized engine.");
        return;
    }
    Chainbinder_RunWindow();
}

// TODO: Not yet implemented.
chainbinder_error_t Chainbinder_GetError(void)
{
    return CHAINBINDER_FAILED_NONE;
}
