# Play with Scratch
How to play a scratch game with a Touch Sensor?

## Things used in this project
### Hardware components
- Seeeduino V4.2
- Seeed Grove - 12 Key Capacitive I2C Touch Sensor V2 (MPR121)
### Software apps and online services
- Arduino IDE

## Story
If we use Seeeduino Lite, we can play acratch games with Touch Sensor via simulating keyboard operations. But here we try to use a Seeeduino.
### Hardware connection
Connect Touch Sensor Grove to I2C port in Seeeduino, then connect Seeeduino to your PC via a USB cable.
### Software programming
**Step 1: **Run KeyboardServer.exe in project root folder, if the application doesn't run, try to install [.Net Framework](https://www.microsoft.com/net/download) to you PC.

**Step 2: **Upload Seeeduino's program to it. Choose Seeeduino's port in Port Name combobox on Settings window, if you don't see the port, click Refresh button on the right.

**Step 3: **Turn to Keys tab, choose channel's mapping key in channel's combobox, and enable it by checking the checkbox.

**Step 4: **Close the Settings window, and find Seeed Keyboard Server's icon in Windows notification area, right  click on it, choose Start to start the server.

Now you can play scratch games with Touch Sensor.

**NOTE: **Before you upload program to Seeeduino, or uses other serial software on it, Stop or Quit Keyboard Server.

## Operation

## Code
