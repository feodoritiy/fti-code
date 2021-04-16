#include "delay.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
void delay(size_t milliseconds) {
   Sleep(milliseconds);
}
#else
void delay(size_t milliseconds) {
   size_t microseconds = milliseconds * 1000;
   usleep(microseconds);
}
#endif
