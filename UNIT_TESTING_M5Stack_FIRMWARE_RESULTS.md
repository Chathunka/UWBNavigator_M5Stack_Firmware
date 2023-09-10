# UWB_Navigator Unit Test Result Document

## Introduction

This document provides a detailed summary of the results obtained from unit testing the UWB_Navigator project firmware. The firmware is designed for indoor localization using UWB sensors in conjunction with an M5 Stack device. The primary focus of this document is to present the outcomes of the unit tests conducted on various aspects of the project.

## Test Environment

### Hardware:
- M5 Stack device
- UWB DW-1000 sensors (configured as Tags and Anchors)
- Mobile phone for communication testing (Bluetooth and Wi-Fi)

### Software:
- UWB_Navigator firmware
- Test environment setup to simulate UWB sensor interactions
- Mobile app for communication testing (Bluetooth and Wi-Fi)

## Test Cases and Results

### 1. UWB Sensor Configuration

#### Test Case 1.1: UWB Sensor Configuration as Tags

- **Test Steps:**
    1. Set up the M5 Stack device with UWB sensors.
    2. Use the UI to configure a UWB sensor as a Tag.
    3. Monitor the sensor's behavior.

- **Actual Result:** The sensor was successfully configured as a Tag and displayed the Linear distance dat ain the LCD screen in the device. Also it transmitted distance data to the mobile app as expected via BLE or Wi-Fi.

- **Pass/Fail:** Pass

#### Test Case 1.2: UWB Sensor Configuration as Anchors

- **Test Steps:**
    1. Set up the M5 Stack device with UWB sensors.
    2. Use the UI to configure a UWB sensor as an Anchor.
    3. Monitor the sensor's behavior.

- **Actual Result:** The sensor was successfully configured as an Anchor. It scanned for available Anchors and assigned Base Station IDs automatically and UWM tag device was able to detect the created base station.

- **Pass/Fail:** Pass

### 2. Distance Measurement

#### Test Case 2.1: Accuracy of Distance Measurements in Tag Mode

- **Test Steps:**
    1. Configured UWB sensors as Tags.
    2. Placed Anchors at known distances from Tags.
    3. Measured and recorded the displayed distances on the M5 Stack device.

- **Actual Result:** The displayed distances accurately reflected the actual distances between Tags and Anchors when the sensors are in Line of sight.

- **Pass/Fail:** Pass

### 3. User Interface

#### Test Case 3.1: Functionality of the User Interface for Mode Selection

- **Test Steps:**
    1. Accessed the UI on the M5 Stack device.
    2. Selected the communication mode (BLE or Wi-Fi).
    3. Verified that the selected mode was reflected in the firmware.

- **Actual Result:** The selected communication mode was accurately reflected within the firmware throgh the LCD display.

- **Pass/Fail:** Pass

### 4. Communication Modes

#### Test Case 4.1: Communication via BLE

- **Test Steps:**
    1. Set up the M5 Stack device as a Tag.
    2. Connected a mobile phone via BLE.
    3. Verified that distance data was sent to the mobile phone.

- **Actual Result:** Distance data was successfully transmitted via BLE to the mobile phone.

- **Pass/Fail:** Pass

#### Test Case 4.2: Communication via Wi-Fi

- **Test Steps:**
    1. Set up the M5 Stack device as a Tag.
    2. Connected to a Wi-Fi network.
    3. Verified that distance data was sent to the mobile app over Wi-Fi.

- **Actual Result:** Distance data was successfully transmitted via Wi-Fi to the mobile app.

- **Pass/Fail:** Pass

### 5. Base Station ID Assignment

#### Test Case 5.1: Automatic Base Station ID Assignment in Anchor Mode

- **Test Steps:**
    1. Configured multiple UWB sensors as Anchors.
    2. Monitored the assignment of Base Station IDs.

- **Actual Result:** The firmware automatically assigned unique Base Station IDs to Anchors in the range 0 to a maximum of 4.

- **Pass/Fail:** Pass

## Conclusion

The unit testing of the UWB_Navigator project firmware was conducted as per the defined test cases. The results indicate that the firmware functions as intended and meets the specified requirements. All tests passed, confirming the correct configuration of UWB sensors, accurate distance measurements, proper user interface functionality, successful communication via BLE and Wi-Fi, and automatic Base Station ID assignment.

The firmware appears to be stable and reliable for indoor localization using UWB technology in conjunction with the M5 Stack device.