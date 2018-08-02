const uint8_t blue = 23;
const uint8_t vbatPin = 35;
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
float VBAT;  // battery voltage from ESP32 ADC read
SSD1306  display(0x3c, 21, 22);
void setup() 
{
  Serial.begin(115200);
  pinMode(blue, OUTPUT);
  pinMode(vbatPin, INPUT);
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}
char string[25];
void drawFontFaceDemo(float Vbat) {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Battery");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Monitoring");
    display.setFont(ArialMT_Plain_24);
    itoa(Vbat,string,10);
    sprintf(string,"%7.5f",Vbat);
    display.drawString(0, 26, string);
}

void loop() 
{
  digitalWrite(blue, 1);
  delay(100);
  digitalWrite(blue, 0);
  delay(100);
  digitalWrite(blue, 1);
  delay(100);
  
  // Battery Voltage
//  VBAT = (120.0/20.0) * (float)(analogRead(vbatPin)) / 1024.0; // LiPo battery voltage in volts
//   VBAT = (float)(analogRead(vbatPin))/(4095)*2*3.3*1.1;
   VBAT = (float)(analogRead(vbatPin)) / 4095*2*3.3*1.1;
  Serial.println("Vbat = "); Serial.print(VBAT); Serial.println(" Volts");
  display.clear();
  drawFontFaceDemo(VBAT);
   display.display();
  digitalWrite(blue, 0);
  delay(700);

}
