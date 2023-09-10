# UWB_Navigator Unit Testing Document

## Introduction

This unit testing document is intended to guide the testing of the UWB_Navigator project firmware. The project aims to provide indoor localization using UWB sensors in conjunction with an M5 Stack device. The primary focus of this document is on unit testing, which involves testing individual components and functions of the firmware in isolation.

## Testing Objectives

The objectives of this unit testing are as follows:

1. Verify the correct behavior of the UWB sensor configurations (Tag and Anchor modes).
2. Confirm the accuracy of distance measurements and calculations.
3. Ensure the proper functioning of the user interface.
4. Validate the communication modes (BLE and Wi-Fi).
5. Test the automatic assignment of Base Station IDs in Anchor mode.

## Test Environment

### Hardware:
- M5 Stack device
- UWB DW-1000 sensors (configured as Tags and Anchors)
- Mobile phone for communication testing (Bluetooth and Wi-Fi)

### Software:
- UWB_Navigator firmware
- Test environment setup to simulate UWB sensor interactions
- Mobile app for communication testing (Bluetooth and Wi-Fi)

## Test Cases

### 1. UWB Sensor Configuration

**Test Case 1.1:** Verify that the firmware correctly configures UWB sensors as Tags.

**Test Steps:**
1. Set up the M5 Stack device with UWB sensors.
2. Use the UI to configure a UWB sensor as a Tag.
3. Monitor the sensor's behavior.

**Expected Result:** The sensor should be configured as a Tag, and it should function as expected, displaying and sending linear distance data to the mobile app.

**Test Case 1.2:** Verify that the firmware correctly configures UWB sensors as Anchors.

**Test Steps:**
1. Set up the M5 Stack device with UWB sensors.
2. Use the UI to configure a UWB sensor as an Anchor.
3. Monitor the sensor's behavior.

**Expected Result:** The sensor should be configured as an Anchor, and it should scan for available Anchors, assigning Base Station IDs as needed.

### 2. Distance Measurement

**Test Case 2.1:** Verify the accuracy of distance measurements in Tag mode.

**Test Steps:**
1. Configure UWB sensors as Tags.
2. Place Anchors at known distances from Tags.
3. Measure and record the displayed distances on the M5 Stack device.

**Expected Result:** The displayed distances should accurately reflect the actual distances between Tags and Anchors.

### 3. User Interface

**Test Case 3.1:** Verify the functionality of the user interface for mode selection.

**Test Steps:**
1. Access the UI on the M5 Stack device.
2. Select the communication mode (BLE or Wi-Fi).
3. Verify that the selected mode is reflected in the firmware.

**Expected Result:** The selected communication mode should be accurately reflected within the firmware.

### 4. Communication Modes

**Test Case 4.1:** Verify communication via BLE.

**Test Steps:**
1. Set up the M5 Stack device as a Tag.
2. Connect a mobile phone via BLE.
3. Verify that distance data is sent to the mobile phone.

**Expected Result:** Distance data should be successfully transmitted via BLE to the mobile phone.

**Test Case 4.2:** Verify communication via Wi-Fi.

**Test Steps:**
1. Set up the M5 Stack device as a Tag.
2. Connect to a Wi-Fi network.
3. Verify that distance data is sent to the mobile app over Wi-Fi.

**Expected Result:** Distance data should be successfully transmitted via Wi-Fi to the mobile app.

### 5. Base Station ID Assignment

**Test Case 5.1:** Verify automatic Base Station ID assignment in Anchor mode.

**Test Steps:**
1. Configure multiple UWB sensors as Anchors.
2. Monitor the assignment of Base Station IDs.

**Expected Result:** The firmware should automatically assign unique Base Station IDs to Anchors in the range 0 to a maximum of 4.

## Test Execution

Execute each test case in the specified order. Document the actual results and compare them with the expected results. If there are any discrepancies, investigate and resolve the issues.

## Conclusion

This unit testing document outlines the testing procedures and test cases for the UWB_Navigator project firmware. Thorough testing of the firmware components will help ensure that it functions as intended, providing accurate indoor localization using UWB sensors.