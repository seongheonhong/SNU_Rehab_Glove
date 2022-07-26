#include "Glove.h"

#ifndef DXL_OP_H
#define DXL_OP_H

extern int32_t pPos[DXL_COUNT], pVel[DXL_COUNT];  
extern int32_t tPos[DXL_COUNT], tVel[DXL_COUNT];  
extern int16_t pPWM[DXL_COUNT], pCur[DXL_COUNT];
extern int16_t tPWM[DXL_COUNT], tCur[DXL_COUNT];
extern float pForce[LC4_COUNT];
extern float tForce[LC4_COUNT];
extern double d_pPos[DXL_COUNT], d_pPWM[DXL_COUNT], d_pCur[DXL_COUNT], d_pVel[DXL_COUNT];
extern double d_tPos[DXL_COUNT], d_tPWM[DXL_COUNT], d_tCur[DXL_COUNT], d_tVel[DXL_COUNT];
extern double d_pForce[LC4_COUNT];
extern double d_tForce[LC4_COUNT];

void setDxl(Dynamixel* dxl);
void updatePresentPos(Dynamixel* dxl, int32_t* pos_buffer);
void updatePresentPos(Dynamixel* dxl, int32_t* pos_buffer, uint8_t id);
void updatePresentPWM(Dynamixel* dxl, int32_t* pwm_buffer, uint8_t id);
void setReturnDelay(Dynamixel *dxl, uint8_t id, uint8_t delayTime);
void setPidGain(Dynamixel* dxl);
void setPidGain(Dynamixel* dxl, uint8_t id);
void setProfileAcc(Dynamixel* dxl);
void setProfileAcc(Dynamixel* dxl, uint8_t id);
void setProfileVel(Dynamixel* dxl);
void setProfileVel(Dynamixel* dxl, uint8_t id);
void printDxlPos(Dynamixel* dxl);

#endif