#include "MKS_draw_language.h"

mc_lg_muilt_t mc_language;
LANGUAGE_PAGE_T language_page;

void mc_language_init(void) {

	if(mks_grbl.language == SimpleChinese) {
		/* 公共 */
		mc_language.back = 					BACK_CH;
		
		/* 主页 */
		mc_language.adjustment = 			ADJUSTMENT_CH;
		mc_language.control = 				CONTROL_CH;
		mc_language.sculpture = 			SCULPTURE_CH;
		mc_language.tool = 					TOOL_CH;
		mc_language.disconnect = 			WIFI_DISCONNECT_CH;
		mc_language.connect = 				WIFI_CONNECT_CH;
		mc_language.connect_btn = 			CONNENCT_BTN_CH;

		/* 移动控制 */
		mc_language.hhome = 				H_HOME_CH;
		mc_language.home = 					HOME_CH;
		mc_language.hard_homing =    		HARD_HOME_CH;
		mc_language.postive = 				POSTITION_CH;
		mc_language.low_speed = 			SPEED_LOW_CH;
		mc_language.mid_speed = 			SPEED_MID_CH;
		mc_language.high_speed = 			SPEED_HIGH_CH;
		mc_language.unlock = 				UNLOCK_CH;
		mc_language.home_succeed = 			HOMING_SU_CH;

		/* 文件界面 */
		mc_language.page_up = 				LAST_PAGE_CH;
		mc_language.page_dowm = 			NEXT_PAGE_CH;
		mc_language.no_sd_card = 			NO_SD_IN_CH;
		mc_language.carve = 				CAVING_CH;
		mc_language.frame = 				FRAME_CH;	

		/* 雕刻界面 */
		mc_language.run = 					CAVRE_RUN_CH;
		mc_language.stop = 					CAVRE_STOP_CH;
		mc_language.hold = 					CAVRE_HOLD_CH;	
		mc_language.power = 				CAVRE_POWER_CH;
		mc_language.speed = 				CAVRE_SPEED_CH;
		mc_language.stp_tis = 				CAVRE_STP_TIS_CH;
		mc_language.finsh_tis = 			CAVRE_FINSH_TIS_CH;
		
		/* 工具界面 */
		mc_language.wifi_name = 			WIFI_USERNAME_CH;
		mc_language.wifi_password = 		WIFI_PASSWORD_CH;
		mc_language.wifi_single_good = 		WIFI_S_GOOD_CH;
		mc_language.wifi_signle_min	= 		WIFI_S_MID_CH;
		mc_language.wifi_single_bad = 		WIFI_S_WEAK_CH;
		mc_language.scanf_ing = 			WIFI_SCANF_ING_CH;

		/* 扩展界面 */
		mc_language.re_scanf =				WIFI_RESCANF_CH;
		mc_language.scanf = 				WIFI_SCANF_CH;
		mc_language.roller = 				OTHER_ROLLER_CH;
		mc_language.safty = 				OTHER_SAFTY_CH;
		mc_language.language = 				OTHER_LANGUAGE_CH;
		mc_language.roller_sw = 			OTHER_ROLLER_LABEL_CH;
		mc_language.flame_sw = 				OTHER_FLAME_LABEL_CH;
		mc_language.gyro_sw = 				OTHER_GYRO_LABEL_CH;

		mc_language.tis_info =				INFO_CH;
		mc_language.tis_err = 				ERROR_CH;
		mc_language.tis_warning = 			WARNING_CH;
		mc_language.tis_yes = 				COM_YES_CH;
		mc_language.tis_cancle = 			COM_CANCLE_CH;
		mc_language.tis_pos_succeed = 		POSTITION_SUCCEDD_CH;
		mc_language.tis_unlock = 			UNLOCK_TIS_CH;
		mc_language.tis_unlock_succeed = 	UNLOCK_SUCCEED_CH;
		mc_language.tis_homing = 			HOMING_CH;
		mc_language.tis_homimg_fail = 		HOMING_FAI_CH;
		mc_language.tis_more_than_1_m = 	TIS_MORE_TAAN_1_M_CH;
		mc_language.tis_is_contiue = 		TIS_IS_CONTIUNE_CH;
		mc_language.tis_no_hard_limit = 	NO_HARD_LIMIT_CH;
		mc_language.tis_loading_file = 		TIS_LOADING_FILE_CH;
		mc_language.tis_frame_ing = 		TIS_FRAME_ING_CH;
		mc_language.tis_wifi_connecting	= 	TIS_WIFI_CONN_ING_CH;

	}
	else if(mks_grbl.language == English) {
		
		/* 公共 */
		mc_language.back = 					BACK_EN;
		
		/* 主页 */
		mc_language.adjustment = 			ADJUSTMENT_EN;
		mc_language.control = 				CONTROL_EN;
		mc_language.sculpture = 			SCULPTURE_EN;
		mc_language.tool = 					TOOL_EN;
		mc_language.disconnect = 			WIFI_DISCONNECT_EN;
		mc_language.connect = 				WIFI_CONNECT_EN;
		mc_language.connect_btn = 			CONNENCT_BTN_EN;
		
		/* 移动控制 */
		mc_language.hhome = 				H_HOME_EN;
		mc_language.home = 					HOME_EN;
		mc_language.hard_homing =    		HARD_HOME_EN;
		mc_language.postive = 				POSTITION_EN;
		mc_language.low_speed = 			SPEED_LOW_EN;
		mc_language.mid_speed = 			SPEED_MID_EN;
		mc_language.high_speed = 			SPEED_HIGH_EN;
		mc_language.unlock = 				UNLOCK_EN;
		mc_language.home_succeed = 			HOMING_SU_EN;

		/* 文件界面 */
		mc_language.page_up = 				LAST_PAGE_EN;
		mc_language.page_dowm = 			NEXT_PAGE_EN;
		mc_language.no_sd_card = 			NO_SD_IN_EN;
		mc_language.carve = 				CAVING_EN;
		mc_language.frame = 				FRAME_EN;	

		/* 雕刻界面 */
		mc_language.run = 					CAVRE_RUN_EN;
		mc_language.stop = 					CAVRE_STOP_EN;
		mc_language.hold = 					CAVRE_HOLD_EN;	
		mc_language.power = 				CAVRE_POWER_EN;
		mc_language.speed = 				CAVRE_SPEED_EN;
		mc_language.stp_tis = 				CAVRE_STP_TIS_EN;
		mc_language.finsh_tis = 			CAVRE_FINSH_TIS_EN;
		
		/* 工具界面 */
		mc_language.wifi_name = 			WIFI_USERNAME_EN;
		mc_language.wifi_password = 		WIFI_PASSWORD_EN;
		mc_language.wifi_single_good = 		WIFI_S_GOOD_EN;
		mc_language.wifi_signle_min	= 		WIFI_S_MID_EN;
		mc_language.wifi_single_bad = 		WIFI_S_WEAK_EN;
		mc_language.scanf_ing = 			WIFI_SCANF_ING_EN;
		/* 扩展界面 */
		mc_language.re_scanf =				WIFI_RESCANF_EN;
		mc_language.scanf = 				WIFI_SCANF_EN;
		mc_language.roller = 				OTHER_ROLLER_EN;
		mc_language.safty = 				OTHER_SAFTY_EN;
		mc_language.language = 				OTHER_LANGUAGE_EN;
		mc_language.roller_sw = 			OTHER_ROLLER_LABEL_EN;
		mc_language.flame_sw = 				OTHER_FLAME_LABEL_EN;
		mc_language.gyro_sw = 				OTHER_GYRO_LABEL_EN;

		mc_language.tis_info =				INFO_EN;
		mc_language.tis_err = 				ERROR_EN;
		mc_language.tis_warning = 			WARNING_EN;
		mc_language.tis_yes = 				COM_YES_EN;
		mc_language.tis_cancle = 			COM_CANCLE_EN;
		mc_language.tis_pos_succeed = 		POSTITION_SUCCEDD_EN;
		mc_language.tis_unlock = 			UNLOCK_TIS_EN;
		mc_language.tis_unlock_succeed = 	UNLOCK_SUCCEED_EN;
		mc_language.tis_homing = 			HOMING_EN;
		mc_language.tis_homimg_fail = 		HOMING_FAI_EN;
		mc_language.tis_more_than_1_m = 	TIS_MORE_TAAN_1_M_EN;
		mc_language.tis_is_contiue = 		TIS_IS_CONTIUNE_EN;
		mc_language.tis_no_hard_limit = 	NO_HARD_LIMIT_EN;
		mc_language.tis_loading_file = 		TIS_LOADING_FILE_EN;
		mc_language.tis_frame_ing = 		TIS_FRAME_ING_EN;
		mc_language.tis_wifi_connecting	= 	TIS_WIFI_CONN_ING_EN;
	}
	else if(mks_grbl.language == Deutsch) { 

		mc_language.back = 					BACK_DE;
		mc_language.adjustment = 			ADJUSTMENT_DE;
		mc_language.control = 				CONTROL_DE;
		mc_language.sculpture = 			SCULPTURE_DE;
		mc_language.tool = 					TOOL_DE;
		mc_language.disconnect = 			WIFI_DISCONNECT_DE;
		mc_language.connect = 				WIFI_CONNECT_DE;
	}
}

