#include "MKS_draw_tool.h"

TOOL_PAGE_T tool_page;

lv_style_t about_src1_style;
lv_style_t btn_tool_style;

static lv_style_t style_line;

static void disp_sw_creat(void);

lv_obj_t *about_src1; 
// lv_obj_t *sw1;

lv_obj_t* label_board_version;
lv_obj_t* label_Firmware_version;
lv_obj_t* label_cpu_info;


enum {
    ID_A_BACK,
    ID_A_WIFI,
    ID_A_LANGUAGE,
    ID_A_SAFTY,
    ID_A_ROLLER,
    ID_A_BEEP,
};  

static uint8_t get_event(lv_obj_t* obj) {

    if(obj == tool_page.imgbtn_back)                return ID_A_BACK;
    else if(obj == tool_page.imgbtn_wifi)           return ID_A_WIFI;
    else if(obj == tool_page.imgbtn_roller)         return ID_A_ROLLER;
    else if(obj == tool_page.imgbtn_language)       return ID_A_LANGUAGE;
    else if(obj == tool_page.imgbtn_safty)          return ID_A_SAFTY;
    else if(obj == tool_page.imgbtn_beep)           return ID_A_BEEP;
}

lv_point_t tool_line_points[3][2] = {

    { {about_first_line_x, about_first_line_y}, {about_first_line_x+460, about_first_line_y} },
    { {about_first_line_x, about_first_line_y+50}, {about_first_line_x+460, about_first_line_y+50} },
    { {about_first_line_x, about_first_line_y+100}, {about_first_line_x+460, about_first_line_y+100} },
};

LV_IMG_DECLARE(back);	
LV_IMG_DECLARE(wifi_tool);	
LV_IMG_DECLARE(png_back_pre);
LV_IMG_DECLARE(png_wifi_pre);

LV_IMG_DECLARE(png_sw_on);
LV_IMG_DECLARE(png_sw_off);
LV_IMG_DECLARE(png_safty);
LV_IMG_DECLARE(png_safty_pre);
LV_IMG_DECLARE(png_roller);
LV_IMG_DECLARE(png_roller_pre);
LV_IMG_DECLARE(png_language);
LV_IMG_DECLARE(png_language_pre);

static void event_handle_wifi(void) {

    mks_clear_tool();
    mks_grbl.wifi_back_from = 1;
    #if defined(USE_WIFI)
        mks_draw_wifi();
    #endif
}

static void event_handle_language(void) { 

    mks_clear_tool();
    mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
    draw_language();
}


static void event_handler_others(void) { 
    mks_clear_tool();
    mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
    draw_other();
}

static void event_handle_back(void) {

    mks_clear_tool();
    mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
    mks_draw_ready();

}

char beep_en[] = "$38=1\n";
char beep_dis[] = "$38=0\n";
static void sw_event_handler(void)
{   
    char cmd[16];
    
    if(beep_status->get()) {
        strcpy(cmd, beep_dis);
        lv_imgbtn_set_src(tool_page.imgbtn_beep, LV_BTN_STATE_PR, &png_sw_off);
        lv_imgbtn_set_src(tool_page.imgbtn_beep, LV_BTN_STATE_REL, &png_sw_off);
    }else{
        strcpy(cmd, beep_en);
        lv_imgbtn_set_src(tool_page.imgbtn_beep, LV_BTN_STATE_PR, &png_sw_on);
        lv_imgbtn_set_src(tool_page.imgbtn_beep, LV_BTN_STATE_REL, &png_sw_on);
    }
    MKS_GRBL_CMD_SEND(cmd);
}

static void event_handler(lv_obj_t* obj, lv_event_t event) {

    uint8_t id = get_event(obj);

    if(event == LV_EVENT_PRESSED) { ts35_beep_on(); }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {

        ts35_beep_off();

        switch(id) {
            case ID_A_BACK:     event_handle_back();        break;
            case ID_A_WIFI:     event_handle_wifi();        break;  
            case ID_A_LANGUAGE: event_handle_language();    break;
            case ID_A_SAFTY:    event_handler_others();     break;
            case ID_A_ROLLER:   event_handler_others();     break;
            case ID_A_BEEP:     sw_event_handler();         break;
        }
    }
}

