void bacaSensor()
{
  DataKelembaban();
  DataSuhu();
  DataKonduktifitas();
  DataPH();
  DataNitrogen();
  DataPhospor();
  DataKalium();
  DataSalinitas();
  DataTDS();
}





void DataKelembaban(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferKelembaban); i++ ) Serial2.write( BufferKelembaban[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  Kelembaban = (float)TotalHextoDec/10;
}

void DataSuhu(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferSuhu); i++ ) Serial2.write( BufferSuhu[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  Suhu = ((float)TotalHextoDec/10) + EEPROMSuhu;
}

void DataKonduktifitas(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferKonduktifitas); i++ ) Serial2.write( BufferKonduktifitas[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  Konduktifitas = ((float)TotalHextoDec/10)+EEPROMKelembaban;


}

void DataPH(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferPH); i++ ) Serial2.write( BufferPH[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  PH = ((float)TotalHextoDec/10)+EEPROMPH;

}

void DataNitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferNitrogen); i++ ) Serial2.write( BufferNitrogen[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  Nitrogen = (float)TotalHextoDec/10;
}

void DataPhospor(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferPhospor); i++ ) Serial2.write( BufferPhospor[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  Phospor = ((float)TotalHextoDec/10)+EEPROMPhospor;

}

void DataKalium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferKalium); i++ ) Serial2.write( BufferKalium[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  Kalium = ((float)TotalHextoDec/10)+EEPROMKalium;


  

}

void DataSalinitas(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferSalinitas); i++ ) Serial2.write( BufferSalinitas[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  Salinitas = ((float)TotalHextoDec/10)+EEPROMSalinitas;


}

void DataTDS(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  for (uint8_t i = 0; i < sizeof(BufferTDS); i++ ) Serial2.write( BufferTDS[i] );
  Serial2.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = Serial2.read();
  }
  int num1,num2,num3;
  num1=values[3];
  num2=values[4];
  num3=(num1<<8)|(num2);
  int TotalHextoDec = ("%x %d",num3,num3);
  TDS = ((float)TotalHextoDec/10)+EEPROMTDS;

}
