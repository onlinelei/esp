# 一、资料

## 1.1 学习网站

太极创客网站：http://www.taichi-maker.com
已经学习到：http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/esp8266-nodemcu-web-client/

TFT屏幕驱动：https://simple-circuit.com/esp8266-nodemcu-st7789-tft-ips-display/
https://blog.csdn.net/weixin_51037539/article/details/120453447

# 二、项目搭建
## 2.1 platformIo 使用
```shell
# 初始化项目
platformio init --ide clion --board esp07

```


# 三、配置环境

Name         GPIO           NodeMCU      Function
PIN_D0        16            GPIO16       WAKE
PIN_D1        5             GPIO5        User purpose
PIN_D2        4             GPIO4        User purpose
PIN_D3        0             GPIO0        Low on boot means enter FLASH mode
PIN_D4        2             GPIO2        TXD1 (must be high on boot to go to UART0 FLASH mode)
PIN_D5        14            GPIO14       HSCLK
PIN_D6        12            GPIO12       HMISO
PIN_D7        13            GPIO13       HMOSI  RXD2
PIN_D8        15            GPIO15       HCS    TXD0 (must be low on boot to enter UART0 FLASH mode)
PIN_D9        3                          RXD0
PIN_D10       1                          TXD0
                            
PIN_MOSI      8             SD1          FLASH and overlap mode
PIN_MISO      7             SD0
PIN_SCLK      6             CLK
PIN_HWCS      0             D3
                            
PIN_D11       9             SD2
PIN_D12       10            SD4




## 3.2 ST7789 屏幕
解开  line 39、49、80、83

BLK:   3.3
DC:    D3    GPIO0
RES:   D4    GPIO2
SDA:   D7    GPIO13
SCL:   D5    GPIO14
VCC:   3.3
GND:   GND