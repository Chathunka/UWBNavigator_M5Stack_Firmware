#include "init.h"

int commMode = 0;

int UWB_B_NUMBER = 0;
int UWB_T_NUMBER = 0;
int UWB_B_COUNT = 0;
String DATA  = "";
int nextAvailableBaseID = 1;

bool clearScreenFlag = false;

JSONVar readings;
String JSON_Data;

bool errorDisplayFlag = true;

void UWB_display() {
}

void UWB_ui_display(int UWB_MODE) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 2, 2, 100, 100, 0, 0, JPEG_DIV_2);
    M5.Lcd.drawString("UWB Navigator", 120, 10, 4);  // UI
    M5.Lcd.setTextColor(WHITE,DARKCYAN);
    M5.Lcd.fillRect(150, 45, 112, 10, DARKCYAN);
    M5.Lcd.drawString(" BRYCEN ", 150, 50, 4);
    M5.Lcd.setTextColor(WHITE,DARKCYAN);
    M5.Lcd.fillRect(0, 212, 320, 30, DARKCYAN);
    M5.Lcd.drawString(" Tag ", 25, 215, 4);
    M5.Lcd.drawString(" Base ", 130, 215, 4);
    M5.Lcd.drawString("Reset", 230, 215, 4);

    switch (UWB_MODE) {
        case 0:
            if(commMode == 1){
                M5.Lcd.setTextColor(BLACK,WHITE);
                M5.Lcd.drawString(" Mode : ", 155, 89, 4);
                M5.Lcd.setTextColor(WHITE,OLIVE);
                M5.Lcd.drawString(" WIFI ", 250, 89, 4);
            }else if(commMode == 2){
                M5.Lcd.setTextColor(BLACK,WHITE);
                M5.Lcd.drawString(" Mode : ", 155, 89, 4);
                M5.Lcd.setTextColor(WHITE,BLUE);
                M5.Lcd.drawString(" BLE ", 254, 89, 4);
            }
            //menu
            M5.Lcd.setTextColor(WHITE,DARKCYAN);
            M5.Lcd.drawString("Reset", 230, 215, 4);
            break;
        case 1:
            M5.Lcd.setTextColor(BLACK,WHITE);
            //M5.Lcd.drawString(" Base Mode ", 115, 80, 4);
            M5.Lcd.drawString(" Base ", 130, 215, 4);
            break;
        case 2:
            M5.Lcd.setTextColor(BLACK,WHITE);
            M5.Lcd.drawString("Reset", 230, 215, 4);
            break;
        case 3:
            M5.Lcd.setTextColor(BLACK,WHITE);
            M5.Lcd.drawString("Please Configure...", 5, 115, 4);
            break;
        case 4:
            break;
    }
    M5.Lcd.setTextColor(BLACK,WHITE);
}


String UWB_clear() {
  String DATA;
    if (Serial1.available()) {
        delay(3);
        DATA = Serial1.readString();
    }
    return DATA;
}

void clearLowerScreen(){
  M5.Lcd.fillRect(0, 115, 320, 95, WHITE);
}

int countStations(String Data){
  int stationCount=0;
  int tempindex=-1;
  tempindex = Data.indexOf('m');
  while(tempindex>-1){
    stationCount++;
    tempindex =  Data.indexOf('m',tempindex+1);
  }
  return stationCount;
}

String displayData(String Data, int StationCount){
  String msg = "";
  int tempindex = 0;
  int startindex=0;
  int endindex=0;
  String baseid = "";
  String ldistance = "";
  int startpointy = 120;
  M5.Lcd.fillRect(10, startpointy-5, 80, 90, DARKCYAN);
  M5.Lcd.setTextColor(WHITE,DARKCYAN);
  M5.Lcd.drawString("Station", 28, 120, 2);
  M5.Lcd.drawString("Count", 33, 140, 2);
  M5.Lcd.drawString(String(StationCount), 43, 165, 4);
  M5.Lcd.setTextColor(WHITE,ORANGE);
  M5.Lcd.fillRect(100, startpointy-5, 210, 90, ORANGE);
  for(int i = 0; i<StationCount; i++){
    if(i<3){
      startindex = DATA.indexOf('n',tempindex);
      endindex = DATA.indexOf('m',tempindex);
      baseid = DATA.substring(startindex+1,startindex+2);
      int tempid = baseid.toInt();
      if(tempid == nextAvailableBaseID){
        if(nextAvailableBaseID<3){
          nextAvailableBaseID++;
        }else{
          nextAvailableBaseID = 1;
        }
      }
      ldistance = DATA.substring(startindex+3,endindex); 
      tempindex = endindex+1;
      msg = "Base "+baseid+" :  "+ ldistance + " m";
      M5.Lcd.drawString(msg, 105, startpointy+(i*30), 4);
      readings["state"+baseid] = ldistance;
    }
  }
  M5.Lcd.setTextColor(BLACK,WHITE);
  return JSON.stringify(readings);
}