LV_IMG_DECLARE(back);	
LV_IMG_DECLARE(png_back_pre);

enum {
	ID_L_BACK,
	ID_L_CN,
	ID_L_EN,
	ID_L_DE,
};


static uint8_t get_event(lv_obj_t* obj) {

    if(obj == language_page.imgbtn_back)                		return ID_L_BACK;
    else if(obj == language_page.imgbtn_simple_cn)           	return ID_L_CN;
	else if(obj == language_page.imgbtn_en)						return ID_L_EN;
	else if(obj == language_page.imgbtn_de)						return ID_L_DE;
}

/*
 *	language num:
 *	0------cn
 *	1------en
 *	2------de
 *	3...
*/
static void set_language(uint8_t language) {

	switch(language) {

		case 0:
			mks_grbl.language = SimpleChinese;
		break;

		case 1:
			mks_grbl.language = English;
		break;

		case 2:
			mks_grbl.language = Deutsch;
		break;
	}
	mc_language_init();
}


static void enent_handler_back(void) {

	mks_clear_language();
	mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
	mks_draw_tool();
}

char str_language_ch[10] = "$40=0\n";
char str_language_en[10] = "$40=1\n";
char str_language_de[10] = "$40=2\n"; 
static void event_handler(lv_obj_t* obj, lv_event_t event) {

	uint8_t id = get_event(obj);

    if(event == LV_EVENT_PRESSED) { ts35_beep_on(); }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {

        ts35_beep_off();

        switch(id) {
			case ID_L_BACK: enent_handler_back(); break;
			case ID_L_CN: 
				set_language(0); 
				set_language_btn_style(0);
				MKS_GRBL_CMD_SEND(str_language_ch);
			break;
			case ID_L_EN: 
				set_language(1); 
				set_language_btn_style(1);
				MKS_GRBL_CMD_SEND(str_language_en);
			break;
			case ID_L_DE: 
				set_language(2); 
				set_language_btn_style(2);
				MKS_GRBL_CMD_SEND(str_language_de);
			break;
        }
    }
}

