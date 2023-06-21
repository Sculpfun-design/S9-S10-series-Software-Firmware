#include "draw_ui.h"




void mks_global_style_init(void) {
    // 背景页面style
    lv_style_copy(&mks_global.mks_src_style, &lv_style_scr);
    mks_global.mks_src_style.body.grad_color = LV_COLOR_MAKE(0x13, 0x12, 0x1a);
	mks_global.mks_src_style.body.main_color = LV_COLOR_MAKE(0x13, 0x12, 0x1a);
    mks_global.mks_src_style.text.color = LV_COLOR_WHITE;
    mks_global.mks_src_style.text.font = &dlc32Font;
    
    // 第一个
    lv_style_copy(&mks_global.mks_src_1_style, &lv_style_scr);
    mks_global.mks_src_1_style.body.grad_color = LV_COLOR_MAKE(0x1F, 0x23, 0x33);
	mks_global.mks_src_1_style.body.main_color = LV_COLOR_MAKE(0x1F, 0x23, 0x33);
    mks_global.mks_src_1_style.text.color = LV_COLOR_WHITE;
    mks_global.mks_src_1_style.body.radius = 17;
    mks_global.mks_src_1_style.text.font = &dlc32Font;

    lv_style_copy(&mks_global.mks_src_2_style, &lv_style_scr);
    mks_global.mks_src_2_style.body.grad_color = LV_COLOR_MAKE(0x1F, 0x23, 0x33);
	mks_global.mks_src_2_style.body.main_color = LV_COLOR_MAKE(0x1F, 0x23, 0x33);
    mks_global.mks_src_2_style.text.color = LV_COLOR_WHITE;
    mks_global.mks_src_2_style.body.radius = 17;
    mks_global.mks_src_2_style.text.font = &dlc32Font;

    lv_style_copy(&mks_global.mks_src_3_style, &lv_style_scr);
    mks_global.mks_src_3_style.body.grad_color = LV_COLOR_MAKE(0x1F, 0x23, 0x33);
	mks_global.mks_src_3_style.body.main_color = LV_COLOR_MAKE(0x1F, 0x23, 0x33);
    mks_global.mks_src_3_style.text.color = LV_COLOR_WHITE;
    mks_global.mks_src_3_style.body.radius = 17;
    mks_global.mks_src_3_style.text.font = &dlc32Font;

    //wifi 按键
    lv_style_copy(&mks_global.wifi_btn_style, &lv_style_scr); 
    mks_global.wifi_btn_style.body.main_color = LV_COLOR_MAKE(0x13, 0x12, 0x1A);
    mks_global.wifi_btn_style.body.grad_color = LV_COLOR_MAKE(0x13, 0x12, 0x1A);
    mks_global.wifi_btn_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    mks_global.wifi_btn_style.text.color = LV_COLOR_WHITE;
    mks_global.wifi_btn_style.text.font = &dlc32Font;

    // 语言设置按键
    lv_style_copy(&mks_global.language_btn_pr_style, &lv_style_scr); 
    mks_global.language_btn_pr_style.body.main_color = LV_COLOR_MAKE(0x4, 0xD9, 0x19);
    mks_global.language_btn_pr_style.body.grad_color = LV_COLOR_MAKE(0x4, 0xD9, 0x19);
    mks_global.language_btn_pr_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    mks_global.language_btn_pr_style.text.color = LV_COLOR_WHITE;
    mks_global.language_btn_pr_style.text.font = &dlc32Font;
    mks_global.language_btn_pr_style.body.border.color =  LV_COLOR_MAKE(0x4, 0xD9, 0x19);
    mks_global.language_btn_pr_style.body.border.width = 1;

    lv_style_copy(&mks_global.language_btn_rel_style, &lv_style_scr); 
    mks_global.language_btn_rel_style.body.main_color = LV_COLOR_MAKE(0x13, 0x12, 0x1A);
    mks_global.language_btn_rel_style.body.grad_color = LV_COLOR_MAKE(0x13, 0x12, 0x1A);
    mks_global.language_btn_rel_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    mks_global.language_btn_rel_style.text.color = LV_COLOR_WHITE;
    mks_global.language_btn_rel_style.text.font = &dlc32Font;
    mks_global.language_btn_rel_style.body.border.color =  LV_COLOR_MAKE(0x4, 0xD9, 0x19);
    mks_global.language_btn_rel_style.body.border.width = 1;

    // test
    lv_style_copy(&mks_global.mks_test_style, &lv_style_scr); 
    mks_global.mks_test_style.body.main_color = LV_COLOR_MAKE(0x13, 0x12, 0x1A);
    mks_global.mks_test_style.body.grad_color = LV_COLOR_MAKE(0x13, 0x12, 0x1A);
    mks_global.mks_test_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    mks_global.mks_test_style.text.font = &lv_font_roboto_28;
    mks_global.mks_test_style.text.color = LV_COLOR_WHITE;
}



void message_event(uint8_t event) {

    switch(event) {
        case MS_EVENT_HARD_LIMIT:                   break;
        case MS_EVENT_SOFT_LIMIT:                   break;
        case MS_EVENT_X_POSTION:                    break;
        case MS_EVENT_Y_POSTION:                    break;
        case MS_EVENT_Z_POSTION:                    break;
        case MS_EVENT_XY_POSTION:                   break;
        case MS_EVENT_XYZ_POSTION:                  break;
        case MS_EVENT_SOFT_HOME:                    break;
        case MS_EVENT_HARD_HOME:                    break;
        case MS_EVENT_UNLOCK:                       break;
        case MS_EVENT_JOY:                          break;
        case MS_EVENT_ALARM:                        break;
        case MS_EVENT_SAFEDOOR:                     break;
        case MS_EVENT_PROBE:                        break;
        case MS_EVENT_SD_FAIL:                      break;
        case MS_EVENT_SD_UNCONNECT:                 break;
        case MS_EVENT_FRAME:                        break;
        case MS_EVENT_PRINT_COMFRM:                 break;
        case MS_EVENT_PRINT_STOP:                   break;
        case MS_EVENT_PRINT_FINSH:                  break;
        case MS_EVENT_WARNING_CPU_TEMP:             break; 
    }
}


uint8_t get_current_ui(void) { 
    return mks_ui_page.mks_ui_page;
}


void lv_obj_click_enable(uint8_t ui_id) {

    switch (ui_id) {
        case MKS_UI_Logo:           break;    
        case MKS_UI_Ready:          break;   
        case MKS_UI_Adjust:         break;  
        case MKS_UI_Control: break; 
        case MKS_UI_Caving: break;  
        case MKS_UI_Pring: break;   
        case MKS_UI_Tool: break;    
        case MKS_UI_Wifi: break;    
        case MKS_UI_Frame: break;   
        case MKS_UI_inFile: break;  
        case MKS_UI_UPDATA: break;  
        case MKS_UI_TEST: break;   
    }
}




