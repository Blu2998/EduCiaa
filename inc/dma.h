//Definiciones
//DMA
#define GPDMA_BASE 0x40002000
#define PGPDMA ((GPDMA_T *)GPDMA_BASE)

//DAC
#define DAC_BASE 0x400E1000
#define PDAC ((DAC_T *)DAC_BASE)

extern struct LLI_T LLI0;
extern struct LLI_T LLI1;

//Estructuras
//DMA
struct LLI_T {
 unsigned int  source;		// inicio del area donde se encuentran los datos a transferir
 unsigned int  destination; // inicio del area destino de los datos transferidos
 unsigned int  next;        // address of next strLLI in chain
 unsigned int  control;     // DMACCxControl register
};

// Registros para el canal del GPDMA
typedef struct {
	struct LLI_T  LLI ;		// DMA Channel Source Address Register
	unsigned int  CONFIG;		// DMA Channel Configuration Register
	unsigned int  RESERVED1[3];
} _GPDMA_CH_T;

// // Registros para el GPDMA
typedef struct {
	unsigned int  INTSTAT;			// DMA Interrupt Status Register
	unsigned int  INTTCSTAT;		// DMA Interrupt Terminal Count Request Status Register
	unsigned int  INTTCCLEAR;		// DMA Interrupt Terminal Count Request Clear Register
	unsigned int  INTERRSTAT;		// DMA Interrupt Error Status Register
	unsigned int  INTERRCLR;		// DMA Interrupt Error Clear Register
	unsigned int  RAWINTTCSTAT;		// DMA Raw Interrupt Terminal Count Status Register
	unsigned int  RAWINTERRSTAT;	// DMA Raw Error Interrupt Status Register
	unsigned int  ENBLDCHNS;		// DMA Enabled Channel Register
	unsigned int  SOFTBREQ;			// DMA Software Burst Request Register
	unsigned int  SOFTSREQ;			// DMA Software Single Request Register
	unsigned int  SOFTLBREQ;		// DMA Software Last Burst Request Register
	unsigned int  SOFTLSREQ;		// DMA Software Last Single Request Register
	unsigned int  CONFIG;			// DMA Configuration Register
	unsigned int  SYNC;				// DMA Synchronization Register
	unsigned int  RESERVED0[50];
	_GPDMA_CH_T   CH[8];
} GPDMA_T;

//Estructura para DAC
typedef struct {
	int  CR;
	int  CTRL;
	int  CNTVAL;
} DAC_T;

//Funciones
void configDAC (void);

void toggleDAC(void);

void rampDAC(int f);

void writeDAC (int valor);

void clearDMA(void);

//// Funciones para seno
//void genSin (int Ts);

//void configDMA_DAC(int Ts);
