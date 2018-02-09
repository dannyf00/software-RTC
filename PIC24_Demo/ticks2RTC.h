#ifndef TICKS2RTC_H
#define TICKS2RTC_H

#include "gpio.h"
#include <time.h>							//we use time.h routines

//global defines
#define TICKS_PER_SEC			(F_CPU)		//timer input = F_CPU

//global variables

//update time
time_t time_update(uint32_t ticks);

//get time
time_t time_get(void);

//set time
time_t time_set(time_t time);

#endif
