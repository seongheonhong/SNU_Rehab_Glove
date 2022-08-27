#include "Glove.h"
#include "func.h"
#include "loadcell.h"
#include "dxl_op.h"

#ifndef MODE_H
#define MODE_H

void initializeQueue(uint16_t size);
void initializeQueue(void);
void setupSpringMode(uint8_t id);
void runSpringMode(Dynamixel* dxl, uint8_t id, float stiffness);
void runAdmittanceControlMode(Dynamixel* dxl, uint8_t id, float admittance);
void runAdmAvgControlMode(Dynamixel* dxl, uint8_t id, float admittance);
void updatePPos(Dynamixel* dxl, uint8_t id);
void initialUnWind(Dynamixel* dxl);
void initialUnWind(Dynamixel* dxl, uint8_t id);
void initialUnWindAtOnce(Dynamixel* dxl);
void saveInitialPos(Dynamixel* dxl, String method);
void saveInitialPos(Dynamixel* dxl, uint8_t id, String method);
void saveInitialFlexorPos(Dynamixel* dxl, String method);
void saveInitialFlexorPos(Dynamixel* dxl, uint8_t id, String method);

#endif
