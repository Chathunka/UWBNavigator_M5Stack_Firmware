#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.h>
#include "FS.h"
#include "SPIFFS.h"
#include <M5Core2.h>
#include "Configurations.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "init.h"

void setup() {
  M5.begin(true, false, false, false);
  M5.Lcd.setTextColor(BLACK,WHITE);
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 33, 32);
  Splash_Screen1();
  UWB_ui_display(3);
  #ifdef APWEBSERVER
    //initAPServer();
    initbleserver();
    delay(1000);
  #endif
  
}
 
void loop() {
  M5.update();
  int temp = UWB_Keyscan(UWB_MODE);

  if(UWB_MODE == 0 && temp == 2){
    if(COMM_MODE == 0){ 
      UWB_display_mode(0);
      turnBLEAdapter(TURN_BLE_OFF);
      turnWifiAdapter(TURN_WIFI_ON);
      delay(1000);
      UWB_display_mode_after(0);
      COMM_MODE = 1;
    }
    else{
      UWB_display_mode(1);
      turnWifiAdapter(TURN_WIFI_OFF);
      turnBLEAdapter(TURN_BLE_ON);
      delay(1000);
      UWB_display_mode_after(1);
      COMM_MODE = 0;
    }
  }else if(UWB_MODE == 1 && temp == 2){
    restartDevice();
  }
  
  if(temp<2){
    UWB_MODE = temp;
  }

  JSONData = UWB_readString(UWB_MODE);
  #ifdef APWEBSERVER
  if(UWB_MODE == 0){
    if(COMM_MODE == 1){
      setWifi(0); // set wifi AP for now
      updateClients(JSONData);
    }else{
      sendDataBLE(JSONData);
    }
  }
  #endif
  #ifdef DEBUG
    //Serial.print("UWB_MODE : ");
    //Serial.println(UWB_MODE);
    //Serial.print("COMM mode :");
    //Serial.println(COMM_MODE);
  #endif
}
