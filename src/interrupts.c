#include "gpio.h"
#include "board_map.h"
#include "interrupts.h"
#include "dma.h"
#include "timer.h"

GPIO_MAP MapStructInt; //defino una estructura para poder conocer los valores del gpio y scu

void configSystick (int time_ms){
	PSYSTICK->CTRL = 0;
	PSYSTICK->LOAD = PSYSTICK->CAL;
	PSYSTICK->LOAD = (int) ((PSYSTICK->CAL)-1)*100*time_ms;
	PSYSTICK->VAL = 0;
	PSYSTICK->CTRL = 3;
}

//void ConfInter(char port, char pin, char interrupt, int irq){
void configInter(char but, int interrupt, int mode){
	char port, pin;
	int irq;
	Map (&MapStructInt, but);
	irq = interrupt+32;

	port = MapStructInt.GPIO_PORT;
	pin = MapStructInt.GPIO_PIN;

	int aux;
	int bl = 0xFF; //blanqueo
	aux = (port << 5) | pin; //concateno pin y port
	if (interrupt < 0x4){  // para pintsel0
		for (int i = 0; i<interrupt; i++){ //dependiendo el interrupt lo corro
			bl = bl <<8;
			aux = aux << 8;
		}
		PSCU->PINTSEL[0] &= ~bl;
		PSCU->PINTSEL[0] |= aux;
	}

	if (interrupt >= 0x4){  // para pintsel0
		for (int i=4; i<interrupt; i++){ //dependiendo el interrupt lo corro
			bl = bl <<8;
			aux = aux << 8;
		}
		PSCU->PINTSEL[1] &= ~bl;
		PSCU->PINTSEL[1] |= aux;
	}

	configNVIC (irq);

	switch(mode){
	case 0:
		PINT->ISEL &= ~(0x1 <<interrupt); //edge sensitive
		PINT->IENR |= 0x1<<interrupt;
		break;
	case 1:
		PINT->ISEL &= ~(0x1 <<interrupt); //edge sensitive
		PINT->SIENF |= 0x1 << interrupt;
		break;
	case 2:
		PINT->ISEL &= 0x1 <<interrupt; //level sensitive
		PINT->IENR |= 0x1<<interrupt;
		break;
	}

	return;
}

void configNVIC (int irq){
	int aux=0x1;
	if (irq < 32){
		for (int i=0; i<irq; i++)
			aux = aux<<1;

		PNVIC->ISER [0] |= aux;
	}
	else{
		if (irq < 64){
			for (int i=32; i<irq; i++)
				aux=aux<<1;
			PNVIC->ISER [1] |= aux;
		}
		else{
			for (int i=64; i<irq; i++)
				aux=aux<<1;
			PNVIC->ISER [2] |= aux;
		}
	}
}

void clearInt (int interrupt){
	PINT->IST = 1 << interrupt; //Pin interrupt status. Bit n returns the status, clears the edge interrupt, or inverts the active level of the pin selected in PINTSELn.
	PNVIC->ICPR[1] = 1 << interrupt; //Modifico el vector NVIC
}
