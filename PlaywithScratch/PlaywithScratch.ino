#include "Seeed_MPR121_driver.h"

Mpr121 mpr121;

bool touchStatus[CHANNEL_NUM] = {0};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (mpr121.begin() >= 0) {
    Serial.println("init success.");
    
    mpr121.set_sensitivity(0x60); 
  } else {
    Serial.println("init failed.");
  }
}

void loop() {
  uint16_t result = 0;
  uint16_t filteredData[CHANNEL_NUM] = {0};
  
  result = mpr121.check_status_register();
  mpr121.get_filtered_reg_data((u16 *)&result, (u16 *)filteredData);

  for (uint8_t i = 0; i < CHANNEL_NUM; i++) {
    if (result & (1 << i) && !touchStatus[i]) {
      touchStatus[i] = true;
      Serial.write(0x00 | i);
      
      //Serial.print(i);
      //Serial.println(" is pressed.");
    } else {
      if (!(result & (1 << i)) && touchStatus[i]) {
        touchStatus[i] = false;
        Serial.write(0x80 | i);
        
        //Serial.print(i);
        //Serial.println(" is released.");
      }
    }
  }
  
  delay(10);
}
