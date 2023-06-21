#include "mks_draw_other.h"

OTHER_PAGE_T other_page;


LV_IMG_DECLARE(back);	
LV_IMG_DECLARE(png_back_pre);

LV_IMG_DECLARE(png_sw_on);
LV_IMG_DECLARE(png_sw_off);

static void draw_other_imgbtn();
static void draw_other_label();

enum {
	ID_O_BACK,
    // ID_O_SAFTY_SW,
    ID_O_ROLLER_SW,

    ID_O_FLAME_SW,
    ID_O_GYRO_SW,
};


static uint8_t get_event(lv_obj_t* obj) {

    if      (obj == other_page.imgbtn_back)             return ID_O_BACK;  
    else if (obj == other_page.imgbtn_roller_sw)        return ID_O_ROLLER_SW;
    else if (obj == other_page.imgbtn_flame_sw)         return ID_O_FLAME_SW;
    else if (obj == other_page.imgbtn_gyro_sw)          return ID_O_GYRO_SW;
}

static void event_handler_back(void) {

	mks_clear_other();
	mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
	mks_draw_tool();
}



// static void 

char str_flame_alarm_on[]="$37=1\n";
char str_flame_alarm_off[]="$37=0\n";
char str_gyro_alarm_on[]="$39=1\n";
char str_gyro_alarm_off[]="$39=0\n";

char str_roller_on[] = "$101=102\n";
char str_roller_off[] = "$101=80\n";

char str_roller_sw_on[] = "$41=1\n";
char str_roller_sw_off[] = "$41=0\n";

static void event_handler_roller(void) {

    // if(roller_status->get()) {
    //     MKS_GRBL_CMD_SEND(str_roller_off);
    //     MKS_GRBL_CMD_SEND(str_roller_sw_off);
    //     lv_imgbtn_set_src(other_page.imgbtn_roller_sw, LV_BTN_STATE_PR, &png_sw_off);
    //     lv_imgbtn_set_src(other_page.imgbtn_roller_sw, LV_BTN_STATE_REL, &png_sw_off);
    // }else{
    //     MKS_GRBL_CMD_SEND(str_roller_on);
    //     MKS_GRBL_CMD_SEND(str_roller_sw_on);
    //     lv_imgbtn_set_src(other_page.imgbtn_roller_sw, LV_BTN_STATE_PR, &png_sw_on);
    //     lv_imgbtn_set_src(other_page.imgbtn_roller_sw, LV_BTN_STATE_REL, &png_sw_on);
    // }
}


char str_flame_sw_on[] = "$37=1\n";
char str_flame_sw_off[] = "$37=0\n";
static void event_handler_flame() {

    // if(flame_status->get()) {
    //     MKS_GRBL_CMD_SEND(str_flame_sw_off);
    //     MKS_GRBL_CMD_SEND(str_flame_sw_off);
    //     lv_imgbtn_set_src(other_page.imgbtn_flame_sw, LV_BTN_STATE_PR, &png_sw_off);
    //     lv_imgbtn_set_src(other_page.imgbtn_flame_sw, LV_BTN_STATE_REL, &png_sw_off);
    // }else {
    //     MKS_GRBL_CMD_SEND(str_flame_sw_on);
    //     MKS_GRBL_CMD_SEND(str_flame_sw_on);
    //     lv_imgbtn_set_src(other_page.imgbtn_flame_sw, LV_BTN_STATE_PR, &png_sw_on);
    //     lv_imgbtn_set_src(other_page.imgbtn_flame_sw, LV_BTN_STATE_REL, &png_sw_on);
    // }
}

char str_gyro_sw_on[] = "$39=1\n";
char str_gyro_sw_off[] = "$39=0\n";
static void event_handler_gyro() { 

    // if(gyro_status->get()) {
    //     MKS_GRBL_CMD_SEND(str_gyro_sw_off);
    //     MKS_GRBL_CMD_SEND(str_gyro_sw_off);
    //     lv_imgbtn_set_src(other_page.imgbtn_gyro_sw, LV_BTN_STATE_PR, &png_sw_off);
    //     lv_imgbtn_set_src(other_page.imgbtn_gyro_sw, LV_BTN_STATE_REL, &png_sw_off);
    // }else {
    //     MKS_GRBL_CMD_SEND(str_gyro_sw_on);
    //     MKS_GRBL_CMD_SEND(str_gyro_sw_on);
    //     lv_imgbtn_set_src(other_page.imgbtn_gyro_sw, LV_BTN_STATE_PR, &png_sw_on);
    //     lv_imgbtn_set_src(other_page.imgbtn_gyro_sw, LV_BTN_STATE_REL, &png_sw_on);
    // }
}


