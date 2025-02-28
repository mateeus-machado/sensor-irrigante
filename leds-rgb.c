#include "leds-rgb.h"

void controle_leds_init() {
    gpio_init(PINO_LED_VERMELHO);
    gpio_set_dir(PINO_LED_VERMELHO, GPIO_OUT);
    gpio_init(PINO_LED_VERDE);
    gpio_set_dir(PINO_LED_VERDE, GPIO_OUT);
    gpio_init(PINO_LED_AZUL);
    gpio_set_dir(PINO_LED_AZUL, GPIO_OUT);
}

void definir_cor_led(int estado) {
    switch (estado) {
        case 1: // Crítico: Vermelho
            gpio_put(PINO_LED_VERMELHO, 1);
            gpio_put(PINO_LED_VERDE, 0);
            gpio_put(PINO_LED_AZUL, 0);
            break;
        case 2: // Alerta: Amarelo (Vermelho + Verde)
            gpio_put(PINO_LED_VERMELHO, 1);
            gpio_put(PINO_LED_VERDE, 1);
            gpio_put(PINO_LED_AZUL, 0);
            break;
        case 3: // Saudável: Verde
            gpio_put(PINO_LED_VERMELHO, 0);
            gpio_put(PINO_LED_VERDE, 1);
            gpio_put(PINO_LED_AZUL, 0);
            break;
        case 4: // Cuidado: Azul
            gpio_put(PINO_LED_VERMELHO, 0);
            gpio_put(PINO_LED_VERDE, 0);
            gpio_put(PINO_LED_AZUL, 1);
            break;
        default: // Desconhecido: Desligar todos os LEDs
            gpio_put(PINO_LED_VERMELHO, 0);
            gpio_put(PINO_LED_VERDE, 0);
            gpio_put(PINO_LED_AZUL, 0);
            break;
    }
}