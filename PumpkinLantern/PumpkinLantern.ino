#include "FreeRTOS_AVR.h"
#include "MP3.h"
#include "Servo.h"

Servo servo;
MP3 mp3(2, 3);
uint8_t pir = 4;
uint8_t led = 5;

SemaphoreHandle_t xPIRBinarySemaphore;

static void vFadingLEDsTask(void * pvArg) {
  for (;;) {
    for(int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
      analogWrite(led, fadeValue);
      vTaskDelay(30 / portTICK_PERIOD_MS);
    }
  
    for(int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(led, fadeValue);
      vTaskDelay(30 / portTICK_PERIOD_MS);
    }
  }
}

static void vScaningPIRTask(void * pvArg) {
  for (;;) {
    if (digitalRead(pir)) {
      xSemaphoreGive(xPIRBinarySemaphore);
      
      vTaskDelay(10000 / portTICK_PERIOD_MS);
      continue;
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void vHandlePIRTask(void * pvArg) {
  for (;;) {
    xSemaphoreTake(xPIRBinarySemaphore, portMAX_DELAY);
    
    mp3.playMP3Folder(1);

    for (uint8_t i = 0; i < 3; i++) {
      analogWrite(led, 255);
      servo.write(40);
      delay(500);

      analogWrite(led, 0);
      servo.write(0);
      delay(500);
    }
  }
}

void setup() {
  portBASE_TYPE s1, s2, s3;
  
  Serial.begin(9600);
  while (!Serial);

  mp3.init();
 servo.attach(6);
  
  vSemaphoreCreateBinary(xPIRBinarySemaphore);

  s1 = xTaskCreate(vFadingLEDsTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  s2 = xTaskCreate(vScaningPIRTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  s3 = xTaskCreate(vHandlePIRTask, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  if (xPIRBinarySemaphore == NULL || s1 != pdPASS || s2 != pdPASS || s3 != pdPASS) {
    Serial.println("Creation problem");
    for (;;);
  }

  vTaskStartScheduler();

  Serial.println("Insufficient RAM");
  for (;;);
}

void loop() { }

