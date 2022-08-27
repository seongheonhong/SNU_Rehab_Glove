#include "Glove.h"

#ifndef LOADCELL
#define LOADCELL
#define LC4_COUNT 2

const float read2force = 128 * LOADCELL_FS / (pow(2, (AMP_RESBITS)) * AMP_GAIN * LOADCELL_RO_MVV);
void setLC4();
void readLC4EEPROM(uint8_t id, uint8_t cmd_byte);
void writeLC4EEPROM(uint8_t id, uint8_t cmd_byte, uint16_t data_word);
float read_Force(uint8_t id);

#endif
