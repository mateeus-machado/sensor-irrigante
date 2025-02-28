#ifndef LEDS_RGB_H
#define LEDS_RGB_H

#include "pico/stdlib.h"

#define PINO_LED_VERMELHO 13
#define PINO_LED_VERDE 11
#define PINO_LED_AZUL 12

void controle_leds_init();
void definir_cor_led(int estado);
#endif