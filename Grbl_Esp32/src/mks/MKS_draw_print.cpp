#include "MKS_draw_print.h"
#include "../System.h"

PWR_CTRL_t mks_pwr_ctrl;
SPEED_CTRL_t mks_speed_ctrl;
MKS_PRINT_PAGE_t print_src;
MKS_PRINT_DATA_UPDATA_t print_data_updata;
MKS_PRINT_SETTING_T print_setting;

uint32_t ddxd;

/* btn */
static lv_obj_t* btn_popup_cancle;
static lv_obj_t* btn_popup_sure;
static lv_obj_t* btn_finsh_popup_sure;

lv_obj_t* Label_print_file_name;

LV_IMG_DECLARE(M_Pause);  // 暂停
LV_IMG_DECLARE(M_start);  // 开始
LV_IMG_DECLARE(M_Stop);  // 停止
LV_IMG_DECLARE(M_PWRr);  // 功率
LV_IMG_DECLARE(M_SPEED);  // 速度
LV_IMG_DECLARE(back);  // 速度

LV_IMG_DECLARE(add);  // 加
LV_IMG_DECLARE(confirm);  // 确认
LV_IMG_DECLARE(s_return);  // 确认
LV_IMG_DECLARE(reduce);  // 减

LV_IMG_DECLARE(png_cave_pwr);
LV_IMG_DECLARE(png_cave_speed);
LV_IMG_DECLARE(png_cave_xpos);
LV_IMG_DECLARE(png_cave_ypos);
LV_IMG_DECLARE(png_cave_zpos);
LV_IMG_DECLARE(png_pause_pre);          // 暂停
LV_IMG_DECLARE(png_start_pre);          // 开始
LV_IMG_DECLARE(png_stop_pre);           // 停止
LV_IMG_DECLARE(png_cave_pwr_pre);       // 功率
LV_IMG_DECLARE(png_cave_speed_pre);     // 速度
LV_IMG_DECLARE(png_times);              // 雕刻次数

static void event_handler_suspend(lv_obj_t* obj, lv_event_t event) {

    if(event == LV_EVENT_PRESSED) { 
        ts35_beep_on(); 
    }
        
    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST)) {

        ts35_beep_off(); 

        if(sys.state == State::Hold) {
            lv_imgbtn_set_src(print_src.print_imgbtn_suspend, LV_BTN_STATE_PR, &png_pause_pre);
            lv_imgbtn_set_src(print_src.print_imgbtn_suspend, LV_BTN_STATE_REL, &M_Pause);
            lv_label_set_static_text(print_src.print_Label_p_suspend, (char *)mc_language.hold);
            MKS_GRBL_CMD_SEND("~");
            if(print_setting._need_to_start_write) {
                sys_rt_s_override = print_setting.cur_spindle_pwr;
            }
        }   
        else if(sys.state == State::Cycle)    {
            lv_imgbtn_set_src(print_src.print_imgbtn_suspend, LV_BTN_STATE_PR, &png_start_pre);
            lv_imgbtn_set_src(print_src.print_imgbtn_suspend, LV_BTN_STATE_REL, &M_start);
            lv_label_set_static_text(print_src.print_Label_p_suspend, (char *)mc_language.run);
            MKS_GRBL_CMD_SEND("!");
        } 
        delay(10); // yied 10ms to other task
    }
}

static void event_handler_stop(lv_obj_t* obj, lv_event_t event) {

    if(event == LV_EVENT_PRESSED) { 
        ts35_beep_on(); 
    }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {

        ts35_beep_off(); 

        mks_draw_print_popup(mc_language.stp_tis);
    }
}

static void event_handler_pwr_set(lv_obj_t* obj, lv_event_t event) {

    if(event == LV_EVENT_PRESSED) { 
        ts35_beep_on(); 
    }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {
        ts35_beep_off(); 
        mks_print_pwr_set();
    }
}

static void event_handler_speed_set(lv_obj_t* obj, lv_event_t event) {

    if(event == LV_EVENT_PRESSED) { 
        ts35_beep_on(); 
    }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {

        ts35_beep_off(); 
        mks_print_speed_set();
    }
}

static void event_handler_op(lv_obj_t* obj, lv_event_t event) {
    
    if(event == LV_EVENT_PRESSED) { 
        ts35_beep_on(); 
    }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {
        mks_clear_print();
        mks_draw_operation();
    }
}

static void event_handler_none(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {

    }
}

