//
// Created by Administrator on 2021/12/24.
//

#ifndef ESP_8266_ST7789UTIL_H
#define ESP_8266_ST7789UTIL_H


class ST7789Util {

};


#endif //ESP_8266_ST7789UTIL_H


void my_screen_init();

void my_screen_printText(int16_t x, int16_t y, uint8_t fontSize, uint16_t color, const String &message);

void my_screen_fillScreen();


void drawX(int x, int y);

void showMessage(String msg);