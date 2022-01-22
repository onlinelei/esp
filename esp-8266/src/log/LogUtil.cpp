#include <Arduino.h>
#include <ESPDateTime.h>
#include "LogUtil.h"


void my_log(const String &message) {
    String dateTime = DateTime.toString();
    Serial.print("[");
    Serial.print(dateTime);
    Serial.print("]");
    Serial.print(" --> ");
    Serial.println(message);
}