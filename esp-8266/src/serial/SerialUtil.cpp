//
// Created by 钱磊 on 2021/12/21.
//

#include "SerialUtil.h"
#include <Arduino.h>

void my_serial_reciveString() {
    // 当串口接收到信息后
    // 将接收到的信息使用readString()存储于serialData变量
    // 以便查看serialData变量的信息
    if (Serial.available()) {
        String serialData = Serial.readString();
        Serial.println(serialData);
    }
}

void my_serial_receiveInt() {
    // 当串口接收到信息后
    if (Serial.available()) {
        int intValue = Serial.parseInt();
        Serial.println(intValue);
    }
}