String UWB_readString(int UWB_MODE) {
    JSON_Data = "";
    switch (UWB_MODE) {
        case 0:
            UWB_clear();
            Serial1.write("AT\r\n");
            delay(50);
            while(Serial1.available()){
              DATA= Serial1.readString();
            }
            //Serial.print(DATA);
            if(DATA.indexOf('O')==-1){
              clearLowerScreen();
              M5.Lcd.drawString("UWB Sensor error..", 5, 115, 4);
              Serial.println("UWB Sensor error..");
              clearScreenFlag = true;
              JSON_Data ="";
            }else{
              UWB_B_COUNT = countStations(DATA);
              if(UWB_B_COUNT==0){
                clearLowerScreen();
                M5.Lcd.drawString("No stations. Please Config.", 5, 115, 4);
                Serial.print("No stations. Please reset device.");
                clearScreenFlag = true;
                JSON_Data ="";
              }else{
                if(clearScreenFlag){
                  clearLowerScreen();
                  clearScreenFlag = false;
                }
                JSON_Data = displayData(DATA,UWB_B_COUNT);
              }
            }
            DATA="";
            #ifdef DEBUG
            Serial.println(DATA);
            #endif
            break;
        case 1:
            break;
    }
    return JSON_Data;
}

void UWB_display_error(){
  if(errorDisplayFlag){
    M5.Lcd.drawString("UWB Sensor error..", 5, 115, 4);
    errorDisplayFlag=false;
  }
}

void ATCommandSET(int UWB_MODE){
    for (int b = 0; b < 2; b++) {
        M5.Lcd.drawString("Configuring ..", 50, 115, 4);
        delay(50);
        Serial1.write("AT+anchor_tag=0\r\n");
        delay(50);
          while(Serial1.available()){
            Serial.print(Serial1.readString());
          }
          Serial.println("");
        M5.Lcd.drawString("Configuring ....", 50, 115, 4);
        delay(50);
        Serial1.write("AT+interval=5\r\n");
        delay(50);
          while(Serial1.available()){
            Serial.print(Serial1.readString());
          }
          Serial.println("");
        delay(50);
        Serial1.write("AT+switchdis=1\r\n");
          delay(50);
          while(Serial1.available()){
            Serial.print(Serial1.readString());
          }
          Serial.println("");
        M5.Lcd.drawString("Configuring .......", 50, 115, 4);
        if (b == 0) {
            Serial1.write("AT+RST\r\n");
        }
    }
}

void UWB_setupmode(int UWB_MODE, int UWB_B_NUMBER) {
  String temp;
    switch (UWB_MODE) {
        case 0:
            ATCommandSET(0);
            M5.Lcd.drawString("Configuration Done.", 50, 115, 4);
            clearScreenFlag = true;
            UWB_clear();
            break;
        case 1:
            ATCommandSET(0);
            for(int i=0; i<3; i++){ 
              UWB_readString(0);
            }
            for (int b = 0; b < 2; b++) {
              delay(50);
              Serial1.write("AT+anchor_tag=1,");
              Serial1.print(nextAvailableBaseID);
              Serial1.write("\r\n");
              delay(1);
              delay(50);
              if (b == 0) {
                  Serial1.write("AT+RST\r\n");
              }
            }
            clearLowerScreen();
            M5.Lcd.drawString("Configuration Done.", 50, 115, 4);
            delay(1000);
            clearLowerScreen();
            M5.Lcd.drawString("Base Station ID", 80, 115, 4);
            M5.Lcd.drawString(String(nextAvailableBaseID), 150, 165, 4);
            nextAvailableBaseID = 1;
            clearScreenFlag = true;
            UWB_clear();
            break;
    }
}

