# Setup
This section contains the physical setup required to connect the two parts of the device together.
## UART Connection
A wire must be connected between pin 33 on the ESP32 and pin PA10 on the STM32. A wire must also be connected between pin 32 on the ESP32 and pin PA9 on the STM32.
## RFID Sensor
Connect:
- PA6 to MISO
- PA7 to MOSI
- PB3 to SCLK
- PA4 to SS
- PB4 to RST
- GND to GND
## Motion Sensor
Connect:
- PC4 to input
- 5V to VCC
- GND to GND
## Distance Sensor
Connect:
- SCL to SCL
- SDA to SDM
- 3v3 to VCC
- GND to GND
## Green LED
Connect pin 2 on the ESP32 to the positive side of the LED, and then then ground the other side to one of the ground pins on the ESP32
## Red LED
Connect pin 14 on the STM32 to the positive side of the LED, and then then ground the other side to one of the ground pins on the STM32
