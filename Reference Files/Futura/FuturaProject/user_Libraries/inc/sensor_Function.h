#ifndef SENSOR_FUNCTION_H
#define SENSOR_FUNCTION_H 

#include <stm32f4xx.h>

extern int reflectionRate;

extern int32_t volMeter;
extern int32_t voltage;
extern int32_t LFSensor;
extern int32_t RFSensor;
extern int32_t DLSensor;
extern int32_t DRSensor;
extern int32_t Outz;
extern int32_t aSpeed;
extern int32_t angle;

void readSensor(void);
void readGyro(void);
void readVolMeter(void);
void lowBatCheck(void);

#endif
