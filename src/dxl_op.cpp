#include "dxl_op.h"

void setDxl(Dynamixel dxl) {
    dxl.attach(DYNAMIXEL_SERIAL, DYNAMIXEL_BAUDRATE);
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
        dxl.addModel<DxlModel::X>(dxl_id[id]);
    }
    bool connected = true;
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
        if (!dxl.ping(dxl_id[id])) {
            connected = false;
            break;
        }
        dxl.torqueEnable(dxl_id[id], false);
    }
    if (connected) {
        DEBUG_SERIAL.println("DXL setup done!");
    } else {
        DEBUG_SERIAL.println("DXL setup failed!");
    }
    delay(100);
}

void printDxlPos(Dynamixel dxl){
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
    int pos = dxl.presentPosition(dxl_id[id]);
    if (pos == -1) {
      DEBUG_SERIAL.printf("MOTOR%d ERROR: %d\t", id, dxl.hardwareErrorStatus(id));
      continue;
    } else{
        DEBUG_SERIAL.printf("MOTOR %d POS: %d\t", id, pos);
        dxl.verbose(id);
    }
  }
  DEBUG_SERIAL.println();
}
void updatePresentPos(Dynamixel dxl, int32_t* pos_buffer, uint8_t id){    
    pos_buffer[id] = dxl.presentPosition(dxl_id[id]);    
}
void updatePresentPos(Dynamixel dxl, int32_t* pos_buffer, double* d_pos_buffer, uint8_t id){    
    pos_buffer[id] = dxl.presentPosition(dxl_id[id]);    
    d_pos_buffer[id] = static_cast<double>(pos_buffer[id]);
}
void updatePresentPWM(Dynamixel dxl, int32_t* pwm_buffer, double* d_pwm_buffer, uint8_t id){    
    pwm_buffer[id] = dxl.presentPwm(dxl_id[id]);    
    d_pwm_buffer[id] = static_cast<double>(pwm_buffer[id]);
}
