#include "MKS_draw_move.h"

MKS_MOVE_PAGE move_page;
MKS_MOVE_CTRL_T ui_move_ctrl;

LV_FONT_DECLARE(dlc32Font);	

LV_IMG_DECLARE(back);
LV_IMG_DECLARE(Home);
LV_IMG_DECLARE(Positionting);
LV_IMG_DECLARE(Unlock);
LV_IMG_DECLARE(X_N);			
LV_IMG_DECLARE(X_P);			
LV_IMG_DECLARE(Y_N);			
LV_IMG_DECLARE(Y_P);			
LV_IMG_DECLARE(Hhome);		

LV_IMG_DECLARE(png_home_pre);
LV_IMG_DECLARE(png_hhome_pre);		
LV_IMG_DECLARE(png_unlock_pre);		
LV_IMG_DECLARE(png_pos_pre);	
LV_IMG_DECLARE(png_m_up);
LV_IMG_DECLARE(png_m_right);		
LV_IMG_DECLARE(png_m_left);		
LV_IMG_DECLARE(png_m_down);
LV_IMG_DECLARE(png_back_pre);	

enum {
	ID_M_UP,
	ID_M_DOWN,
	ID_M_LEFT,
	ID_M_RIGHT,
	ID_M_STEP,
	ID_M_SPEED,
	ID_M_UNLOCK,
	ID_M_HOME,
	ID_M_POS,
	ID_M_HHOME,
	ID_M_RETURN,
};

static uint8_t get_event(lv_obj_t* obj) {

    if      (obj == move_page.y_n)  		return ID_M_UP;
    else if (obj == move_page.y_p)     		return ID_M_DOWN;
    else if (obj == move_page.x_n)			return ID_M_LEFT;
    else if (obj == move_page.x_p) 			return ID_M_RIGHT;
    else if (obj == move_page.m_unlock)     return ID_M_UNLOCK;
	else if (obj == move_page.postivs)     	return ID_M_POS;
	else if (obj == move_page.home)     	return ID_M_HOME;
	else if (obj == move_page.hhome)     	return ID_M_HHOME;
	else if (obj == move_page.Back)     	return ID_M_RETURN;
	else if (obj == move_page.btn_len)     	return ID_M_STEP;
	else if (obj == move_page.btn_speed)	return ID_M_SPEED;
}

static void event_henadle_pupup_com(lv_obj_t* obj, lv_event_t event) { 

	if(event == LV_EVENT_PRESSED) { 
        ts35_beep_on(); 
    }

    if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST))  {

        ts35_beep_off(); 
		draw_move_click(true);
		common_popup_com_del();
	}
}

void set_move(char axis, float step, uint32_t speed) {
	if(step == 0) return;
	char str[30];
	sprintf(str, "$J=G91%c%.2fF%d\n", axis, step, speed);
	MKS_GRBL_CMD_SEND(str);
}

void move_ctrl(char axis, uint8_t dir) {
	float step;
	uint32_t speed;

	if(mks_grbl.move_dis == M_0_1_MM) 			step = 0.1;
	else if(mks_grbl.move_dis == M_1_MM)		step = 1;
	else if(mks_grbl.move_dis == M_10_MM)		step = 10;

	if(mks_grbl.move_speed == LOW_SPEED) 		speed = 500;
	else if(mks_grbl.move_speed == MID_SPEED)	speed = 1000;
	else if(mks_grbl.move_speed == HIGHT_SPEED)	speed = 2000;

	if(dir == 0) set_move(axis, -step, speed);
	else set_move(axis, step, speed);
}

void mc_unlock(void) {
	MKS_GRBL_CMD_SEND("$X\n");
	draw_move_click(false);
	mks_draw_common_popup_info_com((char *)mc_language.tis_info, (char *)mc_language.tis_unlock_succeed, "", event_henadle_pupup_com);
}

