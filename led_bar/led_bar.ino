#include "LEDBar.h"

LEDBar bar(9, 8, 2);

void setup() {
  bar.begin();
}

void loop() {
  bar.setBits(0x01f);
}
