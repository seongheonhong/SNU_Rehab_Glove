#include "Glove.h"

const uint8_t dxl_id[] = {1, 2};
uint8_t dxl_count = sizeof(dxl_id) / sizeof(dxl_id[0]);
unsigned int microSec;

Dynamixel dxl(20);
ADC *adc = new ADC();
ADS1115_WE adcext = ADS1115_WE(EXTADC_I2C_ADDRESS);
// PID_HSH pid1 = PID_HSH(PID_KP, PID_KI, PID_KD, PID_UPDATE_US, )
void setup() {
  Wire.begin();
  DYNAMIXEL_SERIAL.begin(DYNAMIXEL_BAUDRATE, SERIAL_8N1_HALF_DUPLEX);
  dxl.attach(DYNAMIXEL_SERIAL, DYNAMIXEL_BAUDRATE);
  for (uint8_t i = 0; i < dxl_count; i++){
    dxl.addModel<DxlModel::X>(dxl_id[i]);           
  }    
  delay(2000);
    
  setextADC(adcext); 
  setTimers();
  setPinModes();
  startDebugSerial(1000000);
  setLC4();
  for (uint8_t i = 0; i < dxl_count; i++){    
    DEBUG_SERIAL.printf("ID: %d\tPOS: %d\n", dxl_id[i], dxl.presentPosition(dxl_id[i]));
  }    
}

void loop() {

  microSec = micros();
  Serial.printf("FORCE: %f [N]\t%f [N]\t", read_Force(0), read_Force(1));  
  Serial.printf("DELAY: %d\n", micros() - microSec);
  delay(400);  
}