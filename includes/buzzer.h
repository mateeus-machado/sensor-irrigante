#ifndef BUZZER_H
#define BUZZER_H
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#define BUZZER 21
extern volatile bool deve_tocar;

void pwm_init_buzzer(uint pin);
void beep_task();

#endif // BUZZER_H