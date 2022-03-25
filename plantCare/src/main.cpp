//
// Created by 钱磊 on 2022/3/4.
//

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();
int a = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("8266 Begin!!!");
    pinMode(BUILTIN_LED, OUTPUT);

    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(0, 0);
}


void loop() {

    digitalWrite(BUILTIN_LED, LOW);
    delay(1000);
    digitalWrite(BUILTIN_LED, HIGH);

    tft.setTextSize(1);
    tft.setTextColor(RANDOM_REG32);
//    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.println("hello");



    delay(2000);
}