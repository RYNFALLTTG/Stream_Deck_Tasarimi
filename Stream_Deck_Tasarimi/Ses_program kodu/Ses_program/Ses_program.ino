const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};
int x;
 int genislik = 128;
int yukseklik = 32;
int adres = 0x3C;

#include "SPI.h"            
#include "Wire.h"            
#include "Adafruit_SSD1306.h"

int analogSliderValues[NUM_SLIDERS];
  Adafruit_SSD1306 ekran(genislik, yukseklik, &Wire);
void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  Serial.begin(9600);

ekran.begin(SSD1306_SWITCHCAPVCC, adres);

}

void loop() {
ekran.clearDisplay();
ekran.setTextSize(4);
ekran.setTextColor(SSD1306_WHITE);
  
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
   
      x=round(analogSliderValues[1]);
      x=map(x,0,1020,0,100);
      ekran.setCursor(40, 0);
      ekran.println(x); 
      ekran.display();
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());
    
    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