void set_language_btn_style(uint8_t language) {

	switch (language) {

		case 0: 
			lv_btn_set_style(language_page.imgbtn_simple_cn, LV_BTN_STYLE_REL, &mks_global.language_btn_pr_style);
			lv_btn_set_style(language_page.imgbtn_simple_cn,LV_BTN_STYLE_PR, &mks_global.language_btn_pr_style);

			lv_btn_set_style(language_page.imgbtn_en, LV_BTN_STYLE_REL, &mks_global.language_btn_rel_style);
			lv_btn_set_style(language_page.imgbtn_en,LV_BTN_STYLE_PR, &mks_global.language_btn_rel_style);

			// lv_btn_set_style(language_page.imgbtn_de, LV_BTN_STYLE_REL, &mks_global.language_btn_rel_style);
			// lv_btn_set_style(language_page.imgbtn_de,LV_BTN_STYLE_PR, &mks_global.language_btn_rel_style);
		break;

		case 1: 
			lv_btn_set_style(language_page.imgbtn_simple_cn, LV_BTN_STYLE_REL, &mks_global.language_btn_rel_style);
			lv_btn_set_style(language_page.imgbtn_simple_cn,LV_BTN_STYLE_PR, &mks_global.language_btn_rel_style);

			lv_btn_set_style(language_page.imgbtn_en, LV_BTN_STYLE_REL, &mks_global.language_btn_pr_style);
			lv_btn_set_style(language_page.imgbtn_en,LV_BTN_STYLE_PR, &mks_global.language_btn_pr_style);

			// lv_btn_set_style(language_page.imgbtn_de, LV_BTN_STYLE_REL, &mks_global.language_btn_rel_style);
			// lv_btn_set_style(language_page.imgbtn_de,LV_BTN_STYLE_PR, &mks_global.language_btn_rel_style);
		break;

		case 2: 
			lv_btn_set_style(language_page.imgbtn_simple_cn, LV_BTN_STYLE_REL, &mks_global.language_btn_rel_style);
			lv_btn_set_style(language_page.imgbtn_simple_cn,LV_BTN_STYLE_PR, &mks_global.language_btn_rel_style);

			lv_btn_set_style(language_page.imgbtn_en, LV_BTN_STYLE_REL, &mks_global.language_btn_rel_style);
			lv_btn_set_style(language_page.imgbtn_en,LV_BTN_STYLE_PR, &mks_global.language_btn_rel_style);

			// lv_btn_set_style(language_page.imgbtn_de, LV_BTN_STYLE_REL, &mks_global.language_btn_pr_style);
			// lv_btn_set_style(language_page.imgbtn_de,LV_BTN_STYLE_PR, &mks_global.language_btn_pr_style);
		break;
	}
}


