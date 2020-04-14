#define GPIO_BASE 0x400F4000
#define PGPIO ((GPIO_T *)GPIO_BASE)

#define SCU_BASE 0x40086000
#define PSCU ((SCU_T *)SCU_BASE)

#define INPUT 0
#define OUTPUT 1
#define ENABLE 0
#define DISABLE 1
#define SET_GPIO 0
#define CLEAR_GPIO 1
#define TRUE 1
#define FALSE 0

//defino estructura gpio
typedef struct{
	unsigned char B [128][32];
	int W [32][32];
	int DIR [32];
	int MASK[32];
	int PIN [32];
	int MPIN [32];
	int SET [32];
	int CLR [32];
	int NOT [32];
}GPIO_T;


typedef struct {
	int  SFSP[16][32];		// Los pines digitales estan divididos en 16 grupos (P0-P9 y PA-PF)
	int  RESERVED0[256];
	int  SFSCLK[4];			// Pin configuration register for pins CLK0-3
	int  RESERVED16[28];
	int  SFSUSB;			// Pin configuration register for USB
	int  SFSI2C0;			// Pin configuration register for I2C0-bus pins
	int  ENAIO[3];			// Analog function select registers
	int  RESERVED17[27];
	int  EMCDELAYCLK;		// EMC clock delay register
	int  RESERVED18[63];
	int  PINTSEL[2];		// Pin interrupt select register for pin int 0 to 3 index 0, 4 to 7 index 1
} SCU_T;

void configPinGPIO (int gpio, unsigned int bit, unsigned int state);

void configPinModeGPIO (int gpio);

void setPinGPIO (int gpio, unsigned int state);

void setPortDirGPIO(int gpio, unsigned int io);


void configGPIO (int gpio, unsigned int io);

int readGPIO(int gpio);

void SetClr (int gpio, unsigned int set_clr);

void toggleGPIO (int gpio);


void configBut (int but);

void configLed(int led);

void initAllBut (void);

void initAllLeds(void);


void delay(int valor);

