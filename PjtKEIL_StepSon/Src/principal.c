

#include "DriverJeuLaser.h"
#include "GestionSon.h"


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

	
Timer_1234_Init_ff(TIM4, 91 * 72); //91mics
Active_IT_Debordement_Timer( TIM4, 2, timer_callback);

	
PWM_Init_ff( TIM3, 3, 720 );
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
Systick_Period_ff(72 * 5 * 1000 * 1000);
Systick_Prio_IT( 1, Start_Son);
SysTick_On;
SysTick_Enable_IT;

	
	

//============================================================================	
	
	
while	(1)
	{
	}
}

/*
static int position;

void CallbackSon(void){
	if (position < LongeurSon){
		SortieSon = son[position] * (360 / 32767) + 360
		position = position +1
	}
}
*/
