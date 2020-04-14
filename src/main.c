#include "gpio.h"
#include "board_map.h"
#include "interrupts.h"
#include "dma.h"
#include "timer.h"
#include <stdio.h>

int flag = 1;

int riseEdgeEcho = 0;
int fallEdgeEcho = 0;
int count = 0;

void SysTick_Handler (void){ // En este handler pongo lo que quiero que pase cuando llamo al systick

}

void DMA_IRQHandler(void){

	clearDMA(); // Limpio la interrupción para volver al main
}

void GPIO0_IRQHandler(void){ //Interrupcion 1, esto haria que se saque un pulso de 10 useg en el trigger


	clearInt(0);
}

void GPIO1_IRQHandler(void){
	SetClr(LEDB, SET_GPIO);
	riseEdgeEcho = readTimer(TIMER0);

	clearInt (1);
}

void GPIO2_IRQHandler(void){
	SetClr(LEDB, CLEAR_GPIO);
	fallEdgeEcho = readTimer(TIMER0);
	count = riseEdgeEcho - fallEdgeEcho;
	printf("%d",count);
	clearInt (2);
}

void TIMER0_IRQHandler(void){
	toggleGPIO (LED1);

	SetClr (GPIO1, CLEAR_GPIO); // a los 10us se apaga el trigger
	//deInitTimer(TIMER0);

	clearMatchIntFlag(TIMER0, MATCH0);
}

void TIMER1_IRQHandler(void){

}


int main(void) {
	initAllLeds (); //se inicializan todos los leds configurados y apagados
	initAllBut (); //inicializo todos los botones


	configGPIO (GPIO0, INPUT); //echo
	configGPIO (GPIO1, OUTPUT); //trigger

	configInter(BUT1, 1,  RISE_EDGE); //cuando el echo vuelve genera una interrupcion
	configInter(BUT1, 2,  FALL_EDGE);


	//toggleGPIO(LEDB);

	LPC_TIMER_T* pTimerStruct = getPtrStruct(TIMER0);

	SetClr (GPIO1, SET_GPIO);

	initTimer(TIMER0, 1000000);
	int matchValue = 10;
	configMatchInterrupt(TIMER0, MATCH0, matchValue, FALSE);
	configNVIC (12);

//Con esto funciona timer 0
//		initTimer(TIMER0, 1000000);
//
//		int matchValue = 256000;
//
//		configMatchInterrupt(TIMER0, MATCH0, matchValue, FALSE);
//
//		configNVIC (12);




	while (1) {


	}
	return 0;
}
