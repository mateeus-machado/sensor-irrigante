#include "controle-leds.h"
#include "animacoes.h"
#include <stdio.h>

// Função para converter valores de cor (0.0 a 1.0) em um valor de 32 bits
uint32_t get_color(double r, double g, double b)
{
    uint8_t R = (uint8_t)(r * 255); // Intensidade do vermelho
    uint8_t G = (uint8_t)(g * 255); // Intensidade do verde
    uint8_t B = (uint8_t)(b * 255); // Intensidade do azul
    return (R << 16) | (G << 8) | B; // Formato GRB para WS2812B
}

// Função para exibir a matriz no terminal (para depuração)
void print_matrix(const uint8_t *pattern)
{
    printf("Matrix Display:\n");
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            int index = row * 5 + col;
            printf("%c ", pattern[index] ? 'X' : '.'); // 'X' para ON, '.' para OFF
        }
        printf("\n");
    }
    printf("\n");
}

// Função para enviar dados para os LEDs
void put_leds(const uint8_t *pattern, double *red, double *green, double *blue, PIO pio, uint sm)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        uint32_t led_value = get_color(red[i], green[i], blue[i]);
        if (pattern[i])
        {
            pio_sm_put_blocking(pio, sm, led_value); // Envia a cor para o LED
        }
        else
        {
            pio_sm_put_blocking(pio, sm, 0); // Desliga o LED
        }
    }
}

// Função para exibir um número na matriz de LEDs
void display_number(PIO pio, uint sm, uint number)
{
    // Verifica se o número está dentro do intervalo válido
    if (number >= 3)
    {
        printf("Erro: Número fora do intervalo válido (0-2).\n");
        return;
    }

    // Define as intensidades de cor para os LEDs
    double red[NUM_PIXELS];
    double green[NUM_PIXELS];
    double blue[NUM_PIXELS];

    for (int i = 0; i < NUM_PIXELS; i++)
    {
        red[i] = 0.05;   // Intensidade do vermelho (5%)
        green[i] = 0.0;  // Intensidade do verde (0%)
        blue[i] = 0.0;   // Intensidade do azul (0%)
    }

    // Exibe o padrão da matriz no terminal (para depuração)
    print_matrix(numbers[number]);

    // Envia os dados para os LEDs
    put_leds(numbers[number], red, green, blue, pio, sm);
}


void display_pattern(PIO pio, uint sm, const uint8_t *pattern, uint8_t umidade)
{
    double red[NUM_PIXELS] = {0.0};
    double green[NUM_PIXELS] = {0.0};
    double blue[NUM_PIXELS] = {0.0};

    // Definir cores conforme a umidade
    if (umidade < 30) {
        // Vermelho - Crítico
        for (int i = 0; i < NUM_PIXELS; i++) red[i] = 0.05;
    } else if (umidade >= 30 && umidade < 50) {
        // Amarelo - Alerta
        for (int i = 0; i < NUM_PIXELS; i++) {
            blue[i] = 0.05;
            green[i] = 0.05;
        }
    } else if (umidade >= 50 && umidade < 70) {
        // Verde - Planta saudável
        for (int i = 0; i < NUM_PIXELS; i++) green[i] = 0.05;
    } else {
        // Azul - Cuidado
        for (int i = 0; i < NUM_PIXELS; i++) blue[i] = 0.05;
    }

    print_matrix(pattern);  // Debug: imprime no console
    put_leds(pattern, red, green, blue, pio, sm);
}
