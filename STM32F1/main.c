#include "gpio.h"					//we use F_CPU + gpio functions
#include "delay.h"					//we use software delays
#include "coretick.h"				//we use dwt
#include "systick.h"				//we use systick
#include "rtc_sw.h"					//we ues software rtc

//hardware configuration
#define LEDG_PORT		GPIOC
#define LEDG			(1<<9)		//green led on PC9 on Discovery board

#define LEDB_PORT		GPIOC
#define LEDB			(1<<8)		//blue led on PC8 on Discovery board

#define LED_PORT		LEDG_PORT
#define LED				LEDG
//end hardware configuration

//global defines

//global variables

int main(void) {
	time_t time_now, time_last;

	mcu_init();									//reset the  mcu
	coretick_init();							//reset coretick
	systick_init();								//initialize systick
	time_now = time_last = time_get();			//initialize time_now/time_last -> time set to advance every second

	//initialize the pins to outout
	IO_OUT(LEDG_PORT, LEDG);					//ledg/b as output
	IO_OUT(LEDB_PORT, LEDB);

	ei();										//enable global interrupts
	while (1) {
		//time_now = time_update(coreticks());	//update time - using coreticks
		time_now = time_update(systicks());	//update time - using systicks
		if (time_now ^ time_last) {				//if time has elapsed
			time_last = time_now;				//update time_last
			IO_FLP(LEDG_PORT, LEDG);			//flip ledg
		}
		//delay_ms(100);						//waste sometime
	};
}
