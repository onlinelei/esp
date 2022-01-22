//
// Created by 钱磊 on 2021/12/21.
//

#include <Arduino.h>
#include <FS.h>
#include "FileUtils.h"
#include <LittleFS.h>

String file_name = "/test.txt";
String configFileName = "/config/config.properties";


void my_fs_formatFS() {
    // 格式化SPIFFS
    Serial.println("SPIFFS format start");
    LittleFS.format();
    Serial.println("SPIFFS format finish");
}

void my_fs_start() {
    // 启动SPIFFS
    if (LittleFS.begin()) {
        Serial.println("SPIFFS Started.");
    } else {
        Serial.println("SPIFFS Failed to Start.");
    }
}

// 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
// 向dataFile写入字符串信息
// 完成文件写入后关闭文件
void my_fs_writ() {
    File dataFile = LittleFS.open(file_name, "w");
    dataFile.println("Hello IOT World.");
    dataFile.close();
    Serial.println("Finished Writing data to SPIFFS");
}

void my_fs_addConfig(const String &value) {
    if (LittleFS.exists(configFileName)) {
        Serial.print(configFileName);
        Serial.println(" FOUND.");
    } else {
        Serial.print(configFileName);
        Serial.println(" NOT FOUND.");
        Serial.println("start to create config file");
        File configFile = LittleFS.open(configFileName, "w");
        configFile.close();
    }

    // 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
    // 向dataFile添加字符串信息
    // 完成文件操作后关闭文件
    File configFile = LittleFS.open(configFileName, "a");
    configFile.println(value);
    configFile.close();
}

void my_fs_getConfig(String key) {
    if (LittleFS.exists(configFileName)) {
        Serial.print(configFileName);
        Serial.println(" FOUND.");
    } else {
        Serial.print(configFileName);
        Serial.println(" NOT FOUND.");
        Serial.println("start to create config file");
        File configFile = LittleFS.open(configFileName, "w");
        configFile.close();
        return;
    }

    File configFile = LittleFS.open(configFileName, "a");
//    for (int i = 0; i < configFile.size(); i++) {
//        Serial.println(configFile.readString());
//    }
    configFile.close();
}


void my_fs_showDirList(const String &path) {
    Dir dir = LittleFS.openDir(path);  // 建立“目录”对象
    // dir.next()用于检查目录中是否还有“下一个文件”
    while (dir.next()) {
        if (dir.isDirectory()) {
            String dirName = path + "/" + dir.fileName();
            my_fs_showDirList(dirName);
        }
        Serial.println(dir.fileName());
    }
}

void my_fs_removeFile(const String &path) {
    //从闪存中删除file_name文件
    if (LittleFS.remove(path)) {

        Serial.print(path);
        Serial.println(" remove sucess");

    } else {
        Serial.print(path);
        Serial.println(" remove fail");
    }
}

void my_fs_info() {
    FSInfo fs_info{};

    // 闪存文件系统信息
    LittleFS.info(fs_info);

    // 可用空间总和（单位：字节）
    Serial.print("totalBytes: ");
    Serial.print(fs_info.totalBytes);
    Serial.println(" Bytes");

    // 已用空间（单位：字节）
    Serial.print("usedBytes: ");
    Serial.print(fs_info.usedBytes);
    Serial.println(" Bytes");

    // 最大文件名字符限制（含路径和'\0'）
    Serial.print("maxPathLength: ");
    Serial.println(fs_info.maxPathLength);

    // 最多允许打开文件数量
    Serial.print("maxOpenFiles: ");
    Serial.println(fs_info.maxOpenFiles);

    // 存储块大小
    Serial.print("blockSize: ");
    Serial.println(fs_info.blockSize);

    // 存储页大小
    Serial.print("pageSize: ");
    Serial.println(fs_info.pageSize);
}