#include "dxl_op.h"

void setDxl(Dynamixel* dxl) {
    dxl->attach(DYNAMIXEL_SERIAL, DYNAMIXEL_BAUDRATE);
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
        dxl->addModel<DxlModel::X>(dxl_id[id]);
    }
    bool connected = true;
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
        if (!dxl->ping(dxl_id[id])) {
            connected = false;
            DEBUG_SERIAL.println("FAILED ID: " + String(dxl_id[id]));
            break;            
        }        
        dxl->torqueEnable(dxl_id[id], false);
    }    
    if (connected) {
        DEBUG_SERIAL.println("DXL setup done!");
    } else {
        DEBUG_SERIAL.println("DXL setup failed!");
        delay(500);
        SCB_AIRCR = 0x05FA0004;
    }
    delay(2000);
    return;
}
void setReturnDelay(Dynamixel *dxl, uint8_t id, uint8_t delayTime){
    dxl->returnDelayTime(dxl_id[id], delayTime);
}
void setPidGain(Dynamixel* dxl){
    for (uint8_t id = 0; id < DXL_COUNT; id ++){
        setPidGain(dxl, id);
    }
}
void setPidGain(Dynamixel* dxl, uint8_t id){    
    switch(dxl->operatingMode(dxl_id[id])){
        case 0x03 || 0x04:
        dxl->positionPGain(dxl_id[id], dxl_position_Pgain[id]);
        dxl->positionIGain(dxl_id[id], dxl_position_Igain[id]);
        dxl->positionDGain(dxl_id[id], dxl_position_Dgain[id]);                
        break;
        default:
        break;
    }    
}

void setProfileAcc(Dynamixel* dxl){
    for (uint8_t id = 0; id < DXL_COUNT; id++){
        setProfileAcc(dxl, id);
    }
}
void setProfileAcc(Dynamixel* dxl, uint8_t id){
    dxl->profileAcceleration(dxl_id[id], dxl_profile_acc[id]);
}

void setProfileVel(Dynamixel* dxl){
    for (uint8_t id = 0; id < DXL_COUNT; id++){
        setProfileVel(dxl, id);
    }
}
void setProfileVel(Dynamixel* dxl, uint8_t id){
    dxl->profileVelocity(dxl_id[id], dxl_profile_vel[id]);
}

void printDxlPos(Dynamixel* dxl){
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
    int pos = dxl->presentPosition(dxl_id[id]);
    if (pos == -1) {
      DEBUG_SERIAL.printf("MOTOR%d ERROR: %d\t", dxl_id[id], dxl->hardwareErrorStatus(dxl_id[id]));
      continue;
    } else{
        DEBUG_SERIAL.printf("MOTOR %d POS: %d\t", dxl_id[id], pos);
        dxl->verbose(dxl_id[id]);
    }
  }
}
void updatePresentPos(Dynamixel* dxl, int32_t* pos_buffer){    
    for (uint8_t id = 0; id < DXL_COUNT; id++){
        updatePresentPos(dxl, &pos_buffer[id], id);
    }    
}
void updatePresentPos(Dynamixel* dxl, int32_t* pos_buffer, uint8_t id){    
    pos_buffer[id] = dxl->presentPosition(dxl_id[id]);    
}
void updatePresentPos(Dynamixel* dxl, int32_t* pos_buffer, double* d_pos_buffer, uint8_t id){    
    pos_buffer[id] = dxl->presentPosition(dxl_id[id]);    
    d_pos_buffer[id] = static_cast<double>(pos_buffer[id]);
}
void updatePresentPWM(Dynamixel* dxl, int32_t* pwm_buffer, double* d_pwm_buffer, uint8_t id){    
    pwm_buffer[id] = dxl->presentPwm(dxl_id[id]);    
    d_pwm_buffer[id] = static_cast<double>(pwm_buffer[id]);
}
