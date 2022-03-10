//
// Created by 钱磊 on 2022/3/4.
//

#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println("8266 Begin!!!");
    pinMode(BUILTIN_LED, OUTPUT);
}


void loop() {

    digitalWrite(BUILTIN_LED, LOW);
    delay(1000);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(2000);
}