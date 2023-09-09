# UWB Navigator Project M5-Stack Firmware

This repository contains C++ code for configuring the initial communication mode on an M5-Stack device (Wi-Fi / BLE) and setting up UWB DW1000 Ultra-Wide Band Transceivers in either Anchor Mode or Tag mode.

## Prerequisites

Before you can use this code, you will need the following:

1. **Arduino IDE / PlatformIO**: Ensure that you have the Arduino IDE / PlatformIO installed on your computer. You can download the software from the [official Arduino website](https://www.arduino.cc/en/software) or the [official PlatformIO website](https://platformio.org/).

2. **M5-Stack Core2 Board Support**: Follow these steps to add ESP32 board support to your Arduino IDE:

   - Open Arduino IDE.
   - Go to **File > Preferences**.
   - In the "Additional Boards Manager URLs" field, add the following URL: `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Click "OK" to close the Preferences window.
   - Navigate to **Tools > Board > Boards Manager...**
   - In the Boards Manager, search for "esp32" and install the "esp32" board by Espressif Systems.

3. **Libraries**:

   - You will require the following libraries:
     - **WiFi** library for ESP32's Wi-Fi functionality.
     - **ESPAsyncWebServer** library for ESP32's Webserver functionality.
     - **AsyncTCP** library for ESP32's TCP functionality.
     - **BLEDevice** library for ESP32's BLE functionality.
     - **BLEServer** library for ESP32's BLE server functionality.
     - **ArduinoJson** library for parsing JSON data.
     - **M5Core2** Official library for M5-Stack Core2. [More details...](https://github.com/m5stack/M5Core2)

   To install these libraries, navigate to **Sketch > Include Library > Manage Libraries...** and search for the necessary libraries.

## Installation

To get started with this code:

1. Clone this repository to your computer:

   ```bash
   git clone http://tec-server:8080/scm/repo/UWBResearchProject/UWBRepo
   ```

2. Open the Arduino IDE and go to **File > Open**. Select the `UWBNavigator.ino` file from the cloned repository.

3. Connect your M5-Stack Core2 board to your computer using a USB cable.

4. In the Arduino IDE, navigate to **Tools > Board** and select your ESP32 board model as M5-Stack Core2.

5. Choose the appropriate COM port under **Tools > Port**.

6. If you need to configure additional settings, such as Wi-Fi credentials or sensor parameters, edit the `Configurations.h` file.

7. Upload the code to your M5-Stack Core2 board by clicking the "Upload" button (the right arrow icon).

8. Open the Serial Monitor (**Tools > Serial Monitor**) to view the output and debug information.

## Usage

The code in this repository creates a user-friendly UI on an M5Stack Core2 device to select either the communication mode (Wi-Fi or BLE) for interaction with the mobile app and configure the UWB DW-1000 module as either a Tag or Anchor, ultimately obtaining distance data from the sensor module. Please refer to the sensor manufacturer's documentation for proper setup and calibration.

## License

This project is licensed under the MIT License. For more details, please consult the [LICENSE](LICENSE) file.

If you have any questions or encounter issues, feel free to open an issue in the GitHub repository.

Happy coding!