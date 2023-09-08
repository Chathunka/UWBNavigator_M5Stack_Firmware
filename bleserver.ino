BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic1 = NULL;
BLECharacteristic* pCharacteristic2 = NULL;
BLECharacteristic* pCharacteristic3 = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

#define SERVICE_UUID         "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID1 "beb5483e-36e1-4688-b7f5-ea07361b26a7"
#define CHARACTERISTIC_UUID2 "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID3 "beb5483e-36e1-4688-b7f5-ea07361b26a9"

DynamicJsonDocument doc(256);

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void initbleserver(){
  BLEDevice::init("UWB_Navigator");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic1 = pService->createCharacteristic(
                    CHARACTERISTIC_UUID1,
                    BLECharacteristic::PROPERTY_READ   |
                    BLECharacteristic::PROPERTY_WRITE  |
                    BLECharacteristic::PROPERTY_NOTIFY |
                    BLECharacteristic::PROPERTY_INDICATE
                  );
  pCharacteristic1->addDescriptor(new BLE2902());

  pCharacteristic2 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID2,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic2->addDescriptor(new BLE2902());

  pCharacteristic3 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID3,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic3->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("BLE initilaised...");
}

void turnOffBLE(){
  esp_bt_controller_disable();
  esp_bt_controller_deinit();
  delay(2000);
}

void sendDataBLE(String data){
    // notify changed value
  if (deviceConnected) {
    Serial.println(data);
    deserializeJson(doc, data);
    const char* data1 = doc["state1"];
    const char* data2 = doc["state2"];
    const char* data3 = doc["state3"];

    String str = "noDevice";
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);

    if(data1 == null){
      data1 = char_array;
    }
    if(data2 == null){
      data2 = char_array;
    }
    if(data3 == null){
      data3 = char_array;
    }

    // Serial.println(data1);
    // Serial.println(data2);
    // Serial.println(data3);

    pCharacteristic1->setValue(data1);
    pCharacteristic1->notify();
    delay(10);
    pCharacteristic2->setValue(data2);
    pCharacteristic2->notify();
    delay(10);
    pCharacteristic3->setValue(data3);
    pCharacteristic3->notify();
    delay(100);
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
      delay(500);
      pServer->startAdvertising();
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
      oldDeviceConnected = deviceConnected;
  }
}
