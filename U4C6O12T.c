#include <stdio.h>
#include "pico/stdlib.h"
#include "ws2818b.h"
#include "hardware/i2c.h"
#include "src/ssd1306.h"
#include "src/font.h"

// Definição de GPIOs
#define LED_BLUE_PIN 12
#define LED_GREEN_PIN 11
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15
#define DEBOUNCE_DELAY_MS 100

// Variáveis globais
ssd1306_t display;
volatile bool led_green_state = false;
volatile bool led_blue_state = false;
volatile uint32_t last_interrupt_A_time = 0;
volatile uint32_t last_interrupt_B_time = 0;
char received_char = '\0';

// Protótipos
void initialize_hardware(void);
void gpio_irq_handler(uint gpio, uint32_t events);
char read_serial_character(void);
void update_display(ssd1306_t *display, bool led_green, bool led_blue, char character);

int main() {
    initialize_hardware();

    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        char new_char = read_serial_character();
        if (new_char != '\0') {
            received_char = new_char;
            printf("Caractere: %c\n", received_char);
            if (received_char >= '0' && received_char <= '9') {
                display_number(received_char - '0');
            }
        }

        update_display(&display, led_green_state, led_blue_state, received_char);
        sleep_ms(100);
    }
}

void initialize_hardware(void) {
    init_leds();
    clear_leds();
    stdio_init_all();
    

    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    gpio_pull_up(BUTTON_B_PIN);

    i2c_init(i2c1, 400000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    ssd1306_init(&display, WIDTH, HEIGHT, false, 0x3C, i2c1);
    ssd1306_config(&display);
    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A_PIN) {
        if (current_time - last_interrupt_A_time > DEBOUNCE_DELAY_MS) {
            last_interrupt_A_time = current_time;
            led_green_state = !led_green_state;
            gpio_put(LED_GREEN_PIN, led_green_state);
            printf("LED Verde %s\n", led_green_state ? "ligado" : "desligado");
        }
    } else if (gpio == BUTTON_B_PIN) {
        if (current_time - last_interrupt_B_time > DEBOUNCE_DELAY_MS) {
            last_interrupt_B_time = current_time;
            led_blue_state = !led_blue_state;
            gpio_put(LED_BLUE_PIN, led_blue_state);
            printf("LED Azul %s\n", led_blue_state ? "ligado" : "desligado");
        }
    }
}

char read_serial_character() {
    if (stdio_usb_connected()) {
        int c = getchar_timeout_us(0);
        return (c == PICO_ERROR_TIMEOUT) ? '\0' : (char)c;
    }
    return '\0';
}

void update_display(ssd1306_t *display, bool led_green, bool led_blue, char character) {
    ssd1306_fill(display, false);
    char message[32];
    snprintf(message, sizeof(message), "Caractere: %c", character);
    ssd1306_draw_string(display, message, 5, 10);

    ssd1306_draw_string(display, led_green ? "LED Verde ON" : "LED Verde OFF", 5, display->height - 12);
    ssd1306_draw_string(display, led_blue ? "LED Azul ON" : "LED Azul OFF", 5, display->height - 20);

    ssd1306_send_data(display);
}
