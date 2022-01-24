//
// Created by Administrator on 2021/12/24.
//

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "ST7789Util.h"

// 声明一个eSprinte对象。并将这个sprite对象和tft屏幕关联。
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

void my_screen_init() {
    //Set up the display
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(0, 0);

//    spr.createSprite(240, 240);
//    spr.fillScreen(TFT_BLACK);
    // Create the Sprite
//    spr.setColorDepth(8);      // Create an 8bpp Sprite of 60x30 pixels
//    spr.createSprite(240, 240);  // 8bpp requires 64 * 30 = 1920 bytes
//    spr.setPivot(120, 120);      // Set pivot relative to top left corner of Sprite
//    spr.fillSprite(TFT_BLACK); // Fill the Sprite with black
}

void my_screen_printText(int16_t x, int16_t y, uint8_t fontSize, uint16_t color, const String &message) {
//    //Display a simple splash screen
////    spr.fillScreen(TFT_BLACK);
    tft.setTextSize(fontSize);
////    tft.setTextColor(TFT_WHITE);
    tft.setTextColor(color);
    tft.setCursor(x, y);
    tft.println(message);
//
////    tft.fillRect(CELLXY * x, CELLXY * y, CELLXY, CELLXY, color);
////    tft.fillScreen(TFT_BLACK);

//    int xw = tft.width() / 2;   // xw, yh is middle of screen
//    int yh = tft.height() / 2;
//
//
//    showMessage("90 degree angles");
//    tft.setPivot(xw, yh);     // Set pivot to middle of TFT screen
//    drawX(xw, yh);            // Show where screen pivot is
//
//    // Create the Sprite
//    spr.setColorDepth(8);      // Create an 8bpp Sprite of 60x30 pixels
//    spr.createSprite(64, 30);  // 8bpp requires 64 * 30 = 1920 bytes
//    spr.setPivot(32, 55);      // Set pivot relative to top left corner of Sprite
//    spr.fillSprite(TFT_BLACK); // Fill the Sprite with black
//
//    spr.setTextColor(TFT_GREEN);        // Green text
//    spr.setTextDatum(MC_DATUM);         // Middle centre datum
//    spr.drawString("Hello", 32, 15, 4); // Plot text, font 4, in Sprite at 30, 15
//
//    spr.pushRotated(0);
//    spr.pushRotated(90);
//    spr.pushRotated(180);
//    spr.pushRotated(270);
//
//    delay(2000);
//
//
//    showMessage("45 degree angles");
//    drawX(xw, yh);            // Show where screen pivot is
//
//    spr.pushRotated(45);
//    spr.pushRotated(135);
//    spr.pushRotated(225);
//    spr.pushRotated(315);
//
//    delay(2000);  // Pause so we see it
//
//
//    showMessage("Moved Sprite pivot point");
//    drawX(xw, yh);          // Show where screen pivot is
//
//    spr.setPivot(-20, 15);  // Change just the Sprite pivot point
//
//    spr.pushRotated(45);
//    spr.pushRotated(135);
//    spr.pushRotated(225);
//    spr.pushRotated(315);
//
//    delay(2000);  // Pause so we see it
//
//
//    showMessage("Moved TFT pivot point");
//    tft.setPivot(100, 100); // Change just the TFT pivot point
//    drawX(100, 100);        // Show where pivot is
//
//    spr.pushRotated(45);
//    spr.pushRotated(135);
//    spr.pushRotated(225);
//    spr.pushRotated(315);
//
//    delay(2000);  // Pause so we see it
//
//
//    showMessage("Transparent rotations");
//    tft.fillCircle(xw, yh, 70, TFT_DARKGREY); // Draw a filled circle
//
//    tft.setPivot(xw, yh);         // Set pivot to middle of screen
//    drawX(xw, yh);                // Show where pivot is
//
//    spr.deleteSprite();
//
//    spr.setColorDepth(8);         // Create a 8bpp Sprite
//    spr.createSprite(40, 30);     // Create a new Sprite 40x30
//    spr.setPivot(20, 70);         // Set Sprite pivot at 20,80
//
//    spr.setTextColor(TFT_RED);    // Red text in Sprite
//    spr.setTextDatum(MC_DATUM);   // Middle centre datum
//
//    int num = 1;
//
//    for (int16_t angle = 30; angle <= 360; angle += 30)
//    {
//        spr.fillSprite(TFT_BLACK);         // Clear the Sprite
//        spr.drawNumber(num, 20, 15, 4);    // Plot number, in Sprite at 20,15 and with font 4
//        spr.pushRotated(angle, TFT_BLACK); // Plot rotated Sprite, black being transparent
//        num++;
//    }
//
//    spr.setTextColor(TFT_WHITE);    // White text in Sprite
//    spr.setPivot(-75, 15);          // Set Sprite pivot at -75,15
//
//    for (int16_t angle = -90; angle < 270; angle += 30)
//    {
//        spr.fillSprite(TFT_BLACK);           // Clear the Sprite
//        spr.drawNumber(angle+90, 20, 15, 4); // Plot number, in Sprite at 20,15 and with font 4
//        spr.pushRotated(angle, TFT_BLACK);   // Plot rotated Sprite, black being transparent
//        num++;
//    }
//
//    delay(8000);  // Pause so we see it
//
//    spr.deleteSprite();
}

void my_screen_fillScreen() {
//    tft.pushSprite(0, 0);
    tft.fillScreen(TFT_BLACK);
}



// =======================================================================================
// Draw an X centered on x,y
// =======================================================================================

void drawX(int x, int y)
{
    tft.drawLine(x - 5, y - 5, x + 5, y + 5, TFT_WHITE);
    tft.drawLine(x - 5, y + 5, x + 5, y - 5, TFT_WHITE);
}

// =======================================================================================
// Show a message at the top of the screen
// =======================================================================================

void showMessage(String msg)
{
    // Clear the screen areas
    tft.fillRect(0, 0, tft.width(), 20, TFT_BLACK);
    tft.fillRect(0, 20, tft.width(), tft.height() - 20, TFT_BLUE);

    uint8_t td = tft.getTextDatum(); // Get current datum

    tft.setTextDatum(TC_DATUM);      // Set new datum

    tft.drawString(msg, tft.width() / 2, 2, 2); // Message in font 2

    tft.setTextDatum(td); // Restore old datum
}

void test(){
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);

    tft.drawString("012345", 0, 0, 6);
    tft.drawString("6789", 0, 40, 6);
    tft.drawString("apm-:.", 0, 80, 6);
//    delay(WAIT);
}