void mks_draw_print(void) {
    char print_file_name[128];
    
    print_setting.cur_spindle_pwr = sys_rt_s_override;
    print_setting.cur_spindle_speed = sys_rt_f_override;

    // mks fix
    print_setting.carve_staus = CAVRE_START;

    memcpy(print_file_name, file_print_send, sizeof(file_print_send));
    if(print_file_name[0] == '/') print_file_name[0] = ' ';

    mks_pwr_ctrl.pwr_len = PWR_1_PERSEN;
    mks_speed_ctrl.speed_len = SPEED_1_PERSEN;

    mks_global.mks_src_1 = lv_obj_create(mks_global.mks_src, NULL);
    lv_obj_set_size(mks_global.mks_src_1, print_src1_size_x, print_src1_size_y);
    lv_obj_set_pos(mks_global.mks_src_1, print_src1_x, print_src1_y);

    mks_global.mks_src_2 = lv_obj_create(mks_global.mks_src, NULL);
    lv_obj_set_size(mks_global.mks_src_2, print_src2_size_x, print_src2_size_y);
    lv_obj_set_pos(mks_global.mks_src_2, print_src2_x, print_src2_y);

    lv_obj_set_style(mks_global.mks_src_1, &mks_global.mks_src_1_style);
    lv_obj_set_style(mks_global.mks_src_2, &mks_global.mks_src_2_style);

    /* 进度条背景样式 */
    lv_style_copy(&print_src.print_bar_bg_style, &lv_style_plain_color);
    print_src.print_bar_bg_style.body.main_color = LV_COLOR_MAKE(0x3F,0x46,0x66);
    print_src.print_bar_bg_style.body.grad_color = LV_COLOR_MAKE(0x3F,0x46,0x66);
    print_src.print_bar_bg_style.body.radius = 5;

    /* 进度条显示样式 */
    lv_style_copy(&print_src.print_bar_indic_style,&lv_style_plain_color);
    print_src.print_bar_indic_style.body.main_color = LV_COLOR_MAKE(0x52,0xCC,0x82);
    print_src.print_bar_indic_style.body.grad_color = LV_COLOR_MAKE(0x52,0xCC,0x82);
    print_src.print_bar_indic_style.body.radius = 5;
    print_src.print_bar_indic_style.body.padding.left = 0;//让指示器跟背景边框之间没有距离
    print_src.print_bar_indic_style.body.padding.top = 0;
    print_src.print_bar_indic_style.body.padding.right = 0;
    print_src.print_bar_indic_style.body.padding.bottom = 0;

    print_src.print_imgbtn_suspend = lv_imgbtn_creat_n_mks(mks_global.mks_src_1,  
                                         print_src.print_imgbtn_suspend, 
                                         &png_pause_pre, 
                                         &M_Pause, 
                                         print_src1_first_pic_x,
                                         print_src1_first_pic_y,
                                         event_handler_suspend);

    print_src.print_imgbtn_stop = lv_imgbtn_creat_n_mks(mks_global.mks_src_1, 
                                     print_src.print_imgbtn_stop, 
                                     &png_stop_pre, 
                                     &M_Stop, 
                                     print_src1_first_pic_x + 90, 
                                     print_src1_first_pic_y, 
                                     event_handler_stop);

    print_src.print_imgbtn_pwr = lv_imgbtn_creat_n_mks(mks_global.mks_src_1, 
                                     print_src.print_imgbtn_pwr, 
                                     &png_cave_pwr_pre,
                                     &M_PWRr, 
                                     print_src1_first_pic_x + 180, 
                                     print_src1_first_pic_y, 
                                     event_handler_pwr_set);
    
    print_src.print_imgbtn_speed = lv_imgbtn_creat_n_mks(mks_global.mks_src_1, 
                                        print_src.print_imgbtn_speed, 
                                        &png_cave_speed_pre, 
                                        &M_SPEED, 
                                        print_src1_first_pic_x + 270, 
                                        print_src1_first_pic_y, 
                                        event_handler_speed_set);

    lv_imgbtn_creat_n_mks(mks_global.mks_src_2 ,print_src.print_icon_X, &png_cave_xpos,  &png_cave_xpos, print_src2_first_pic_x+200, print_src2_first_pic_y, event_handler_none);
    lv_imgbtn_creat_n_mks(mks_global.mks_src_2 ,print_src.print_icon_Y, &png_cave_ypos,  &png_cave_ypos, print_src2_first_pic_x+200, print_src2_first_pic_y + 30, event_handler_none);
    lv_imgbtn_creat_n_mks(mks_global.mks_src_2 ,print_src.print_icon_Z, &png_cave_zpos,  &png_cave_zpos, print_src2_first_pic_x+200, print_src2_first_pic_y + 60, event_handler_none);
    lv_imgbtn_creat_n_mks(mks_global.mks_src_2 ,print_src.print_icon_PWR,       &png_cave_pwr,  &png_cave_pwr, print_src2_first_pic_x, print_src2_first_pic_y, event_handler_none);
    lv_imgbtn_creat_n_mks(mks_global.mks_src_2 ,print_src.print_icon_SPEED,  &png_cave_speed,  &png_cave_speed, print_src2_first_pic_x, print_src2_first_pic_y+30, event_handler_none);
    lv_imgbtn_creat_n_mks(mks_global.mks_src_2 ,print_src.print_icon_TIMES,  &png_times,  &png_times, print_src2_first_pic_x, print_src2_first_pic_y+60, event_handler_none);

    print_src.print_bar_print = mks_lv_bar_set(mks_global.mks_src_2, print_src.print_bar_print, 440, 35, print_bar_pic_x, print_bar_pic_y, 0);

    lv_bar_set_style(print_src.print_bar_print, LV_BAR_STYLE_BG , &print_src.print_bar_bg_style);
    lv_bar_set_style(print_src.print_bar_print, LV_BAR_STYLE_INDIC , &print_src.print_bar_indic_style);

    print_src.print_Label_p_suspend = label_for_imgbtn_name(mks_global.mks_src_1, print_src.print_Label_p_suspend, print_src.print_imgbtn_suspend ,0 ,0 ,(char *)mc_language.hold);
    print_src.print_Label_p_stop = label_for_imgbtn_name(mks_global.mks_src_1, print_src.print_Label_p_stop, print_src.print_imgbtn_stop ,0 ,0 ,(char *)mc_language.stop);
    print_src.print_Label_p_power = label_for_imgbtn_name(mks_global.mks_src_1, print_src.print_Label_p_power, print_src.print_imgbtn_pwr ,0 ,0 ,(char *)mc_language.power);
    print_src.print_Label_p_caveSpeed = label_for_imgbtn_name(mks_global.mks_src_1, print_src.print_Label_p_caveSpeed, print_src.print_imgbtn_speed ,0 ,0 ,(char *)mc_language.speed);


    print_src.print_Label_x_pos = mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src_2, print_src.print_Label_x_pos, print_first_data_label_x+300, print_first_data_label_y,    "0", 50);
    print_src.print_Label_y_pos = mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src_2, print_src.print_Label_y_pos, print_first_data_label_x+300, print_first_data_label_y+30, "0", 50);
    print_src.print_Label_z_pos = mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src_2, print_src.print_Label_z_pos, print_first_data_label_x+300, print_first_data_label_y+60, "0", 50);
    print_src.print_Label_power = mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src_2, print_src.print_Label_power, print_first_data_label_x + 100, print_first_data_label_y, "0", 50);
    print_src.print_Label_caveSpeed = mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src_2, print_src.print_Label_caveSpeed, print_first_data_label_x + 100, print_first_data_label_y+30, "0", 50);
    print_src.print_Label_caveTimes = mks_lvgl_long_sroll_label_with_wight_set_center(mks_global.mks_src_2, print_src.print_Label_caveTimes, print_first_data_label_x + 100, print_first_data_label_y+60, "0", 50);

    Label_print_file_name = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_bar_print, Label_print_file_name, 10, 8, print_file_name, 400);
    print_src.print_bar_print_percen = label_for_btn_name(print_src.print_bar_print, print_src.print_bar_print_percen, 190, 0, "0%");
    // lv_refr_now(lv_refr_get_disp_refreshing());

    mks_ui_page.mks_ui_page = MKS_UI_Pring;  //进入雕刻界面
}

