/* SPDX-License-Identifier: LicenseRef-Kiikoread-Personal-Study-1.0
 * 中文：只写本板设置命名空间；未配置和显式待完成可进入引导，存储错误不冒充新机。
 * English: Write only this board's settings namespace; fresh/pending profiles need setup, errors are never treated as a fresh device.
 */
#include "setup_state.h"
#include "kiiko_board_config.h"
#include "nvs.h"
#ifdef KIIKO_UI_LOCALIZATION
#include "ui_locale.h"
#endif
static bool s_pending;
static uint8_t s_language;
#define SETUP_STATE_KEY "setup_v1"
#define SETUP_LANGUAGE_KEY "ui_lang"
static esp_err_t save(uint8_t state,uint8_t language) {
    nvs_handle_t h;esp_err_t err=nvs_open(KIIKO_BOARD_SETTINGS_NAMESPACE,NVS_READWRITE,&h);
    if(err!=ESP_OK)return err;
    err=nvs_set_u8(h,SETUP_STATE_KEY,state);
    if(err==ESP_OK)err=nvs_set_u8(h,SETUP_LANGUAGE_KEY,language);
    if(err==ESP_OK)err=nvs_commit(h);
    nvs_close(h);return err;
}
void app_setup_init(void) {
    s_pending=false;
    s_language=0;
#ifdef KIIKO_UI_LOCALIZATION
    ui_locale_set_language(0);
#endif
    nvs_handle_t h;esp_err_t err=nvs_open(KIIKO_BOARD_SETTINGS_NAMESPACE,NVS_READONLY,&h);
    if(err==ESP_ERR_NVS_NOT_FOUND){
        // 先持久化“待完成”，以免引导中的其他设置让下次启动被误判为老用户。
        // Persist Pending before wizard changes could make a restart resemble a legacy profile.
        if(save(0,0)==ESP_OK)s_pending=true;
        return;
    }
    if(err!=ESP_OK)return;
    uint8_t state=255,language=0;
    err=nvs_get_u8(h,SETUP_STATE_KEY,&state);
    if(nvs_get_u8(h,SETUP_LANGUAGE_KEY,&language)==ESP_OK&&language<=2)s_language=language;
    size_t entries=1;
    esp_err_t count_err=err==ESP_ERR_NVS_NOT_FOUND?nvs_get_used_entry_count(h,&entries):ESP_OK;
    nvs_close(h);
#ifdef KIIKO_UI_LOCALIZATION
    ui_locale_set_language(s_language);
#endif
    // 已存在的旧命名空间没有标记就直接沿用旧配置；不自动擦除、不清密码。
    // Existing legacy namespaces without a marker keep their profile; never erase or reset credentials.
    if(err==ESP_ERR_NVS_NOT_FOUND&&count_err==ESP_OK&&entries==0){
        if(save(0,0)==ESP_OK)s_pending=true;
    }else if(err==ESP_OK&&state<=1)s_pending=state==0;
}
bool app_setup_pending(void){return s_pending;}
uint8_t app_setup_language(void){return s_language;}
bool app_setup_english(void){return s_language==1;}
bool app_setup_vietnamese(void){return s_language==2;}
esp_err_t app_setup_set_language(uint8_t language){
    esp_err_t err=save(s_pending?0:1,language);
    if(err==ESP_OK){
        s_language=language;
#ifdef KIIKO_UI_LOCALIZATION
        ui_locale_set_language(language);
#endif
    }
    return err;
}
esp_err_t app_setup_set_english(bool english){
    return app_setup_set_language(english?1:0);
}
esp_err_t app_setup_finish(void){
    esp_err_t err=save(1,s_language);if(err==ESP_OK)s_pending=false;return err;
}
