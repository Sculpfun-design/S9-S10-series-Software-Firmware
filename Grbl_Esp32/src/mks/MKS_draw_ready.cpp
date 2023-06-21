#include "MKS_draw_ready.h"

MKS_PAGE_READY ready_src;
lv_style_t bkl_color;    // main

LV_IMG_DECLARE(Adjustment);  
LV_IMG_DECLARE(Control);  
LV_IMG_DECLARE(Sculpture);	
LV_IMG_DECLARE(Tool);	

LV_IMG_DECLARE(png_adj_pre);  
LV_IMG_DECLARE(png_ctrl_pre);  
LV_IMG_DECLARE(png_file_pre);	
LV_IMG_DECLARE(png_tool_pre);	

LV_IMG_DECLARE(png_back_pre);	
LV_IMG_DECLARE(X_POS);	
LV_IMG_DECLARE(Y_POS);	
LV_IMG_DECLARE(Z_POS);	
LV_IMG_DECLARE(wifi_status);	
LV_IMG_DECLARE(me_status);	
LV_IMG_DECLARE(M_pwr);	
LV_IMG_DECLARE(mks_logo);	

enum {
    ID_R_ADJUST,
    ID_R_CONTRL,
    ID_R_SCULPTURE,
    ID_R_TOOL,
    ID_R_WIFI,
    ID_R_NONE,
};

static uint8_t get_event(lv_obj_t* obj) {
    if      (obj == ready_src.ready_imgbtn_Adjustment)      return ID_R_ADJUST;
    else if (obj == ready_src.ready_imgbtn_Control)         return ID_R_CONTRL;
    else if (obj == ready_src.ready_imgbtn_Sculpture)       return ID_R_SCULPTURE;
    else if (obj == ready_src.ready_btn_wifi)               return ID_R_WIFI;
    else if (obj == ready_src.ready_imgbtn_Tool)            return ID_R_TOOL;
    else if (obj == ready_src.ready_imgbtn_xpos)            return ID_R_NONE;
    else if (obj == ready_src.ready_imgbtn_ypos)            return ID_R_NONE;
    else if (obj == ready_src.ready_imgbtn_zpos)            return ID_R_NONE;
    else if (obj == ready_src.ready_imgbtn_pwr )            return ID_R_NONE;
    else if (obj == ready_src.ready_imgbtn_wifi_status )    return ID_R_NONE;
}

static void event_handler(lv_obj_t* obj, lv_event_t event) {

    uint8_t id = get_event(obj);

    if(event == LV_EVENT_PRESSED) { 
        ts35_beep_on(); 
    }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {

        ts35_beep_off(); 

        if((id != ID_R_NONE)) {
            mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
            mks_lv_clean_ui();
        }

        switch(id) {
            case ID_R_ADJUST:        mks_draw_power(); break;
            
            case ID_R_CONTRL:        mks_draw_move();; break;
            
            case ID_R_SCULPTURE:     
                file_popup_select_flag = false;
                mks_grbl.is_reading_file = true;
                mks_draw_craving();;
                mks_grbl.is_reading_file = false;
            break;

            case ID_R_TOOL:         mks_draw_tool();  break;

            #ifdef USE_WIFI
            case ID_R_WIFI:  
                mks_grbl.wifi_back_from = 0;
                mks_draw_wifi(); 
            break;
            #endif
            case ID_R_NONE: break;
        }
    }
}

lv_obj_t *logo;
uint32_t logo_count = 0;
void mks_draw_logo(void) {

    mks_ui_page.mks_ui_page = MKS_UI_Logo;  
       
    mks_global.mks_src = lv_obj_create(NULL, NULL);

    mks_global.mks_src = lv_scr_act();

    lv_obj_set_style(mks_global.mks_src ,&mks_global.mks_src_style);

    logo = mks_lvgl_img_set(mks_global.mks_src, logo, &mks_logo, 0 ,0);

    mc_language_init();
}