static void event_btn_cancle(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {
        
        lv_obj_set_click(print_src.print_imgbtn_suspend, true);
        lv_obj_set_click(print_src.print_imgbtn_stop, true);
        lv_obj_set_click(print_src.print_imgbtn_pwr, true);
        lv_obj_set_click(print_src.print_imgbtn_speed, true);
        lv_obj_del(print_src.print_stop_popup);
    }
}

static void event_btn_sure(lv_obj_t* obj, lv_event_t event) {
    uint16_t buf_cmd[]={0x18};
    if (event == LV_EVENT_RELEASED) {
        lv_obj_set_click(print_src.print_imgbtn_suspend, true);
        lv_obj_set_click(print_src.print_imgbtn_stop, true);
        lv_obj_set_click(print_src.print_imgbtn_pwr, true);
        lv_obj_set_click(print_src.print_imgbtn_speed, true);
        closeFile();
        mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
        mks_clear_print();
        MKS_GRBL_CMD_SEND("M3 S0\n");
        MKS_GRBL_CMD_SEND("G90X0Y0F800\n");
        MKS_GRBL_CMD_SEND(buf_cmd);
        mks_draw_ready();
    }
}

static void event_btn_printdon(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {
        lv_obj_set_click(print_src.print_imgbtn_suspend, true);
        lv_obj_set_click(print_src.print_imgbtn_stop, true);
        lv_obj_set_click(print_src.print_imgbtn_pwr, true);
        lv_obj_set_click(print_src.print_imgbtn_speed, true);
        mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
        tf.deleteFile("/PLA.txt");
        lv_obj_del(print_src.print_finsh_popup);
        mks_clear_print();
        mks_draw_ready();
    }
}


// stop print popup
void mks_draw_print_popup(const char* text) {
    
    lv_obj_set_click(print_src.print_imgbtn_suspend, false);
    lv_obj_set_click(print_src.print_imgbtn_stop, false);
    lv_obj_set_click(print_src.print_imgbtn_pwr, false);
    lv_obj_set_click(print_src.print_imgbtn_speed, false);
    //  need cancle click

    print_src.print_stop_popup = lv_obj_create(mks_global.mks_src, NULL);

    lv_obj_set_size(print_src.print_stop_popup, print_popup_size_x, print_popup_size_y);
    lv_obj_set_pos(print_src.print_stop_popup, print_popup_x, print_popup_y);

    lv_style_copy(&print_src.printf_popup_style, &lv_style_scr);
    print_src.printf_popup_style.body.main_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.body.grad_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.text.color = LV_COLOR_BLACK;
    print_src.printf_popup_style.body.radius = 17;
    print_src.printf_popup_style.text.font = &dlc32Font;
    lv_obj_set_style(print_src.print_stop_popup, &print_src.printf_popup_style);

    lv_style_copy(&print_src.print_popup_btn_style, &lv_style_scr);
    print_src.print_popup_btn_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_popup_btn_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_popup_btn_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    print_src.print_popup_btn_style.text.color = LV_COLOR_WHITE;
    print_src.print_popup_btn_style.text.font = &dlc32Font;
    print_src.print_popup_btn_style.body.radius = 10; 

    btn_popup_sure = mks_lv_btn_set(print_src.print_stop_popup, btn_popup_sure, 100,40,10,130, event_btn_sure);
	lv_btn_set_style(btn_popup_sure, LV_BTN_STYLE_REL, &print_src.print_popup_btn_style);
    lv_btn_set_style(btn_popup_sure,LV_BTN_STYLE_PR,&print_src.print_popup_btn_style);

    label_for_btn_name(btn_popup_sure, print_src.print_Label_popup_sure, 0, 0, mc_language.tis_yes);

	btn_popup_cancle = mks_lv_btn_set(print_src.print_stop_popup, btn_popup_cancle, 100,40,240,130, event_btn_cancle);
	lv_btn_set_style(btn_popup_cancle, LV_BTN_STYLE_REL, &print_src.print_popup_btn_style);
    lv_btn_set_style(btn_popup_cancle,LV_BTN_STYLE_PR,&print_src.print_popup_btn_style);

    label_for_btn_name(btn_popup_cancle, print_src.print_Label_popup_sure, 0, 0, mc_language.tis_cancle);

    label_for_screen(print_src.print_stop_popup, print_src.print_Label_popup, 0, -10, text);
}

