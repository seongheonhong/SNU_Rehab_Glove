#include "Glove.h"
#include "func.h"
#include "setup.h"
#include "loadcell.h"
#include "adc_glove.h"
#include "dxl_op.h"
#include "mode.h"


unsigned int microSec;
extern float pForce[LC4_COUNT];
extern int32_t pPos[DXL_COUNT];
extern int32_t iPos[DXL_COUNT];
bool flexor_stop = false;

Dynamixel dxl(PIN_RTS);
ADC *adc = new ADC();
ADS1115_WE adcext = ADS1115_WE(EXTADC_I2C_ADDRESS);
// PID_HSH pid1 = PID_HSH(PID_KP, PID_KI, PID_KD, PID_UPDATE_US, )
void setup() {
    Wire.begin();    
    DYNAMIXEL_SERIAL.begin(DYNAMIXEL_BAUDRATE, SERIAL_HALF_DUPLEX);
    setDebugSerial(1000000);    
    setDxl(&dxl);    
    setReturnDelay(&dxl, 0, 10);
    setReturnDelay(&dxl, 1, 10);
    setPidGain(&dxl);
    initialUnWind(&dxl);
    // setProfileAcc(&dxl);
    // setProfileVel(&dxl);
    setTimers();
    setPinModes();    
    setLC4();     
    tare(240);   
    setextADC(&adcext);    
    saveInitialPos(&dxl, "no-slack");    
    saveInitialFlexorPos(&dxl, "no-slack");
    initializeQueue();
    DEBUG_SERIAL.println("SETUP END");
    setTimers();
    Timer3.attachInterrupt(timer3_ISR);  
}

void loop() {    
    microSec = micros();    
    // DEBUG_SERIAL.println("LOOP ++");
    //DEBUG_SERIAL.printf("FORCE: %f [N]\t%f [N]\n", read_Force(0), read_Force(1));    
    runAdmAvgControlMode(&dxl, 0, dxl_admittance[0]);
    runAdmAvgControlMode(&dxl, 1, dxl_admittance[1]);   
    updatePPos(&dxl, 0);
    updatePPos(&dxl, 1);
    if (!flexor_stop){
        DEBUG_SERIAL.printf("%f\t%f", 0.001*(pPos[0]-iPos[0]), pForce[0]);
        DEBUG_SERIAL.printf("\t%f\t%f", 0.001*(pPos[1]-iPos[1]), pForce[1]);    
        DEBUG_SERIAL.printf("\tFLEXORPOS: %d\n", iPos[2] - tPos[2]);
    }
    //DEBUG_SERIAL.printf("DELAY: %d\tPROFILE: %d\t%d\t", micros() - microSec, dxl.movingStatus(dxl_id[0]), dxl.movingStatus(dxl_id[1]));
    //DEBUG_SERIAL.printf("FORCE%d: %f\tFORCE%d: %f\n", dxl_id[0], pForce[0], dxl_id[1], pForce[1]);
}

void timer3_ISR(void){    
    if (!flexor_stop && ((iPos[2] - tPos[2]) > 1300 || pForce[0] > 2.0 || pForce[1] > 2.0)){
        flexor_stop = true;
        DEBUG_SERIAL.println("Flexor Stop");
        DEBUG_SERIAL.println("IPOS: " + String(iPos[2]) + "TPOS: " + String(tPos[2]));
        dxl.torqueEnable(dxl_id[2], false);
        dxl.torqueEnable(dxl_id[2], false);
    }
    if (!flexor_stop){
        dxl.goalPosition(dxl_id[2], --tPos[2]);                
    }
}
