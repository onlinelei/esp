//
// Created by 钱磊 on 2021/12/23.
//

#include "JsonUtil.h"
#include <ArduinoJson.h>

void my_json_print() {
    // 重点1：DynamicJsonDocument对象, JSON_OBJECT_SIZE(2)这条指令。其中指令括号中的2即代表对象包含有两个数据。
    // 用来计算对象需要的大小
    const size_t capacity = JSON_OBJECT_SIZE(2) + 30;
    DynamicJsonDocument doc(capacity);

    // 重点2：即将解析的json文件
    String json = "{\"name\":\"taichi-maker\",\"number\":1}";

    // 重点3：反序列化数据
    deserializeJson(doc, json);

    // 重点4：获取解析后的数据信息
    String nameStr = doc["name"].as<String>();
    int numberInt = doc["number"].as<int>();

    // 通过串口监视器输出解析后的数据信息
    Serial.print("nameStr = ");
    Serial.println(nameStr);
    Serial.print("numberInt = ");
    Serial.println(numberInt);
}

void my_json_printArray() {
    // 重点1：DynamicJsonDocument对象
    const size_t capacity = JSON_ARRAY_SIZE(2) + 2 * JSON_OBJECT_SIZE(1) + 60;
    DynamicJsonDocument doc(capacity);

    // 重点2：即将解析的json文件
    String json = "[{\"name\":\"taichi-maker\"},{\"website\":\"www.taichi-maker.com\"}]";

    // 重点3：反序列化数据
    deserializeJson(doc, json);


    String nameStr = doc[0]["name"].as<String>();
    String websiteStr = doc[1]["website"].as<String>();

    // 通过串口监视器输出解析后的数据信息
    Serial.print("nameStr = ");
    Serial.println(nameStr);
    Serial.print("websiteStr = ");
    Serial.println(websiteStr);
}


String my_json_createJsonString() {
    String jsonCode = "{\"info\": {\"name\": \"taichimaker\",\"url\": \"www.taichi-maker.com\",\"email\": \"taichimaker@163.com\"},\"digital_pin\": {\"d1\": \"";
    jsonCode += String(digitalRead(D1));
    jsonCode += "\",\"d2\": \"";
    jsonCode += String(digitalRead(D2));
    jsonCode += "\",\"d3\": \"";
    jsonCode += String(digitalRead(D3));
    jsonCode += "\"},\"analog_pin\": {\"a0\": \"";
    jsonCode += String(analogRead(A0));
    jsonCode += "\"}}";

    Serial.print("jsonCode: ");
    Serial.println(jsonCode);

    return jsonCode;
}

String my_json_createJson() {
    // 开始ArduinoJson Assistant的serialize代码
    const size_t capacity = JSON_OBJECT_SIZE(1) + 3 * JSON_OBJECT_SIZE(3) + 140;
    DynamicJsonDocument doc(capacity);

    JsonObject info = doc.createNestedObject("info");
    info["name"] = "taichimaker";
    info["url"] = "www.taichi-maker.com";
    info["email"] = "taichimaker@163.com";

    JsonObject digital_pin = doc.createNestedObject("digital_pin");
    digital_pin["d1"] = String(digitalRead(D1));
    digital_pin["d2"] = String(digitalRead(D2));
    digital_pin["d3"] = String(digitalRead(D3));

    JsonObject analog_pin = doc.createNestedObject("analog_pin");
    analog_pin["a0"] = String(analogRead(A0));
    // 结束assistant的serialize代码

    String jsonCode;
    serializeJson(doc, jsonCode);
    Serial.print("Root Json Code: ");
    Serial.println(jsonCode);

    return jsonCode;
}