#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

// LED
#define LED1_PIO		PIOA
#define LED1_PIO_ID		ID_PIOA
#define LED1_PIO_IDX	0
#define LED1_PIO_IDX_MASK	(1u << LED1_PIO_IDX)

// Botão
#define BUT1_PIO			PIOD
#define BUT1_PIO_ID		ID_PIOD
#define BUT1_PIO_IDX		28
#define BUT1_PIO_IDX_MASK	(1u << BUT1_PIO_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
volatile char but1_flag = 0;
//volatile int freq = 1;
/************************************************************************/

/************************************************************************/
/* prototype                                                            */
/************************************************************************/
void but1_callback(void);
void io_init(void);
void handle_frequency(int is_up);

/************************************************************************/
/* handler / callbacks                                                  */
/************************************************************************/

void but1_callback(void){
	but1_flag != but1_flag;
}

void handle_frequency(int is_up){
	if (freq <= 10 && is_up){
		freq += 1;
	} if (freq > 1 && !is_up){
		freq -= 1;
	}
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.

void io_init(void){
	// Inicializa clock do periférico PIO responsavel pelo LED1
	pmc_enable_periph_clk(LED1_PIO_ID);
	pio_configure(LED1_PIO, PIO_OUTPUT_0, LED1_PIO_IDX_MASK, PIO_DEBOUNCE);
	
	// Inicializa clock do periférico PIO responsavel pelo botao
	pmc_enable_periph_clk(BUT1_PIO_ID);
	
	// Configura PIO para lidar com o pino do botão como entrada com pull-up
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT1_PIO, BUT1_PIO_IDX_MASK, 60);
	
	// Configura interrupção no pino referente ao botao e associa
	// função de callback caso uma interrupção for gerada
	// a função de callback é a: but_callback()
	pio_handler_set(BUT1_PIO, BUT1_PIO_ID, BUT1_PIO_IDX_MASK, PIO_IT_EDGE, but1_callback);
	
	// Ativa interrupção e limpa primeira IRQ gerada na ativacao
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT1_PIO);
	
	// Configura NVIC para receber interrupcoes do PIO do botao
	// com prioridade 4 (quanto mais próximo de 0 maior)
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4);
}


int main (void)
{
	board_init();
	sysclk_init();
	delay_init();
	io_init();

  // Init OLED
	gfx_mono_ssd1306_init();
  
  
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
  gfx_mono_draw_string("mundo", 50,16, &sysfont);
  
  

  /* Insert application code here, after the board has been initialized. */
	while(1) {



			// Escreve na tela um circulo e um texto
			
			for(int i=70;i<=120;i+=2){
				
				gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_SET);
				delay_ms(10);
				
			}
			
			for(int i=120;i>=70;i-=2){
				
				gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_CLR);
				delay_ms(10);
				
			}
			
			
	}
}
