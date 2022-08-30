#include "func.h"
extern int32_t tPos[DXL_COUNT], pPos[DXL_COUNT];
extern Dynamixel dxl;
uint8_t findInd(uint8_t* arr, uint8_t value){
    uint8_t i = 0;
    for (i = 0; i < sizeof(arr); i++){
        if (arr[i] == value){
            return i;
        }
    }
    return 0;    
}