void set_step_len(void) {
	if(mks_grbl.move_dis == M_0_1_MM) {
		mks_grbl.move_dis = M_1_MM;
		mks_lv_label_updata(move_page.label_len, "1mm");
	}else if(mks_grbl.move_dis == M_1_MM) {
		mks_grbl.move_dis = M_10_MM;
		mks_lv_label_updata(move_page.label_len, "10mm");
	}else if(mks_grbl.move_dis == M_10_MM) {
		mks_grbl.move_dis = M_0_1_MM;
		mks_lv_label_updata(move_page.label_len, "0.1mm");
	}
}

void set_speed(void) {
	if(mks_grbl.move_speed == LOW_SPEED) {
		mks_grbl.move_speed = MID_SPEED;
		mks_lv_label_updata(move_page.label_speed, mc_language.mid_speed);
	}else if(mks_grbl.move_speed == MID_SPEED) {
		mks_grbl.move_speed = HIGHT_SPEED;
		mks_lv_label_updata(move_page.label_speed, mc_language.high_speed);
	}else if(mks_grbl.move_speed == HIGHT_SPEED) {
		mks_grbl.move_speed = LOW_SPEED;
		mks_lv_label_updata(move_page.label_speed, mc_language.low_speed);
	}
}

void set_home(void) {
		MKS_GRBL_CMD_SEND("M5\n");
		mks_grbl.power_persen = P_0_PERSEN;
       	MKS_GRBL_CMD_SEND("$J=G90X0Y0F2000\n");
		draw_move_click(false);
		mks_draw_common_pupup_info((char *)mc_language.tis_info, (char *)mc_language.tis_homing, " ");
		ui_move_ctrl.soft_homing_status = HOMING_START;
}

static void set_hhome(void) {

	MKS_GRBL_CMD_SEND("M5\n");

	mks_grbl.power_persen = P_0_PERSEN;

	draw_move_click(false);

	if(hard_limits->get()) {

		MKS_GRBL_CMD_SEND("$H\n");

		ui_move_ctrl.hard_homing_status = HOMING_START;
		
		mks_draw_common_pupup_info((char *)mc_language.tis_info, (char *)mc_language.hard_homing , " ");
	}
	else {
		mks_draw_common_popup_info_com((char *)mc_language.tis_warning, (char *)mc_language.tis_no_hard_limit, " ", event_henadle_pupup_com);
	}
}

void set_pos(void) {
	draw_move_click(false);
	if(sys.state == State::Idle) {
		MKS_GRBL_CMD_SEND("G92X0Y0Z0\n");
		mks_draw_common_popup_info_com((char *)mc_language.tis_info, (char *)mc_language.tis_pos_succeed, " ", event_henadle_pupup_com);
	}else {
		mks_draw_common_popup_info_com((char *)mc_language.tis_warning, (char *)mc_language.tis_wait_mc_stop, " ", event_henadle_pupup_com);
	}
}

void set_move_back(void) {
	mks_lv_clean_ui();
	mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
	mks_ui_page.wait_count = DEFAULT_UI_COUNT;
	mks_draw_ready();
}

static void event_handler(lv_obj_t* obj, lv_event_t event) {

	uint8_t id=get_event(obj);

	if(event == LV_EVENT_PRESSED) { ts35_beep_on(); }

	if((event == LV_EVENT_RELEASED) || (event == LV_EVENT_PRESS_LOST)) {

		ts35_beep_off();

		switch(id) {
			case ID_M_UP	:	move_ctrl('Y', 1);		break;
			case ID_M_DOWN	:	move_ctrl('Y', 0);		break;
			case ID_M_LEFT	:	move_ctrl('X', 1);		break;
			case ID_M_RIGHT	:	move_ctrl('X', 0);		break;
			case ID_M_STEP	:	set_step_len();			break;
			case ID_M_SPEED	:	set_speed();			break;
			case ID_M_UNLOCK:	mc_unlock();			break;
			case ID_M_HOME	:	set_home();				break;
			case ID_M_POS	:	set_pos();				break;
			case ID_M_HHOME	:	set_hhome();			break;
			case ID_M_RETURN:	set_move_back();		break;
		}
	}
}

