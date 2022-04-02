//
// Created by 钱磊 on 2022/3/4.

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <Thread.h>                 //协程
#include <StaticThreadController.h> //协程控制


// GPIO4 控制电机 mos 管
int MOTOR_PIN = 4;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite clk = TFT_eSprite(&tft);

//创建时间更新函数线程
Thread updateStatus_thread = Thread();
//创建电机驱动线程
Thread motor_thread = Thread();
//创建恢复WIFI链接
//Thread reflash_openWifi = Thread();
//创建动画绘制线程
//Thread reflash_Animate = Thread();

//创建协程池
StaticThreadController<2> controller(&updateStatus_thread, &motor_thread);


WiFiUDP Udp;
unsigned int localPort = 8000;

// NTP服务器参数
static const char ntpServerName[] = "ntp6.aliyun.com";
const int timeZone = 8; //东八区
time_t currentTime = 0;       //显示时间显示记录

const int NTP_PACKET_SIZE = 48;     // NTP时间在消息的前48字节中
byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming & outgoing packets

// 向NTP服务器发送请求
void sendNTPpacket(IPAddress &address) {

    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011; // LI, Version, Mode
    packetBuffer[1] = 0;          // Stratum, or type of clock
    packetBuffer[2] = 6;          // Polling Interval
    packetBuffer[3] = 0xEC;       // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    Udp.beginPacket(address, 123); // NTP requests are to port 123
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}

time_t getNtpTime() {
    IPAddress ntpServerIP; // NTP server's ip address

    while (Udp.parsePacket() > 0); // discard any previously received packets
    // Serial.println("Transmit NTP Request");
    //  get a random server from the pool
    WiFi.hostByName(ntpServerName, ntpServerIP);
    // Serial.print(ntpServerName);
    // Serial.print(": ");
    // Serial.println(ntpServerIP);
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500) {
        int size = Udp.parsePacket();
        if (size >= NTP_PACKET_SIZE) {
            Serial.println("Receive NTP Response");
            Udp.read(packetBuffer, NTP_PACKET_SIZE); // read packet into the buffer
            unsigned long secsSince1900;
            // convert four bytes starting at location 40 to a long integer
            secsSince1900 = (unsigned long) packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long) packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long) packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long) packetBuffer[43];
            // Serial.println(secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR);
            return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
        }
    }
    Serial.println("No NTP Response :-(");
    return 0; // 无法获取时间时返回0
}

void updateStatus() {
    tft.fillRect(62, 2, 97, 15, TFT_BLACK);
    tft.fillRect(62, 19, 97, 15, TFT_BLACK);
    tft.fillRect(2, 53, 157, 26, TFT_BLACK);

    tft.setTextSize(2);
    tft.setCursor(62, 2);
    tft.print(F(" OK"));

    tft.setCursor(62, 19);
    tft.print(F(" 100"));


    tft.setTextSize(1);
    tft.setCursor(2, 53);
    tft.println(F("running ..."));
    tft.println(F("im ok !"));
    tft.print(F("ip address:"));
    tft.println(WiFi.localIP());
}

void updateTime() {
    tft.fillRect(62, 36, 97, 15, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(62, 40);
    tft.print(year());
    tft.print(" ");
    tft.print(hour());
    tft.print(":");
    tft.print(minute());
    tft.print(":");
    tft.print(minute());
    tft.print(":");
    tft.print(second());
    String time = year() + " " + hour();


    clk.setColorDepth(8);

    clk.createSprite(97, 15); //创建窗口
    clk.fillSprite(0x0000);     //填充率

    clk.setTextDatum(CC_DATUM);                      //设置文本数据
    clk.setTextColor(TFT_DARKCYAN, 0x0000);
    clk.drawString("Connecting to WiFi......", 0, 0, 1);
    clk.setTextColor(TFT_WHITE, 0x0000);
    clk.drawRightString(Version, 180, 60, 2);
    clk.pushSprite(20, 120); //窗口位置

    // clk.setTextDatum(CC_DATUM);
    // clk.setTextColor(TFT_WHITE, 0x0000);
    // clk.pushSprite(130,180);

    clk.deleteSprite();
    loadNum += 1;
    delay(delayTime);
}

void updateMotor() {
    if (second() == 0) {
        digitalWrite(MOTOR_PIN, HIGH);
    } else if (second() == 30) {
        digitalWrite(MOTOR_PIN, LOW);
    }
}

void statusPage() {
    tft.drawLine(0, 0, 0, 80, TFT_DARKCYAN);
    tft.drawLine(0, 0, 159, 0, TFT_DARKCYAN);
    tft.drawLine(159, 0, 159, 79, TFT_DARKCYAN);
    tft.drawLine(0, 79, 159, 79, TFT_DARKCYAN);

    tft.drawLine(0, 17, 159, 17, TFT_DARKCYAN);
    tft.drawLine(0, 34, 159, 34, TFT_DARKCYAN);
    tft.drawLine(0, 51, 159, 51, TFT_DARKCYAN);
    tft.drawLine(60, 0, 60, 51, TFT_DARKCYAN);


    tft.setTextSize(2);
    tft.setCursor(2, 2);
    tft.setTextColor(TFT_DARKCYAN);
    tft.println(F("stat:"));
    tft.setCursor(2, 19);
    tft.println(F("coun:"));
    tft.setCursor(2, 36);
    tft.println(F("time:"));
    updateStatus();
}


void setup() {
    // 设置串口速率
    Serial.begin(115200);
    Serial.println("8266 Begin!!!");

    // 设置引脚状态
//    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);

    // 初始化屏幕
    //Set up the display
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(0, 0);

    // 开机显示
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(15, 12);
    tft.println(F("Plant Carer"));

    tft.setTextSize(1);
    tft.setCursor(70, 50);
    tft.setTextColor(TFT_DARKGREEN);
    tft.println(F("Version: 1.0"));
    delay(300);

    for (int i = 0; i < 70; ++i) {
        tft.setCursor(10 + i * 2, 70);
        tft.println(F(">"));
        delay(30);
    }

    tft.fillScreen(TFT_BLACK);

    // 连接wifi
    char wiFiName[32] = "Mi";
    char wiFiPass[64] = "12345678";


    WiFi.begin(wiFiName, wiFiPass);
    tft.setTextSize(1);
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_DARKCYAN);
    tft.print(F("wifi name:"));
    tft.println(wiFiName);
    tft.print(F("connect wifi ."));

    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i < 30) {
        tft.print(F("."));
        delay(1000);
        i++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        tft.println(F(""));
        tft.print(F("IP:"));
        tft.println(WiFi.localIP());
        delay(1000);
        tft.println(F("UDP START ..."));
        delay(1000);
        Udp.begin(localPort);
        tft.println(F("SYNC TIME ..."));
        delay(1000);
        setSyncProvider(getNtpTime);
        setSyncInterval(300);
        currentTime = now();
        tft.print(F("TIME LONG:"));
        tft.println(currentTime);
        delay(1000);

        tft.print("TIME:");
        tft.print(year());
        tft.print(" ");
        tft.print(hour());
        tft.print(":");
        tft.print(minute());
        tft.print(":");
        tft.print(minute());
        delay(5000);
    }

    tft.fillScreen(TFT_BLACK);
    // 状态显示界面
    statusPage();

    updateStatus_thread.setInterval(100); //设置所需间隔 100毫秒
    updateStatus_thread.onRun(updateTime);

    motor_thread.setInterval(100);
    motor_thread.onRun(updateMotor);

    controller.run();
}


void loop() {
    if (controller.shouldRun()) {
        controller.run();
    }
}