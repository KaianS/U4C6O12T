#include <stdio.h>
#include "pico/stdlib.h"
#include "ws2818b.h"
#include "hardware/i2c.h"
#include "src/ssd1306.h"
#include "src/font.h"

// Definição dos pinos GPIO para LEDs e botões
#define LED_BLUE_PIN 12       // Pino do LED azul
#define LED_GREEN_PIN 11      // Pino do LED verde
#define BUTTON_A_PIN 5        // Pino do Botão A
#define BUTTON_B_PIN 6        // Pino do Botão B
#define I2C_SDA_PIN 14        // Pino para SDA (I2C)
#define I2C_SCL_PIN 15        // Pino para SCL (I2C)
#define DEBOUNCE_DELAY_MS 100 // Delay para debounce dos botões em milissegundos

// Variáveis globais para controle de LEDs e estado
ssd1306_t display;                     // Estrutura para o display OLED
volatile bool led_green_state = false; // Estado do LED verde
volatile bool led_blue_state = false;  // Estado do LED azul
volatile uint32_t last_interrupt_A_time = 0; // Tempo do último evento do Botão A
volatile uint32_t last_interrupt_B_time = 0; // Tempo do último evento do Botão B
char received_char = '\0';            // Caractere recebido via porta serial

// Protótipos das funções
void initialize_hardware(void);                      // Inicializa os componentes do hardware
void gpio_irq_handler(uint gpio, uint32_t events);   // Handler de interrupção dos GPIOs
char read_serial_character(void);                    // Lê caractere recebido via serial
void update_display(ssd1306_t *display, bool led_green, bool led_blue, char character); // Atualiza o display

int main() {
    // Inicializa o hardware
    initialize_hardware();

    // Configura interrupções nos botões com callback para o handler
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        // Verifica se há novo caractere recebido via porta serial
        char new_char = read_serial_character();
        if (new_char != '\0') {
            received_char = new_char;
            printf("Caractere: %c\n", received_char);

            // Exibe números recebidos diretamente no display se forem dígitos
            if (received_char >= '0' && received_char <= '9') {
                display_number(received_char - '0');
            }
        }

        // Atualiza o display com os estados dos LEDs e o caractere recebido
        update_display(&display, led_green_state, led_blue_state, received_char);
        sleep_ms(100); // Aguarda 100 ms antes de repetir o loop
    }
}

// Inicializa todos os componentes do hardware
void initialize_hardware(void) {
    // Inicializa LEDs RGB
    init_leds();
    clear_leds();
    write_leds();  
    
    // Inicializa a comunicação serial
    stdio_init_all();

    // Configura pinos dos LEDs
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Configura pinos dos botões
    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    gpio_pull_up(BUTTON_B_PIN);

    // Configura pinos para comunicação I2C
    i2c_init(i2c1, 400000); // Inicializa I2C com freqüa de 400 kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa e configura o display OLED
    ssd1306_init(&display, WIDTH, HEIGHT, false, 0x3C, i2c1);
    ssd1306_config(&display);
    ssd1306_fill(&display, false); // Limpa o display
    ssd1306_send_data(&display);   // Envia dados ao display
}

// Handler de interrupção para os botões
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Tratamento para o Botão A
    if (gpio == BUTTON_A_PIN) {
        if (current_time - last_interrupt_A_time > DEBOUNCE_DELAY_MS) {
            last_interrupt_A_time = current_time;
            led_green_state = !led_green_state; // Alterna o estado do LED verde
            gpio_put(LED_GREEN_PIN, led_green_state);
            printf("LED Verde %s\n", led_green_state ? "ligado" : "desligado");
        }
    } 
    // Tratamento para o Botão B
    else if (gpio == BUTTON_B_PIN) {
        if (current_time - last_interrupt_B_time > DEBOUNCE_DELAY_MS) {
            last_interrupt_B_time = current_time;
            led_blue_state = !led_blue_state; // Alterna o estado do LED azul
            gpio_put(LED_BLUE_PIN, led_blue_state);
            printf("LED Azul %s\n", led_blue_state ? "ligado" : "desligado");
        }
    }
}

// Lê caractere recebido via porta serial, retorna '\0' se não houver caractere
char read_serial_character() {
    if (stdio_usb_connected()) {
        int c = getchar_timeout_us(0); // Lê caractere com timeout
        return (c == PICO_ERROR_TIMEOUT) ? '\0' : (char)c;
    }
    return '\0';
}

// Atualiza o display OLED com informações sobre os LEDs e caractere recebido
void update_display(ssd1306_t *display, bool led_green, bool led_blue, char character) {
    ssd1306_fill(display, false); // Limpa o display
    char message[32];

    // Exibe o caractere recebido no display
    snprintf(message, sizeof(message), "Caractere: %c", character);
    ssd1306_draw_string(display, message, 5, 10);

    // Exibe o estado dos LEDs
    ssd1306_draw_string(display, led_green ? "LED Verde ON" : "LED Verde OFF", 5, display->height - 12);
    ssd1306_draw_string(display, led_blue ? "LED Azul ON" : "LED Azul OFF", 5, display->height - 20);

    // Envia as alterações ao display
    ssd1306_send_data(display);
}
