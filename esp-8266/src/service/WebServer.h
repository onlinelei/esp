//
// Created by 钱磊 on 2021/12/20.
//

#ifndef ESP_8266_WEBSERVER_H
#define ESP_8266_WEBSERVER_H


class WebServer {

};


#endif //ESP_8266_WEBSERVER_H

void my_server_handleRoot();

void my_server_handleNotFound();

void my_server_handleLED();

void my_server_startServer();

void my_server_handleClient();

void my_server_getParam();

void my_server_doGet(const String &host, int port, const String &pathAndParam);

