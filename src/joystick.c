#include "../includes/joystick.h"
#include "hardware/adc.h"

void joystick_init()
{
    adc_gpio_init(PINO_JOYSTICK_Y);
}

uint16_t ler_joystick_y()
{
    adc_select_input(0);
    return adc_read();
}