#include "mode.h"

PID_HSH pid[DXL_COUNT];

int32_t pPos[DXL_COUNT], pVel[DXL_COUNT];  
int16_t pPWM[DXL_COUNT], pCur[DXL_COUNT];

int32_t tPos[DXL_COUNT], tVel[DXL_COUNT];  
int16_t tPWM[DXL_COUNT], tCur[DXL_COUNT];

int32_t iPos[DXL_COUNT];

float pForce[DXL_COUNT];
float tForce[DXL_COUNT];

double d_pPos[DXL_COUNT], d_pVel[DXL_COUNT];
double d_pPWM[DXL_COUNT], d_pCur[DXL_COUNT];

double d_tPos[DXL_COUNT], d_tVel[DXL_COUNT];
double d_tPWM[DXL_COUNT], d_tCur[DXL_COUNT];

double d_pForce[DXL_COUNT];
double d_tForce[DXL_COUNT];

void setupSpringMode(uint8_t id){        
    pid[id].setPIDCoeffs(PID_KP, PID_KI, PID_KD);
    pid[id].setPeriodinMicroseconds(1000);
    pid[id].setPIDBuffers(&d_tPWM[id], &d_pForce[id], &d_tForce[id]);    
    pid[id].setControlLimits(-dxl_pwm_limit[id], dxl_pwm_limit[id]);
}
void runSpringMode(Dynamixel dxl, uint8_t id, float stiffness){   
    updatePresentPos(dxl, pPos, id);    
    d_pForce[id] = read_Force(id);
    d_tForce[id] = (pPos[id] - 3) * 13;
    
    pid[id].computePID();
    dxl.goalPwm(id, static_cast<int16_t>(d_pPWM[id]));    
    
}
void saveInitialPos(Dynamixel dxl, uint8_t id, String method){
    int32_t cPos = dxl.presentPosition(dxl_id[id]);
    int32_t iPos_temp = cPos;
    uint16_t tick = 0;
    if (method.equals("no-slack")){
        dxl.torqueEnable(dxl_id[id], false);
        dxl.operatingMode(dxl_id[id], 0x04);
        dxl.torqueEnable(dxl_id[id], true);
        do {
            dxl.goalPosition(dxl_id[id], --iPos_temp);
            delay(50);
            DEBUG_SERIAL.println(++tick);
        } while (read_Force(id) < 0.04);
        iPos[id] = iPos_temp;
        printDxlPos(dxl);    
    }
}