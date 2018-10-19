#include "MP3.h"
#include "Seeed_MPR121_driver.h"

MP3 mp3(2, 3);
Mpr121 mpr121;

uint8_t instrument = 1;
bool touchStatus[CHANNEL_NUM] = {0};

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  if (mp3.init() && mpr121.begin() >= 0) {
    Serial.println("Initialize Success.");

    mp3.setVolume(0xff);
    mpr121.set_sensitivity(0x60); 
  } else {
    Serial.println("Initialize Failed.");
  }

  Serial.println(
    "Select a piece of instrument:\r\n"
    "1 Piano\r\n"
    "2 Drum\r\n"
  );
}

void loop() {
  uint16_t result = 0; 
  uint16_t filteredData[CHANNEL_NUM] = {0};
  
  result = mpr121.check_status_register();
  mpr121.get_filtered_reg_data((u16 *)&result, (u16 *)filteredData);

  for (int i = 0; i < CHANNEL_NUM; i++) {
    if (result & (1 << i) && !touchStatus[i]) {
      touchStatus[i] = true;
      mp3.play(instrument, i);
      
      // Serial.print("Note: ");
      // Serial.print(i);
      // Serial.println(" is pressed.");
    } else {
      if (!(result & (1 << i)) && touchStatus[i]) {
        touchStatus[i] = false;
      }
    }
  }

  if (Serial.available()) {
    switch (Serial.read() - '0') {
      case 1:
        instrument = 1;
        Serial.println("Piano is Selected.");
        break;

      case 2:
        instrument = 2;
        Serial.println("Drum is Selected.");
        break;

      default:
        break;
    }
  }

  delay(50);
}

