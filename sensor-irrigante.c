#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/multicore.h"

#include "./includes/ssd1306.h"
#include "./includes/joystick.h"
#include "./includes/controle-leds.h"
#include "./includes/botoes.h"
#include "./includes/display.h"
#include "./includes/buzzer.h"

int main() {
    stdio_init_all();

    adc_init();
    joystick_init();
    controle_leds_init();
    display_init();
    botoes_init();
    pwm_init_buzzer(BUZZER);
    multicore_launch_core1(beep_task);

    while (true) {
        uint16_t valor_y = ler_joystick_y();
        bool bomba_irrigacao_ligado = botao_joystick();
        display_exibir_valores(valor_y, bomba_irrigacao_ligado);

        sleep_ms(10);
    }

    return 0;
}