#include "mode.h"

#include <queue>

PID_HSH pid[DXL_COUNT];

int32_t pPos[DXL_COUNT], pVel[DXL_COUNT];
int16_t pPWM[DXL_COUNT], pCur[DXL_COUNT];

int32_t tPos[DXL_COUNT], tVel[DXL_COUNT];
int16_t tPWM[DXL_COUNT], tCur[DXL_COUNT];

int32_t iPos[DXL_COUNT];

float pForce[LC4_COUNT];
float tForce[LC4_COUNT];

float force_offset[LC4_COUNT];

double d_pPos[DXL_COUNT], d_pVel[DXL_COUNT];
double d_pPWM[DXL_COUNT], d_pCur[DXL_COUNT];

double d_tPos[DXL_COUNT], d_tVel[DXL_COUNT];
double d_tPWM[DXL_COUNT], d_tCur[DXL_COUNT];

double d_pForce[LC4_COUNT];
double d_tForce[LC4_COUNT];
std::vector<std::deque<float>> q_vector;
void initializeQueue(uint16_t size) {
    std::queue<float> k;
    for (uint8_t i = 0; i < LC4_COUNT; i++) {
        q_vector.push_back(std::deque<float>());
        for (uint16_t j = 0; j < size; j++) {
            q_vector[i].push_back(0.0);
        }
    }
}
void initializeQueue() {
    std::queue<float> k;
    for (uint8_t i = 0; i < LC4_COUNT; i++) {
        q_vector.push_back(std::deque<float>());
        for (uint16_t j = 0; j < dxl_force_queue_size[i]; j++) {
            q_vector[i].push_back(0.0);
        }
    }
}
void setupSpringMode(uint8_t id) {
    pid[id].setPIDCoeffs(PID_KP, PID_KI, PID_KD);
    pid[id].setPeriodinMicroseconds(1000);
    pid[id].setPIDBuffers(&d_tPWM[id], &d_pForce[id], &d_tForce[id]);
    pid[id].setControlLimits(-dxl_pwm_limit[id], dxl_pwm_limit[id]);
}
void runSpringMode(Dynamixel* dxl, uint8_t id, float stiffness) {
    updatePPos(dxl, id);
    d_pForce[id] = read_Force(id);
    d_tForce[id] = (pPos[id] - 3) * 13;
    pid[id].computePID();
    dxl->goalPwm(id, static_cast<int16_t>(d_pPWM[id]));
}
void setupAdmittanceControlMode(uint8_t id) {}
void runAdmittanceControlMode(Dynamixel* dxl, uint8_t id, float admittance) {
    pForce[id] = read_Force(id);
    tPos[id] = iPos[id] + static_cast<int32_t>(admittance * pForce[id]);
    dxl->goalPosition(dxl_id[id], tPos[id]);
}
void runAdmAvgControlMode(Dynamixel* dxl, uint8_t id, float admittance) {
    double avg_Force = 0.0;
    q_vector[id].pop_front();
    q_vector[id].push_back(read_Force(id));

    for (uint16_t j = 0; j < q_vector[id].size(); j++) {
        avg_Force += (q_vector[id])[j];
    }

    avg_Force /= q_vector[id].size();
    pForce[id] = static_cast<float>(avg_Force);
    tPos[id] = iPos[id] + static_cast<int32_t>(admittance * pForce[id]);
    dxl->goalPosition(dxl_id[id], tPos[id]);
}
void initialUnWind(Dynamixel* dxl) {
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
        initialUnWind(dxl, id);
    }
}
void initialUnWindAtOnce(Dynamixel* dxl) {
    int32_t cPos[DXL_COUNT];
    for (uint8_t id = 0; id < DXL_COUNT; id++) {
        cPos[id] = dxl->presentPosition(dxl_id[id]);
        dxl->torqueEnable(dxl_id[id], false);
        dxl->torqueEnable(dxl_id[id], false);
        dxl->operatingMode(dxl_id[id], 0x04);
        dxl->torqueEnable(dxl_id[id], true);
    }
    for (uint8_t i = 0; i < 150; i++) {
        for (uint8_t id = 0; id < DXL_COUNT; id++){
            dxl->goalPosition(dxl_id[id], ++cPos[id]);
        }
        delay(10);
    }
}
void initialUnWind(Dynamixel* dxl, uint8_t id) {
    int32_t cPos = dxl->presentPosition(dxl_id[id]);
    dxl->torqueEnable(dxl_id[id], false);
    dxl->torqueEnable(dxl_id[id], false);
    dxl->operatingMode(dxl_id[id], 0x04);
    dxl->torqueEnable(dxl_id[id], true);
    for (uint8_t i = 0; i < 150; i++) {
        dxl->goalPosition(dxl_id[id], ++cPos);
        delay(10);
    }
}
void saveInitialFlexorPos(Dynamixel* dxl, uint8_t id, String method) {
    int32_t cPos = dxl->presentPosition(dxl_id[id]);
    int32_t iPos_temp = cPos;
    bool togo = true;
    if (method.equals("no-slack")) {
        dxl->torqueEnable(dxl_id[id], false);
        dxl->operatingMode(dxl_id[id], 0x04);
        dxl->torqueEnable(dxl_id[id], true);
        do {
            dxl->goalPosition(dxl_id[id], --iPos_temp);
            delay(20);
            for (uint8_t i = 0; i < LC4_COUNT; i++) {
                pForce[i] = read_Force(i);
                togo &= pForce[i] < 0.14;
            }
        } while (togo);
        iPos[id] = iPos_temp;
        tPos[id] = iPos[id];
        printDxlPos(dxl);
    }
}
void saveInitialFlexorPos(Dynamixel* dxl, String method) {
    for (uint8_t id = LC4_COUNT; id < DXL_COUNT; id++) {
        saveInitialFlexorPos(dxl, id, method);
    }
}
void updatePPos(Dynamixel* dxl, uint8_t id) { pPos[id] = dxl->presentPosition(dxl_id[id]); }
void saveInitialPos(Dynamixel* dxl, String method) {
    for (uint8_t id = 0; id < LC4_COUNT; id++) {
        saveInitialPos(dxl, id, method);
    }
}
void saveInitialPos(Dynamixel* dxl, uint8_t id, String method) {
    int32_t cPos = dxl->presentPosition(dxl_id[id]);
    int32_t iPos_temp = cPos;
    uint16_t tick = 0;
    if (method.equals("no-slack")) {
        dxl->torqueEnable(dxl_id[id], false);
        dxl->operatingMode(dxl_id[id], 0x04);
        dxl->torqueEnable(dxl_id[id], true);
        do {
            dxl->goalPosition(dxl_id[id], --iPos_temp);
            delay(20);
        } while (read_Force(id) < 0.08);
        iPos[id] = iPos_temp;
        printDxlPos(dxl);
    }
}