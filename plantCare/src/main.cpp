//
// Created by 钱磊 on 2022/3/4.

#include <Arduino.h>
#include <TFT_eSPI.h>

int a = 0;
// GPIO4 控制电机 mos 管
int MOTOR_PIN = 4;
TFT_eSPI tft = TFT_eSPI();

void setup() {
    // 设置串口速率
    Serial.begin(115200);
    Serial.println("8266 Begin!!!");

    // 设置引脚状态
//    pinMode(BUILTIN_LED, OUTPUT);
//    pinMode(MOTOR_PIN, OUTPUT);

    // 初始化屏幕
    //Set up the display
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(0, 0);

    // 开机显示
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_CYAN);
    tft.setCursor(20, 12);
    tft.println(F("Plant Carer"));

    tft.setTextSize(1);
    tft.setCursor(70, 60);
    tft.setTextColor(TFT_BLUE);
    tft.println(F("Version 1.0"));

    delay(6000);
    tft.fillScreen(TFT_BLACK);
}


void loop() {

    // 控制led
//    digitalWrite(BUILTIN_LED, LOW);
//    delay(200);
//    digitalWrite(BUILTIN_LED, HIGH);


    // 控制电机
//    delay(1000);
//    digitalWrite(MOTOR_PIN, HIGH);
//    // 浇水时间 30 秒
//    delay(1000 * 1);
//    digitalWrite(MOTOR_PIN, LOW);



    // 状态显示
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.setTextColor(0x4810);
    tft.println(F("Status:"));
    tft.setCursor(0, 20);
    tft.println(F("Count:"));
    tft.setCursor(0, 40);
    tft.println(F("Time:"));
    delay(3000);

    // 休息时间
    delay(1000 * 2);
}