void mks_draw_finsh_pupop(void) { 

    lv_obj_set_click(print_src.print_imgbtn_suspend, false);
    lv_obj_set_click(print_src.print_imgbtn_stop, false);
    lv_obj_set_click(print_src.print_imgbtn_pwr, false);
    lv_obj_set_click(print_src.print_imgbtn_speed, false);

    print_src.print_finsh_popup = lv_obj_create(mks_global.mks_src, NULL);

    lv_obj_set_size(print_src.print_finsh_popup, 350, 200);
    lv_obj_set_pos(print_src.print_finsh_popup, 80, 50);

    lv_style_copy(&print_src.printf_popup_style, &lv_style_scr);
    print_src.printf_popup_style.body.main_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.body.grad_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.text.color = LV_COLOR_BLACK;
    print_src.printf_popup_style.body.radius = 17;
    print_src.printf_popup_style.text.font = &dlc32Font;
    lv_obj_set_style(print_src.print_finsh_popup, &print_src.printf_popup_style);

    lv_style_copy(&print_src.print_popup_btn_style, &lv_style_scr);
    print_src.print_popup_btn_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_popup_btn_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_popup_btn_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    print_src.print_popup_btn_style.text.color = LV_COLOR_WHITE;
    print_src.print_popup_btn_style.text.font = &dlc32Font;
    print_src.print_popup_btn_style.body.radius = 10; 

    btn_finsh_popup_sure = lv_btn_create(print_src.print_finsh_popup, NULL);
    lv_obj_set_size(btn_finsh_popup_sure,   100, 50);
    lv_obj_set_pos(btn_finsh_popup_sure,    120, 130);
    lv_obj_set_event_cb(btn_finsh_popup_sure, event_btn_printdon);
    lv_btn_set_style(btn_finsh_popup_sure, LV_BTN_STYLE_REL, &print_src.print_popup_btn_style);
    lv_btn_set_style(btn_finsh_popup_sure,LV_BTN_STYLE_PR,&print_src.print_popup_btn_style);

    label_for_btn_name(btn_finsh_popup_sure, print_src.print_Label_popup_sure, 0, 0, (char *)mc_language.tis_yes);
    label_for_screen(print_src.print_finsh_popup, print_src.print_Label_popup, 0, -20, (char *)mc_language.finsh_tis);
    
}

char bar_percen_str[20];
void mks_print_bar_updata(void) {
    print_src.print_bar_print = mks_lv_bar_updata(print_src.print_bar_print, (uint16_t)sd_report_perc_complete());
    sprintf(bar_percen_str, "%d%%", (uint16_t)sd_report_perc_complete());
    print_src.print_bar_print_percen = mks_lv_label_updata(print_src.print_bar_print_percen, bar_percen_str);
}

/****************************************************************************************pwr_popup****************************************************************************************/

lv_obj_t *pwr_label_power;

char power_add_dec_buf[20];

static void event_pwr_setting_add(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {
        
        if(mks_pwr_ctrl.pwr_len == PWR_1_PERSEN) {
            print_setting.cur_spindle_pwr += SpindleSpeedOverride::FineIncrement;
            if(print_setting.cur_spindle_pwr > SpindleSpeedOverride::Max) {
                print_setting.cur_spindle_pwr = SpindleSpeedOverride::Max;    
            }
        }else if(mks_pwr_ctrl.pwr_len == PWR_10_PERSEN) {
            print_setting.cur_spindle_pwr += SpindleSpeedOverride::CoarseIncrement;
            if(print_setting.cur_spindle_pwr > SpindleSpeedOverride::Max) {
                print_setting.cur_spindle_pwr = SpindleSpeedOverride::Max;    
            }
        }
        sprintf(power_add_dec_buf, "Power:%d%%", print_setting.cur_spindle_pwr);
        lv_label_set_static_text(pwr_label_power, power_add_dec_buf);
    }
}

