# Pumpkin Lantern

We built a pumpkin lantern which will play music and spit candies when somebody comes up to it. 

## Things used in this project

### Hardware components

- Seeeduino V4.2
- Base Shield V2
- Grove - PIR Motion Sensor
- NeoPixel strip
- Grove - MP3 v2.0
- EMax 12g ES08MD high Sensitive servo

### Software apps and online services

- Arduino IDE

## Story

Halloween is coming, pumpkin lanterns are essential. We use Seeeduino and PIR Motion Senser built an pumpkin lantern, when somebody comes up to it, it will play music and spit candies. 

### Mechanial structure

**Step 1: **Buy some candies and a pumpkin, dig a hole behind the pumpkin so that we can put Seeeduino to it.

**Step 2: **Cut a box like this, and fix it to the mouth of pumpkin.

![p1](\images\p1.jpg)

**Setp 3: **Mount a arm to the servo motor. To fix a servo motor inside the pumpkin, we use a can as a holder. 

**Step 4: **Make sure when the servo motor arm turns up, candies in the box will be spit out from the pumpkin's mouth. 

![p2](\images\p2.jpg)

*TIPS: If we put something heavy in the back of the box, the effect will be better.*

### Hardware Connection

**Step 1: **Make a folder named MP3 in a piece of SD card, copy a mp3 file to it, name it 0001.mp3. Connect a speaker to MP3 Grove's via 3.5mm port, and connect MP3 Grove to port D2 on Base Shield.

**Step 2: **Connect PIR Motion Sensor Grove to Base Shield's D4 port, and connect NeoPixel strip to Base Shield's D5 port.

**Step 3: **Connect Servo Grove to Base Shield's digital pin 9, so we may need to use the DuPont lines.

**Step 4: **plug Base Shield to Seeeduino.

![p3](\images\p3.jpg)

**Step 5: **To download the program to Seeeduino, we use an USB cable connection it to computer. After downloaded, we can only use a power cable inside pumpkin.

### Software Programming

**Step 1: **Install Libraries

For better effect, we use an operating system called FreeRTOS, it can be downloaded from [here](https://github.com/greiman/FreeRTOS-Arduino).

Besides, this project needs the following libraries, download and install them: 

- [Grove - MP3 v2.0](https://github.com/Seeed-Studio/Grove_Serial_MP3_Player_V2.0)
- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [Adafruit TicoServo](https://github.com/adafruit/Adafruit_TiCoServo)

Or you can simply include MP3.h in the project folder to use MP3 Grove.

**Step 2: **Build and upload the program

*NOTICE: Marco MAX_BRIGHTNESS control the max brightness of NeoPixel, reduce the brightness of it to reduce power consumption.*

It may be hard to understand the program if you didn't use operating system on Seeeduino before, following article will make it simply.

In setup() method, we initialized Serial, MP3 Grove and Servo Motor normally, and created a varible we call semaphore, you can consider it as a flag variable which used to indicate if it is somebody comes or not.

    vSemaphoreCreateBinary(xPIRBinarySemaphore);
 
Then we created 3 tasks, they can run together. But the priorities of then may not be the same.

    s1 = xTaskCreate(vFadingLEDsTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    s2 = xTaskCreate(vScaningPIRTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    s3 = xTaskCreate(vHandlePIRTask, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

After checking semaphore and tasks are initialized currectly, the vTaskSetartScheduler() method start the entire FreeRTOS.


    if (xPIRBinarySemaphore == NULL || s1 != pdPASS || s2 != pdPASS || s3 != pdPASS) {
    	for (;;);
    }
    
    vTaskStartScheduler();

The loop() method nerver used in FreeRTOS. Now the rest is simple, vFadingLEDsTask task fading Variable Color LED and vScanPIRTask task scan PIR Motion Sensor' pin all the time. When PIR Motion Sensor detect somebody is coming, it set the flag, then the vHandlePIRTask task start running. Because the priority of vHandlePIRTask task is 2, when it is running, other two remaining tasks will be suspened.

Following calls are used to set or reset a flag.

    xSemaphoreGive(xPIRBinarySemaphore);
    xSemaphoreTake(xPIRBinarySemaphore, portMAX_DELAY);

## Operation
Put the speaker, Seeeduino and Groves inside the pumpkin lantern, and power it on. Now you can waiting somebody comes to it, Trick or Treat :-).

[Halloween pumpkin light](https://youtu.be/CFjuWXOIUN4)