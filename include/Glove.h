#ifndef GLOVE_H
  #define GLOVE_H

  #include <CRC16.h>
  #include <CRC.h>
  #include <PID_HSH.h>
  #include <Bounce.h>
  #include <Wire.h>
  #include <TimerThree.h>
  #include <ADC.h>
  #include <AnalogBufferDMA.h>
  //#include <ADC_util.h>
  #include <ADS1115_WE.h> 
  #include <Dynamixel.h>
  #include <LoadCell4_HSH.h>


  // Pin Configuration
  #define BUTTON1                         7
  #define BUTTON2                         3
  #define SWITCH1                         15
  const uint8_t LC4_INTPIN[] = {10, 8};
  const uint8_t LC4_ENPIN[] = {11, 9};  

  // Loadcell Config.
  #define LOADCELL_RO_MVV                 1.416
  #define AMP_GAIN                        96
  #define AMP_RESBITS                     14
  #define LOADCELL_FS                     20 * 9.81

  // Dynamixel Config.
  #define DYNAMIXEL_SERIAL                Serial5
  #define PIN_RTS                         11
  #define DYNAMIXEL_BAUDRATE              3000000
  #define DXL_COUNT                       2
  #define READ_WAIT_US                    200

  // IIC Config.
  #define EXTADC_I2C_ADDRESS              0x48  
  #define EXTADC_CHANGE_SETTING           false
  #define LC4_CHANGE_SETTING              false
  const uint8_t LC4_I2C_ADDRESS[] = {0x27, 0x24};

  // LOG Settings
  #define DEBUG_SERIAL                    Serial
  #define PACKET_LOG                      false
  #define P_LOG                           false
  #define SERIAL_DATAMODE                 false

  // LOADCELL CONFIG.
  #define FS_LOAD                         20 * 9.81
  #define RATED_OUTPUT                    1.416

  // PID Settings
  #define PID_UPDATE_US                   996
  #define PID_KP                          0.7
  #define PID_KI                          0.1
  #define PID_KD                          0.005
  #define LC_SCALER                       0.3f
  #define PID_IMAX                        (3000000 / PID_UPDATE_US)
  #define PID_AW                          200
  #define SINE_FREQ                       0.5
  #define PWM1_MAX                        800
  #define TPOS_OFFSET                     100
  #define PWM2_MAX                        300
  #define ON_DISTURB                      false

  void timer3_ISR(void);
  void processADC(void);
  void setLC4(void);
  void setextADC(void);
  void setTimers(void);
  void setPinModes(void);
  void startDebugSerial(unsigned long _baudrate);
  void setextADC(ADS1115_WE adcext);

  uint8_t findInd(uint8_t* arr, uint8_t value);
  float read_Force(uint8_t id);
  
#endif