//
// Created by 钱磊 on 2021/12/22.
//

#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 60 * 60 * 8, 30 * 60 * 1000);

void my_time_init() {
    timeClient.update();
    Serial.println(String("day:") + timeClient.getDay());
    Serial.println(String("hour:") + timeClient.getHours());
    Serial.println(String("minutes:") + timeClient.getMinutes());
    Serial.println(String("second:") + timeClient.getSeconds());
    Serial.println(String("epocTime:") + timeClient.getEpochTime());
    Serial.println("formatTime:" + timeClient.getFormattedTime());
}

void my_time_sync() {
    timeClient.update();

    Serial.println(String("day:") + timeClient.getDay());
    Serial.println(String("hour:") + timeClient.getHours());
    Serial.println(String("minutes:") + timeClient.getMinutes());
    Serial.println(String("second:") + timeClient.getSeconds());
    Serial.println(String("epocTime:") + timeClient.getEpochTime());
    Serial.println("formatTime:" + timeClient.getFormattedTime());
}

String my_time_currentTimeString() {
    return timeClient.getFormattedTime();
}