void mks_draw_ready(void) {

    mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;

    mks_global.mks_src_1 = lv_obj_create(mks_global.mks_src, NULL);

    lv_obj_set_size(mks_global.mks_src_1, READY_src1_x_size, READY_src1_y_size);
    lv_obj_set_pos(mks_global.mks_src_1, READY_src1_x, READY_src1_y);
    lv_obj_set_style(mks_global.mks_src_1 ,&mks_global.mks_src_1_style);

    ready_src.ready_imgbtn_Adjustment   = lv_imgbtn_creat_mks(mks_global.mks_src_1, ready_src.ready_imgbtn_Adjustment, &png_adj_pre, &Adjustment, LV_ALIGN_CENTER, -150, -10, event_handler);
    ready_src.ready_imgbtn_Control      = lv_imgbtn_creat_mks(mks_global.mks_src_1, ready_src.ready_imgbtn_Control, &png_ctrl_pre, &Control, LV_ALIGN_CENTER,-50, -10, event_handler);
    ready_src.ready_imgbtn_Sculpture    = lv_imgbtn_creat_mks(mks_global.mks_src_1, ready_src.ready_imgbtn_Sculpture, &png_file_pre, &Sculpture, LV_ALIGN_CENTER, 50, -10, event_handler);
    ready_src.ready_imgbtn_Tool         = lv_imgbtn_creat_mks(mks_global.mks_src_1, ready_src.ready_imgbtn_Tool, &png_tool_pre, &Tool, LV_ALIGN_CENTER, 150, -10, event_handler);

    ready_src.ready_imgbtn_xpos = lv_imgbtn_creat_n_mks(mks_global.mks_src ,ready_src.ready_imgbtn_xpos, &X_POS,  &X_POS, READY_FIRST_IMG_X+30, READY_FIRST_IMG_Y + 40, event_handler);
    ready_src.ready_imgbtn_ypos = lv_imgbtn_creat_n_mks(mks_global.mks_src ,ready_src.ready_imgbtn_ypos, &Y_POS,  &Y_POS, READY_FIRST_IMG_X+160, READY_FIRST_IMG_Y + 40, event_handler);
    ready_src.ready_imgbtn_zpos = lv_imgbtn_creat_n_mks(mks_global.mks_src ,ready_src.ready_imgbtn_zpos, &Z_POS,  &Z_POS, READY_FIRST_IMG_X+290, READY_FIRST_IMG_Y + 40, event_handler);
    ready_src.ready_imgbtn_pwr  = lv_imgbtn_creat_n_mks(mks_global.mks_src ,ready_src.ready_imgbtn_pwr,  &M_pwr,  &M_pwr, READY_FIRST_IMG_X+30, READY_FIRST_IMG_Y + 80, event_handler);
    ready_src.ready_imgbtn_wifi_status = lv_imgbtn_creat_n_mks(mks_global.mks_src ,ready_src.ready_imgbtn_wifi_status, &wifi_status, &wifi_status, READY_FIRST_IMG_X+160, READY_FIRST_IMG_Y + 80, event_handler);

    ready_src.ready_btn_wifi = mks_lv_btn_set(mks_global.mks_src, ready_src.ready_btn_wifi, 100, 30, READY_FIRST_LABEL_X+160, READY_FIRST_LABEL_Y+80, event_handler);

    lv_btn_set_style(ready_src.ready_btn_wifi, LV_BTN_STYLE_REL, &mks_global.wifi_btn_style);
    lv_btn_set_style(ready_src.ready_btn_wifi,LV_BTN_STYLE_PR, &mks_global.wifi_btn_style);

    label_for_imgbtn_name(mks_global.mks_src_1, ready_src.ready_label_Adjustment, ready_src.ready_imgbtn_Adjustment, 0, 5, mc_language.adjustment);
    
    label_for_imgbtn_name(mks_global.mks_src_1, ready_src.ready_label_Control, ready_src.ready_imgbtn_Control, 0, 5, mc_language.control);
    label_for_imgbtn_name(mks_global.mks_src_1, ready_src.ready_label_Sculpture, ready_src.ready_imgbtn_Sculpture, 0, 5, mc_language.sculpture);
    label_for_imgbtn_name(mks_global.mks_src_1, ready_src.ready_label_Tool, ready_src.ready_imgbtn_Tool, 0, 5, mc_language.tool);

    ready_src.ready_label_xpos = label_for_text(mks_global.mks_src,   ready_src.ready_label_xpos, ready_src.ready_imgbtn_xpos, 0, 0, LV_ALIGN_OUT_RIGHT_MID, "0");
    ready_src.ready_label_ypos = label_for_text(mks_global.mks_src,   ready_src.ready_label_ypos, ready_src.ready_imgbtn_ypos, 0, 0, LV_ALIGN_OUT_RIGHT_MID, "0");
    ready_src.ready_label_zpos = label_for_text(mks_global.mks_src,   ready_src.ready_label_zpos, ready_src.ready_imgbtn_zpos, 0, 0, LV_ALIGN_OUT_RIGHT_MID, "0");
    ready_src.ready_label_mpwr = label_for_text(mks_global.mks_src,   ready_src.ready_label_mpwr, ready_src.ready_imgbtn_pwr , 0, 0, LV_ALIGN_OUT_RIGHT_MID, "0");

    #if defined(USE_WIFI)
        if (mks_get_wifi_status() == false){ 
            ready_src.ready_label_wifi_status = label_for_btn_name(ready_src.ready_btn_wifi, ready_src.ready_label_wifi_status, 0, 0, mc_language.disconnect);
            
        }else {
            ready_src.ready_label_wifi_status = label_for_btn_name(ready_src.ready_btn_wifi, ready_src.ready_label_wifi_status, 40, 0, mc_language.connect);
        }
    #else 
        ready_src.ready_label_wifi_status = label_for_btn_name(ready_src.ready_btn_wifi, ready_src.ready_label_wifi_status, 0, 0, "Disconnect");
    #endif
    mks_ui_page.mks_ui_page = MKS_UI_Ready;
}

