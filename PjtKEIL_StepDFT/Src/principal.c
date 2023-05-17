
#include "DriverJeuLaser.h"
#include "GestionSon.h"
#include "Affichage_Valise.h"



extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal;

#define NBJOUEURS 6
#define F1 85
#define F2 90
#define F3 95
#define F4 100
#define F5 115
#define F6 120
#define SEUIL 2097152
#define SEUILCOMPTE 50
int tabScores[NBJOUEURS];
int tabVerif[NBJOUEURS];
int freqs[6] = {F1/5, F2/5, F3/5, F4/5, F5/5, F6/5} ;



int dft[64];
short dma_buf[64];

void Callback() {
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
		for (int i = 0; i<64; i++) {
			int value =  DFT_ModuleAuCarre(dma_buf, i);
			dft[i] = value;
		}
		
		for (int i = 0; i<NBJOUEURS; i++) {
			if (tabVerif[i] > 0) {
				tabVerif[i]--;
			} else if (dft[freqs[i]] > SEUIL) {
				tabScores[i]++;
				Start_Son();
				tabVerif[i] = SEUILCOMPTE;
			}
		}
	
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();
Systick_Period_ff(5 * 72 * 1000);
Systick_Prio_IT( 1, Callback);
SysTick_On;
SysTick_Enable_IT;

Timer_1234_Init_ff(TIM4, 91 * 72); //91mics
Active_IT_Debordement_Timer( TIM4, 2, timer_callback);
PWM_Init_ff( TIM3, 3, 720 );
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

Init_TimingADC_ActiveADC_ff(ADC1, 72);
Single_Channel_ADC(ADC1, 2);
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225);
Init_ADC1_DMA1( 0, dma_buf );

	
	

//============================================================================	
	
	
while	(1) {

}
}
