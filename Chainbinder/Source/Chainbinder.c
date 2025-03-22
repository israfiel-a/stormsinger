/**
 * @file Chainbinder.c
 * @author Israfiel Argos (israfiel-a)
 * @brief This file provides the implementation of the public interface for
 * Chainbinder.
 *
 * @since 0.1.0
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

#include <Chainbinder.h>
#include <Vulkan/Context.h>
#include <Window.h>

bool Chainbinder_Initialize(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!Chainbinder_CreateWindow("TEST", CHAINBINDER_SPLASHSCREEN))
        return false;
    // I would like to do this before creating the window, but GLFW
    // requires some extensions and in order to grab them, we need to have
    // the library initialized.
    if (!Chainbinder_CreateVulkanInstance()) return false;

    return true;
}

void Chainbinder_CleanUp(void)
{
    Chainbinder_DestroyWindow();
    Chainbinder_CleanupWindows();
    Chainbinder_DestroyVulkanInstance();
}

void Chainbinder_Run(void) { Chainbinder_RunWindow(); }

// TODO: Not yet implemented.
chainbinder_error_t Chainbinder_GetError(void)
{
    return CHAINBINDER_FAILED_NONE;
}