void mks_draw_move(void) {
 
	mks_global.mks_src_1 = lv_obj_create(mks_global.mks_src, NULL);
	lv_obj_set_size(mks_global.mks_src_1, 460, 90);
    lv_obj_set_pos(mks_global.mks_src_1, 10, 10);

	mks_global.mks_src_2 = lv_obj_create(mks_global.mks_src, NULL);
	lv_obj_set_size(mks_global.mks_src_2, 270, 200);
    lv_obj_set_pos(mks_global.mks_src_2, 10, 110);

	mks_global.mks_src_3 = lv_obj_create(mks_global.mks_src, NULL);
	lv_obj_set_size(mks_global.mks_src_3, 180, 200);
    lv_obj_set_pos(mks_global.mks_src_3, 290, 110);

	/* 背景层样式 */
	lv_obj_set_style(mks_global.mks_src_1, &mks_global.mks_src_1_style);
	lv_obj_set_style(mks_global.mks_src_2, &mks_global.mks_src_2_style);
	lv_obj_set_style(mks_global.mks_src_3, &mks_global.mks_src_3_style);

	move_page.Back = lv_imgbtn_creat_mks(mks_global.mks_src_1, move_page.Back, &png_back_pre, &back, LV_ALIGN_IN_LEFT_MID, 10, -15 , event_handler);
    move_page.m_unlock = lv_imgbtn_creat_mks(mks_global.mks_src_1, move_page.m_unlock, &png_unlock_pre, &Unlock, LV_ALIGN_IN_LEFT_MID, 100, -15, event_handler);
	move_page.home = lv_imgbtn_creat_mks(mks_global.mks_src_1, move_page.home, &png_home_pre, &Home, LV_ALIGN_IN_LEFT_MID, 190, -15, event_handler);
	move_page.postivs = lv_imgbtn_creat_mks(mks_global.mks_src_1, move_page.postivs, &png_pos_pre, &Positionting, LV_ALIGN_IN_LEFT_MID, 280, -15, event_handler);
	move_page.hhome = lv_imgbtn_creat_mks(mks_global.mks_src_1, move_page.hhome, &png_hhome_pre, &Hhome, LV_ALIGN_IN_LEFT_MID, 370, -15, event_handler);

	move_page.x_n = lv_imgbtn_creat_mks(mks_global.mks_src_2, move_page.x_n, &png_m_right, &X_N, LV_ALIGN_CENTER, 90, 0, event_handler);
    move_page.x_p = lv_imgbtn_creat_mks(mks_global.mks_src_2, move_page.x_p, &png_m_left, &X_P, LV_ALIGN_CENTER, -90, 0, event_handler);
    move_page.y_n = lv_imgbtn_creat_mks(mks_global.mks_src_2, move_page.y_n, &png_m_up, &Y_N, LV_ALIGN_CENTER, 0, -50, event_handler);
    move_page.y_p = lv_imgbtn_creat_mks(mks_global.mks_src_2, move_page.y_p, &png_m_down, &Y_P, LV_ALIGN_CENTER, 0, 50, event_handler);

	/* 按键样式 */
	lv_style_copy(&move_page.btn_color, &lv_style_scr);
    move_page.btn_color.body.main_color = LV_COLOR_MAKE(0x3f, 0x47, 0x66);
    move_page.btn_color.body.grad_color = LV_COLOR_MAKE(0x3f, 0x47, 0x66);
    move_page.btn_color.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    move_page.btn_color.text.color = LV_COLOR_MAKE(0x5C, 0xE6, 0x93);
	move_page.btn_color.body.radius = 10;
	move_page.btn_color.text.font = &dlc32Font;

	lv_style_copy(&move_page.btn_color_press, &lv_style_scr);
	move_page.btn_color_press.body.main_color = LV_COLOR_MAKE(0x5C, 0xE6, 0x93);
    move_page.btn_color_press.body.grad_color = LV_COLOR_MAKE(0x5C, 0xE6, 0x93);
    move_page.btn_color_press.body.opa = LV_OPA_COVER;//设置背景色完全不透明
    move_page.btn_color_press.text.color = LV_COLOR_BLACK;
	move_page.btn_color_press.body.radius = 10;
	move_page.btn_color_press.text.font = &dlc32Font;

	move_page.btn_len = mks_lv_btn_set_for_screen(mks_global.mks_src_3, move_page.btn_len, 120, 50, 0, -40, event_handler);
	move_page.btn_speed = mks_lv_btn_set_for_screen(mks_global.mks_src_3, move_page.btn_speed, 120, 50, 0, 40, event_handler);

	lv_btn_set_style(move_page.btn_len, LV_BTN_STYLE_REL, &move_page.btn_color);
	lv_btn_set_style(move_page.btn_len, LV_BTN_STYLE_PR, &move_page.btn_color_press);

	lv_btn_set_style(move_page.btn_speed, LV_BTN_STYLE_REL, &move_page.btn_color);
	lv_btn_set_style(move_page.btn_speed,LV_BTN_STYLE_PR,&move_page.btn_color_press);
	
	label_for_imgbtn_name(mks_global.mks_src_1, move_page.Label_back, move_page.Back, 0, 0, mc_language.back);
	label_for_imgbtn_name(mks_global.mks_src_1, move_page.Label_back, move_page.m_unlock, 0, 0, mc_language.unlock);
	label_for_imgbtn_name(mks_global.mks_src_1, move_page.Label_back, move_page.home, 0, 0, mc_language.home);
	label_for_imgbtn_name(mks_global.mks_src_1, move_page.Label_back, move_page.postivs, 0, 0, mc_language.postive);
	label_for_imgbtn_name(mks_global.mks_src_1, move_page.Label_back, move_page.hhome, 0, 0, mc_language.hhome);

	if(mks_grbl.move_dis == M_0_1_MM) {
		move_page.label_len = mks_lvgl_long_sroll_label_with_wight_set_center(move_page.btn_len, move_page.label_len, 0, 0, "0.1mm", 50);
	}else if(mks_grbl.move_dis == M_1_MM) {
		move_page.label_len = mks_lvgl_long_sroll_label_with_wight_set_center(move_page.btn_len, move_page.label_len, 0, 0, "1mm", 50);
	}else if(mks_grbl.move_dis == M_10_MM) {
		move_page.label_len = mks_lvgl_long_sroll_label_with_wight_set_center(move_page.btn_len, move_page.label_len, 0, 0, "10mm", 50);
	}
	
	if(mks_grbl.move_speed == LOW_SPEED) {
		move_page.label_speed = mks_lvgl_long_sroll_label_with_wight_set_center(move_page.btn_speed, move_page.label_speed, 0, 0, mc_language.low_speed, 100); //l:500, m:1000, h:2000
	}else if(mks_grbl.move_speed == MID_SPEED) {
		move_page.label_speed = mks_lvgl_long_sroll_label_with_wight_set_center(move_page.btn_speed, move_page.label_speed, 0, 0, mc_language.mid_speed, 100);
	}else if(mks_grbl.move_speed == HIGHT_SPEED) {
		move_page.label_speed = mks_lvgl_long_sroll_label_with_wight_set_center(move_page.btn_speed, move_page.label_speed, 0, 0, mc_language.high_speed, 100);
	}	

	mks_ui_page.mks_ui_page = MKS_UI_Control;
    mks_ui_page.wait_count = DEFAULT_UI_COUNT;
}

