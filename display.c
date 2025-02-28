#include "display.h"
#include "controle-leds.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "leds-rgb.h"
#include <stdio.h>

ssd1306_t display;

void display_init() {
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(PINO_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PINO_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_I2C_SDA);
    gpio_pull_up(PINO_I2C_SCL);

    ssd1306_init(&display, LARGURA_DISPLAY, ALTURA_DISPLAY, false, 0x3C, i2c1);
    ssd1306_config(&display);
    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);
}

void display_exibir(int estado, int umidade) {
    ssd1306_fill(&display, false);

    // Exibe a mensagem conforme o estado da umidade
    switch (estado) {
        case 1:
            ssd1306_draw_string(&display, "CRITICO", 0, 10);
            definir_cor_led(1);
            break;
        case 2:
            ssd1306_draw_string(&display, "ALERTA", 0, 10);
            definir_cor_led(2);
            break;
        case 3:
            ssd1306_draw_string(&display, "SAUDAVEL", 0, 10);
            definir_cor_led(3);
            break;
        case 4:
            ssd1306_draw_string(&display, "CUIDADO", 0, 10);
            definir_cor_led(4);
            break;
        default:
            ssd1306_draw_string(&display, "DESCONHECIDO", 0, 10);
            definir_cor_led(0);
            break;
    }

    // Exibe a porcentagem de umidade
    char umidade_str[16];
    snprintf(umidade_str, sizeof(umidade_str), "Umidade %d%%", umidade);
    ssd1306_draw_string(&display, umidade_str, 0, 20);

    ssd1306_send_data(&display);
}