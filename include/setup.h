#include "Glove.h"

#ifndef SETUP_H
#define SETUP_H

void setLC4(void);
void setTimers(void);
void setPinModes(void);
void setDebugSerial(unsigned long _baudrate);
void setextADC(ADS1115_WE* adcext);

#endif