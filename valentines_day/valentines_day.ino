/*
 * valentines_day.ino
 * Main file of Valentine's Day project.
 * Use Grove - Gesture V1.0 and Grove - Red LED Matrix w/Driver interaction 
 * with people.
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Yuki ZHU
 * Created Time: Dec 2018
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
#include "Grove_LED_Matrix_Driver_HT16K33.h"
#include "MsTimer2.h"
#include "paj7620.h"
#include "Wire.h"

#define TIMEOUT             5000
#define GES_REG_ADDR        0x43
#define ARRAY_LENGTH(array) \
  (sizeof(array) / sizeof(array[0]))

Matrix_8x8 matrix;
uint64_t matrixDisplay = 0;
unsigned long prevTime = millis();

int8_t sIndex = 0;
bool showStatic = true;
const uint64_t STATIC[] = {
  0x00003c000000e700,
  0x00003c004242e700
};

int8_t dIndex = 0;
const uint64_t DYNAMIC[] = {
  0x00003c000021e700,
  0x00003c000042e700,
  0x00003c000084e700
};

const uint64_t HEART[] = {
  0x00183c7e7e240000,
  0x00183c7effff6600,
  0x183c7effffffff66,
  0x00183c7effff6600
};

void displayStatic(void) {
  if (showStatic) {
    matrixDisplay = STATIC[sIndex];
    sIndex = (sIndex + 1) % ARRAY_LENGTH(STATIC);
  }
}

void heartBeat() {
  for (uint8_t i = 0; i < ARRAY_LENGTH(HEART); ++i) {
    matrix.writeOnePicture(HEART[i]);
    matrix.display();
    delay(500);
  }
}

void displayDynamic(bool leftToRight) {
  unsigned long currentTime = millis();
  if (currentTime - prevTime > TIMEOUT) {
    dIndex = leftToRight ? 0 : ARRAY_LENGTH(DYNAMIC) - 1;
    showStatic = false;
  }

  
  // This is used to avoid exceed the boundary.
  if (dIndex >= ARRAY_LENGTH(DYNAMIC) || dIndex <= -1) {
    heartBeat();
    dIndex = leftToRight ? ARRAY_LENGTH(DYNAMIC) - 1 : 0;
  }
  
  prevTime = currentTime;
  matrixDisplay = DYNAMIC[leftToRight ? dIndex++ : dIndex--];
}

void setup() {
  // Initialized the serial to debug.
  Serial.begin(9600);
  while(!Serial);
  
  uint8_t errorCode = paj7620Init();
  
  Wire.begin();
  matrix.init();
  matrix.setBrightness(15);
  matrix.setBlinkRate(BLINK_OFF);
  
  MsTimer2::set(1000, displayStatic);
  MsTimer2::start();
}

void loop() {
  uint8_t data, errorCode = paj7620ReadReg(GES_REG_ADDR, 1, &data);
  
  if (!errorCode) {
    switch (data) {
      case GES_RIGHT_FLAG:
        displayDynamic(true);
        break;

      case GES_LEFT_FLAG: 
        displayDynamic(false);
        break;
    }
  }

  if (millis() - prevTime > TIMEOUT) {
    showStatic = true;
  }

  matrix.writeOnePicture(matrixDisplay);
  matrix.display();
  
  delay(100);
}
