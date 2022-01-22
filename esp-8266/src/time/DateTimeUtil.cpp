//
// Created by 钱磊 on 2021/12/22.
//

#include <Arduino.h>
#include <ESPDateTime.h>
#include "DateTimeUtil.h"


void my_date_init() {
    /** changed from 0.2.x **/
    DateTime.setTimeZone("CST-8");
    // this method config ntp and wait for time sync
    // default timeout is 10 seconds
    DateTime.begin(/* timeout param */);
    if (!DateTime.isTimeValid()) {
        Serial.println("Failed to get time from server.");
    }
}

String my_date_currentDateTime() {
    return DateTime.toString();

}

void my_date_printCurrentDate(){
    Serial.println(DateTime.now());
    Serial.println(DateTime.getTime());
//    Serial.println(DateTime.utcTime());
    Serial.println("--------------------");
    Serial.println(DateTime.toString());
    Serial.println(DateTime.toISOString());
    Serial.println(DateTime.toUTCString());
    Serial.println("--------------------");
    Serial.println(DateTime.format(DateFormatter::COMPAT));
    Serial.println(DateTime.format(DateFormatter::DATE_ONLY));
    Serial.println(DateTime.format(DateFormatter::TIME_ONLY));
    Serial.println("--------------------");
    DateTimeParts p = DateTime.getParts();
    Serial.printf("%04d/%02d/%02d %02d:%02d:%02d %lld %5s\n", p.getYear(),
                  p.getMonth(), p.getMonthDay(), p.getHours(), p.getMinutes(),
                  p.getSeconds(), p.getTime(), p.getTimeZone());
    Serial.println("--------------------");
    time_t t = DateTime.now();
    Serial.println(DateFormatter::format("%Y/%m/%d %H:%M:%S", t));
    Serial.println(DateFormatter::format("%x - %I:%M %p", t));
    Serial.println(DateFormatter::format("Now it's %F %I:%M%p.", t));
}