#include "../includes/controle-leds.h"
#include "../includes/botoes.h"
#include "../includes/buzzer.h"
#include <stdlib.h>
#include "hardware/pwm.h"

void configurar_pwm(uint pino) {
  gpio_set_function(pino, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(pino);
  pwm_set_wrap(slice_num, 4095);
  pwm_set_enabled(slice_num, true);
}

void controle_leds_init() {
  configurar_pwm(PINO_LED_VERMELHO);
  configurar_pwm(PINO_LED_VERDE);
  configurar_pwm(PINO_LED_AZUL);
}

void definir_cor_led(uint16_t nivel_umidade, bool bomba_irrigacao_ligado) {
  if (!bomba_irrigacao_ligado) {
      // bomba_irrigacao desligado: LED vermelho e buzzer
      pwm_set_gpio_level(PINO_LED_VERDE, 0);
      pwm_set_gpio_level(PINO_LED_VERMELHO, 4095);
      pwm_set_gpio_level(PINO_LED_AZUL, 0);
      deve_tocar = true;
  } else {
      // bomba_irrigacao ligado, comportamento normal do LED com base no CO2
      if (nivel_umidade <= 1000) {
          // LED verde
          pwm_set_gpio_level(PINO_LED_VERDE, 4095);
          pwm_set_gpio_level(PINO_LED_VERMELHO, 0);
          pwm_set_gpio_level(PINO_LED_AZUL, 0);
      } else if (nivel_umidade > 1000 && nivel_umidade <= 2000) {
          // LED amarelo (vermelho + verde)
          pwm_set_gpio_level(PINO_LED_VERDE, 2048);
          pwm_set_gpio_level(PINO_LED_VERMELHO, 2048);
          pwm_set_gpio_level(PINO_LED_AZUL, 0);
      } else {
          // LED vermelho + buzzer
          deve_tocar = true;
          pwm_set_gpio_level(PINO_LED_VERDE, 0);
          pwm_set_gpio_level(PINO_LED_VERMELHO, 4095);
          pwm_set_gpio_level(PINO_LED_AZUL, 0);
      }
  }
}