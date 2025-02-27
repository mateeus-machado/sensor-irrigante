#ifndef CONTROLE_UMIDADE_H
#define CONTROLE_UMIDADE_H

#include <stdint.h>
#include <stdbool.h>

float calcular_nivel_umidade(uint16_t valor_y, bool bomba_irrigacao_ligado, float *vazao, float *irrigacao);
void definir_dimensoes(float largura, float comprimento, float altura);

#endif