#ifndef __mks_draw_language_h
#define __mks_draw_language_h

#include "MKS_draw_lvgl.h"

typedef struct {

    lv_obj_t *imgbtn_back;
    lv_obj_t *imgbtn_simple_cn;         // 简体中文
    lv_obj_t *imgbtn_en;                // 英语
    lv_obj_t *imgbtn_de;                // 德语

    lv_obj_t *label_back;
    lv_obj_t *label_simple_cn;         // 简体中文
    lv_obj_t *label_en;                // 英语
    lv_obj_t *label_de;                // 德语


}LANGUAGE_PAGE_T;


typedef struct {

    /* 公共 */
    const char *back;

    /* 主页 */
    const char *adjustment;
    const char *control;
    const char *sculpture;
    const char *tool;
    const char *disconnect;
    const char *connect;
    const char *connect_btn;

    /* 移动控制 */
    const char *hhome;
    const char *home;
    const char *postive;
    const char *low_speed;
    const char *high_speed;
    const char *mid_speed;
    const char *unlock;
    const char *home_succeed;
    const char *hard_homing;

    /* 文件界面 */
    const char *page_up;
    const char *page_dowm;
    const char *no_sd_card;
    const char *carve;
    const char *frame;

    /* wifi */
    const char *re_scanf;

    /* 雕刻界面 */
    const char *run;
    const char *stop;
    const char *hold;
    const char *power;
    const char *speed;
    const char *stp_tis;
    const char *finsh_tis;

    /* 工具界面 */
    const char *roller;
    const char *safty;
    const char *language;
    const char *scanf;
    const char *scanf_ing;
    const char *disconnecting;

    const char *roller_sw;
    const char *flame_sw;
    const char *gyro_sw;
    
    /*wifi*/
    const char *wifi_name;
    const char *wifi_password;
    const char *wifi_single_good;
    const char *wifi_signle_min;
    const char *wifi_single_bad;

    /* 扩展界面 */
    

    /* 提示框 */
    const char *tis_err;
    const char *tis_info;
    const char *tis_warning;

    const char *tis_homing;
    const char *tis_homimg_fail;
    const char *tis_unlock;
    const char *tis_unlock_succeed;
    const char *tis_pos_succeed;
    const char *tis_is_carve;
    const char *tis_wait_mc_stop;
    const char *tis_no_hard_limit;
    const char *tis_yes;
    const char *tis_no;
    const char *tis_cancle;
    const char *tis_more_than_1_m;
    const char *tis_is_contiue;
    const char *tis_loading_file;
    const char *tis_frame_ing;
    const char *tis_wifi_connecting;
    // const char 
    
}mc_lg_muilt_t;
extern mc_lg_muilt_t mc_language;

void mc_language_init(void);
void draw_language(void);
void mks_clear_language(void);
void set_language_btn_style(uint8_t language);
#endif
