#define MAX_FREC 204000000

#define LPC_TIMER0_BASE 0x40084000
#define LPC_TIMER0 		((LPC_TIMER_T*)LPC_TIMER0_BASE)

#define LPC_TIMER1_BASE 0x40084000
#define LPC_TIMER1 		((LPC_TIMER_T*)LPC_TIMER1_BASE)

#define LPC_TIMER2_BASE 0x40084000
#define LPC_TIMER2 		((LPC_TIMER_T*)LPC_TIMER2_BASE)

#define LPC_TIMER3_BASE 0x40084000
#define LPC_TIMER3 		((LPC_TIMER_T*)LPC_TIMER3_BASE)

// Macros to chose a timer with the diferent functions
#define TIMER0		0
#define TIMER1		1
#define TIMER2		2
#define TIMER3		3

// Macros to chose a match of each timer
#define MATCH0		0
#define MATCH1		1
#define MATCH2		2
#define MATCH3		3

//ver timers en pagina 1015 del manual, tabla 784
typedef struct {					/*!< TIMERn Structure       */
	int IR;				/*!< Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
	int TCR;				/*!< Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
	int TC;				/*!< Timer Counter. The 32 bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
	int PR;				/*!< Prescale Register. The Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
	int PC;				/*!< Prescale Counter. The 32 bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
	int MCR;				/*!< Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
	int MR[4];			/*!< Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
	int CCR;				/*!< Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
	int CR[4];			/*!< Capture Register. CR is loaded with the value of TC when there is an event on the CAPn.0 input. */
	int EMR;				/*!< External Match Register. The EMR controls the external match pins MATn.0-3 (MAT0.0-3 and MAT1.0-3 respectively). */
	int RESERVED0[12];
	int CTCR;				/*!< Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
} LPC_TIMER_T;

void enableTimer( LPC_TIMER_T* pTimerStruct );

void resetOnNextEdge( LPC_TIMER_T* pTimerStruct );

void dontResetOnNextEdge( LPC_TIMER_T* pTimerStruct );

LPC_TIMER_T* getPtrStruct(int num_timer);

void setTimerMode ( LPC_TIMER_T* pTimerStruct );

void setMatchValue( LPC_TIMER_T* timerStruct, int matchNumber, int matchValue );

void setTimerFrequency( LPC_TIMER_T* timerStruct, int frequency );

void setResetOnMatch( LPC_TIMER_T* timerStruct, int matchNumber );

int readTimer(int chosenTimer);

int* initTimer(int chosenTimer, int timerFrequency );

void deInitTimer(int chosenTimer);

void clearMatchIntFlag(int chosenTimer, int matchNumber );

void disableMatchInterrupt(int chosenTimer, int matchNumber );

void enableMatchInterrupt(int chosenTimer, int matchNumber );

void configMatchInterrupt(int chosenTimer, int matchNumber, int matchValue, int resetOnMatch );

void initNonBlockingDelay(int us, int chosenTimer, int matchNumber, int timerFreq);




#define CCU1_TIMER0_BASE	0x40051520
#define CCU1_TIMER1_BASE	0x40051528
#define CCU1_TIMER2_BASE	0x40051618
#define CCU1_TIMER3_BASE	0x40051620

#define CCU1_TIMER0	((CCU_CFGSTAT_T*) CCU1_TIMER0_BASE)
#define CCU1_TIMER1	((CCU_CFGSTAT_T*) CCU1_TIMER1_BASE)
#define CCU1_TIMER2	((CCU_CFGSTAT_T*) CCU1_TIMER2_BASE)
#define CCU1_TIMER3	((CCU_CFGSTAT_T*) CCU1_TIMER3_BASE)

// CCU clock config/status register pair
typedef struct {
	unsigned int	CFG;					// CCU clock configuration register
	unsigned		STAT;					// CCU clock status register
} CCU_CFGSTAT_T;

/* @brief enable timer clock. */
void CCU_enableTimerClock( int chosenTimer );




