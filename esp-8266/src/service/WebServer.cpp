//
// Created by 钱磊 on 2021/12/20.
//

#include <Arduino.h>
#include "WebServer.h"
#include <ESP8266WebServer.h>


// 建立ESP8266WebServer对象，对象名称为esp8266_server
// 括号中的数字是网路服务器响应http请求的端口号
// 网络服务器标准http端口号为80，因此这里使用80为端口号
ESP8266WebServer esp8266_server(80);


//  此部分为程序为本示例程序重点1
//  详细讲解请参见太极创客网站《零基础入门学用物联网》
//  第3章-第2节 ESP8266-NodeMCU网络服务器-1
void my_server_startServer() {
    //--------"启动网络服务功能"程序部分开始--------
    esp8266_server.begin();
    esp8266_server.on("/", my_server_handleRoot);
    esp8266_server.onNotFound(my_server_handleNotFound);
    esp8266_server.on("/LED", HTTP_POST, my_server_handleLED);  // 设置处理LED控制请求的函数'handleLED'
    esp8266_server.on("/update", my_server_getParam);
    //--------"启动网络服务功能"程序部分结束--------
    Serial.println("HTTP esp8266_server started");
}

void my_server_handleClient() {
    esp8266_server.handleClient();
}

/* 以下两个函数为本示例程序重点2
详细讲解请参见太极创客网站《零基础入门学用物联网》
第3章-第2节 3_2_1_First_Web_Server 的说明讲解*/
//处理网站根目录“/”的访问请求
// NodeMCU将调用此函数。
void my_server_handleRoot() {
    esp8266_server.send(200, "text/html",
                        "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

// 设置处理404情况的函数'handleNotFound'
// 当浏览器请求的网络资源无法在服务器找到时，
// NodeMCU将调用此函数。
void my_server_handleNotFound() {
    esp8266_server.send(404, "text/plain", "404: Not found");
}

void my_server_handleLED() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));// 改变LED的点亮或者熄灭状态
    esp8266_server.sendHeader("Location", "/");          // 跳转回页面根目录
    esp8266_server.send(303);                           // 发送Http相应代码303 跳转
}

void my_server_getParam() {
    // 获取客户端发送HTTP信息中的参数
    float floatValue = esp8266_server.arg("float").toFloat();
    int intValue = esp8266_server.arg("int").toInt();
    int buttonValue = esp8266_server.arg("button").toInt();

    // 发送http响应
    esp8266_server.send(200, "text/plain", "Received");

//    buttonValue == 0 ? digitalWrite(LED_BUILTIN, LOW) : digitalWrite(LED_BUILTIN, HIGH);

    // 通过串口监视器输出获取到的变量数值
    Serial.print("floatValue = ");
    Serial.println(floatValue);
    Serial.print("intValue = ");
    Serial.println(intValue);
    Serial.print("buttonValue = ");
    Serial.println(buttonValue);
    Serial.println("=================");
}

void my_server_doGet(const String &host, int port, const String &pathAndParam) {
    WiFiClient client;

    // 将需要发送的数据信息放入客户端请求
    if (pathAndParam.isEmpty()) {
        Serial.println("url is empty!");
    }

    // 建立字符串，用于HTTP请求
    String httpRequest = String("GET ") + pathAndParam + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" +
                         "Connection: close\r\n" +
                         "\r\n";

    Serial.print("Connecting to ");
    Serial.print(host);

    if (client.connect(host, port)) {  //如果连接失败则串口输出信息告知用户然后返回loop
        Serial.println(" Sucess");

        client.print(httpRequest);          // 向服务器发送HTTP请求
        Serial.println("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
        Serial.println(httpRequest);
    } else {
        Serial.println(" failed");
    }

    client.stop();
}