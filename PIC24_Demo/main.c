#include "config.h"					//configuration words - for C30. Use config.h for XC16
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "ticks2RTC.h"				//we use software rtc
#include "systick.h"

//hardware configuration
#define LED_PORT			PORTB
#define LED_DDR				TRISB
#define LED					(1<<0)
//end hardware configuration

//global defines

//global variables
struct tm rtc_time;

int main(void) {
	static time_t time_last=0;
	time_t time0;
	
	mcu_init();							//reset the mcu
	systick_init();						//initialize systick
	//initilize the time
	time_set(0);						//initialize time
#if 1
	//alternatively, set time to: June 4th, 2006, 3:2:1
  	rtc_time.tm_sec = 1;
  	rtc_time.tm_min = 2;
  	rtc_time.tm_hour= 3;
  	rtc_time.tm_mday= 4;				//4th
  	rtc_time.tm_mon = 5;				//0->Jan, ..., 5->June
  	rtc_time.tm_year= 106;				//year since 1900 -> 2006
  	time_set(mktime(&rtc_time));		//set time to May 4th, 2006
#endif  
	IO_OUT(LED_DDR, LED);				//led as output
	ei();								//enable interrupts
	while (1) {
		time0=time_update(ticks());		//update time
		if (time0 != time_last) {		//time has advanced
			time_last = time0;			//update time_last
			IO_FLP(LED_PORT, LED);		//flip the led
		}
	}
}
