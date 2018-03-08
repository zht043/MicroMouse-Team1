#include "Initiation.h"
#include "SysTime.h"
#define OneMillSecInterr 1000
void SysTime_Init() {
		SysTick_Init(OneMillSecInterr);
}
void doNothing(void) {
}
