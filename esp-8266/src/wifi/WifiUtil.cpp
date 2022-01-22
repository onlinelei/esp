/**
 * @file WifiUtil.cpp
 * @author your name (onlinelei@sina.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>


// wifiMulti 对象
ESP8266WiFiMulti wifiMulti;

// 这里定义将要建立的WiFi名称。此处以"taichi-maker"为示例
// 您可以将自己想要建立的WiFi名称填写入此处的双引号中
const char *outSsid = "8266";

// 这里定义将要建立的WiFi密码。此处以12345678为示例
// 您可以将自己想要使用的WiFi密码放入引号内
// 如果建立的WiFi不要密码，则在双引号内不要填入任何信息
const char *outPassword = "12345678";

// 连接 wifi 名称
//const char *ssid = "Redmi_016C";
const char *ssid = "Mi";

// 连接 wifi 密码
//const char *password = "12345678";
const char *password = "12345678";

/**
 * @brief Set the WifiMode STA objects
 * 
 */
void my_wifi_setWifiMode_STA() {
    WiFi.mode(WIFI_STA);
}

/**
 * @brief Set the WifiMode AP object
 * 
 */
void my_wifi_setWifiMode_AP() {
    WiFi.mode(WIFI_AP);
}

/**
 * @brief 不连接wifi
 * 
 */
void my_wifi_disconnect() {
    WiFi.disconnect();
}

/**
 * @brief 获取并打印扫描到的wifi
 * 需要 STA 模式，且关闭wifi连接
 * 
 */
void my_wifi_scanAndPrintWifi() {
    Serial.println("\n\n---Scan Wifi-------------");
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; i++) {
        Serial.printf("%02d: %s, Ch:%d (%ddBm) %s\n", i + 1,
                      WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i),
                      WiFi.encryptionType(i) == ENC_TYPE_NONE ? "" : "*");
    }
    Serial.println("---Wifi End-------------\n\n");
}

/**
 * @brief 创建 wifi,不用判断模式
 * 
 */
void my_wifi_createWifi() {
    // 此语句是重点。WiFi.softAP用于启动NodeMCU的AP模式。
    // 括号中有两个参数，ssid是WiFi名。password是WiFi密码。
    // 这两个参数具体内容在setup函数之前的位置进行定义。
    WiFi.softAP(outSsid, outPassword);

    // 通过串口监视器输出信息
    // 告知用户NodeMCU所建立的WiFi名
    // 以及NodeMCU的IP地址
    // 通过调用WiFi.softAPIP()可以得到NodeMCU的IP地址
    Serial.print("Access Point: ");
    Serial.println(outSsid);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
}

/**
 * @brief 连接 wifi,不用判断模式
 *
 */
void my_wifi_connectWifi() {
    // 启动网络连接
    WiFi.begin(ssid, password);
    // 串口监视器输出网络连接信息
    Serial.print("Connecting to ");
    // 告知用户NodeMCU正在尝试WiFi连接
    Serial.print(ssid);
    Serial.println(" ...");

    // 这一段程序语句用于检查WiFi是否连接成功
    // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。
    // 如果WiFi连接成功则返回值为WL_CONNECTED
    // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
    // 同时NodeMCU将通过串口监视器输出连接时长读秒。
    // 这个读秒是通过变量i每隔一秒自加1来实现的。
    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(i++);
        Serial.print(' ');
    }

    // WiFi连接成功后
    // NodeMCU将通过串口监视器输出"连接成功"信息。
    // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
    // WiFi.localIP()函数来实现的。该函数的返回值即NodeMCU的IP地址。
    Serial.println("");
    Serial.println("Connection established!");
    Serial.print("IP address:    ");
    Serial.println(WiFi.localIP());
}


/**
 * 根据存储的 wifi 列表，自动连接 wifi，连接信号最好的
 */
void my_wifi_connectWifiAuto() {
    /** 通过addAp函数存储  WiFi名称       WiFi密码
    * 这三条语句通过调用函数addAP来记录3个不同的WiFi网络信息
    */
    wifiMulti.addAP("Mi", "12345678");
    wifiMulti.addAP("Redmi_016C", "87654321");
    wifiMulti.addAP("xxx", "12345678");


    /** 通过串口监视器输出信息告知用户NodeMCU正在尝试连接WiFi
    * 此处的wifiMulti.run()是重点。通过wifiMulti.run()，NodeMCU将会在当前
    * 环境中搜索addAP函数所存储的WiFi。如果搜到多个存储的WiFi那么NodeMCU
    * 将会连接信号最强的那一个WiFi信号。
    * 一旦连接WiFI成功，wifiMulti.run()将会返回“WL_CONNECTED”。这也是
    */
    Serial.print("try auto connect wifi .");
    while (wifiMulti.run() != WL_CONNECTED) {
        delay(1000);
        Serial.print('.');
    }

    Serial.println('\n');
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}

String my_wifi_getIpAddr(){
    return WiFi.localIP().toString();
}

String my_wifi_getSSID(){
    return WiFi.BSSIDstr();
}