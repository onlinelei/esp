//
// Created by 钱磊 on 2022/3/4.

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "font.h"
#include "jpeg4.h"
#include "Free_Fonts.h" // Include the header file attached to this sketch

int a = 0;
// GPIO4 控制电机 mos 管
int MOTOR_PIN = 4;
TFT_eSPI tft = TFT_eSPI();

#define PI_BUF_SIZE 128
void showImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data){
    int32_t dx = 0;
    int32_t dy = 0;
    int32_t dw = w;
    int32_t dh = h*2;

    if (x < 0) { dw += x; dx = -x; x = 0; }
    if (y < 0) { dh += y; dy = -y; y = 0; }

    if (dw < 1 || dh < 1) return;


    data += dx + dy * w;

    uint16_t  buffer[PI_BUF_SIZE];
    uint16_t* pix_buffer = buffer;
    uint16_t  high,low;

    tft.setWindow(x, y, x + dw - 1, y + dh - 1);

    // Work out the number whole buffers to send
    uint16_t nb = (dw * dh) / (2 * PI_BUF_SIZE);

    // Fill and send "nb" buffers to TFT
    for (int32_t i = 0; i < nb; i++) {
        for (int32_t j = 0; j < PI_BUF_SIZE; j++) {
            high = pgm_read_word(&data[(i * 2 * PI_BUF_SIZE) + 2 * j + 1]);
            low = pgm_read_word(&data[(i * 2 * PI_BUF_SIZE) + 2 * j ]);
            pix_buffer[j] = (high<<8)+low;
        }
        tft.pushPixels(pix_buffer, PI_BUF_SIZE);
    }

    // Work out number of pixels not yet sent
    uint16_t np = (dw * dh) % (2 * PI_BUF_SIZE);

    // Send any partial buffer left over
    if (np) {
        for (int32_t i = 0; i < np; i++)
        {
            high = pgm_read_word(&data[(nb * 2 * PI_BUF_SIZE) + 2 * i + 1]);
            low = pgm_read_word(&data[(nb * 2 * PI_BUF_SIZE) + 2 * i ]);
            pix_buffer[i] = (high<<8)+low;
        }
        tft.pushPixels(pix_buffer, np);
    }
}


void setup() {
    // 设置串口速率
    Serial.begin(115200);
    Serial.println("8266 Begin!!!");

    // 设置引脚状态
//    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);

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
    tft.setCursor(15, 12);
    tft.println(F("Plant Carer"));

    tft.setTextSize(1);
    tft.setCursor(70, 50);
    tft.setTextColor(TFT_DARKGREEN);
    tft.println(F("Version: 1.0"));

    delay(300);

    for (int i = 0; i < 70; ++i) {
        tft.setCursor(10 + i * 2, 70);
        tft.println(F(">"));
        delay(100);
    }

    tft.fillScreen(TFT_BLACK);
}


void loop() {

    // 控制led 会使显示屏幕异常
//    digitalWrite(BUILTIN_LED, LOW);
//    delay(200);
//    digitalWrite(BUILTIN_LED, HIGH);


    // 控制电机
    delay(1000);
    digitalWrite(MOTOR_PIN, HIGH);
    // 浇水时间 30 秒
    delay(1000 * 1);
    digitalWrite(MOTOR_PIN, LOW);


    tft.fillScreen(TFT_BLACK);
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
    delay(1000 * 2);

    tft.fillScreen(TFT_BLACK);

    // 状态显示界面2
//    tft.pushImage()
    tft.pushImage(4,4,40, 40, image);
    tft.pushImage(60,0,31, 31, Hzk32);

    delay(1000 * 2);
    tft.fillScreen(TFT_BLACK);
    showImage(4,4,40, 40, image);


    delay(1000 * 2);
    tft.fillScreen(TFT_BLACK);
    showImage(60,6,32, 32, Hzk32);

    delay(1000 * 2);
    tft.fillScreen(TFT_BLACK);

    tft.pushImage(0,0,299, 299, EagleEye);


    delay(1000 * 2);
    tft.fillScreen(TFT_BLACK);
//    tft.drawBitmap()

    delay(1000 * 2);
}