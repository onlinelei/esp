#include <Arduino.h>
#include "wifi/WifiUtil.h"
#include "service/WebServer.h"
#include "file/FileUtils.h"
#include "net/HttpUtil.h"
#include "serial/SerialUtil.h"
#include "log/LogUtil.h"
#include "time/NTPUtil.h"
#include "time/DateTimeUtil.h"
#include "json/JsonUtil.h"
#include "display/ST7789Util.h"
#include "display/StartPage.h"


void setup() {
    // 初始化串口
    Serial.begin(115200);
    Serial.println("8266 Begin!!!");

//    pinMode(LED_BUILTIN, OUTPUT);
//    my_wifi_connectWifiAuto();
//    my_server_startServer();
//    my_fs_start();
//    my_fs_writ();
//    my_fs_addConfig("key1=value");
//    my_fs_getConfig("key1");
//    my_fs_showDirList("/");
//    my_wifi_connectWifiAuto();
//    my_time_init();
//    my_date_init();
//    my_server_startServer();
//    my_screen_init();
}

void loop() {
//    my_server_handleClient();
//    my_fs_info();
//    my_http_getResponse("www.example.com", 80);
//    my_serial_reciveString();
//    my_http_getStreamResponse("www.example.com", 80);
//    my_log("hello world!");
//    my_time_sync();
//    my_date_currentDateTime();
//    my_server_doGet("http://192.168.43.111", 80, "/update?int=1&float=1.1&button=1");
//    my_server_handleClient();
//    my_json_print();
//    String currentTime = my_date_currentDateTime();
//    my_screen_printText(0, random(180), 2, RANDOM_REG32, currentTime);
//    my_screen_printText(0, 200, 2, RANDOM_REG32, my_wifi_getSSID());
//    my_screen_printText(0, 220, 2, RANDOM_REG32, my_wifi_getIpAddr());
//    my_screen_fillScreen();
//    delay(2000);
    my_page_starField();
}