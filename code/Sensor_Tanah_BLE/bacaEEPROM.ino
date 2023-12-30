  void baca() {
        
        EEPROMSuhu = preferences.getFloat("suhup",0);
        EEPROMKelembaban = preferences.getFloat("kelembabanp",0);
        EEPROMNitrogen = preferences.getFloat("nitrogenp",0);
        EEPROMPhospor = preferences.getFloat("phosporp",0);
        EEPROMKalium = preferences.getFloat("kaliump",0);
        EEPROMSalinitas = preferences.getFloat("salinitasp",0);
        EEPROMKonduktifitas = preferences.getFloat("konduktifitasp",0);
        EEPROMPH = preferences.getFloat("php",0);
        EEPROMTDS = preferences.getFloat("tdsp",0);
 }
