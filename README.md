# Monitor de Rega de Plantas - Bit Dog Lab

## Descrição
Este projeto consiste em um sistema de monitoramento de umidade do solo utilizando a placa **Bit Dog Lab** e diversos periféricos para fornecer informações visuais e sonoras sobre o estado da planta. O objetivo é alertar o usuário quando a planta precisa ser regada e confirmar a ação realizada.

## Funcionalidades
- **Leitura da umidade do solo**: Mede a umidade do solo e compara com um limite ajustável.
- **Joystick**: Permite ajustar a sensibilidade da medição da umidade.
- **LED RGB**: Indica o estado da planta:
  - **Vermelho**: Planta seca, precisa de água.
  - **Amarelo**: Atenção.
  - **Verde**: Planta saudável.
  - **Azul**: Alerta de excesso de umidade.
- **Buzzer**: Emite aterta sonoro no estado crítico.
- **Display OLED**: Exibe mensagens "crítico" ou "Planta Saudável" com emojis correspondentes.
- **Matriz de LED 5x5**: Exibe carinhas felizes ou tristes dependendo da umidade.


## Materiais Utilizados
- Placa **Bit Dog Lab**
- Sensor de umidade do solo
- Joystick analógico
- LED RGB
- Buzzer
- Display OLED
- Matriz de LED 5x5
  

## Instalação e Uso
1. **Clone este repositório:**
   ```bash
   git clone https://github.com/mateeus-machado/sensor-irrigante.git
   ```
2. **Carregue o código na placa Bit Dog Lab utilizando a IDE apropriada (ex: Arduino IDE, Thonny para MicroPython, etc.).**
3. **Alimente a placa e acompanhe os alertas visuais e sonoros.**
4. **Ajuste a sensibilidade da leitura com o joystick e leia o resultado no display.**

## Contribuição
Sinta-se à vontade para abrir issues ou enviar pull requests para melhorias neste projeto!

## Funcionamento

Segue o vídeo de explicação do código demonstração do funcionamento do código na placa.



