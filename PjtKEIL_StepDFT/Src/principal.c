
#include "DriverJeuLaser.h"
extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal;

int v;
int i;
int dft[64];
short dma_buf[64];

void Callback() {
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
		for (i = 0; i<64; i++) {
			v = DFT_ModuleAuCarre(dma_buf, i);
			dft[i] = v;
		}
	
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();
Systick_Period_ff(5 * 72 * 1000);
Systick_Prio_IT( 1, Callback);
SysTick_On;
SysTick_Enable_IT;

Init_TimingADC_ActiveADC_ff(ADC1, 72);
Single_Channel_ADC(ADC1, 2);
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225);
Init_ADC1_DMA1( 0, dma_buf );

	
	

//============================================================================	
	
	
while	(1) {}
}