void mks_draw_tool(void) {

    char cpu_info[128]="CPU:Freq:";
    mks_global.mks_src_1 = lv_obj_create(mks_global.mks_src, NULL);
	lv_obj_set_size(mks_global.mks_src_1, about_src1_x_size, about_src1_y_size);
    lv_obj_set_pos(mks_global.mks_src_1, about_src1_x, about_src1_y);
    lv_obj_set_style(mks_global.mks_src_1, &mks_global.mks_src_1_style);

    tool_page.imgbtn_back = lv_imgbtn_creat_mks(mks_global.mks_src_1, tool_page.imgbtn_back, &png_back_pre, &back, LV_ALIGN_IN_LEFT_MID, 10, -15, event_handler);
#if defined(USE_WIFI)
    tool_page.imgbtn_wifi = lv_imgbtn_creat_mks(mks_global.mks_src_1, tool_page.imgbtn_wifi, &png_wifi_pre, &wifi_tool, LV_ALIGN_IN_RIGHT_MID, -10, -15, event_handler);
#endif

    if(beep_status->get()) {
        tool_page.imgbtn_beep = lv_imgbtn_creat_mks(mks_global.mks_src, tool_page.imgbtn_beep, &png_sw_on, &png_sw_on, LV_ALIGN_IN_BOTTOM_LEFT, 80, -25, event_handler);
    }else{
        tool_page.imgbtn_beep = lv_imgbtn_creat_mks(mks_global.mks_src, tool_page.imgbtn_beep, &png_sw_off, &png_sw_off, LV_ALIGN_IN_BOTTOM_LEFT, 80, -25, event_handler);
    }

    tool_page.imgbtn_language = lv_imgbtn_creat_mks(mks_global.mks_src_1, tool_page.imgbtn_language, &png_language_pre, &png_language, LV_ALIGN_IN_RIGHT_MID, -100, -15, event_handler);

    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
    style_line.line.width = 1;
    style_line.line.rounded = 1;

    tool_page.tool_line1 = mks_lv_set_line(mks_global.mks_src, tool_page.tool_line1, tool_line_points[0]);
    lv_line_set_style(tool_page.tool_line1, LV_LINE_STYLE_MAIN, &style_line);
    tool_page.tool_line2 = mks_lv_set_line(mks_global.mks_src, tool_page.tool_line2, tool_line_points[1]);
    lv_line_set_style(tool_page.tool_line2, LV_LINE_STYLE_MAIN, &style_line);
    tool_page.tool_line3 = mks_lv_set_line(mks_global.mks_src, tool_page.tool_line3, tool_line_points[2]);
    lv_line_set_style(tool_page.tool_line3, LV_LINE_STYLE_MAIN, &style_line);

    label_for_imgbtn_name(mks_global.mks_src_1, tool_page.label_back, tool_page.imgbtn_back, 0, 0, mc_language.back);

    label_for_imgbtn_name(mks_global.mks_src_1, tool_page.label_tool_wifi, tool_page.imgbtn_language, 0, 0, mc_language.language);

    label_for_text(mks_global.mks_src, tool_page.label_beep, tool_page.imgbtn_beep, -10,0, LV_ALIGN_OUT_LEFT_MID,  "Beep");

#if defined(USE_WIFI)
    label_for_imgbtn_name(mks_global.mks_src_1, tool_page.label_tool_wifi, tool_page.imgbtn_wifi, 0, 0, "Wifi");
#endif
    mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src, label_board_version, 10, 120, BOARD_NAME, 400);

    mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src, tool_page.label_board_version, 10, 170, FW_NAME, 400);

    strcat(cpu_info, String(ESP.getCpuFreqMHz()).c_str());
    strcat(cpu_info, "MHz/ T:");
    strcat(cpu_info, String(temperatureRead(), 1).c_str());
    strcat(cpu_info, "C/ ID:");
    strcat(cpu_info, String((uint16_t)(ESP.getEfuseMac() >> 32)).c_str());
    mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src, label_cpu_info, 10, 220, cpu_info, 400);
    mks_ui_page.mks_ui_page = MKS_UI_Tool; 
}

void mks_clear_tool(void) {
    lv_obj_clean(mks_global.mks_src);
}