static void event_pwr_setting_dec(lv_obj_t* obj, lv_event_t event) {

    uint16_t temp;

    if (event == LV_EVENT_RELEASED) {

        if(mks_pwr_ctrl.pwr_len == PWR_1_PERSEN) {
            print_setting.cur_spindle_pwr -= SpindleSpeedOverride::FineIncrement;
            if(print_setting.cur_spindle_pwr < SpindleSpeedOverride::Min) {
                print_setting.cur_spindle_pwr = SpindleSpeedOverride::Min;
            }
        }else if(mks_pwr_ctrl.pwr_len == PWR_10_PERSEN) {
            print_setting.cur_spindle_pwr -= SpindleSpeedOverride::CoarseIncrement;
            if(print_setting.cur_spindle_pwr < SpindleSpeedOverride::Min) {
                print_setting.cur_spindle_pwr = SpindleSpeedOverride::Min;
            }
        }
        sprintf(power_add_dec_buf, "Power:%d%%", print_setting.cur_spindle_pwr);
        lv_label_set_static_text(pwr_label_power, power_add_dec_buf);
    }
}

static void event_btn_pwr_1mm(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {

        if(mks_pwr_ctrl.pwr_len == PWR_10_PERSEN) {
            mks_pwr_ctrl.pwr_len = PWR_1_PERSEN;
            lv_label_set_text(print_src.print_label_1_mm, "#ffffff 1% #");
            lv_label_set_text(print_src.print_label_10_mm, "#000000 10% #");

            print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
            lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);

            print_src.print_mm_btn2_style.body.main_color = LV_COLOR_WHITE;
            print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_WHITE;
            lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn2_style);
            lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn2_style); 
        }
    }
}

static void event_btn_pwr_10mm(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {

        if(mks_pwr_ctrl.pwr_len == PWR_1_PERSEN) {
            mks_pwr_ctrl.pwr_len = PWR_10_PERSEN;
            lv_label_set_text(print_src.print_label_1_mm, "#000000 1% #");
            lv_label_set_text(print_src.print_label_10_mm, "#ffffff 10% #");

            print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
            lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);

            print_src.print_mm_btn2_style.body.main_color = LV_COLOR_WHITE;
            print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_WHITE;
            lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn2_style);
            lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn2_style);
        }
    }
}

static void event_pwr_setting_confirm(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {

        if(sys.state == State::Hold) {
            print_setting._need_to_start_write = true;
        }else{
            sys_rt_s_override = print_setting.cur_spindle_pwr;
        }

        lv_obj_set_click(print_src.print_imgbtn_suspend, true);
        lv_obj_set_click(print_src.print_imgbtn_stop, true);
        lv_obj_set_click(print_src.print_imgbtn_pwr, true);
        lv_obj_set_click(print_src.print_imgbtn_speed, true);
        lv_obj_del(print_src.print_pwr_speed_src);
    }
}

static void event_pwr_setting_return(lv_obj_t* obj, lv_event_t event) {

    if (event == LV_EVENT_RELEASED) {

        print_setting.cur_spindle_pwr = sys_rt_s_override;

        lv_obj_set_click(print_src.print_imgbtn_suspend, true);
        lv_obj_set_click(print_src.print_imgbtn_stop, true);
        lv_obj_set_click(print_src.print_imgbtn_pwr, true);
        lv_obj_set_click(print_src.print_imgbtn_speed, true);
        lv_obj_del(print_src.print_pwr_speed_src);
    }
}


