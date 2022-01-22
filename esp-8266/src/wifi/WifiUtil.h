void my_wifi_scanAndPrintWifi();

void my_wifi_setWifiMode_STA();

/**
 * @brief Set the WifiMode AP object
 * 
 */
void my_wifi_setWifiMode_AP();

/**
 * @brief 不连接wifi
 * 
 */
void my_wifi_disconnect();

/**
 * @brief 创建 wifi,不用判断模式
 *
 */
void my_wifi_createWifi();

/**
 * @brief 连接 wifi,不用判断模式
 * 
 */
void my_wifi_connectWifi();

/**
 * 根据存储的 wifi 列表，自动连接 wifi，连接信号最好的
 */
void my_wifi_connectWifiAuto();

String my_wifi_getIpAddr();

String my_wifi_getSSID();