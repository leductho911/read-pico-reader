/* SPDX-License-Identifier: LicenseRef-Kiikoread-Personal-Study-1.0
 * 中文：Flash只读字典二分查询，语言标记原子更新；无堆分配或设备I/O。
 * English: Binary lookup in a flash-only catalog, with an atomic locale flag; no heap or device IO.
 */
#include "ui_locale.h"
#include <stdatomic.h>
#include <stddef.h>
#include <string.h>
#ifdef ESP_PLATFORM
#include "esp_memory_utils.h"
#elif defined(KIIKO_LOCALE_TEST)
extern bool ui_locale_test_readonly(const void *text);
#endif
static atomic_int s_language;
typedef struct {const char *zh,*en,*vi;} ui_locale_pair_t;
#include "ui_locale_catalog.inc"
void ui_locale_set_language(int lang){atomic_store_explicit(&s_language,lang,memory_order_relaxed);}
int ui_locale_get_language(void){return atomic_load_explicit(&s_language,memory_order_relaxed);}
void ui_locale_set_english(bool value){ui_locale_set_language(value?UI_LOCALE_EN:UI_LOCALE_ZH);}
bool ui_locale_english(void){return ui_locale_get_language()==UI_LOCALE_EN;}
bool ui_locale_vietnamese(void){return ui_locale_get_language()==UI_LOCALE_VI;}
const char *ui_tr(const char *text){
    int lang=ui_locale_get_language();
    if(!text||lang==UI_LOCALE_ZH)return text;
#ifdef ESP_PLATFORM
    if(!esp_ptr_in_drom(text))return text;
#elif defined(KIIKO_LOCALE_TEST)
    if(!ui_locale_test_readonly(text))return text;
#else
    return text;
#endif
    size_t lo=0,hi=sizeof(s_pairs)/sizeof(s_pairs[0]);
    while(lo<hi){size_t mid=lo+(hi-lo)/2;int order=strcmp(text,s_pairs[mid].zh);
        if(!order){
            if(lang==UI_LOCALE_VI&&s_pairs[mid].vi&&s_pairs[mid].vi[0])return s_pairs[mid].vi;
            return s_pairs[mid].en;
        }
        if(order<0)hi=mid;else lo=mid+1;
    }
    return text;
}
