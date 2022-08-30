#include "loadcell.h"

#ifdef LOADCELL4_HSH
LoadCell4_HSH lc4[LC4_COUNT];
float tare_offset[LC4_COUNT] = {0.0f};
float polarity[LC4_COUNT] = {-1.0f, 1.0f};

void setLC4() {
    Wire.setClock(400000);
    Wire.begin();
    for (uint8_t i = 0; i < LC4_COUNT; i++) {
        lc4[i].setWireObj(&Wire);
        lc4[i].cfg_setup(LC4_INTPIN[i], LC4_ENPIN[i], 400000, LC4_I2C_ADDRESS[i]);
        lc4[i].init();
        lc4[i].restartAndWait(100);
    }

    if (LC4_CHANGE_SETTING) {
        lc4[0].power_dev(LOADCELL4_PWR_OFF);
        delay(3000);
        lc4[0].power_dev(LOADCELL4_PWR_ON);

        lc4[0].start_cmd_mode();
        delay(3);
        Serial.println("WRITING EEPROM");
        lc4[0].write_eeprom(LOADCELL4_EEPROM_CONFIG_1, 0x0001);
        // lc4[0].write_eeprom(LOADCELL4_EEPROM_BRIDGE_CONFIG, 0x0BB8);
        delay(15);

        for (int i = 0; i < 0x14; i++) {
            Serial.println("READING EEPROM");
            lc4[0].read_eeprom(i);
            delay(10);
        }

        lc4[0].end_cmd_mode();
        delay(2);
        lc4[0].restartAndWait(1000);
    }
}
void readLC4EEPROM(uint8_t id, uint8_t cmd_byte) {
    lc4[id].power_dev(LOADCELL4_PWR_OFF);
    delay(1000);
    lc4[id].power_dev(LOADCELL4_PWR_ON);
    lc4[id].start_cmd_mode();
    delay(3);
    lc4[id].read_eeprom(cmd_byte);
    lc4[id].end_cmd_mode();
    delay(1000);
    lc4[id].restartAndWait(1000);
}
void writeLC4EEPROM(uint8_t id, uint8_t cmd_byte, uint16_t data_word) {
    lc4[id].power_dev(LOADCELL4_PWR_OFF);
    delay(1000);
    lc4[id].power_dev(LOADCELL4_PWR_ON);
    lc4[id].start_cmd_mode();
    delay(3);
    lc4[id].write_eeprom(cmd_byte, data_word);
    lc4[id].end_cmd_mode();
    delay(1000);
    lc4[id].restartAndWait(1000);
}
float readLC4(uint8_t id) { return lc4[id].get_raw_weight_data(1); }
float read_Force(uint8_t id) { return (readLC4(id) - tare_offset[id]) * read2force * polarity[id]; }
void tare(uint16_t count){
    for (uint8_t id = 0; id < LC4_COUNT; id++){
        lc4[id].tare(count);
        DEBUG_SERIAL.print("TARE VALUE of LOADCELL ID" + String(id) + ":");
        DEBUG_SERIAL.println(tare_offset[id] = lc4[id].getOffset());    
        lc4[id].restartAndWait(100);
    }
}
void tare(uint8_t id, uint16_t count) {
    lc4[id].tare(count);
    DEBUG_SERIAL.print("TARE VALUE of LOADCELL ID" + String(id) + ":");
    DEBUG_SERIAL.println(tare_offset[id] = lc4[id].getOffset());    
    lc4[id].restartAndWait(100);
}
#endif