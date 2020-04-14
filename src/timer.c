#include "gpio.h"
#include "board_map.h"
#include "interrupts.h"
#include "dma.h"
#include "timer.h"

//Resets the TC and PC registers on the next clock positive edge.
void resetOnNextEdge( LPC_TIMER_T* pTimerStruct ){
	pTimerStruct->TCR |= 0x02; //pongo un uno en el bit CRST
}

//Don't reset the TC and PC registers on the next clock positive edge.
void dontResetOnNextEdge( LPC_TIMER_T* pTimerStruct ){
	pTimerStruct->TCR &= ~(0x02); //pido que no se resetee
}

//enables timer.
void enableTimer( LPC_TIMER_T* pTimerStruct ){
	pTimerStruct->TCR |= 0x01; //si pongo un uno en el bit cero del TCR, el CEN, se habilita el conteo
}

//returns a pointer to the chosen timer struct.
LPC_TIMER_T* getPtrStruct(int num_timer){
	switch(num_timer)
	{
	case(TIMER0):
		return LPC_TIMER0;
		break;
	case(TIMER1):
		return LPC_TIMER1;
		break;
	case(TIMER2):
		return LPC_TIMER2;
		break;
	case(TIMER3):
		return LPC_TIMER3;
		break;
	default:
		return 0;
	}
}

//chose timer mode for the selected timer.
//Note: There are 2 modes for each timer: Counter and Timer
void setTimerMode (LPC_TIMER_T* pTimerStruct ){
	pTimerStruct->CTCR &= ~(0x1); //pone todo en cero para elegir timer
}


//set match value. This value is continuosly compared with
//TC register value and can trigger some events if they are configured.
void setMatchValue(LPC_TIMER_T* timerStruct, int matchNumber, int matchValue){
	timerStruct->MR[matchNumber] = matchValue;
}

//set a certain frequency on a timer.
//The maths are: PPCLK * (PR-1) = P
//Where: PCLK = 1/PCLK_MAX_FREQ , P = 1/frequency, PR = value of PR register
void setTimerFrequency(LPC_TIMER_T* timerStruct, int frequency){
	timerStruct->PR = ( (int) MAX_FREC/frequency - 1 );
}

//config the timer to reset for match.
void setResetOnMatch( LPC_TIMER_T* timerStruct, int matchNumber ){
	timerStruct->MCR |= (0x2 << ( matchNumber*3 ) );
}

int readTimer(int chosenTimer){
	LPC_TIMER_T* pTimerStruct = getPtrStruct(chosenTimer);
	int count = pTimerStruct->TC;

	return count;
}

//function to init timer0/1/2/3
//pointer to register TC, this registers have the actual count of the timer */
int* initTimer(int chosenTimer, int timerFrequency ){
	LPC_TIMER_T* pTimerStruct = getPtrStruct( chosenTimer );

	//CCU_enableTimerClock( chosenTimer );

	setTimerMode( pTimerStruct );

	setTimerFrequency( pTimerStruct, timerFrequency );

	resetOnNextEdge( pTimerStruct );

	enableTimer( pTimerStruct );

	dontResetOnNextEdge( pTimerStruct );

	return (int*) &( pTimerStruct->TC );
}

//stop timer
void deInitTimer(int chosenTimer){
	LPC_TIMER_T* timerStruct = getPtrStruct( chosenTimer );
	timerStruct->TCR &= ~(0x1);
}

//clear match interrupt flag of a timer.
void clearMatchIntFlag(int chosenTimer, int matchNumber ){
	LPC_TIMER_T* timerStruct = getPtrStruct( chosenTimer );
	timerStruct->IR = (0x1 << matchNumber);
}

//disable interrupt for match.
void disableMatchInterrupt(int chosenTimer, int matchNumber ){
	LPC_TIMER_T* timerStruct = getPtrStruct( chosenTimer );
	timerStruct->MCR &= ~(0x1 << ( matchNumber*3 ) );
}

//enable interrupt for match.
void enableMatchInterrupt(int chosenTimer, int matchNumber ){
	LPC_TIMER_T* timerStruct = getPtrStruct( chosenTimer );
	timerStruct->MCR |= (0x1 << ( matchNumber*3 ) );
}

//config timer match interrupts.
void configMatchInterrupt(int chosenTimer, int matchNumber, int matchValue, int resetOnMatch ){
	LPC_TIMER_T* timerStruct = getPtrStruct( chosenTimer );

	enableMatchInterrupt( chosenTimer, matchNumber );

	if( resetOnMatch == 1 )
		setResetOnMatch( timerStruct, matchNumber );

	setMatchValue( timerStruct, matchNumber, matchValue );
}

void initNonBlockingDelay(int us, int chosenTimer, int matchNumber, int timerFreq){
//	Timer_deInit( chosenTimer );

	int matchValue = 0;
	if( us > 1000000 )
		matchValue = ( (us / 1000000 ) * timerFreq );
	else
		matchValue = ( (us * timerFreq) / 1000000 );

	configMatchInterrupt(chosenTimer, matchNumber, matchValue, 1);

	initTimer(chosenTimer, timerFreq);

	switch(chosenTimer){
		case TIMER0:
			configNVIC (12);
			break;
		case TIMER1:
			configNVIC (13);
			break;
		case TIMER2:
			configNVIC (14);
			break;
		case TIMER3:
			configNVIC (15);
			break;
		};
}




/* @brief Enables a peripheral clock. */
//void CCU_clockEnable( CHIP_CCU_CLK_T clk ){
//	CCU1->CLKCCU[clk].CFG = 1;
//}

/* @brief enable timer clock. */
void CCU_enableTimerClock(int chosenTimer ){
	switch(chosenTimer){
		case TIMER0:
			CCU1_TIMER0->CFG |= 1;
			break;
		case TIMER1:
			CCU1_TIMER1->CFG |= 1;
			break;
		case TIMER2:
			CCU1_TIMER2->CFG |= 1;
			break;
		case TIMER3:
			CCU1_TIMER3->CFG |= 1;
			break;
		};
}
