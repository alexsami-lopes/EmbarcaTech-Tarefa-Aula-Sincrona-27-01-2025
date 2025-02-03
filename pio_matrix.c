//Embarcatec 
//Tarefa 1 - Aula Sincrona - 27/01/2025
//Discente: Alexsami


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_matrix.pio.h"


//pino de saída
#define OUT_PIN 7

#define FRAME_SIZE 25

#define PIXEL_INTENSITY 0.2 // 1 equivale a 100% e 0.5 a 50%, se for testar na placa não ponha em 1 pois a intensidade é muito alta e pode prejudicar a visão
#define LED_INTERVAL_TIME 100 // Como são 5 por segundo, 1000/5 = 200, mas como para piscar é chamado 2 vezes 200/2 = 100

//botão de interupção
const uint button_a = 5;
const uint button_b = 6;

const uint ledGreen_pin = 11; // Green=> GPIO11
const uint ledBlue_pin = 12; // Blue => GPIO12
const uint ledRed_pin = 13; // Red => GPIO13

// Variáveis globais
static volatile uint a = 0;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
PIO pio = pio0; 
uint sm = 0;


//rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255 * PIXEL_INTENSITY;
  G = g * 255 * PIXEL_INTENSITY;
  B = b * 255 * PIXEL_INTENSITY;
  return (R << 24) | (G << 16) | (B << 8);
}

uint32_t matrix_rgb_dois(double b, double r, double g, double intensity)
{
  unsigned char R, G, B;
  R = r * 255 * intensity;
  G = g * 255 * intensity;
  B = b * 255 * intensity;
  return (R << 24) | (G << 16) | (B << 8);
}

// Função para acionar a matriz de LEDs - ws2812b
void desenho_pio(double frame[FRAME_SIZE][3], uint32_t valor_led, PIO pio, uint sm) {
    // Ordem desejada dos índices
    int ordem_indices[FRAME_SIZE] = {24, 23, 22, 21, 20, 15, 16, 17, 18, 19, 14, 13, 12, 11, 10, 5, 6, 7, 8, 9, 4, 3, 2, 1, 0};
    
    // Iterar sobre os índices na ordem desejada
    for (int i = 0; i < FRAME_SIZE; i++) {
        int idx = ordem_indices[i];
        double r = frame[idx][0];
        double g = frame[idx][1];
        double b = frame[idx][2];
        valor_led = matrix_rgb(r, g, b);  // Assumindo que esta função converte os valores RGB em um valor de LED
        pio_sm_put_blocking(pio, sm, valor_led);  // Envia o valor do LED para o PIO
    }
}


/*
//rotina da interrupção
static void gpio_irq_handler(uint gpio, uint32_t events){
    printf("Interrupção ocorreu no pino %d, no evento %d\n", gpio, events);
    printf("HABILITANDO O MODO GRAVAÇÃO");
	reset_usb_boot(0,0); //habilita o modo de gravação do microcontrolador
}*/


// Função para lidar com a interrupção de ambos os botões
void gpio_irq_handler(uint gpio, uint32_t events) {

    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    printf("A = %d\n", a);
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) // 200 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        if (gpio == 5) {  // Verifica se o botão A foi pressionado
          if(a < 9) {
            a++;  // incrementa a variavel de verificação
          }else {
            a = 0;
          }
        }
        if (gpio == 6) {  // Verifica se o botão B foi pressionado
          if(a > 0) {
            a--;  // incrementa a variavel de verificação
          }else {
            a = 9;
          }
        }        

        exibir_animacao_digito(a, pio, sm);
                                           
    }

}

static double frames_digitos[10][FRAME_SIZE][3] = {
// Frame 0
{       {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

// Frame 1
{       {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

// Frame 2
{       {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}},

// Frame 3
{       {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

// Frame 4
{       {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

// Frame 5
{       {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}},

// Frame 6
{       {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

// Frame 7
{       {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

// Frame 8
{       {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},

// Frame 9
{       {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}

};




// Função para exibir animação das letras
void exibir_animacao_digito(uint digito, PIO pio, uint sm) {
    
    if((digito < 10) && (digito >= 0)) {
      desenho_pio(frames_digitos[digito], 0, pio, sm);
    }
        
    
}

//função principal
int main()
{
  //PIO pio = pio0;
  pio = pio0;  
  bool ok;
  uint16_t i;
  uint32_t valor_led;
  double r = 0.0, b = 0.0 , g = 0.0;
  //bool apagar = false;

  //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
  ok = set_sys_clock_khz(128000, false);

  // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
  stdio_init_all();

  printf("iniciando a transmissão PIO");
  if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

  //configurações da PIO
  uint offset = pio_add_program(pio, &pio_matrix_program);
  //uint sm = pio_claim_unused_sm(pio, true);
  sm = pio_claim_unused_sm(pio, true);
  pio_matrix_program_init(pio, sm, offset, OUT_PIN);

  // Inicializar o botão de interrupção - GPIO5
  gpio_init(button_a);
  gpio_set_dir(button_a, GPIO_IN);       // Configura GPIO5 como entrada
  gpio_pull_up(button_a);                // Ativa o resistor pull-up interno
  //

  // Inicializar o botão de interrupção - GPIO6
  gpio_init(button_b);
  gpio_set_dir(button_b, GPIO_IN);       // Configura GPIO6 como entrada
  gpio_pull_up(button_b);                // Ativa o resistor pull-up interno
  gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_FALL, 1, gpio_irq_handler);  // Configura a interrupção para borda de descida
  gpio_set_irq_enabled_with_callback(button_b, GPIO_IRQ_EDGE_FALL, 1, gpio_irq_handler);  // Configura a interrupção para borda de descida

  gpio_init(ledRed_pin);              // Inicializa o pino do LED
  gpio_set_dir(ledRed_pin, GPIO_OUT); // Configura o pino como saída  

  exibir_animacao_digito(a, pio, sm);
  
  while (true) {

        gpio_put(ledRed_pin, true);
        sleep_ms(LED_INTERVAL_TIME);
        gpio_put(ledRed_pin, false);
        sleep_ms(LED_INTERVAL_TIME);
  
  }
  return 0;
}