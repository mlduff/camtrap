# Camtrap
This project provides the ability to create a DIY home monitoring system. Each device will automatically detect movement within a certain distance, taking a photo and saving it to a central server when triggered. Devices can be enabled or disabled remotely via the server, or physically with an RFID-tag.
# Parts List
This project requires the following parts:
- ESP32 Freenove WROVER CAM Module
- STM32 Nucleo-64
- Wires

# Setup
To setup this project, follow the following guides in order:
1. [Server](server/README.md)
2. [Device](device/README.md)
3. [ESP32](device/client/README.md)
4. [STM32](device/stm32_main/README.md)

# User Manual
## Recording RFID tag
1. Navigate to the page of the device you want to use to add an RFID tag
2. Enable configure mode
3. Swipe the RFID tag against the reading panel
4. Navigate to the RFID tags page and verify that the tag has been navigated
5. Navigate back to the device page and disable configure mode
