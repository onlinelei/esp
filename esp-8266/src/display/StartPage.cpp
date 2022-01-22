//
// Created by 钱磊 on 2021/12/30.
//
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "StartPage.h"

TFT_eSPI tftPage = TFT_eSPI();

// With 1024 stars the update rate is ~65 frames per second
#define NSTARS 1024
uint8_t sx[NSTARS] = {};
uint8_t sy[NSTARS] = {};
uint8_t sz[NSTARS] = {};

uint8_t za, zb, zc, zx;

// Fast 0-255 random number generator from http://eternityforest.com/Projects/rng.php:
uint8_t __attribute__((always_inline)) rng() {
    zx++;
    za = (za ^ zc ^ zx);
    zb = (zb + za);
    zc = ((zc + (zb >> 1)) ^ za);
    return zc;
}


void my_page_starField() {

    za = random(256);
    zb = random(256);
    zc = random(256);
    zx = random(256);

    Serial.begin(115200);
    tftPage.init();
    tftPage.setRotation(1);
    tftPage.fillScreen(TFT_BLACK);
    // fastSetup() must be used immediately before fastPixel() to prepare screen
    // It must be called after any other graphics drawing function call if fastPixel()
    // is to be called again
    //tft.fastSetup(); // Prepare plot window range for fast pixel plotting

    for (int i = 0; i < 10000; ++i) {
        unsigned long t0 = micros();
        uint8_t spawnDepthVariation = 255;

        for (int i = 0; i < NSTARS; ++i) {
            if (sz[i] <= 1) {
                sx[i] = 160 - 120 + rng();
                sy[i] = rng();
                sz[i] = spawnDepthVariation--;
            } else {
                int old_screen_x = ((int) sx[i] - 160) * 256 / sz[i] + 160;
                int old_screen_y = ((int) sy[i] - 120) * 256 / sz[i] + 120;

                // This is a faster pixel drawing function for occassions where many single pixels must be drawn
                tftPage.drawPixel(old_screen_x, old_screen_y, TFT_BLACK);

                sz[i] -= 2;
                if (sz[i] > 1) {
                    int screen_x = ((int) sx[i] - 160) * 256 / sz[i] + 160;
                    int screen_y = ((int) sy[i] - 120) * 256 / sz[i] + 120;

                    if (screen_x >= 0 && screen_y >= 0 && screen_x < 320 && screen_y < 240) {
                        uint8_t r, g, b;
                        r = g = b = 255 - sz[i];
                        tftPage.drawPixel(screen_x, screen_y, tftPage.color565(r, g, b));
                    } else
                        sz[i] = 0; // Out of screen, die.
                }
            }
        }
        unsigned long t1 = micros();
        //static char timeMicros[8] = {};

        // Calcualte frames per second
        Serial.println(1.0 / ((t1 - t0) / 1000000.0));
    }

}