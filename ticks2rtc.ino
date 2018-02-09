//ticks2rtc.ino

#include <time.h>				//use time library

//global defines
#define TICKS_PER_SEC			(1000)		//1000ms = 1second, as millis() is used for ticks

//global variables
volatile time_t time_now=0;	//current time, in second

//update time
time_t time_update(uint32_t ticks) {
	static uint32_t ticks_last=0;

	if (ticks - ticks_last >= TICKS_PER_SEC) {
		ticks_last += TICKS_PER_SEC;	//update ticks
		time_now+=1;					//increment time
	}
	return time_now;
}

//get time
time_t time_get(void) {
	return time_now;
}

//set time
time_t time_set(time_t time) {
	return time_now = time;
}

int led = 13;
struct tm rtc_time;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);							//serial at 9600bps

  //set time
  time_set(100000ul);							//initialize time to 2000/1/1+100000 seconds = Jan 2, 3:46:40, 2000
#if 1
  //alternatively, set time to: June 4th, 2006, 3:2:1
  rtc_time.tm_sec = 1;
  rtc_time.tm_min = 2;
  rtc_time.tm_hour= 3;
  rtc_time.tm_mday= 4;							//4th
  rtc_time.tm_mon = 5;							//0->Jan, ..., 5->June
  rtc_time.tm_year= 106;						//year since 1900 -> 2006
  time_set(mktime(&rtc_time));					//set time to May 4th, 2006
#endif  
}

void loop() {
	static time_t time_last=0;
	time_t time0;

	//update time and blink led once per second
	time0 = time_update(millis());
	if (time_last ^ time0) {					//enough time has passed
		time_last = time0;						//update time_last
		digitalWrite(led, !digitalRead(led));	//flip led

		//convert time_t to string
		Serial.print("the time is: "); Serial.print(ctime(&time0)); Serial.println(".");
	}
}
