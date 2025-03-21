#ifndef CHAINBINDER_WINDOW_H
#define CHAINBINDER_WINDOW_H

#include <Definitions.h>

CHAINBINDER_ENUM(chainbinder_window_type_t, CHAINBINDER_SPLASHSCREEN,
                 CHAINBINDER_GAMEWINDOW);

bool Chainbinder_CreateWindow(const char *const title,
                              chainbinder_window_type_t type);
void Chainbinder_DestroyWindow(void);
void Chainbinder_RunWindow(void);

void Chainbinder_CleanupWindows(void);

#endif // CHAINBINDER_WINDOW_H
