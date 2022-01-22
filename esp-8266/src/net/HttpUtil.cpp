//
// Created by 钱磊 on 2021/12/21.
//
#include <Arduino.h>
#include <ESP8266WiFi.h>


// 发送HTTP请求并且将服务器响应通过串口输出
void my_http_getResponse(const String &host, int port) {

    // 建立WiFi客户端对象，对象名称client
    WiFiClient client;

    // 建立字符串，用于HTTP请求
    String httpRequest = String("GET /") + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" +
                         "Connection: close\r\n" +
                         "\r\n";

    // 通过串口输出连接服务器名称以便查阅连接服务器的网址
    Serial.print("Connecting to ");
    Serial.print(host);

    // 连接网络服务器，以下段落中的示例程序为本程序重点1
    // 请参考太极创客网站中关于本程序的讲解页面获取详细说明信息。网址：
    // http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
    if (client.connect(host, port)) {
        Serial.println(" Success!");        // 连接成功后串口输出“Success”信息

        client.print(httpRequest);          // 向服务器发送HTTP请求
        Serial.println("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
        Serial.println(httpRequest);

        // 通过串口输出网络服务器响应信息， 以下段落中的示例程序为本程序重点2
        // 请参考太极创客网站中关于本程序的讲解页面获取详细说明信息。网址：
        // http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
        Serial.println("Web Server Response:");
        while (client.connected() || client.available()) {
            if (client.available()) {
                String line = client.readStringUntil('\n');
                Serial.println(line);
            }
        }

        client.stop();                      // 断开与服务器的连接
        Serial.print("Disconnected from "); // 并且通过串口输出断开连接信息
        Serial.print(host);

    } else {    // 如果连接不成功则通过串口输出“连接失败”信息
        Serial.println(" connection failed!");
        client.stop();
    }
}


void my_http_getStreamResponse(const String &host, int port) {
    // 建立WiFi客户端对象，对象名称client
    WiFiClient client;

    // 建立字符串，用于HTTP请求
    String httpRequest = String("GET /") + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" +
                         "Connection: close\r\n" +
                         "\r\n";

    // 通过串口输出连接服务器名称以便查阅连接服务器的网址
    Serial.print("Connecting to ");
    Serial.print(host);

    // 连接网络服务器，以下段落中的示例程序为本程序重点1
    // 请参考太极创客网站中关于本程序的讲解页面获取详细说明信息。网址：
    // http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
    if (client.connect(host, port)) {
        Serial.println(" Success!");        // 连接成功后串口输出“Success”信息

        client.print(httpRequest);          // 向服务器发送合同谈判请求
        Serial.println("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
        Serial.println(httpRequest);

        // 通过串口输出网络服务器响应信息， 以下段落中的示例程序为本程序重点2
        // 请参考太极创客网站中关于本程序的讲解页面获取详细说明信息。网址：
        // http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/http-request/
        Serial.println("Web Server Response:");
        while (client.connected() || client.available()) {
            if (client.available()) {
                String line = client.readStringUntil('\n');
                Serial.println(line);
            }
        }

        client.stop();                      // 断开与服务器的连接
        Serial.print("Disconnected from "); // 并且通过串口输出断开连接信息
        Serial.print(host);

    } else {    // 如果连接不成功则通过串口输出“连接失败”信息
        Serial.println(" connection failed!");
        client.stop();
    }
}

