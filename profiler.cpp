#include <Arduino.h>

hw_timer_t *hTimer = NULL;
portMUX_TYPE enterCritical = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCount = 0;
volatile uint32_t isrTicks = 0;
//--------------------------------------------

void ARDUINO_ISR_ATTR onTimer() {

	// Increment the counter and set the time of ISR
	portENTER_CRITICAL_ISR(&enterCritical);
	isrCount = isrCount + 1;
	isrTicks = millis();
	portEXIT_CRITICAL_ISR(&enterCritical);
}

void setup3() {

  // Set hTimer frequency to 1Mhz
  hTimer = timerBegin(1000000);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(hTimer, &onTimer);

}

#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

uint64_t stopStart(int line, char *file, char *fmt, ...)
{
   char buffer[200];
   char unit;

   uint64_t clock = timerReadMicros(hTimer);

   float scale = (float) clock;
   if (scale < 1000)
   {
   	  unit = 'u';
   }
   else if (scale < 1000000)
   {
      unit = 'm';
      scale /= 1000.;
   }
   else
   {
   	  unit = ' ';
   	  scale /= 1000000.;
   }
   va_list args;
   va_start(args, fmt);
   vsprintf(buffer, fmt, args);
   printf(AC_YELLOW"%6.2f %cS %s:%d %s\n"AC_NORMAL,scale, unit,  file, line, buffer);
   va_end(args);
   timerRestart(hTimer);

   return clock;
}

void mem_report() {
    printf("Total heap: %lu\n", ESP.getHeapSize());
    printf("Free heap: %lu\n", ESP.getFreeHeap());
    printf("Total PSRAM: %lu\n", ESP.getPsramSize());
    printf("Free PSRAM: %lu\n", ESP.getFreePsram());
    printf(" built %s %s\n", __DATE__, __TIME__);
}