void draw_move_click(bool status) {
	lv_obj_set_click(move_page.Back, status);
	lv_obj_set_click(move_page.m_unlock, status);
	lv_obj_set_click(move_page.home, status);
	lv_obj_set_click(move_page.postivs, status);
	lv_obj_set_click(move_page.hhome, status);
	lv_obj_set_click(move_page.x_n, status);
	lv_obj_set_click(move_page.x_p, status);
	lv_obj_set_click(move_page.y_n, status);
	lv_obj_set_click(move_page.y_p, status);
	lv_obj_set_click(move_page.btn_len, status);
	lv_obj_set_click(move_page.btn_speed, status);
}

void hard_home_check(void) {
	switch(ui_move_ctrl.hard_homing_status) {

		case HOMING_NONE:
			
		break;

		case HOMING_START:
			if(sys.state == State::Homing) 		ui_move_ctrl.hard_homing_status = HOMING_RUNNING;
			else if(sys.state == State::Idle)	ui_move_ctrl.hard_homing_status = HOMING_SUCCEED;
			else if(sys.state == State::Alarm)	ui_move_ctrl.hard_homing_status = HOMING_FAIL;
			else								ui_move_ctrl.hard_homing_status = HOMING_FAIL;
		break;

		case HOMING_RUNNING:
			if(sys.state == State::Idle) 		ui_move_ctrl.hard_homing_status = HOMING_SUCCEED;
			else if(sys.state == State::Alarm)	ui_move_ctrl.hard_homing_status = HOMING_FAIL;
			else if(sys.state == State::Homing)	ui_move_ctrl.hard_homing_status = HOMING_RUNNING;
			else 								ui_move_ctrl.hard_homing_status = HOMING_FAIL;
		break;

		case HOMING_SUCCEED:
			ui_move_ctrl.hard_homing_status = HOMING_NONE;
			common_pupup_info_del();
			mks_draw_common_popup_info_com((char *)mc_language.tis_info, (char *)mc_language.home_succeed, " ", event_henadle_pupup_com);
		break;

		case HOMING_FAIL:
			ui_move_ctrl.hard_homing_status = HOMING_NONE;
			common_pupup_info_del();
			mks_draw_common_popup_info_com((char *)mc_language.tis_info, (char *)mc_language.tis_homimg_fail, (char *)mc_language.tis_unlock, event_henadle_pupup_com);
		break;
	}
}

