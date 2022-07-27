#include "Glove.h"
#include "func.h"
#include "loadcell.h"
#include "dxl_op.h"

#ifndef MODE_H
#define MODE_H

void setupSpringMode(uint8_t id);
void runSpringMode(Dynamixel dxl, uint8_t id, float stiffness);
void saveInitialPos(Dynamixel dxl, uint8_t id, String method);

#endif