char xpos_str[50] = "0.0";
char status_str[50];
char ypos_str[50] = "0.0";
char zpos_str[50] = "0.0";
char mpwr_str[50] = "100%";
char wifi_status_str[50];
char wifi_ip_str[100];

void mks_widi_show_ip(IPAddress ip, uint8_t p) { 
    if(p) {
        strcat(wifi_ip_str, ip.toString().c_str());
    }else {
    }
}

void ready_data_updata(void) {

    if (SD_ready_next == false) {

        static uint8_t wifi_ref_count = 0;
        static float mks_print_position[MAX_N_AXIS];

        system_convert_array_steps_to_mpos(mks_print_position, sys_position);

        sprintf(xpos_str, "%.1f", mks_print_position[0]);
        sprintf(ypos_str, "%.1f", mks_print_position[1]);
        sprintf(zpos_str, "%.1f", mks_print_position[2]);
        sprintf(mpwr_str, "%d",  sys.spindle_speed);
        
        lv_label_set_static_text(ready_src.ready_label_xpos, xpos_str);
        lv_label_set_static_text(ready_src.ready_label_ypos, ypos_str);
        lv_label_set_static_text(ready_src.ready_label_zpos, zpos_str);
        lv_label_set_static_text(ready_src.ready_label_mpwr, mpwr_str);
        
        #if defined(USE_WIFI)
        if (mks_get_wifi_status() == false){
            ready_src.ready_label_wifi_status = mks_lv_label_updata(ready_src.ready_label_wifi_status, mc_language.disconnect);
        }
        else {
            ready_src.ready_label_wifi_status = mks_lv_label_updata(ready_src.ready_label_wifi_status, mc_language.connect);
        }
        #endif
    } 
}

void draw_read_click(bool status) {
    lv_obj_set_click(ready_src.ready_imgbtn_Adjustment, status);
    lv_obj_set_click(ready_src.ready_imgbtn_Control, status);
    lv_obj_set_click(ready_src.ready_imgbtn_Sculpture, status);
    lv_obj_set_click(ready_src.ready_imgbtn_Tool, status);
#if defined(USE_WIFI)
    lv_obj_set_click(ready_src.ready_btn_wifi, status);
#endif
}