static void event_handler(lv_obj_t* obj, lv_event_t event) {

	uint8_t id = get_event(obj);

    if(event == LV_EVENT_PRESSED) { ts35_beep_on(); }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {

        ts35_beep_off();

        switch(id) {

            case ID_O_BACK: 
                event_handler_back();
            break;

            case ID_O_FLAME_SW: 
                event_handler_flame();
            break;

            case ID_O_GYRO_SW: 
                event_handler_gyro();
            break;
            
            case ID_O_ROLLER_SW: 
                event_handler_roller();
            break;
        }
    }
}

void draw_other(void) {

    draw_other_imgbtn();

    draw_other_label();

    mks_ui_page.mks_ui_page = MKS_UI_OTHER;
}                      


static void draw_other_imgbtn() { 

    other_page.imgbtn_back = lv_imgbtn_creat_mks(mks_global.mks_src, other_page.imgbtn_back, &png_back_pre, &back, LV_ALIGN_IN_TOP_LEFT, 10, 10, event_handler);

    // if(roller_status->get()) {
    //     other_page.imgbtn_roller_sw = lv_imgbtn_creat_mks(mks_global.mks_src, other_page.imgbtn_roller_sw, &png_sw_on, &png_sw_on, LV_ALIGN_CENTER, 100, -30, event_handler);
    // }else{
    //     other_page.imgbtn_roller_sw = lv_imgbtn_creat_mks(mks_global.mks_src, other_page.imgbtn_roller_sw, &png_sw_off, &png_sw_off, LV_ALIGN_CENTER, 100, -30, event_handler);
    // }

    // if(flame_status->get()) {
    //     other_page.imgbtn_flame_sw = lv_imgbtn_creat_mks(mks_global.mks_src, other_page.imgbtn_flame_sw, &png_sw_on, &png_sw_on, LV_ALIGN_CENTER, 100, 30, event_handler);
    // }else {
    //     other_page.imgbtn_flame_sw = lv_imgbtn_creat_mks(mks_global.mks_src, other_page.imgbtn_flame_sw, &png_sw_off, &png_sw_off, LV_ALIGN_CENTER, 100, 30, event_handler);
    // }

    // if(gyro_status->get()) {
    //     other_page.imgbtn_gyro_sw = lv_imgbtn_creat_mks(mks_global.mks_src, other_page.imgbtn_gyro_sw, &png_sw_on, &png_sw_on, LV_ALIGN_CENTER, 100, 90, event_handler);
    // }else {
    //     other_page.imgbtn_gyro_sw = lv_imgbtn_creat_mks(mks_global.mks_src, other_page.imgbtn_gyro_sw, &png_sw_off, &png_sw_off, LV_ALIGN_CENTER, 100, 90, event_handler);
    // }
}

static void draw_other_label() { 

    other_page.label_back = label_for_imgbtn_name(mks_global.mks_src, other_page.label_back, other_page.imgbtn_back, 0, 0, mc_language.back);
    
    other_page.label_roller_sw =  label_for_text(mks_global.mks_src, other_page.label_roller_sw, other_page.imgbtn_roller_sw, -150, 0, LV_ALIGN_OUT_LEFT_MID,  mc_language.roller_sw);

    other_page.label_flame_sw =  label_for_text(mks_global.mks_src, other_page.label_flame_sw, other_page.imgbtn_flame_sw, -150, 0, LV_ALIGN_OUT_LEFT_MID,  mc_language.flame_sw);

    other_page.label_gyro_sw =  label_for_text(mks_global.mks_src, other_page.label_gyro_sw, other_page.imgbtn_gyro_sw, -150, 0, LV_ALIGN_OUT_LEFT_MID,  mc_language.gyro_sw);
}

void mks_clear_other(void) {
    lv_obj_clean(mks_global.mks_src);
}


