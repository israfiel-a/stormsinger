#ifndef STORMSINGER_WINDOW_H
#define STORMSINGER_WINDOW_H

#include <stdint.h>

bool stormsinger_windowCreate(void);

void stormsinger_windowClose(bool close);

void stormsinger_windowRun(void);

uint32_t stormsinger_windowGetWidth(void);
uint32_t stormsinger_windowGetHeight(void);

#endif // STORMSINGER_WINDOWING_H
