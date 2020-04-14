typedef struct{
	char SCU_PORT;
	char SCU_PIN;
	char SCU_FUN;
	char GPIO_PORT;
	char GPIO_PIN;
}GPIO_MAP;

enum periph{
	//Leds
	LED1,
	LED2,
	LED3,
	LEDR,
	LEDG,
	LEDB,
	
	//Botones
	BUT1,
	BUT2,
	BUT3,
	BUT4,
	
	//DAC
	DAC,

	//GPIOs
	GPIO0,
	GPIO1,
	GPIO2,
	GPIO3
};

void Map (GPIO_MAP *InfoPinGpio, int boardPin);



