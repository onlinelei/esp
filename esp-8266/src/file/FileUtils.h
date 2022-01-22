//
// Created by 钱磊 on 2021/12/21.
//

#ifndef ESP_8266_FILEUTILS_H
#define ESP_8266_FILEUTILS_H


class FileUtils {

};


#endif //ESP_8266_FILEUTILS_H

void my_fs_formatFS();

void my_fs_start();


void my_fs_writ();

void my_fs_addConfig(const String &value);

void my_fs_getConfig(String key);

void my_fs_showDirList(const String &path);

void my_fs_removeFile(const String &path);

void my_fs_info();