#ifndef CONTROLE_LEDS_H
#define CONTROLE_LEDS_H

#include "pico/stdlib.h"

#define PINO_LED_VERMELHO 13
#define PINO_LED_VERDE 11
#define PINO_LED_AZUL 12

void controle_leds_init();
void definir_cor_led(uint16_t nivel_umidade, bool bomba_irrigacao_ligado);
#endif