# Fuzz Trap - Client
The client package contains the client firmware, designed to run on the ESP32.

## Configuration
1. Under "Project Configuration" set the WiFi SSID and password to provide access to your local network.
2. Enable PSRAM
3. Enable Bluetooth
4. Set the partition size to "Single factory app (large), no OTA"
5. Set the server address
6. Reserve parts of SRAM1 for app IRAM (WARNING, read help before enabling)