void mks_print_pwr_set(void) { 

    char buf[20]; 

    lv_obj_set_click(print_src.print_imgbtn_suspend, false);
    lv_obj_set_click(print_src.print_imgbtn_stop, false);
    lv_obj_set_click(print_src.print_imgbtn_pwr, false);
    lv_obj_set_click(print_src.print_imgbtn_speed, false);

#if defined(USR_RELASE)
    print_src.print_pwr_speed_src = lv_obj_create(mks_src, NULL);
#else
    print_src.print_pwr_speed_src = lv_obj_create(mks_global.mks_src, NULL);
#endif
    lv_obj_set_size(print_src.print_pwr_speed_src, 350, 200);
    lv_obj_set_pos(print_src.print_pwr_speed_src, 75, 50);

    lv_style_copy(&print_src.printf_popup_style, &lv_style_scr);
    print_src.printf_popup_style.body.main_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.body.grad_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.text.color = LV_COLOR_BLACK;
    print_src.printf_popup_style.body.radius = 17;
    print_src.printf_popup_style.text.font = &dlc32Font;
    lv_obj_set_style(print_src.print_pwr_speed_src, &print_src.printf_popup_style);

    lv_style_copy(&print_src.print_mm_btn1_style, &lv_style_scr);
    print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn1_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    print_src.print_mm_btn1_style.text.color = LV_COLOR_WHITE;
    print_src.print_mm_btn1_style.text.font = &dlc32Font;
    print_src.print_mm_btn1_style.body.radius = 10; 

    lv_style_copy(&print_src.print_mm_btn2_style, &lv_style_scr);
    print_src.print_mm_btn2_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn2_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    print_src.print_mm_btn2_style.text.color = LV_COLOR_WHITE;
    print_src.print_mm_btn2_style.body.radius = 10; 
    print_src.print_mm_btn2_style.text.font = &dlc32Font;

    print_src.print_btn_1_mm = mks_lv_btn_set(print_src.print_pwr_speed_src, print_src.print_btn_1_mm, 100, 40, 60, 80, event_btn_pwr_1mm);
    print_src.print_btn_10_mm = mks_lv_btn_set(print_src.print_pwr_speed_src, print_src.print_btn_10_mm, 100, 40, 180, 80, event_btn_pwr_10mm);

    if(mks_pwr_ctrl.pwr_len == PWR_1_PERSEN) { 
        print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
        lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);

        print_src.print_mm_btn2_style.body.main_color = LV_COLOR_WHITE;
        print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_WHITE;
        lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn2_style);
        lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn2_style); 
    }else {
        print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
        lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);

        print_src.print_mm_btn2_style.body.main_color = LV_COLOR_WHITE;
        print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_WHITE;
        lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn2_style);
        lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn2_style); 
    }

    sprintf(buf, "Power:%d%%", sys_rt_s_override);

    pwr_label_power = label_for_screen(print_src.print_pwr_speed_src, pwr_label_power, 0, -60, buf);

    if(mks_pwr_ctrl.pwr_len == PWR_1_PERSEN) {
        print_src.print_label_1_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_1_mm, print_src.print_label_1_mm, 0, 0, "#ffffff 1%#", 50);
        print_src.print_label_10_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_10_mm, print_src.print_label_10_mm, 0, 0, "#000000 10% #", 50);
    }else{
        print_src.print_label_1_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_1_mm, print_src.print_label_1_mm, 0, 0, "#000000 1%#", 50);
        print_src.print_label_10_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_10_mm, print_src.print_label_10_mm, 0, 0, "#ffffff 10% #", 50);
    }
    
    print_src.print_sp_imgbtn_add = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, print_src.print_sp_imgbtn_add, &add, &add, LV_ALIGN_IN_LEFT_MID, print_pwr_popup_add_btn_x,print_pwr_popup_add_btn_y, event_pwr_setting_add);
    print_src.print_sp_imgbtn_dec = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, print_src.print_sp_imgbtn_dec, &reduce, &reduce, LV_ALIGN_IN_LEFT_MID, print_pwr_popup_add_btn_x+80,print_pwr_popup_add_btn_y, event_pwr_setting_dec);
    print_src.print_sp_btn_sure = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, print_src.print_sp_imgbtn_dec, &confirm, &confirm, LV_ALIGN_IN_LEFT_MID, print_pwr_popup_add_btn_x+160,print_pwr_popup_add_btn_y, event_pwr_setting_confirm);

    print_src.print_sp_btn_return = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, 
                                                        print_src.print_sp_btn_return, 
                                                        &s_return, 
                                                        &s_return, 
                                                        LV_ALIGN_IN_LEFT_MID, 
                                                        print_pwr_popup_add_btn_x+240,
                                                        print_pwr_popup_add_btn_y, event_pwr_setting_return);
}


/****************************************************************************************speed_popup****************************************************************************************/
lv_obj_t *pwr_label_speed;
char speed_add_dec_buf[20];

static void event_speed_setting_add(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {
        
        if(mks_speed_ctrl.speed_len == SPEED_1_PERSEN) {
            print_setting.cur_spindle_speed += FeedOverride::FineIncrement;
            if(print_setting.cur_spindle_speed > FeedOverride::Max) {
                print_setting.cur_spindle_speed = FeedOverride::Max;
            }

        }else if(mks_speed_ctrl.speed_len == SPEED_10_PERSEN) {
            print_setting.cur_spindle_speed += FeedOverride::CoarseIncrement;
            if(print_setting.cur_spindle_speed > FeedOverride::Max) {
                print_setting.cur_spindle_speed = FeedOverride::Max;
            }
        }
        sprintf(speed_add_dec_buf, "Speed:%d%%", print_setting.cur_spindle_speed);
        lv_label_set_static_text(pwr_label_speed, speed_add_dec_buf);
    }
}

static void event_speed_setting_dec(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {
        
        if(mks_speed_ctrl.speed_len == SPEED_1_PERSEN) {
            print_setting.cur_spindle_speed -= FeedOverride::FineIncrement;
            if(print_setting.cur_spindle_speed < FeedOverride::Min) {
                print_setting.cur_spindle_speed = FeedOverride::Min;
            }
        }else if(mks_speed_ctrl.speed_len == SPEED_10_PERSEN) {
            print_setting.cur_spindle_speed -= FeedOverride::CoarseIncrement;
            if(print_setting.cur_spindle_speed < FeedOverride::Min) {
                print_setting.cur_spindle_speed = FeedOverride::Min;
            }
        }
        sprintf(speed_add_dec_buf, "Speed:%d%%", print_setting.cur_spindle_speed);
        lv_label_set_static_text(pwr_label_speed, speed_add_dec_buf);
    }
}

static void event_speed_setting_confirm(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {

        sys_rt_f_override = print_setting.cur_spindle_speed;

        lv_obj_set_click(print_src.print_imgbtn_suspend, true);
        lv_obj_set_click(print_src.print_imgbtn_stop, true);
        lv_obj_set_click(print_src.print_imgbtn_pwr, true);
        lv_obj_set_click(print_src.print_imgbtn_speed, true);
        lv_obj_del(print_src.print_pwr_speed_src);
    }
}

