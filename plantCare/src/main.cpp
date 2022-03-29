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
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(20, 12);
    tft.println(F("Plant Carer"));

    tft.setTextSize(1);
    tft.setCursor(70, 60);
    tft.setTextColor(TFT_DARKGREEN);
    tft.println(F("Version: 1.0"));

    delay(300);

    for (int i = 0; i < 60; ++i) {
        tft.setCursor(10 + i * 2, 70);
        tft.println(F("."));
        delay(100);
    }

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



    // 状态显示界面1
    tft.drawLine(0, 0, 0, 80, TFT_DARKCYAN);
    tft.drawLine(0, 0, 159, 0, TFT_DARKCYAN);
    tft.drawLine(159, 0, 159, 79, TFT_DARKCYAN);
    tft.drawLine(0, 79, 159, 79, TFT_DARKCYAN);

    tft.drawLine(0, 17, 159, 17, TFT_DARKCYAN);
    tft.drawLine(0, 34, 159, 34, TFT_DARKCYAN);
    tft.drawLine(0, 51, 159, 51, TFT_DARKCYAN);
    tft.drawLine(70, 0, 70, 51, TFT_DARKCYAN);


    tft.setTextSize(2);
    tft.setCursor(2, 2);
    tft.setTextColor(TFT_DARKCYAN);
    tft.println(F("stat:"));
    tft.setCursor(2, 19);
    tft.println(F("coun:"));
    tft.setCursor(2, 36);
    tft.println(F("time:"));

    tft.setTextSize(1);
    tft.setCursor(2, 53);
    tft.println(F("plant care started"));


    tft.fillScreen(TFT_BLACK);

    // 状态显示界面2
//    tft.pushImage()


    // 休息时间
    delay(1000 * 2);
}