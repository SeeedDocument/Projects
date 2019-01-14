/*
 * valentines_day.ino
 * Main file of Valentine's Day project.
 * Use Grove - Water Sensor and Grove - RGB LED Matrix w/Driver interaction 
 * with people.
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : L. Blu
 * Created Time: Jan 2019
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
#include "grove_two_rgb_led_matrix.h"

#define SENSOR_PIN            2
#define INTERVAL              500

#define WAIT_MATRIX_READY()   \
  delay(1000)
#define EMOJI(array, index)   \
  (array + index * 8)
#define EMOJI_COUNT(array)    \
  (sizeof(array) / sizeof(array[0]) / 8)

GroveTwoRGBLedMatrixClass matrix;
uint64_t example[] = {

  0xffffffffffffffff,
  0xffffffffffffffff,
  0xffff00ffff00ffff,
  0xff000000000000ff,
  0xff000000000000ff,
  0xffff00000000ffff,
  0xffffff0000ffffff,
  0xffffffffffffffff,
 
  0xffffffffffffffff,
  0xffe9e9ffffe9e9ff,
  0xe9e900e9e900e9e9,
  0xe9000000000000e9,
  0xffe900000000e9ff,
  0xffffe90000e9ffff,
  0xffffffe9e9ffffff,
  0xffffffffffffffff,
 
  0xffdedeffffdedeff,
  0xdee9e9dedee9e9de,
  0xdee900e9e900e9de,
  0xde000000000000de,
  0xdee900000000e9de,
  0xffdee90000e9deff,
  0xffffdee9e9deffff,
  0xffffffdedeffffff
};

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  
  WAIT_MATRIX_READY();
}

void loop() {
  if (digitalRead(SENSOR_PIN) == LOW) {
    for (uint8_t i = 0; i < EMOJI_COUNT(example); ++i) {
      matrix.displayFrames(EMOJI(example, i), INTERVAL, false, 1);
      delay(INTERVAL);
    }
  }
}
