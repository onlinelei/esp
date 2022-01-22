### 将下面代码拷贝到main.cpp
```c++
#include <Arduino.h>
#include <wifi/WifiUtil.h>


void setup() {
// 初始化串口
    Serial.begin(115200);
    Serial.println("8266 Begin!!!");

    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    // 设置wifi模式
    my_wifi_setWifiMode_STA();
    my_wifi_disconnect();
}

void loop() {
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_BUILTIN, HIGH);
    my_wifi_scanAndPrintWifi();
    // wait for a second
    delay(6000);
    // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);

    Serial.println("hello world");

    // wait for a second
    delay(20);
}
```