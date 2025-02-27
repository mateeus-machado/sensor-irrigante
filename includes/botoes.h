#ifndef BOTOES_H
#define BOTOES_H

#include "pico/stdlib.h"

#define PINO_BOTAO_JOYSTICK 22  
#define PINO_BOTAO_A 5
#define PINO_BOTAO_B 6
extern volatile float eficiencia_bomba_irrigacao;

void botoes_init();
volatile bool botao_joystick();

#endif 