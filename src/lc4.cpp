#include <Glove.h>

#ifdef LOADCELL4_H
  static loadcell4_t loadcell4[2];
  static loadcell4_data_t cell_data[2];
  static loadcell4_cfg_t loadcell4_cfg[2];
  volatile float weight_val[2] = {0.0f};
  const uint32_t initial_average_value = 2048;
  const float read2force = 128 * LOADCELL_FS / (pow(2,(AMP_RESBITS)) * AMP_GAIN * LOADCELL_RO_MVV);

void setLC4() {
  
  for (uint8_t i = 0; i < sizeof(loadcell4) / sizeof(loadcell4[0]); i++){
    loadcell4_cfg_setup( &loadcell4_cfg[i], LC4_INTPIN[i], LC4_ENPIN[i], LC4_I2C_ADDRESS[i]);
    loadcell4_init( &loadcell4[i], &loadcell4_cfg[i]);
    loadcell4_default_cfg ( &loadcell4[i] );

    loadcell4_power_dev( &loadcell4[i], LOADCELL4_PWR_OFF );
    delay(1000);
    loadcell4_power_dev( &loadcell4[i], LOADCELL4_PWR_ON );
    delay(1000);      
  }
    
  if (LC4_CHANGE_SETTING){
    loadcell4_power_dev( &loadcell4[1], LOADCELL4_PWR_OFF ); delay(3000);
    loadcell4_power_dev( &loadcell4[1], LOADCELL4_PWR_ON );
    
    Wire.beginTransmission( 0x28 );
    Wire.write(0xA0); Wire.write(0x00); Wire.write(0x00);
    Wire.endTransmission(); delay(3);
    Serial.println("WRITING EEPROM");
    
    loadcell4_write_eeprom( &loadcell4[1], 0x01, 0x0001); delay(15);    
    //loadcell4_write_eeprom( &loadcell4[1], 0x0F, 0x0BB8); delay(15);
    
    for (int i = 0; i < 0x14; i++) {
      Serial.println("READING EEPROM");
      loadcell4_read_eeprom( &loadcell4[1], i); delay(10);
    }
    
    Wire.beginTransmission( 0x28 );    
    Wire.write(0x80); 
    Wire.write(0x00); 
    Wire.write(0x00);
    Wire.endTransmission(); 
    delay(2);
    loadcell4_power_dev( &loadcell4[1], LOADCELL4_PWR_OFF ); 
    delay(1000);
    loadcell4_power_dev( &loadcell4[1], LOADCELL4_PWR_ON ); 
    delay(1);
  }
}

float readLC4(uint8_t id){    
    DEBUG_SERIAL.println("readLC4 CALLED");
    return loadcell4_get_raw_weight_data( &loadcell4[id], &cell_data[id], 1);
}

float read_Force(uint8_t id){
    return (readLC4(id) - 8168) * read2force;
}

#endif