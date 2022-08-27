#include "Glove.h"

void setPinModes() {
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(SWITCH1, INPUT_PULLUP);
    //  for (uint8_t i = 0; i < 12; i++) pinMode(dacBits[i], OUTPUT);
}

void setextADC(ADS1115_WE* adcext) {
    if (!adcext->init()) Serial.println("ADS1115 not connected!");
    if (EXTADC_CHANGE_SETTING) {
        adcext->setVoltageRange_mV(ADS1115_RANGE_4096);
        adcext->setCompareChannels(ADS1115_COMP_0_GND);
        adcext->setMeasureMode(ADS1115_CONTINUOUS);
    }
}


void setDebugSerial(unsigned long _baudrate) {
    Serial.begin(_baudrate);
    while (!Serial) {
    }
    Serial.println("BEGIN!!");
}

void setTimers() {
    Timer3.initialize(PID_UPDATE_US);  // MAX is 55 ms = 55000
}