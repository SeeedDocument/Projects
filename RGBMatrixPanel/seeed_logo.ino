// testshapes demo for RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x64 RGB LED matrix.

// WILL NOT FIT on ARDUINO UNO -- requires a Mega, M0 or M4 board

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

//#define CLK  8   // USE THIS ON ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() {

  matrix.begin();

  // draw a pixel in solid white
  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7));
  delay(500);

  // fix the screen with green
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));
  delay(500);

  // draw a box in yellow
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 7, 0));
  delay(500);

  // draw an 'X' in red
  matrix.drawLine(0, 0, matrix.width()-1, matrix.height()-1, matrix.Color333(7, 0, 0));
  matrix.drawLine(matrix.width()-1, 0, 0, matrix.height()-1, matrix.Color333(7, 0, 0));
  delay(500);

  // draw a blue circle
  matrix.drawCircle(10, 10, 10, matrix.Color333(0, 0, 7));
  delay(500);

  // fill a violet circle
  matrix.fillCircle(40, 21, 10, matrix.Color333(7, 0, 7));
  delay(500);

  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));
/************************************************************************************/
//显示SeeedStudio
  // draw some text!
  matrix.setTextSize(2);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  matrix.setCursor(3, 0);    // start at top left, with 8 pixel of spacing

 matrix.setTextColor(matrix.Color333(7,0,0));//绿色
 matrix.print("Seeed");

  matrix.setTextSize(1); 
  matrix.setCursor(14, 16);    // next line 

  matrix.setTextColor(matrix.Color333(7,7,0));
  matrix.println("Studio");//换行输出
 /************************************************************************************/
  matrix.setTextColor(matrix.Color333(0,0,7));//红色
  matrix.println("TechSupport");//换行输出
  delay(500);
}
void loop(){
  matrix.setCursor(0, 24);   
  matrix.setTextColor(matrix.Color333(0,0,0));
  matrix.print("TechSupport");//换行输出
  delay(500);
  delay(500);
  matrix.setCursor(0, 24);  
  matrix.setTextColor(matrix.Color333(0,0,7));//红色
  matrix.print("TechSupport");//换行输出
  delay(500);
  delay(500);
  delay(500);
  delay(500);
}


