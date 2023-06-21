#ifndef __mks_draw_move_h
#define __mks_draw_move_h


#include "MKS_draw_lvgl.h"
#include "MKS_LVGL.h"


typedef enum {

    move_popup_x = 75,
    move_popup_y = 70,
    move_popup_size_x = 330,
    move_popup_size_y = 180,

    move_popup_btn_x = 120,
    move_popup_btn_y = 120,
    move_popup_btn_size_x = 100,
    move_popup_btn_size_y = 40,

}MOVE_XY_t;

typedef struct {

#if defined(USR_RELASE)
    /* Screan Build */
    lv_obj_t* move_scr;
    lv_obj_t* dist_scr;
    lv_obj_t* tool_scr;

    lv_style_t mbk_color;
    
#endif
    lv_style_t btn_color;
    lv_style_t btn_color_press;

    /* imgbtn */
    lv_obj_t* x_n;			//+
    lv_obj_t* x_p;			//-
    lv_obj_t* y_n;			//+
    lv_obj_t* y_p;			//-

    lv_obj_t* m_unlock;
    lv_obj_t* postivs;
    lv_obj_t* home;
    lv_obj_t* hhome;

    // lv_obj_t* btn_len_0_1;
    // lv_obj_t* btn_len_1;
    // lv_obj_t* btn_len_10;
    lv_obj_t* btn_len;
    lv_obj_t* btn_speed;

    lv_obj_t* Back;

    /* Label */
    lv_obj_t* Label_len;
    lv_obj_t* Label_back;
    lv_obj_t* Label_unlock;
    lv_obj_t* Label_postivs;
    lv_obj_t* Label_home;

    // lv_obj_t* label_len_0_1;
    // lv_obj_t* label_len_1;
    // lv_obj_t* label_len_10;
    lv_obj_t* label_len;
    lv_obj_t* label_speed;

}MKS_MOVE_PAGE;



typedef enum {
    HOMING_NONE,
    HOMING_START,
    HOMING_RUNNING,
    HOMING_SUCCEED,
    HOMING_FAIL,
}MKS_HOMING_T;

typedef struct{

    MKS_HOMING_T hard_homing_status;        // 硬限位回零配置
    MKS_HOMING_T soft_homing_status;        // 软限位回零配置
    uint8_t      limit_dis_delay_count=0;     // 类似于消抖
    
}MKS_MOVE_CTRL_T;

extern MKS_MOVE_PAGE move_page;
extern MKS_MOVE_CTRL_T ui_move_ctrl;


void mks_draw_move(void);
// void draw_pos_popup(void);
void mks_clear_move(void);
void draw_pos_popup(const char *text);
void draw_pos_popup_1(const char *text);
void hard_home_check(void);
void soft_home_check(void);
void draw_pos_popup_2(const char *text);
bool mks_get_motor_status(void);
void draw_move_click(bool status);
#endif
