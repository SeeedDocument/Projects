/*
 * PumpkinLantern.ino
 * A pumpkin lantern which will play music and spit candies when somebody comes up to it. 
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Lets Blu
 * Created Time: Oct 2018
 * Modified Time:
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Adafruit_NeoPixel.h"
#include "Adafruit_TiCoServo.h"
#include "FreeRTOS_AVR.h"
#include "MP3.h"

#define PIR_PIN         4
#define PIXEL_NUMBER    64
#define MAX_BRIGHTNESS  127

MP3                     mp3(2, 3);
Adafruit_NeoPixel       pixels = Adafruit_NeoPixel(PIXEL_NUMBER, 5, NEO_GRB + NEO_KHZ800);
Adafruit_TiCoServo      servo;

SemaphoreHandle_t				xPIRBinarySemaphore;

void showPixels(uint8_t brightness) {
	pixels.setBrightness(brightness);
	for (int pixel = 0; pixel < PIXEL_NUMBER; pixel++) {
		pixels.setPixelColor(pixel, pixels.Color(255, 0, 0));
	}

	pixels.show();
}

static void vFadingLEDsTask(void * pvArg) {
	for (;;) {
		for (int fadeValue = 0; fadeValue <= 127; fadeValue += 5) {
			showPixels(fadeValue);
			vTaskDelay(30 / portTICK_PERIOD_MS);
		}

		for (int fadeValue = 127; fadeValue >= 0; fadeValue -= 5) {
			showPixels(fadeValue);
			vTaskDelay(30 / portTICK_PERIOD_MS);
		}
	}
}

void vScanPIRTask(void * pvArg) {
  for (;;) {
    if (digitalRead(PIR_PIN)) {
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

		for (auto i = 0; i < 3; i++) {
			showPixels(0);
			servo.write(40);
			delay(500);

			showPixels(127);
			servo.write(0);
			delay(500);
		}
	}
}

void setup() {
	portBASE_TYPE s1, s2, s3;

	mp3.init();
	pixels.begin();
	servo.attach(9);

	vSemaphoreCreateBinary(xPIRBinarySemaphore);
  xSemaphoreTake(xPIRBinarySemaphore, 0);

	s1 = xTaskCreate(vFadingLEDsTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	s2 = xTaskCreate(vScanPIRTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	s3 = xTaskCreate(vHandlePIRTask, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	if (xPIRBinarySemaphore == NULL || s1 != pdPASS || s2 != pdPASS || s3 != pdPASS) {
		for (;;);
	}

	vTaskStartScheduler();
}

void loop() { }
