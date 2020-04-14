//averiguar como devolver struct
#include "board_map.h"

void Map (GPIO_MAP *InfoPinGpio, int boardPin){

switch (boardPin){
	//Leds
	case 0:  //LED1 GPIO0[14] (FUNC0) (P2_10)
		InfoPinGpio->GPIO_PORT = 0;
		InfoPinGpio->GPIO_PIN = 14;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 2;
		InfoPinGpio->SCU_PIN = 10;
		break;
	case 1:  //LED2 GPIO1[11] (FUNC0) (P2_11)
		InfoPinGpio->GPIO_PORT = 1;
		InfoPinGpio->GPIO_PIN = 11;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 2;
		InfoPinGpio->SCU_PIN = 11;
		break;
	case 2:  //LED3 GPIO1[12] (FUNC0) (P2_12)
		InfoPinGpio->GPIO_PORT = 1;
		InfoPinGpio->GPIO_PIN = 12;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 2;
		InfoPinGpio->SCU_PIN = 12;
		break;
	case 3:  //LEDR GPIO5[0] (FUNC4) (P2_0)
		InfoPinGpio->GPIO_PORT = 5;
		InfoPinGpio->GPIO_PIN = 0;
		InfoPinGpio->SCU_FUN = 4;
		InfoPinGpio->SCU_PORT = 2;
		InfoPinGpio->SCU_PIN = 0;
		break;
	case 4:  //LEDG GPIO5[1] (FUNC4) (P2_1)
		InfoPinGpio->GPIO_PORT = 5;
		InfoPinGpio->GPIO_PIN = 1;
		InfoPinGpio->SCU_FUN = 4;
		InfoPinGpio->SCU_PORT = 2;
		InfoPinGpio->SCU_PIN = 1;
		break;
	case 5:  //LEDB GPIO5[2] (FUNC4) (P2_2)
		InfoPinGpio->GPIO_PORT = 5;
		InfoPinGpio->GPIO_PIN = 2;
		InfoPinGpio->SCU_FUN = 4;
		InfoPinGpio->SCU_PORT = 2;
		InfoPinGpio->SCU_PIN = 2;
		break;
	
	//Botones
	case 6:  //BUT1 GPIO0[4] (FUNC0) (P1_0)
		InfoPinGpio->GPIO_PORT = 0;
		InfoPinGpio->GPIO_PIN = 4;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 1;
		InfoPinGpio->SCU_PIN = 0;
		break;
	case 7:  //BUT2 GPIO0[8] (FUNC0) (P1_1)
		InfoPinGpio->GPIO_PORT = 0;
		InfoPinGpio->GPIO_PIN = 8;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 1;
		InfoPinGpio->SCU_PIN = 1;
		break;
	case 8:  //BUT3 GPIO0[9] (FUNC0) (P1_2)
		InfoPinGpio->GPIO_PORT = 0;
		InfoPinGpio->GPIO_PIN = 9;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 1;
		InfoPinGpio->SCU_PIN = 2;
		break;
	case 9:  //BUT4 GPIO1[9] (FUNC0) (P1_6)
		InfoPinGpio->GPIO_PORT = 1;
		InfoPinGpio->GPIO_PIN = 9;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 1;
		InfoPinGpio->SCU_PIN = 6;
		break;
		
	//Pin analogico DAC
	case 10:
		InfoPinGpio->GPIO_PORT = 2;
		InfoPinGpio->GPIO_PIN = 4;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 4;
		InfoPinGpio->SCU_PIN = 4;
		break;

	//Pines GPIO
	case 11: //GPIO3[0] (FUNC0) (P6_1)
		InfoPinGpio->GPIO_PORT = 3;
		InfoPinGpio->GPIO_PIN = 0;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 6;
		InfoPinGpio->SCU_PIN = 1;
		break;
	case 12://GPIO3[3] (FUNC0) (P6_4)
		InfoPinGpio->GPIO_PORT = 3;
		InfoPinGpio->GPIO_PIN = 3;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 6;
		InfoPinGpio->SCU_PIN = 4;
		break;
	case 13://GPIO3[4] (FUNC0) (P6_5)
		InfoPinGpio->GPIO_PORT = 3;
		InfoPinGpio->GPIO_PIN = 4;
		InfoPinGpio->SCU_FUN = 0;
		InfoPinGpio->SCU_PORT = 6;
		InfoPinGpio->SCU_PIN = 5;
		break;
	case 14://GPIO5[15] (FUNC4) (P6_7)
		InfoPinGpio->GPIO_PORT = 5;
		InfoPinGpio->GPIO_PIN = 15;
		InfoPinGpio->SCU_FUN = 4;
		InfoPinGpio->SCU_PORT = 6;
		InfoPinGpio->SCU_PIN = 7;
		break;
	}
}

