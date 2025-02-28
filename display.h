#ifndef DISPLAY_H
#define DISPLAY_H

#include "ssd1306.h"

#define LARGURA_DISPLAY 128
#define ALTURA_DISPLAY 64
#define TAMANHO_QUADRADO 8
#define PINO_I2C_SDA 14
#define PINO_I2C_SCL 15

void display_init();
void display_exibir(int animacao, int umidade);
#endif