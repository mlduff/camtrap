# Client
The client package contains the client firmware, designed to run on the ESP32.

# Configuration
These instructions will assist you with the setup for this project, but assume you know how to use the ESP-IDF framework.

## Software Configuration
To get the software running on an ESP32, follow these instructions:
1. Open the menuconfig editor of your choice
2. Select the device target to be ESP-WROVER-KIT 3.3V
3. Select UART as the flash method
4. Attach the ESP32 to the computer and select the correct COM PORT
6. Run build, flash and start a monitor command


## User Configuration
Once you have the ESP32 running the project software, follow these instructions to connect it to your home system.
1. Ensure that the server is running
2. Attach the ESP32 to power
3. Using a device not running the server:
    1. Connect to the local WiFi network with the configured name (default is `camtrap-device`)
    2. Navigate to http://192.168.4.1/ in a browser
    3. Enter your WiFi network details as well as the address of the device running your server
    4. Submit
4. Check that the ESP32 network is no longer available and that the device has been registed by navigating to the `/devices/` page on your server. Repeat from step 3 if there are any issues (most likely incorrect details)
