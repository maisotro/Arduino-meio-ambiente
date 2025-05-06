#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
// ==== CONFIGURAÇÕES ====
#define LED_PIN     4
#define LED_COUNT   14
#define PH_PIN      34 // entrada analógica do ESP32 (ADC1)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;
// ==== VARIÁVEIS ====
unsigned long lastBlink = 0;
bool ledState = false;
String faceAnim[] = {"Cara triste :-(", "Cara neutra :-|", "Cara feliz :-)"};
int blinkDelay = 500;
int activeLed = -1;
String lcdLine2 = "";
String scrollText = ""
;int scrollIndex = 0;
unsigned long lastScroll = 0;
// ==== FUNÇÃO HSV para RGB ====
uint32_t HSVtoRGB(float h, float s, float v) {
    int r, g, b;
    int i = int(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    switch (i % 6) {
      case 0: 
      r = v * 255;
      g = t * 255;
      b = p * 255;
      break;
      case 1: r = q * 255;
      g = v * 255;
      b = p * 255;
      break;
      case 2: r = p * 255;
      g = v * 255;
      b = t * 255;
      break;
      case 3: r = p * 255; g = q * 255; b = v * 255; break; 
      case 4: r = t * 255; g = p * 255; b = v * 255; break;
      case 5: r = v * 255; g = p * 255; b = q * 255; break;
      }
      return strip.Color(r, g, b);
      }
      // ==== FUNÇÃO DE CLASSIFICAÇÃO ====
      void updateDisplayAndLEDs(float pH) {
        s1trip.clear();
        activeLed = -1;
        if (pH > 0.0 && pH <= 6.0) {
          activeLed = 0;
          blinkDelay = 500;
          lcdLine2 = "Acido";
          scrollText = faceAnim[0];
          }
          else if (pH > 6.0 && pH <= 6.2){
          activeLed = 1;
          blinkDelay = 500;
          lcdLine2 = "Acido";
          scrollText = faceAnim[0];
          }
          else if (pH > 6.2 && pH <= 6.4){
          activeLed = 2;
          blinkDelay = 500;
          lcdLine2 = "Acido";
          scrollText = faceAnim[0];
          }
          else if (pH > 6.4 && pH <= 6.6){
          activeLed = 3;
          blinkDelay = 500;
          lcdLine2 = "Acido";
          scrollText = faceAnim[0];
          }
          else if (pH > 6.6 && pH <= 6.8){
          activeLed = 4;
          blinkDelay = 500;
          lcdLine2 = "Acido";
          scrollText = faceAnim[0];
          }
          else if (pH > 6.8 && pH <= 7.0){
          activeLed = 5;
          blinkDelay = 1000;
          lcdLine2 = "Neutro";
          scrollText = faceAnim[1];
          }
          else if (pH > 7.0 && pH <= 7.2){
          activeLed = 6;
          blinkDelay = 1000;
          lcdLine2 = "Neutro";
          scrollText = faceAnim[1];
          }
          else if (pH > 7.2 && pH <= 7.4){
          activeLed = 7;
          blinkDelay = 2000;
          lcdLine2 = "Alcalino";
          scrollText = faceAnim[2];
          }
          else if (pH > 7.4 && pH <= 7.6){
          activeLed = 8;
          blinkDelay = 2000;
          lcdLine2 = "Alcalino";
          scrollText = faceAnim[2];
          }
          else if (pH > 7.6 && pH <= 7.8){
          activeLed = 9;
          blinkDelay = 500;
          lcdLine2 = "Alcalino";
          scrollText = faceAnim[0];
          }
          else if (pH > 7.8 && pH <= 8.0){
          activeLed = 10;
          blinkDelay = 500;
          lcdLine2 = "Alcalino";
          scrollText = faceAnim[0];
          }
          else if (pH > 8.0 && pH <= 8.2)
          { activeLed = 11; blinkDelay = 500;
            lcdLine2 = "Alcalino";
             scrollText = faceAnim[0];
              }
                else if (pH > 8.2 && pH <= 8.4)   { 
                  activeLed = 12; blinkDelay = 500;
                    lcdLine2 = "Alcalino";
                     scrollText = faceAnim[0];
                      }  else if (pH > 8.4){
                        activeLed = 13; blinkDelay = 500;
                          lcdLine2 = "Alcalino";
                           scrollText = faceAnim[0];
                           }
if (activeLed >= 0) {
float hsvColors[][3] = { {0.096, 0.93, 0.3}, {0.097, 0.97, 0.2}, {0.094, 0.992, 0.98}, {0.14, 0.99, 0.30},{0.27, 0.99, 0.30}, {0.33, 0.99, 0.30}, {0.34, 0.99, 0.19}, {0.36, 0.99, 0.20},{0.34, 0.97, 0.51}, {0.58, 0.92, 0.54}, {0.58, 0.96, 0.41}, {0.61, 0.97, 0.27},      {0.74, 0.97, 0.34}, {0.74, 0.97, 0.34}    };
auto color = HSVtoRGB(hsvColors[activeLed][0], hsvColors[activeLed][1], hsvColors[activeLed][2]);
if (ledState) strip.setPixelColor(activeLed, color); 
strip.show();
}
lcd.setCursor(0, 0);
lcd.print("Sensor de pH: ");
lcd.print(String(pH, 2));
lcd.setCursor(0, 1);
lcd.print(" ");  // limpa linha
lcd.setCursor((16 - lcdLine2.length()) / 2, 1);
lcd.print(lcdLine2);
}
// ==== SETUP ====
void setup() {
Serial.begin(115200);
Wire.begin(21, 22);
strip.begin();
strip.clear();
strip.show();
lcd.init();
lcd.backlight();
rtc.begin();
}
// ==== LOOP ====
void loop() {
int rawValue = analogRead(PH_PIN);
float voltage = rawValue * (3.3 / 4095.0);
float pH = 7 + ((2.5 - voltage) / 0.18);
// ajuste da calibração
updateDisplayAndLEDs(pH);  // Piscar LED  
if (millis() - lastBlink >= blinkDelay) { 
  ledState = !ledState;  
  lastBlink = millis();
    }
// Scroll animado
if (millis() - lastScroll >= 1000) {
lcd.setCursor(0, 1);
String scrollOut = scrollText.substring(scrollIndex) + " " + scrollText.substring(0, scrollIndex);
lcd.print(scrollOut.substring(0, 16));
scrollIndex = (scrollIndex + 1) % scrollText.length();
lastScroll = millis();  }  
delay(100);
}