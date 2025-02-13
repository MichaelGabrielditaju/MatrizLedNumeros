#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/irq.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
#include "matrizes.h"
#include "neopixel_pio.h"

#define LED_COUNT 25
#define LED_PIN 7
#define BOTAO_A 5
#define BOTAO_B 6
#define LED_VERMELHO 13
#define DEBOUNCE_TIME 50  // Debounce para os botões em ms

PIO np_pio;
uint sm;
npLED_t leds[LED_COUNT];
uint8_t numero_atual = 0; // Número exibido atualmente (0 a 9)

void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, false);
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);
    for (uint i = 0; i < LED_COUNT; ++i) {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

void npWrite() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}

int getIndex(int x, int y) {
    return (y % 2 == 0) ? (24 - (y * 5 + x)) : (24 - (y * 5 + (4 - x)));
}

void desenha_fig(int matriz[5][5][3]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = getIndex(i, j);
            npSetLED(index, matriz[j][i][0], matriz[j][i][1], matriz[j][i][2]);
        }
    }
    npWrite();
}

void tratar_botao_a() {
    printf("Botão A pressionado\n"); // Mensagem de debug
    numero_atual = (numero_atual + 1) % 10; // Limita o valor a 0-9
    desenha_fig(matrizes[numero_atual]);
}

void tratar_botao_b() {
    printf("Botão B pressionado\n"); // Mensagem de debug
    numero_atual = (numero_atual == 0) ? 9 : (numero_atual - 1); // Corrige o limite
    desenha_fig(matrizes[numero_atual]);
}

void botoes_callback(uint gpio, uint32_t events) {
    static absolute_time_t last_time = {0}; 
    absolute_time_t now = get_absolute_time();

    if (absolute_time_diff_us(last_time, now) > DEBOUNCE_TIME * 1000) { // converter ms para µs
        last_time = now;

        // Verifica qual botão foi pressionado
        if (gpio == BOTAO_A) {
            tratar_botao_a();
        } else if (gpio == BOTAO_B) {
            tratar_botao_b();
        }
    }
}

void inicializar_botoes() {
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &botoes_callback);
    
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &botoes_callback); 
}

void piscar_led_vermelho() {
    static bool estado_led = false;
    static uint32_t ultimo_tempo = 0;
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (tempo_atual - ultimo_tempo >= 100) {  // Frequência de 5 Hz (100 ms)
        estado_led = !estado_led; // Alterna o estado do LED
        gpio_put(LED_VERMELHO, estado_led); // Atualiza o LED
        ultimo_tempo = tempo_atual;
    }
}

int main() {
    stdio_init_all();
    npInit(LED_PIN);
    
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    inicializar_botoes();

    // Exibe o número inicial
    desenha_fig(matrizes[numero_atual]);

    while (true) {
        piscar_led_vermelho(); // Chama a função para piscar o LED vermelho
        sleep_ms(10); // Adiciona um pequeno atraso para evitar sobrecarga
    }
}