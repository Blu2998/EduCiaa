extern int flag;

//Macros
#define RISE_EDGE 0
#define FALL_EDGE 1
#define LEVEL 2

//Direcciones para punteros
#define PIN_INT_BASE 0x40087000
#define PINT ((PIN_INT_T *)PIN_INT_BASE)

#define NVIC_T_BASE 0xE000E100
#define PNVIC ((NVIC_T *)NVIC_T_BASE)

//direcciones para systick
#define SYSTICK_CTRL 0xE000E010
#define SYSTICK_LOAD 0xE000E014
#define SYSTICK_VAL 0xE000E018
#define SYSTICK_CAL 0xE000E01C

#define SYSTICK_T_BASE 0xE000E010
#define PSYSTICK ((SYSTICK_T *)SYSTICK_T_BASE)

//Estructuras
typedef struct{
	int CTRL;
	int LOAD;
	int VAL;
	int CAL;
}SYSTICK_T;

typedef struct{
	int ISEL;				// Pin Interrupt Mode register
	int IENR;				// Pin Interrupt Enable (Rising) register
	int SIENR;				// Set Pin Interrupt Enable (Rising) register
	int CIENR;				// Clear Pin Interrupt Enable (Rising) register
	int IENF;				// Pin Interrupt Enable Falling Edge / Active Level register
	int SIENF;				// Set Pin Interrupt Enable Falling Edge / Active Level register
	int CIENF;				// Clear Pin Interrupt Enable Falling Edge / Active Level address
	int RISE;				// Pin Interrupt Rising Edge register
	int FALL;				// Pin Interrupt Falling Edge register
	int IST;				// Pin Interrupt Status register
}PIN_INT_T; //GPIO pin interrupts (base address: 0x4008 7000)

typedef struct{ 
	int ISER[8];			//Interrupt Set-Enable Register
	int RESERVD0[24];     
	int ICER [8];			//Interrupt Clear-Enable Register		
	int RESERVD1[24];
	int ISPR [8];			//Interrupt Set-Pending Register
	int RESERVD2[24];
	int ICPR [8];			//Interrupt Clear-Pending Register
	int RESERVD3[24];
	int IABR [8];			//Interrupt Active Bit Register
	int RESERVD4[56];
	unsigned char IP[240];	//Interrupt Priority Registers
	int RESERVD5[644];
	int STIR;				//Software Trigger Interrupt Register.
}NVIC_T; //Register overview: NVIC (base address 0xE000 E000)

//Funciones
void configInter(char but, int interrupt, int mode); //funcion para configurar la interrupcion

void configNVIC (int irq); //funcion para configurar el nvic en la interrupcion

void clearInt (int interrupt); //funcion para limpiar la interrupcion una vez llamada

void configSystick (int time_ms); // funcion para configurar systick