void soft_home_check(void) { 

	switch(ui_move_ctrl.soft_homing_status) {

		case HOMING_NONE:

		break;

		case HOMING_START:
			if(sys.state == State::Jog) 		ui_move_ctrl.soft_homing_status = HOMING_RUNNING;
			else if(sys.state == State::Idle)	ui_move_ctrl.soft_homing_status = HOMING_SUCCEED;
			else if(sys.state == State::Alarm)	ui_move_ctrl.soft_homing_status = HOMING_FAIL;
			else 								ui_move_ctrl.soft_homing_status = HOMING_FAIL;
		break;

		case HOMING_RUNNING:
			if(sys.state == State::Idle)		ui_move_ctrl.soft_homing_status = HOMING_SUCCEED;
			else if(sys.state == State::Alarm)	ui_move_ctrl.soft_homing_status = HOMING_FAIL;
			else if(sys.state == State::Jog)	ui_move_ctrl.soft_homing_status = HOMING_RUNNING;
			else 								ui_move_ctrl.soft_homing_status = HOMING_FAIL;
		break;

		case HOMING_SUCCEED:
			ui_move_ctrl.soft_homing_status = HOMING_NONE;
			common_pupup_info_del();
			mks_draw_common_popup_info_com((char *)mc_language.tis_info, (char *)mc_language.home_succeed, " ", event_henadle_pupup_com);
		break;

		case HOMING_FAIL:
			ui_move_ctrl.soft_homing_status = HOMING_NONE;
			common_pupup_info_del();
			mks_draw_common_popup_info_com((char *)mc_language.tis_info, (char *)mc_language.tis_homimg_fail, " ", event_henadle_pupup_com);
		break;
	}
}

bool mks_get_motor_status(void) { 
	return stepper_idle;
}

void mks_clear_move(void) {
	lv_obj_clean(mks_src);
}




