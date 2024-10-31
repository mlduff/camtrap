#include <Wire.h>
#include <VL53L1X.h>
#include <STM32FreeRTOS.h>
#include <SPI.h>
#include <MFRC522.h>

#define UART_Tx         PA9
#define UART_Rx         PA10
#define PIR_IN          PC4
#define SS_PIN          PA4
#define RST_PIN         PB4

#define TARGET_DISTANCE 5000

SemaphoreHandle_t pirSemaphore;
SemaphoreHandle_t laserSemaphore;
SemaphoreHandle_t uartSemaphore;

bool pirValue = false;
bool laserValue = false;

HardwareSerial mySerial(USART3);

static void pirReadThread(void* arg) {
  UNUSED(arg);
  pinMode(PIR_IN, INPUT);

  while (1) {
    if (digitalRead(PIR_IN) == HIGH) {
      if (xSemaphoreTake(pirSemaphore, (TickType_t) 5) == pdTRUE) {
        pirValue = true;
        xSemaphoreGive(pirSemaphore);
      }
    } else {
      if (xSemaphoreTake(pirSemaphore, (TickType_t) 5) == pdTRUE) {
        pirValue = false;
        xSemaphoreGive(pirSemaphore);
      }
    }
  }
}

static void laserRangeReadThread(void* arg) {
  UNUSED(arg);
  VL53L1X sensor;
  Wire.begin();
  Wire.setClock(400000); 

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);

  sensor.startContinuous(50);

  while (1) {
    if (sensor.read() < TARGET_DISTANCE) {
      if (xSemaphoreTake(laserSemaphore, (TickType_t) 5) == pdTRUE) {
        laserValue = true;
        xSemaphoreGive(laserSemaphore);
      }
    } else {
      if (xSemaphoreTake(laserSemaphore, (TickType_t) 5) == pdTRUE) {
        laserValue = false;
        xSemaphoreGive(laserSemaphore);
      }
    }
    if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  }
}

static void processingThread(void* arg) {
  UNUSED(arg);

  pinMode(LED_BUILTIN, OUTPUT);

  bool alarmTriggered = false;

  while (1) {
    if (alarmTriggered == true) {
      alarmTriggered = false;
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    }
    if (xSemaphoreTake(pirSemaphore, (TickType_t) 10) == pdTRUE) {
      if (xSemaphoreTake(laserSemaphore, (TickType_t) 10) == pdTRUE) {
        if (pirValue == true && laserValue == true) {
          Serial.println("INTRUDER DETECTED!!!");
          alarmTriggered = true;
          if (xSemaphoreTake(uartSemaphore, (TickType_t) 10) == pdTRUE) {
            digitalWrite(LED_BUILTIN, HIGH);
            vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
            mySerial.print("alarm");
            vTaskDelay((5000L * configTICK_RATE_HZ) / 1000L);
            digitalWrite(LED_BUILTIN, LOW);
            xSemaphoreGive(uartSemaphore);
          }
        }
        xSemaphoreGive(laserSemaphore);
      }
      xSemaphoreGive(pirSemaphore);
    }
  }
}

static void rfidTask(void* arg) {
  UNUSED(arg);

  Serial.println("Beginning RFID task.");

  MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
  MFRC522::MIFARE_Key key;

  SPI.setMISO(PA6);
  SPI.setMOSI(PA7);
  SPI.setSCLK(PB3);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  while (1) {
    // Check if a card is present
    if (!rfid.PICC_IsNewCardPresent()) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      continue; // If no card is present, return
    }

    // Check if we can read the card
    if (!rfid.PICC_ReadCardSerial()) {
      continue; // If the card can't be read, return
    }

    // Print card UID
    Serial.print("Tag UID: ");
    String rfidUid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      rfidUid += rfid.uid.uidByte[i] < 0x10 ? " 0" : " ";
      rfidUid += String(rfid.uid.uidByte[i], HEX);
    }

    if (xSemaphoreTake(uartSemaphore, (TickType_t) 10) == pdTRUE) {
      mySerial.print("rfid" + rfidUid);
      xSemaphoreGive(uartSemaphore);
    }

    Serial.println(rfidUid);

    // Check card type
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    Serial.print("PICC Type: ");
    Serial.println(rfid.PICC_GetTypeName(piccType));

    // Check if the card is of type MIFARE TNP3XXX
    if (piccType == MFRC522::PICC_TYPE_MIFARE_MINI) {
      Serial.println("MIFARE TNP3XXX tag detected!");
    } else {
      Serial.println("Different tag type detected.");
    }

    // Halt PICC
    rfid.PICC_HaltA();
    
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();

    // Wait for the tag to be removed
    while (rfid.PICC_IsNewCardPresent() || rfid.PICC_ReadCardSerial()) {
      vTaskDelay(100 / portTICK_PERIOD_MS); // Delay to allow time for the tag to be removed
    }
  }
}

void readUartTask(void* arg) {
  UNUSED(arg);

  while (mySerial.available()) {
    mySerial.read(); // Clear any existing data
  }

  if (xSemaphoreTake(uartSemaphore, (TickType_t) 10) == pdTRUE) {
    mySerial.print("start");
    xSemaphoreGive(uartSemaphore);
  }

  String incoming;
  while (1) {
    if (mySerial.available() > 0) {
      incoming = mySerial.readStringUntil('\n');
      incoming.trim();

      Serial.print("I received: " + incoming);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Add a delay to prevent tight looping
  }
}

void setup()
{
  portBASE_TYPE pirThread, laserThread, processThread, rfidThread, readUartThread;

  Serial.begin(9600);
  while (!Serial) {}

  Serial.println("Setting up...");

  // Initialize UART Serial
  mySerial.setRx(UART_Rx);
  mySerial.setTx(UART_Tx);
  mySerial.begin(9600);

  pirSemaphore = xSemaphoreCreateMutex();
  laserSemaphore = xSemaphoreCreateMutex();
  uartSemaphore = xSemaphoreCreateMutex();

  pirThread = xTaskCreate(pirReadThread, NULL, 512, NULL, 1, NULL);

  laserThread = xTaskCreate(laserRangeReadThread, NULL, 768, NULL, 1, NULL);

  processThread = xTaskCreate(processingThread, NULL, 512, NULL, 1, NULL);

  rfidThread = xTaskCreate(rfidTask, NULL, 1024, NULL, 1, NULL);

  readUartThread = xTaskCreate(readUartTask, NULL, 512, NULL, 1, NULL);

  if (
    pirSemaphore == NULL || 
    laserSemaphore == NULL ||
    uartSemaphore == NULL ||
    pirThread != pdPASS ||
    laserThread != pdPASS ||
    processThread != pdPASS ||
    rfidThread != pdPASS ||
    readUartThread != pdPASS
  ) {
    Serial.println(F("Creation problem"));
    while(1);
  }

  vTaskStartScheduler();
}

void loop()
{
  
}