static void event_speed_setting_return(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {

        print_setting.cur_spindle_speed = sys_rt_f_override;

        lv_obj_set_click(print_src.print_imgbtn_suspend, true);
        lv_obj_set_click(print_src.print_imgbtn_stop, true);
        lv_obj_set_click(print_src.print_imgbtn_pwr, true);
        lv_obj_set_click(print_src.print_imgbtn_speed, true);
        lv_obj_del(print_src.print_pwr_speed_src);
    }
}


static void event_btn_speed_1mm(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {
        if(mks_speed_ctrl.speed_len == SPEED_10_PERSEN) {
            mks_speed_ctrl.speed_len = SPEED_1_PERSEN;

            lv_label_set_text(print_src.print_label_1_mm, "#ffffff 1% #");  //000000
            lv_label_set_text(print_src.print_label_10_mm, "#000000 10% #"); //ffffff
            
            print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
            lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);

            print_src.print_mm_btn2_style.body.main_color = LV_COLOR_WHITE;
            print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_WHITE;
            lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn2_style);
            lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn2_style);
        }
    }
}

static void event_btn_speed_10mm(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_RELEASED) {
        if(mks_speed_ctrl.speed_len == SPEED_1_PERSEN) {
            mks_speed_ctrl.speed_len = SPEED_10_PERSEN;
            lv_label_set_text(print_src.print_label_1_mm, "#000000 1% #");
            lv_label_set_text(print_src.print_label_10_mm, "#ffffff 10% #");

            print_src.print_mm_btn1_style.body.main_color = LV_COLOR_WHITE;
            print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_WHITE;
            lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
            lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);

            print_src.print_mm_btn2_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
            lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn2_style);
            lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn2_style);
        }
    }
}

void mks_print_speed_set(void) { 

    char buf[20]; 

    lv_obj_set_click(print_src.print_imgbtn_suspend, false);
    lv_obj_set_click(print_src.print_imgbtn_stop, false);
    lv_obj_set_click(print_src.print_imgbtn_pwr, false);
    lv_obj_set_click(print_src.print_imgbtn_speed, false);

    print_src.print_pwr_speed_src = lv_obj_create(mks_global.mks_src, NULL);

    lv_obj_set_size(print_src.print_pwr_speed_src, 350, 200);
    lv_obj_set_pos(print_src.print_pwr_speed_src, 80, 50);

    lv_style_copy(&print_src.printf_popup_style, &lv_style_scr);
    print_src.printf_popup_style.body.main_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.body.grad_color = LV_COLOR_MAKE(0xCE, 0xD6, 0xE5);
    print_src.printf_popup_style.text.color = LV_COLOR_BLACK;
    print_src.printf_popup_style.body.radius = 17;
    lv_obj_set_style(print_src.print_pwr_speed_src, &print_src.printf_popup_style);

    lv_style_copy(&print_src.print_mm_btn1_style, &lv_style_scr);
    print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn1_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    print_src.print_mm_btn1_style.text.color = LV_COLOR_WHITE;
    print_src.print_mm_btn1_style.body.radius = 10; 

    lv_style_copy(&print_src.print_mm_btn2_style, &lv_style_scr);
    print_src.print_mm_btn2_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
    print_src.print_mm_btn2_style.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    print_src.print_mm_btn2_style.text.color = LV_COLOR_WHITE;
    print_src.print_mm_btn2_style.body.radius = 10; 

    print_src.print_btn_1_mm = mks_lv_btn_set(print_src.print_pwr_speed_src, print_src.print_btn_1_mm, 100, 40, 60, 80, event_btn_speed_1mm);
    print_src.print_btn_10_mm = mks_lv_btn_set(print_src.print_pwr_speed_src, print_src.print_btn_10_mm, 100, 40, 180, 80, event_btn_speed_10mm);

    if(mks_speed_ctrl.speed_len == SPEED_1_PERSEN) {
        print_src.print_mm_btn1_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
        lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);
        
        print_src.print_mm_btn2_style.body.main_color = LV_COLOR_WHITE;
        print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_WHITE;
        lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn2_style);
        lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn2_style);

    }else if(mks_speed_ctrl.speed_len == SPEED_10_PERSEN){
        print_src.print_mm_btn1_style.body.main_color = LV_COLOR_WHITE;
        print_src.print_mm_btn1_style.body.grad_color = LV_COLOR_WHITE;
        lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_mm_btn1_style);
        lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_mm_btn1_style);

         print_src.print_mm_btn2_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
         print_src.print_mm_btn2_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, & print_src.print_mm_btn2_style);
        lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,& print_src.print_mm_btn2_style);
    }
    else {
        print_src.print_popup_btn_style.body.main_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        print_src.print_popup_btn_style.body.grad_color = LV_COLOR_MAKE(0x3F, 0x46, 0x66);
        lv_btn_set_style(print_src.print_btn_1_mm, LV_BTN_STYLE_REL, &print_src.print_popup_btn_style);
        lv_btn_set_style(print_src.print_btn_1_mm,LV_BTN_STYLE_PR,&print_src.print_popup_btn_style);
        
        print_src.print_popup_btn_style.body.main_color = LV_COLOR_WHITE;
        print_src.print_popup_btn_style.body.grad_color = LV_COLOR_WHITE;
        lv_btn_set_style(print_src.print_btn_10_mm, LV_BTN_STYLE_REL, &print_src.print_popup_btn_style);
        lv_btn_set_style(print_src.print_btn_10_mm,LV_BTN_STYLE_PR,&print_src.print_popup_btn_style);
    }

    sprintf(buf, "Speed:%d%%", sys_rt_f_override);
    // pwr_label_speed = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_pwr_speed_src, pwr_label_speed, 20, 50, buf, 100); 
    pwr_label_speed = label_for_screen(print_src.print_pwr_speed_src, pwr_label_speed, 0, -60, buf);

    if(mks_speed_ctrl.speed_len == SPEED_1_PERSEN) {
        print_src.print_label_1_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_1_mm, print_src.print_label_1_mm, 0, 0, "#ffffff 1%#", 50);
        print_src.print_label_10_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_10_mm, print_src.print_label_10_mm, 0, 0, "#000000 10% #", 50);

    }else if(mks_speed_ctrl.speed_len == SPEED_10_PERSEN) {
        print_src.print_label_1_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_1_mm, print_src.print_label_1_mm, 0, 0, "#000000 1%#", 50);
        print_src.print_label_10_mm = mks_lvgl_long_sroll_label_with_wight_set_center(print_src.print_btn_10_mm, print_src.print_label_10_mm, 0, 0, "#ffffff 10% #", 50);
    }

    print_src.print_sp_imgbtn_add = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, print_src.print_sp_imgbtn_add, &add, &add, LV_ALIGN_IN_LEFT_MID, print_pwr_popup_add_btn_x,print_pwr_popup_add_btn_y, event_speed_setting_add);
    print_src.print_sp_imgbtn_dec = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, print_src.print_sp_imgbtn_dec, &reduce, &reduce, LV_ALIGN_IN_LEFT_MID, print_pwr_popup_add_btn_x+80,print_pwr_popup_add_btn_y, event_speed_setting_dec);
    print_src.print_sp_btn_sure = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, 
                                                        print_src.print_sp_btn_sure, 
                                                        &confirm, 
                                                        &confirm, 
                                                        LV_ALIGN_IN_LEFT_MID, 
                                                        print_pwr_popup_add_btn_x+160,
                                                        print_pwr_popup_add_btn_y, event_speed_setting_confirm);
    
    print_src.print_sp_btn_return = lv_imgbtn_creat_mks(print_src.print_pwr_speed_src, 
                                                        print_src.print_sp_btn_return, 
                                                        &s_return, 
                                                        &s_return, 
                                                        LV_ALIGN_IN_LEFT_MID, 
                                                        print_pwr_popup_add_btn_x+240,
                                                        print_pwr_popup_add_btn_y, event_speed_setting_return);
}

