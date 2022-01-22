### 将下面代码拷贝到main.cpp

```c++
#include
<Arduino.h>
#include
"wifi/WifiUtil.h"
#include
"service/WebServer.h"


void setup() {
// 初始化串口
Serial.begin(115200);
Serial.println("8266 Begin!!!");

my_wifi_connectWifiAuto();
my_server_startServer();
}

void loop() {
my_server_handleClient();
}
```