#include "ws2818b.h"
#include "ws2818b.pio.h"

// MACRO
#define LED_PIN 7
#define LED_COUNT 25

PIO np_pio;
uint sm;
struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[LED_COUNT];

void init_leds(void) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);
    ws2818b_program_init(np_pio, sm, offset, LED_PIN, 800000.f);
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}

// Limpa os LEDs
void clear_leds(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}

// Define a cor de um LED
void set_led(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < LED_COUNT) {
        leds[index].R = r;
        leds[index].G = g;
        leds[index].B = b;
    }
}

// Define a cor de todos os LEDs
void set_all_leds(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].R = r;
        leds[i].G = g;
        leds[i].B = b;
    }
}

// Escreve os LEDs
void write_leds(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}

void display_number(uint8_t number) {
    clear_leds();
    switch (number) {
        case 0:
            // Define os LEDs acesos para exibir o número 0
            set_led(1, 50, 0, 0);
            set_led(2, 50, 0, 0);
            set_led(3, 50, 0, 0);
            set_led(5, 50, 0, 0);
            set_led(9, 50, 0, 0);
            set_led(10, 50, 0, 0);
            set_led(14, 50, 0, 0);
            set_led(15, 50, 0, 0);
            set_led(19, 50, 0, 0);
            set_led(21, 50, 0, 0);
            set_led(22, 50, 0, 0);
            set_led(23, 50, 0, 0);
            break;
        case 1:
            // Define os LEDs acesos para exibir o número 1
            set_led(1, 0, 50, 0);
            set_led(2, 0, 50, 0);
            set_led(3, 0, 50, 0);
            set_led(7, 0, 50, 0);
            set_led(12, 0, 50, 0);
            set_led(17, 0, 50, 0);
            set_led(22, 0, 50, 0);
            set_led(16, 0, 50, 0);
            break;
        case 2:
            // Define os LEDs acesos para exibir o número 2
            set_led(0, 0, 0,  15);
            set_led(1, 0, 0,  15);
            set_led(2, 0, 0,  15);
            set_led(3, 0, 0,  15);
            set_led(4, 0, 0,  15);
            set_led(5, 0, 0,  15);
            set_led(10, 0, 0, 15);
            set_led(11, 0, 0, 15);
            set_led(12, 0, 0, 15);
            set_led(13, 0, 0, 15);
            set_led(14, 0, 0, 15);
            set_led(19, 0, 0, 15);
            set_led(20, 0, 0, 15);
            set_led(21, 0, 0, 15);
            set_led(22, 0, 0, 15);
            set_led(23, 0, 0, 15);
            set_led(24, 0, 0, 15);
            break;
        case 3:
            // Define os LEDs acesos para exibir o número 3
            set_led(0, 15, 50, 0);
            set_led(1, 15, 50, 0);
            set_led(2, 15, 50, 0);
            set_led(3, 15, 50, 0);
            set_led(4, 15, 50, 0);
            set_led(9, 15, 50, 0);
            set_led(10, 15, 50, 0);
            set_led(11, 15, 50, 0);
            set_led(12, 15, 50, 0);
            set_led(13, 15, 50, 0);
            set_led(19, 15, 50, 0);
            set_led(20, 15, 50, 0);
            set_led(21, 15, 50, 0);
            set_led(22, 15, 50, 0);
            set_led(23, 15, 50, 0);
            set_led(24, 15, 50, 0);
            break;
        case 4:
            // Define os LEDs acesos para exibir o número 4
            set_led(1, 15, 15, 0);
            set_led(8, 15, 15, 0);
            set_led(11, 15, 15, 0);
            set_led(18, 15, 15, 0);
            set_led(21, 15, 15, 0);
            set_led(12, 15, 15, 0);
            set_led(13, 15, 15, 0);
            set_led(16, 15, 15, 0);
            set_led(23, 15, 15, 0);
            break;
        case 5:
            // Define os LEDs acesos para exibir o número 5
            set_led(0, 0, 0,  15);
            set_led(1, 0, 0,  15);
            set_led(2, 0, 0,  15);
            set_led(3, 0, 0,  15);
            set_led(4, 0, 0,  15);
            set_led(9, 0, 0,  15);
            set_led(10, 0, 0, 15);
            set_led(11, 0, 0, 15);
            set_led(12, 0, 0, 15);
            set_led(13, 0, 0, 15);
            set_led(14, 0, 0, 15);
            set_led(15, 0, 0, 15);
            set_led(20, 0, 0, 15);
            set_led(21, 0, 0, 15);
            set_led(22, 0, 0, 15);
            set_led(23, 0, 0, 15);
            set_led(24, 0, 0, 15);
            break;
        case 6:
            // Define os LEDs acesos para exibir o número 6
            set_led(0, 0, 50, 15);
            set_led(1, 0, 50, 15);
            set_led(2, 0, 50, 15);
            set_led(3, 0, 50, 15);
            set_led(4, 0, 50, 15);
            set_led(5, 0, 50, 15);
            set_led(9, 0, 50, 15);
            set_led(10, 0, 50, 15);
            set_led(11, 0, 50, 15);
            set_led(12, 0, 50, 15);
            set_led(13, 0, 50, 15);
            set_led(14, 0, 50, 15);
            set_led(15, 0, 50, 15);
            set_led(20, 0, 50, 15);
            set_led(21, 0, 50, 15);
            set_led(22, 0, 50, 15);
            set_led(23, 0, 50, 15);
            set_led(24, 0, 50, 15);
            break;
        case 7:
            // Define os LEDs acesos para exibir o número 7
            set_led(20, 10, 0, 10);
            set_led(21, 10, 0, 10);
            set_led(22, 10, 0, 10);
            set_led(23, 10, 0, 10);
            set_led(24, 10, 0, 10);
            set_led(18, 10, 0, 10);
            set_led(12, 10, 0, 10);
            set_led(6, 10, 0, 10);
            set_led(4, 10, 0, 10);
            break;
        case 8:
            // Define os LEDs acesos para exibir o número 8
            set_led(24, 0, 10, 10);
            set_led(23, 0, 10, 10);
            set_led(22, 0, 10, 10);
            set_led(21, 0, 10, 10);
            set_led(20, 0, 10, 10);
            set_led(19, 0, 10, 10);
            set_led(15, 0, 10, 10);
            set_led(14, 0, 10, 10);
            set_led(13, 0, 10, 10);
            set_led(12, 0, 10, 10);
            set_led(11, 0, 10, 10);
            set_led(10, 0, 10, 10);
            set_led(9, 0, 10, 10);
            set_led(5, 0, 10, 10);
            set_led(4, 0, 10, 10);
            set_led(3, 0, 10, 10);
            set_led(2, 0, 10, 10);
            set_led(1, 0, 10, 10);
            set_led(0, 0, 10, 10);
            break;
        case 9:
            // Define os LEDs acesos para exibir o número 9
            set_led(24, 0, 10, 10);
            set_led(23, 0, 10, 10);
            set_led(22, 0, 10, 10);
            set_led(21, 0, 10, 10);
            set_led(20, 0, 10, 10);
            set_led(19, 0, 10, 10);
            set_led(15, 0, 10, 10);
            set_led(14, 0, 10, 10);
            set_led(13, 0, 10, 10);
            set_led(12, 0, 10, 10);
            set_led(11, 0, 10, 10);
            set_led(10, 0, 10, 10);
            set_led(9, 0, 10, 10);
            set_led(4, 0, 10, 10);
            set_led(3, 0, 10, 10);
            set_led(2, 0, 10, 10);
            set_led(1, 0, 10, 10);
            set_led(0, 0, 10, 10);
            break;
        default:
            break;
    }
    write_leds();
}