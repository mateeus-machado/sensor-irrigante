#include "../includes/controle-umidade.h"
#include "../includes/botoes.h"
#include <math.h>

static float volume_medido = 0.0; // Valor padrão, será calculado
static float nivel_umidade = 50.0; // Inicia com 50 de umidade
static float area_medida = 0.0; // Área do ambiente (m²)

// Função para definir as dimensões do ambiente (em centimetros cúbicos)
void definir_dimensoes(float largura, float comprimento, float altura) {
    area_medida = largura * comprimento;  // Área (cm²)
    volume_medido = area_medida * altura; // Volume em cm³
}

// Função para calcular o nível de umidade com base no valor do sensor
float calcular_nivel_umidade(uint16_t valor_y, bool bomba_irrigacao_ligado, float *vazao, float *irrigacao) {
    // Convertendo valor_y (valor do sensor) para nível humidade
    float novo_nivel = (valor_y / 4095.0) * 100; // Converte para porcentagem
    float incremento = 10.0;
    float umidade_ar = 40.0; // umidade no ambiente externo

    // Ajuste do nível de umidade baseado no sensor
    if (valor_y > 50.0) {
        if (novo_nivel > nivel_umidade) {
            nivel_umidade += incremento;
            if (nivel_umidade > novo_nivel) nivel_umidade = novo_nivel;
        }
    } else if (valor_y < 30.0) {
        if (novo_nivel < nivel_umidade) {
            nivel_umidade -= incremento;
            if (nivel_umidade < novo_nivel) nivel_umidade = novo_nivel;
        }
    }

    // Lógica do bomba_irrigacao
    float vs = 0.0, aumento_umidade = 0.0;
    if (bomba_irrigacao_ligado) {
        // Definir dimensões do ambiente quando o bomba_irrigacao estiver ligado
        definir_dimensoes(15.0, 5.0, 2.0); // Exemplo de dimensões do ambiente
        int plantas = 10; // Número de plantas no ambiente
        float fc = 2.5; // Fator de consumo de agua (L/m²)
        float fa = 0.3; // Fator de agua (m²)
        float ez = eficiencia_bomba_irrigacao; // Eficiência do bomba_irrigacao (valor entre 0 e 1)

        // Cálculo do volume de agua necessário para o bomba_irrigacao
        float vef1 = plantas * fc; // Volume deconsumo pelas plantas (L/h)
        float vef2 = area_medida * fa; // Volume de agua pela área (L/h)
        float vef = (vef1 > vef2) ? vef1 : vef2; // Escolher o maior valor entre os dois
        vs = vef * ez; // Ajuste: multiplicando pela eficiência do bomba_irrigacao

        // Cálculo do aumento da umidade
        aumento_umidade = (vs * (nivel_umidade - umidade_ar)) / volume_medido;
        nivel_umidade -= aumento_umidade; // Atualiza o nível de umidade

        // Garantir que o nível de umidade não seja menor que de umidade do ar
       
        if (nivel_umidade < 70.0) {
            nivel_umidade = 70.0; // Limite superior agua
        }
    }

    // Retorna os valores calculados (vazão e aumento de umidade)
    if (vazao) *vazao = vs;
    if (irrigacao) *irrigacao = aumento_umidade;

    // Retorna o nível de umidade atual
    return nivel_umidade;
}