void draw_language(void) {

	uint8_t language_num = 0;

	mks_global.mks_src_1 = lv_obj_create(mks_global.mks_src, NULL);
	lv_obj_set_size(mks_global.mks_src_1, about_src1_x_size, about_src1_y_size);
    lv_obj_set_pos(mks_global.mks_src_1, about_src1_x, about_src1_y);
    lv_obj_set_style(mks_global.mks_src_1, &mks_global.mks_src_1_style);

	// tool_page.imgbtn_back = lv_imgbtn_creat_mks(mks_global.mks_src_1, tool_page.imgbtn_back, &png_back_pre, &back, LV_ALIGN_IN_LEFT_MID, 10, -15, event_handler);

	language_page.imgbtn_back = lv_imgbtn_creat_mks(mks_global.mks_src_1, language_page.imgbtn_back, &png_back_pre, &back, LV_ALIGN_IN_LEFT_MID, 10, -15, event_handler);
	language_page.imgbtn_simple_cn = mks_lv_btn_set(mks_global.mks_src, language_page.imgbtn_simple_cn, 130, 50, 20, 110, event_handler);
	language_page.imgbtn_en = mks_lv_btn_set(mks_global.mks_src, language_page.imgbtn_en, 130, 50, 20, 110 + 60, event_handler);

	language_num = language_select->get();

	set_language_btn_style(language_num);
	
	label_for_imgbtn_name(mks_global.mks_src, language_page.label_back, language_page.imgbtn_back, 0, 0, mc_language.back);
	label_for_btn_name(language_page.imgbtn_simple_cn, language_page.label_simple_cn , 0, 0, "中文");
	label_for_btn_name(language_page.imgbtn_en, language_page.label_en, 0, 0, "English");
	mks_ui_page.mks_ui_page = MKS_UI_LANGUAGE;
}

void mks_clear_language(void) {
    lv_obj_clean(mks_global.mks_src);
}








