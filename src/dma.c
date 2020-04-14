#include <math.h>
#include "gpio.h"
#include "board_map.h"
#include "interrupts.h"
#include "dma.h"
#include "timer.h"

#define PI (float)(3.141592654)
#define GPDMA_CLOCK 204e6              // Frecuencia de operacion del DMA
struct LLI_T LLI0;
struct LLI_T LLI1;

void configDAC (void){
	setPortDirGPIO(DAC, INPUT);
	configPinGPIO (DAC, 3, 0); // EPD
	configPinGPIO (DAC, 4, 1); // EPUN
	configPinGPIO (DAC, 6, 0); // EZI
	PSCU->ENAIO[2] = 1;
	PDAC->CTRL = 1 << 3| 1<<2 |1 ; //ena del DAC y DMA
	//PDAC->CR |= 1 << 16;
}

void toggleDAC(void){
	int aux = 0x3FF, aux1;
	aux1 = PDAC->CR;
	aux1 = aux1>>6;
	aux = aux1 & aux;

	if (aux!=1){
		writeDAC(1);
	}
	else{
		writeDAC(1023);
	}
}



void rampDAC(int periodo){
	int i = 0;
	writeDAC(1);
	while (i < 1023){
		writeDAC(i);
		i++;
		delay(periodo);
	}
}

void writeDAC (int valor){
	PDAC -> CR = valor << 6;
	PDAC->CTRL = 1 << 3; //activo este bit para poder convertir el valor de salida del DAC

}

void clearDMA(void){
	PGPDMA->INTTCCLEAR |= 1;
}

//void genSin (int Ts){ //voy a necesitar frecuencias 1k, 2k, 4k y 8k
//	double aux;
//	for (int j=0; j<Ts; j++){
//
//		aux = (sin(2*PI*j*flag[0]/Ts)+sin(2*2*PI*j*flag[1]/Ts)+sin(4*2*PI*j*flag[2]/Ts)+sin(8*2*PI*j*flag[3]/Ts))/(flag[0]+flag[1]+flag[2]+flag[3]);
//		seno[j]=(((int)(aux*511) + 512)<< 6) | (1<<16); //CASTEO DESPUES DE MULTIPLICAR POR 511
//
//		//seno[j] = ((int)(sin(2*PI*j/Ts)*511 + 512)<< 6) | (1<<16);
//		//seno[j] = ((int)(sin(2*PI*j*frec/Ts)*500 + 500) <<6) | (1<<16);
//		//genero la forma del seno normalmente
//		seno2[j] = seno[j];
//	}
//}

//void configDMA_DAC(int Ts){
//
//
//	PDAC->CNTVAL = ((int)(GPDMA_CLOCK/(1000*Ts)) & 0xFFFF); //frecuencia del dac
//
//	LLI0.source = (unsigned int) &seno[0];
//	LLI0.destination = (unsigned int)  &(PDAC->CR);
//	LLI0.next = (unsigned int) &LLI1;
//	LLI0.control =  	(Ts					|	// transfer size
//						(0 << 12)			|	// source burst size (12-14) = 1
//						(0 << 15)			|	// destination burst size (15-17) = 1
//						(2 << 18)			|	// source width (18-20) = 32 bits
//						(2 << 21)			|	// destination width (21-23) = 32 bits
//						(0 << 24)			|	// source AHB select = AHB 0
//						(1 << 25)			|	// destination AHB select = AHB 1
//						(1 << 26)			|	// source increment = increment (incrementa la posición del vector)
//						(0 << 27)			|	// destination increment = no increment
//						(0 << 28)			|	// mode select = access in user mode
//						(0 << 29)			|	// access not buffereable
//						(0 << 30)			|	// access not cacheable
//						(1 << 31));
//
//	LLI1.source = (unsigned int) &seno2[0];
//	LLI1.destination = (unsigned int)  &(PDAC->CR);
//	LLI1.next = (unsigned int) &LLI0;
//	LLI1.control =  	(Ts					|	// transfer size
//						(0 << 12)			|	// source burst size (12-14) = 1
//						(0 << 15)			|	// destination burst size (15-17) = 1
//						(2 << 18)			|	// source width (18-20) = 32 bits
//						(2 << 21)			|	// destination width (21-23) = 32 bits
//						(0 << 24)			|	// source AHB select = AHB 0
//						(1 << 25)			|	// destination AHB select = AHB 1
//						(1 << 26)			|	// source increment = increment (incrementa la posición del vector)
//						(0 << 27)			|	// destination increment = no increment
//						(0 << 28)			|	// mode select = access in user mode
//						(0 << 29)			|	// access not buffereable
//						(0 << 30)			|	// access not cacheable
//						(1 << 31));
//
//	(PGPDMA->CH[0]).LLI = LLI0;
//
//	PGPDMA->CONFIG = 1;
//
//	(PGPDMA->CH[0]).CONFIG 	=   1					// Channel (0) enabled
//							|	(0 << 1)		// Source peripheral (1-5) = memory (for memory ignore this field)
//							|	(0x0F << 6)		// destination peripheral (6-10) = none
//							|	(1 << 11)		// flow control (11-13) = mem to per
//							|	(0 << 14)		// mask out error interrupt (0 = enmascara)
//							|	(1 << 15)		// mask out terminal count interrupt (0 = enmascara)
//							|	(0 << 16)		// no locked transfers
//							|	(0 << 18);		// no HALT
//
//	configNVIC(2);
//
//}
