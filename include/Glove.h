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
#include "LoadCell4_HSH.h"


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
#define DYNAMIXEL_SERIAL                Serial1
#define PIN_RTS                         1
#define DYNAMIXEL_BAUDRATE              2000000
#define DXL_COUNT                       3
#define READ_WAIT_US                    200

// IIC Config.
#define EXTADC_I2C_ADDRESS              0x48  
#define EXTADC_CHANGE_SETTING           false
#define LC4_CHANGE_SETTING              false
const uint8_t LC4_I2C_ADDRESS[] = {0x24, 0x27};

// LOG Settings
#define DEBUG_SERIAL                    Serial
#define PACKET_LOG                      false
#define P_LOG                           false
#define SERIAL_DATAMODE                 false

// LOADCELL CONFIG.
#define LC4_COUNT                       2
#define FS_LOAD                         20 * 9.81
#define RATED_OUTPUT                    1.416

// PID Settings - NOT USED IN CURRENT VERSION
#define PID_UPDATE_US                   19999
#define PID_KP                          0.7
#define PID_KI                          0.1
#define PID_KD                          0.005
#define LC_SCALER                       0.3f
#define PID_IMAX                        (3000000 / PID_UPDATE_US)
#define PID_AW                          200
#define SINE_FREQ                       0.5
#define TPOS_OFFSET                     100
#define ON_DISTURB                      false

const uint8_t dxl_id[DXL_COUNT] = {1, 2, 11};
const uint16_t dxl_pwm_limit[DXL_COUNT] = {880, 880, 880};
const uint16_t dxl_position_Pgain[DXL_COUNT] = {100, 100, 400};
const uint16_t dxl_position_Igain[DXL_COUNT] = {0, 0, 100};
const uint16_t dxl_position_Dgain[DXL_COUNT] = {40, 40, 0};
const uint16_t dxl_admittance[DXL_COUNT] = {400, 400, 0};
const uint16_t dxl_force_queue_size[DXL_COUNT] = {50, 50, 0};



const uint16_t dxl_profile_acc[DXL_COUNT] = {1, 1, 1};
const uint16_t dxl_profile_vel[DXL_COUNT] = {50, 50, 50};


  
#endif