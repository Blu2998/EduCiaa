#include "gpio.h"
#include "board_map.h"
#include "interrupts.h"
#include "dma.h"
#include "timer.h"

GPIO_MAP MapStruct; //defino estructura con datos

void configPinGPIO (int gpio, unsigned int bit, unsigned int state){
	Map (&MapStruct, gpio);
	int puerto = MapStruct.SCU_PORT;
	int pin = MapStruct.SCU_PIN;

	if (state==0)
		PSCU->SFSP[puerto][pin] &= ~(0x1 << bit);
	else
		PSCU->SFSP[puerto][pin] |= (0x1 << bit);
}

void configPinModeGPIO (int gpio){
	Map (&MapStruct, gpio);
	int puerto = MapStruct.SCU_PORT;
	int pin = MapStruct.SCU_PIN;
	int fun = MapStruct.SCU_FUN;

	PSCU->SFSP[puerto][pin]&= (0xFFFFFFF8);
	PSCU->SFSP[puerto][pin]|= (fun);
}

void setPinGPIO (int gpio, unsigned int state){
	Map (&MapStruct, gpio);
	int puerto = MapStruct.GPIO_PORT;
	int pin = MapStruct.GPIO_PIN;

	if (state==0)
		PGPIO->SET[puerto]&= ~(0x1 << pin);
	else
		PGPIO->SET[puerto]|=(0x1 << pin);
}

void setPortDirGPIO(int gpio, unsigned int io){
	Map (&MapStruct, gpio);
	int puerto = MapStruct.GPIO_PORT;
	int pin = MapStruct.GPIO_PIN;

	if (io==0)
		PGPIO->DIR[puerto]&= ~(0x1 << pin);
	else
		PGPIO->DIR[puerto]|=(0x1 << pin);
}


void configGPIO (int gpio, unsigned int io){
	configPinGPIO (gpio, 1, 1);
	configPinModeGPIO (gpio);
	setPortDirGPIO (gpio, io);
}

void SetClr (int gpio, unsigned int set_clr){
	Map (&MapStruct, gpio);
	int puerto = MapStruct.GPIO_PORT;
	int pin = MapStruct.GPIO_PIN;

	if (set_clr==0)
		PGPIO->SET[puerto]|= (0x1 << pin);
	else
		PGPIO->CLR[puerto]|=(0x1 << pin);
}

void toggleGPIO (int gpio){
	Map (&MapStruct, gpio);
	int puerto = MapStruct.GPIO_PORT;
	int pin = MapStruct.GPIO_PIN;

	PGPIO->NOT[puerto]|= (0x1 << pin);
}

int readGPIO(int gpio){
	Map (&MapStruct, gpio);
	int puerto = MapStruct.GPIO_PORT;
	int pin = MapStruct.GPIO_PIN;

	int state;

	if(PGPIO->B[puerto][pin] == 0)
	    state = 1;
	 else
	    state = 0;

	return state;
}



void delay(int valor){
	for(int i=0; i<valor; i++){}
}



void configBut (int but){
	Map (&MapStruct, but);
	int puerto = MapStruct.SCU_PORT;
	int pin = MapStruct.SCU_PIN;

	PSCU->SFSP[puerto][pin] = (0x1 << 6) | (0x1<<4)| (0x0 <<3);
}

void initLed(int led){
	configPinModeGPIO(led);

	configPinGPIO (led, 4, 1);

	setPortDirGPIO(led, OUTPUT); //configuro las direcciones del los leds

	SetClr (led, 1); //apago led
}

void initAllLeds(void){
	initLed(LED1);
	initLed(LED2);
	initLed(LED3);
	initLed(LEDB);
	initLed(LEDR);
	initLed(LEDG);
}

void initAllBut (void){
	configBut (BUT1);
	configBut (BUT2);
	configBut (BUT3);
	configBut (BUT4);
}


