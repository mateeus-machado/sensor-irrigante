#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "buzzer.h"

#include "pico/multicore.h"
volatile bool deve_tocar = false;

// Inicialização do PWM no pino do buzzer
void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);  // Desativa o buzzer
}

void beep_background(uint note, uint duration) {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    uint32_t clock = clock_get_hz(clk_sys);
    uint32_t divisor = clock / (note * 4096);

    pwm_set_clkdiv(slice_num, divisor);
    pwm_set_gpio_level(BUZZER, 2048);

    sleep_ms(duration);

    pwm_set_gpio_level(BUZZER, 0);
    sleep_ms(20);
}

void beep_task() {
    while (true) {
        if (deve_tocar) {  // Variável global controlando o beep
            beep_background(1000, 500);
            deve_tocar = false;
        }
        sleep_ms(10); // Pequena espera para evitar uso excessivo de CPU
    }
}