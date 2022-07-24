#include <Glove.h>

#ifdef LOADCELL4_HSH

const float read2force = 128 * LOADCELL_FS / (pow(2, (AMP_RESBITS)) * AMP_GAIN * LOADCELL_RO_MVV);
const uint8_t LC4_COUNT = 2;
LoadCell4_HSH lc4[LC4_COUNT];

void setLC4() {
    Wire.begin();
    for (uint8_t i = 0; i < LC4_COUNT; i++) {
        lc4[i].setWireObj(&Wire);
        lc4[i].cfg_setup(LC4_INTPIN[i], LC4_ENPIN[i], 100000, LC4_I2C_ADDRESS[i]);
        lc4[i].init();
        lc4[i].restartAndWait(1000);
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

float readLC4(uint8_t id) {
    DEBUG_SERIAL.println("readLC4 CALLED");
    return lc4[id].get_raw_weight_data(1);
}
float read_Force(uint8_t id) { return (readLC4(id) - 8168) * read2force; }

#endif