int UWB_Keyscan(int CMODE) {
    if (M5.BtnA.isPressed()) {
      Serial.println("Pressed Button A");
      UWB_ui_display(0);
      UWB_setupmode(0,0);
      UWB_clear();
      return 0;
    }
    if (M5.BtnB.isPressed()) {
      Serial.println("Pressed Button B");
      UWB_ui_display(1);
      if (UWB_B_NUMBER == 4) {
          UWB_B_NUMBER = 0;
      }
      UWB_setupmode(1,UWB_B_NUMBER);
      UWB_B_NUMBER++;
      UWB_clear();
      return 1;
    }
    if (M5.BtnC.isPressed()) {
      Serial.println("Pressed Button C");
      restartDevice();
      return 2;
    }
    return 3;
}


void restartDevice(){
  UWB_clear();
  UWB_ui_display(4);
  M5.Lcd.drawString("Restarting >>", 50, 115, 4);
  delay(800);
  M5.Lcd.drawString("Restarting >>>>", 50, 115, 4);
  delay(800);
  M5.Lcd.drawString("Restarting >>>>>>", 50, 115, 4);
  delay(800);
  ESP.restart();
}


void Splash_Screen(){
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 0, 0, 100, 100, 0, 0, JPEG_DIV_8);
  delay(50);
  M5.Lcd.clear();
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 25, 17, 100, 100, 0, 0, JPEG_DIV_4);
  delay(50);
  M5.Lcd.clear();
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 55, 35, 100, 100, 0, 0, JPEG_DIV_2);
  delay(50);
  M5.Lcd.clear();
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 110, 70, 100, 100, 0, 0, JPEG_DIV_NONE);
  delay(50);
}

void Splash_Screen1(){
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 0, 0, 200, 200, 0, 0, JPEG_DIV_8);
  delay(50);
  M5.Lcd.clear();
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 12, 7, 200, 200, 0, 0, JPEG_DIV_4);
  delay(50);
  M5.Lcd.clear();
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 27, 14, 200, 200, 0, 0, JPEG_DIV_2);
  delay(50);
  M5.Lcd.clear();
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 55, 20, 200, 200, 0, 0, JPEG_DIV_NONE);
  delay(500);
  M5.Lcd.clear();
  delay(500);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 55, 20, 200, 200, 0, 0, JPEG_DIV_NONE);
  delay(500);
  M5.Lcd.clear();
  delay(500);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 55, 20, 200, 200, 0, 0, JPEG_DIV_NONE);
  delay(1000);
}

int CommModeSelector(){
  M5.update();
  M5.Lcd.drawJpgFile(SPIFFS, "/lpsmall.jpg", 0, 0, 318, 238, 0, 0, JPEG_DIV_NONE);
  M5.Lcd.setTextColor(WHITE,DARKCYAN);
  M5.Lcd.drawString(" WiFi ", 25, 210, 4);
  M5.Lcd.drawString(" BLE ", 240, 210, 4);
  bool pressed = true;
  while(pressed){
    M5.update();
    Serial.println("onloop");
    if (M5.BtnA.isPressed()) {
      Serial.println("Pressed Button WIFI");
      commMode = 1;
      M5.Lcd.setTextColor(BLACK,WHITE);
      M5.Lcd.drawString(" WiFi ", 25, 210, 4);
      pressed = false;
    }
    if (M5.BtnC.isPressed()) {
      Serial.println("Pressed Button BLE");
      commMode = 2;
      M5.Lcd.setTextColor(BLACK,WHITE);
      M5.Lcd.drawString(" BLE ", 240, 210, 4);
      pressed = false;
    }
    delay(50);
  }
  return commMode;
}

void displayQR(int commMode){
  M5.Lcd.drawJpgFile(SPIFFS, "/infosm.jpg", 0, 0, 318, 238, 0, 0, JPEG_DIV_NONE);
  delay(3000);

  if(commMode == 1){
    M5.Lcd.drawJpgFile(SPIFFS, "/QRWIFIsm.jpg", 0, 0, 318, 238, 0, 0, JPEG_DIV_NONE);
  }else if(commMode == 2){
    M5.Lcd.drawJpgFile(SPIFFS, "/QRBLEsm.jpg", 0, 0, 318, 238, 0, 0, JPEG_DIV_NONE);
  }
  M5.Lcd.setTextColor(WHITE,DARKCYAN);
  M5.Lcd.drawString("  OK ", 240, 210, 4);

  bool pressed = true;
  while(pressed){
    M5.update();
    Serial.println("onloop");
    if (M5.BtnC.isPressed()) {
      Serial.println("Pressed Button OK");
      M5.Lcd.setTextColor(BLACK,WHITE);
      M5.Lcd.drawString("  OK ", 240, 210, 4);
      pressed = false;
    }
    delay(50);
  }
}