char pl_info[128];
void mks_print_data_updata(void) {

    float mks_print_position[MAX_N_AXIS];

    system_convert_array_steps_to_mpos(mks_print_position, sys_position);

    print_data_updata.x_pos = mks_print_position[0];
    print_data_updata.y_pos = mks_print_position[1];
    print_data_updata.z_pos = mks_print_position[2];

    sprintf(print_data_updata.print_xpos_str, "%.2f", print_data_updata.x_pos);
    print_src.print_Label_x_pos = mks_lv_label_updata(print_src.print_Label_x_pos, print_data_updata.print_xpos_str);

    sprintf(print_data_updata.print_ypos_str, "%.2f", print_data_updata.y_pos);
    print_src.print_Label_y_pos = mks_lv_label_updata(print_src.print_Label_y_pos, print_data_updata.print_ypos_str); 

    sprintf(print_data_updata.print_zpos_str, "%.2f", print_data_updata.z_pos);
    print_src.print_Label_z_pos = mks_lv_label_updata(print_src.print_Label_z_pos, print_data_updata.print_zpos_str);

    sprintf(print_data_updata.print_pwr_str, "%d%%", sys_rt_s_override);
    print_src.print_Label_power = mks_lv_label_updata(print_src.print_Label_power, print_data_updata.print_pwr_str);

    sprintf(print_data_updata.print_speed_str, "%2d%%", sys_rt_f_override);
    print_src.print_Label_caveSpeed = mks_lv_label_updata(print_src.print_Label_caveSpeed, print_data_updata.print_speed_str);

    sprintf(print_data_updata.print_times_str, "%2d", mks_grbl.carve_times);
    print_src.print_Label_caveTimes = mks_lv_label_updata(print_src.print_Label_caveTimes, print_data_updata.print_times_str);

    if( (print_data_updata.x_pos != print_data_updata.last_x_pos) || 
        (print_data_updata.y_pos != print_data_updata.last_y_pos) ) {

        // 获取新的值
        print_data_updata.last_x_pos = print_data_updata.x_pos;
        print_data_updata.last_y_pos = print_data_updata.y_pos;
    }
    
    if (SD_ready_next == false) {
        if (mks_grbl.is_mks_ts35_flag == true) {
            mks_print_bar_updata();
        }
    }
}


uint8_t get_print_speed(void) {
    
    return sys_rt_f_override;
}

uint8_t get_print_power(void) {

    return sys_rt_s_override;
}


void mks_clear_print(void) {
    lv_obj_clean(mks_global.mks_src);
}

void mks_del_obj(lv_obj_t *obj) { 
    lv_obj_del(obj);
}