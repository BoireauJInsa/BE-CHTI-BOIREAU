

#include "DriverJeuLaser.h"

void timer_callback(void);

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

	
Timer_1234_Init_ff(TIM4, 91 * 72); //91ms
Active_IT_Debordement_Timer( TIM4, 2, timer_callback);
	


	
	

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
