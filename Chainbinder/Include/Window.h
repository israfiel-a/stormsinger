/**
 * @file Window.h
 * @author Israfiel Argos (israfiel-a)
 * @brief The windowing interface for Chainbinder. This provides logic for
 * displaying windows like the splash screen and game window.
 *
 * @since 0.1.0
 * @updated 0.1.1
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
#ifndef CHAINBINDER_WINDOW_H
#define CHAINBINDER_WINDOW_H

#include <Chainbinder.h>

/**
 * @brief An enum describing the kind of window one wants to create. This
 * will affect positioning and sizing, alongside user permissions.
 *
 * @since 0.1.1
 * @updated 0.1.1
 */
CHAINBINDER_ENUM(window_type, CHAINBINDER_SPLASHSCREEN,
                 CHAINBINDER_GAMEWINDOW);

/**
 * @brief Create a window with the given type and title. If a window is
 * already created, this function will return immediately.
 *
 * @since 0.1.0
 * @updated 0.1.2
 *
 * @see Chainbinder_DestroyWindow(void) to destroy the window created via
 * this function.
 *
 * @param type The type of window to create.
 *
 * @returns A boolean flag representing the success of this operation.
 */
CHAINBINDER_NOIGNORE bool
Chainbinder_CreateWindow(chainbinder_window_type_t type);

/**
 * @brief Destroy the currently created window.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @see Chainbinder_CreateWindow(const char* const,
 * chainbinder_window_type_t) To create another window, call this function.
 */
void Chainbinder_DestroyWindow(void);

/**
 * @brief Display the currently created window, and run its loop until it's
 * told to exit. If no window is created this will do nothing.
 *
 * @since 0.1.0
 * @updated 0.1.1
 *
 * @see Chainbinder_CreateWindow(const char* const,
 * chainbinder_window_type_t) To create a window, call this function.
 */
void Chainbinder_RunWindow(void);

/**
 * @brief Clean up the underlying windowing information and library. This
 * should only be called when you're certain another window will not be
 * created.
 *
 * @since 0.1.1
 * @updated 0.1.1
 */
void Chainbinder_CleanupWindows(void);

#endif // CHAINBINDER_WINDOW_H
