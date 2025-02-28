#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "pio_matrix.pio.h"
#include "controle-leds.h"
#include "joystick.h"
#include "animacoes.h"
#include "display.h"
#include "buzzer.h"
#include "pico/multicore.h"
#include "leds-rgb.h"

#define JOYSTICK_THRESHOLD_UP 3000
#define JOYSTICK_THRESHOLD_DOWN 1000
#define UMIDADE_MAX 100
#define UMIDADE_MIN 0
#define AUMENTO_IRRIGACAO 10


uint8_t umidade = 50;

void verificar_umidade() {
    if (umidade < 30) {
        display_pattern(pio0, 0, numbers[2], umidade);
        display_exibir(1, umidade);
        deve_tocar = true;
    } else if (umidade >= 30 && umidade < 40) {
        display_pattern(pio0, 0, numbers[1], umidade);
        display_exibir(2, umidade);
        deve_tocar = false;
    } else if (umidade > 40 && umidade < 70) {
        display_pattern(pio0, 0, numbers[0], umidade);
        display_exibir(3, umidade);
        deve_tocar = false;
    } else {
        display_pattern(pio0, 0, numbers[3], umidade);
        display_exibir(4, umidade);
        deve_tocar = false;
    }
}

int main() {
    stdio_init_all();
    adc_init();
    display_init();
    controle_leds_init();
    pwm_init_buzzer(BUZZER); // Inicializa o buzzer
    set_sys_clock_khz(128000, false);

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    pio_matrix_program_init(pio, sm, offset, MATRIX_PIN);

    joystick_init();

    // Inicializa o core secundário para o buzzer
    multicore_launch_core1(beep_task);

    while (true) {
        uint16_t joystick_y = ler_joystick_y();
        
        // Converter joystick para "umidade"
        umidade = (joystick_y * UMIDADE_MAX) / 4095;
        verificar_umidade();

        // Verificar se o botão A foi pressionado (simulação de irrigação)
        // if (botao_pressionado()) {
            umidade += AUMENTO_IRRIGACAO;
            if (umidade > UMIDADE_MAX) {
                umidade = UMIDADE_MAX;
            }
            verificar_umidade();
        // }

        sleep_ms(100);
    }
    return 0;
}