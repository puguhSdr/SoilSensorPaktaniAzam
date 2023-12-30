  void baca() {

    int eepromAddress = 50;
    EEPROM.get(eepromAddress, EEPROMSuhu);
    Serial.print(EEPROMSuhu);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMKelembaban);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMNitrogen);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMPhospor);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMKalium);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMSalinitas);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMKonduktifitas);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMPH);
    eepromAddress += sizeof(float);
    EEPROM.get(eepromAddress, EEPROMTDS);
    eepromAddress=50;
  }
