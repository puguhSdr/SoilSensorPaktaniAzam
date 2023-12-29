#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
float phval= 7;
// Jangan lupa. harus unik antara device 1 dengan yg lainnya
#define BLE_NAME            "SNTPPKP-005"
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer *pServer;
BLECharacteristic *pCharacteristic;

#define EEPROM_SIZE 512 

#define SUHU_ADDRESS 0
#define KELEMBABAN_ADDRESS (SUHU_ADDRESS + sizeof(float))
#define NITROGEN_ADDRESS (KELEMBABAN_ADDRESS + sizeof(float))
#define PHOSPOR_ADDRESS (NITROGEN_ADDRESS + sizeof(float))
#define KALIUM_ADDRESS (PHOSPOR_ADDRESS + sizeof(float))
#define SALINITAS_ADDRESS (KALIUM_ADDRESS + sizeof(float))
#define KONDUKTIFITAS_ADDRESS (SALINITAS_ADDRESS + sizeof(float))
#define PH_ADDRESS (KONDUKTIFITAS_ADDRESS + sizeof(float))
#define TDS_ADDRESS (PH_ADDRESS + sizeof(float))

///npk sensor//
const byte BufferKelembaban[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
const byte BufferSuhu[] = {0x01, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA};
const byte BufferKonduktifitas[] = {0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x25, 0xCA};
const byte BufferPH[] = {0x01, 0x03, 0x00, 0x03, 0x00, 0x01, 0x74, 0x0A};
const byte BufferNitrogen[] = {0x01, 0x03, 0x00, 0x04, 0x00, 0x01, 0xC5, 0xCB};
const byte BufferPhospor[] = {0x01, 0x03, 0x00, 0x05, 0x00, 0x01, 0x94, 0x0B};
const byte BufferKalium[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};
const byte BufferSalinitas[] = {0x01, 0x03, 0x00, 0x07, 0x00, 0x01, 0x35, 0xCB};
const byte BufferTDS[] = {0x01, 0x03, 0x00, 0x08, 0x00, 0x01, 0x05, 0xC8};
byte BufferValue[8];
byte values[11];
float Kelembaban = 0;
float Suhu = 0;
float Konduktifitas = 0;
float PH = 0;
float Nitrogen = 0;
float Phospor = 0;
float Kalium = 0;
float Salinitas = 0;
float TDS = 0;


#define DE  18
#define RE  19

class MyCallbacks : public BLECharacteristicCallbacks {

  
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      std::string receivedValue(value.begin(), value.end());
      Serial.println("Received value: ");
      String valueToString = receivedValue.c_str();
      Serial.println(valueToString);
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, receivedValue.c_str());

      if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        pCharacteristic->setValue("Invalid JSON");
        pCharacteristic->notify();
        return;
      }

      const char* reqMethod = doc["method"];
      Serial.print("method: ");
      Serial.print(reqMethod);

      if (std::string(reqMethod) == "get") {
        DynamicJsonDocument jsonResponse(500);
    
        jsonResponse["status"] = true;
        jsonResponse["message"] = "success";
        jsonResponse["method"] = "get";
        jsonResponse["idDevice"] = BLE_NAME;
        jsonResponse["suhu"] = Suhu;
        jsonResponse["kelembaban"] = Kelembaban;
        jsonResponse["nitrogen"] = Nitrogen;
        jsonResponse["phospor"] = Phospor;
        jsonResponse["kalium"] = Kalium;
        jsonResponse["salinitas"] = Salinitas;
        jsonResponse["konduktifitas"] = Konduktifitas;
        jsonResponse["ph"] = PH;
        jsonResponse["tds"] = TDS;

        String jsonString;
        serializeJson(jsonResponse, jsonString);

        pCharacteristic->setValue(jsonString.c_str());
        pCharacteristic->notify();
      }
      else if (std::string(reqMethod) == "patch") 
      {
        

        DynamicJsonDocument jsonResponse(500);  
        jsonResponse["status"] = true;
        jsonResponse["message"] = "success";
        jsonResponse["method"] = "patch";
        jsonResponse["idDevice"] = BLE_NAME;
        KalSuhu = jsonResponse["suhu"];
        Kalkelembaban = jsonResponse["kelembaban"];
        KalNitrogen = jsonResponse["nitrogen"];
        KalPhospor = jsonResponse["phospor"];
        KalKalium = jsonResponse["kalium"];
        KalSalinitas = jsonResponse["salinitas"];
        KalKonduktifitas = jsonResponse["konduktifitas"];
        KalPH = jsonResponse["ph"];
        KalTDS = jsonResponse["tds"];
        saveToEEPROM(doc);

        String jsonString;
        serializeJson(jsonResponse, jsonString);

        pCharacteristic->setValue(jsonString.c_str());
        pCharacteristic->notify();
      }
      else if (std::string(reqMethod) == "kal") {
        DynamicJsonDocument jsonResponse(500);  
        retrieveFromEEPROM(jsonResponse);
        EEPROMRead(); 
        jsonResponse["status"] = true;
        jsonResponse["message"] = "success";
        jsonResponse["method"] = "kal";
        jsonResponse["idDevice"] = BLE_NAME;
        jsonResponse["suhu"] = EEPROMSuhu;
        jsonResponse["kelembaban"] = EEPROMKelembaban;
        jsonResponse["nitrogen"] = EEPROMNitrogen;
        jsonResponse["phospor"] = EEPROMPhospor;
        jsonResponse["kalium"] = EEPROMKalium;
        jsonResponse["salinitas"] = EEPROMSalinitas;
        jsonResponse["konduktifitas"] = EEPROMKonduktifitas;
        jsonResponse["ph"] = EEPROMPH;
        jsonResponse["tds"] = EEPROMTDS;

        String jsonString;
        serializeJson(jsonResponse, jsonString);

        pCharacteristic->setValue(jsonString.c_str());
        pCharacteristic->notify();
      }else if (std::string(reqMethod) == "close") {
        DynamicJsonDocument jsonResponse(500);  
        jsonResponse["status"] = true;
        jsonResponse["message"] = "success";
        jsonResponse["method"] = "close";
        jsonResponse["idDevice"] = BLE_NAME;

        String jsonString;
        serializeJson(jsonResponse, jsonString);

        pCharacteristic->setValue(jsonString.c_str());
        pCharacteristic->notify();
        // buat function untuk mereset esp32
        ESP.restart();
      } else {
        pCharacteristic->setValue("Invalid request");
        pCharacteristic->notify();
      }
    }
  }

  void saveToEEPROM(const DynamicJsonDocument& doc) {
    if (EEPROM_SIZE < TDS_ADDRESS + sizeof(float)) {
      Serial.println("Not enough EEPROM space for variables.");
      return;
    }

    int eepromAddress = SUHU_ADDRESS;

    EEPROM.put(eepromAddress, doc["suhu"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["kelembaban"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["nitrogen"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["phospor"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["kalium"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["salinitas"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["konduktifitas"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["ph"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.put(eepromAddress, doc["tds"].as<float>());
    eepromAddress += sizeof(float);

    EEPROM.commit();
  }

  void retrieveFromEEPROM(DynamicJsonDocument& doc) {
    if (EEPROM_SIZE < TDS_ADDRESS + sizeof(float)) {
      Serial.println("Not enough EEPROM space for variables.");
      return;
    }

    int eepromAddress = SUHU_ADDRESS;

    doc["suhu"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["kelembaban"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["nitrogen"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["phospor"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["kalium"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["salinitas"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["konduktifitas"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["ph"] = retrieveFloatFromEEPROM(eepromAddress);
    doc["tds"] = retrieveFloatFromEEPROM(eepromAddress);
  }

  float retrieveFloatFromEEPROM(int& eepromAddress) {
    float value;
    EEPROM.get(eepromAddress, value);
    eepromAddress += sizeof(float);
    return value;
  }
};

void setup() {

  Serial.begin(115200);
  Serial2.begin(4800);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  
  Serial.println("Initializing Bluetooth");

  BLEDevice::init(BLE_NAME);
  pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );
  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("SENSOR TANAH - PPKP KONAWE UTARA");

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  Serial.println("Bluetooth is ready");
}

void loop() {
 // delay(2000);
      bacaSensor(); 
}
