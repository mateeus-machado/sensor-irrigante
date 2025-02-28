#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pico/stdlib.h"
#define PINO_JOYSTICK_Y 27

void joystick_init();
uint16_t ler_joystick_y();

#endif 