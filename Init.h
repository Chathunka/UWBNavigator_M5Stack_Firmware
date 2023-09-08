#include <Arduino.h>
#include <M5Core2.h>
#include <Arduino_JSON.h>

#define DEBUG

void UWB_display(void);
void UWB_ui_display(int UWB_MODE);
void UWB_display_mode(int MODE);
void UWB_display_mode_after(int MODE);
String UWB_clear(void);
String UWB_readString(int UWB_MODE);
void UWB_setupmode(int UWB_MODE, int UWB_B_NUMBER);
int UWB_Keyscan(int CMODE);
void UWB_Timer(void);
void restartDevice(void);
void Splash_Screen(void);
void Splash_Screen1(void);
int CommModeSelector(void);
void displayQR(int commMode);
