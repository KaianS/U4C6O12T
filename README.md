# Projeto: Interface de Comunicação Serial com RP2040

Este projeto foi desenvolvido para consolidar os conhecimentos sobre o uso de interfaces de comunicação serial em microcontroladores RP2040, explorando as funcionalidades da placa de desenvolvimento BitDogLab.

## **Objetivos**
- Compreender e aplicar comunicação serial UART e I2C.
- Manipular LEDs comuns e LEDs endereçáveis WS2812.
- Controlar display SSD1306.
- Implementar interação com botões e tratar debounce.
- Desenvolver um projeto funcional combinando hardware e software.

## **Componentes Utilizados**
- **Matriz 5x5 de LEDs WS2812:** Conectada ao GPIO 7.
- **LED RGB:** Pinos conectados aos GPIOs 11, 12 e 13.
- **Botão A:** Conectado ao GPIO 5.
- **Botão B:** Conectado ao GPIO 6.
- **Display SSD1306:** Conectado via I2C (GPIO 14 e GPIO 15).

## **Funcionalidades do Projeto**

### 1. Modificação da Biblioteca `font.h`
- Adicionação de caracteres minúsculos para exibição no display SSD1306.

### 2. Entrada de Caracteres via PC
- Entrada de caracteres no Serial Monitor do VS Code.
- Exibição do caractere no display SSD1306.
- Para dígitos entre 0 e 9, um símbolo correspondente é mostrado na matriz 5x5 WS2812.

### 3. Interação com Botões
- **Botão A:** Alterna o estado do LED RGB Verde (ligado/desligado) com mensagens informativas no display e Serial Monitor.
- **Botão B:** Alterna o estado do LED RGB Azul (ligado/desligado) com mensagens informativas no display e Serial Monitor.

### 4. Controle de LEDs e Matriz WS2812
- Controle direto dos LEDs RGB e exibição de padrões específicos na matriz 5x5 WS2812.

### 5. Requisitos Técnicos
- **Uso de Interrupções:** Todas as funcionalidades relacionadas aos botões utilizam rotinas de interrupção (IRQ).
- **Debouncing:** Tratamento do bouncing dos botões via software.
- **Comunicação UART:** Implementa envio e recepção de dados.
- **Estrutura do Código:** Código bem estruturado e comentado.

## **Vídeo Demonstração**
[![Watch the video](https://img.youtube.com/vi/f1k8viThvUA/maxresdefault.jpg)](https://youtu.be/f1k8viThvUA)

### [Clique aqui para assistir](https://youtu.be/f1k8viThvUA)

## **Como Executar**
1. Clone este repositório:
   ```bash
   git clone https://github.com/KaianS/U4C6O12T.git
   ```
2. Certifique-se de ter o VS Code configurado e navegue até a pasta do projeto.
3. Conecte a placa BitDogLab ao computador.
4. Compile e envie o código para a placa.
5. Abra o Serial Monitor para interagir com o projeto.

## **Instruções para uso**
1. Execute o código e pressione os botões A e B para alternar os LEDs.
2. Digite caracteres no Serial Monitor para exibição no display SSD1306.
3. Digite números de 0 a 9 e observe a matriz WS2812 exibindo padrões correspondentes.

## **Considerações Finais**
Este projeto consolida conceitos de comunicação serial e manipulação de hardware, demonstrando o controle integrado de LEDs, display SSD1306 e botões com tratamento eficiente de interrupções.

