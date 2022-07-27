#include "Glove.h"
#include "func.h"
#include "setup.h"
#include "loadcell.h"
#include "adc_glove.h"
#include "dxl_op.h"
#include "mode.h"


unsigned int microSec;


Dynamixel dxl(PIN_RTS);
ADC *adc = new ADC();
ADS1115_WE adcext = ADS1115_WE(EXTADC_I2C_ADDRESS);
// PID_HSH pid1 = PID_HSH(PID_KP, PID_KI, PID_KD, PID_UPDATE_US, )
void setup() {
    Wire.begin();    
    analogWriteFrequency(22, 180);
    analogWrite(22, 7);
    DYNAMIXEL_SERIAL.begin(DYNAMIXEL_BAUDRATE, SERIAL_8N1_HALF_DUPLEX);
    setDebugSerial(1000000);    
    setDxl(dxl);
    setextADC(adcext);
    setTimers();
    setPinModes();
    setLC4();    
    // readLC4EEPROM(0, 0x01);    
    // readLC4EEPROM(1, 0x01);    
    writeLC4EEPROM(0, 0x0F, 0x0AB8);    
    printDxlPos(dxl);
    //saveInitialPos(dxl, 0, "no-slack");
}

void loop() {    
    microSec = micros();
    Serial.printf("FORCE: %f [N]\t%f [N]\t", read_Force(0), read_Force(1));
    Serial.printf("DELAY: %d\n", micros() - microSec);
    delay(1000);
}