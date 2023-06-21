#include "mks_flame.h"

flame_t flame_ctrl;

void mks_flame_init() {
    flame_ctrl.flame_status = FLAME_INIT;
#if defined(FLAME_PIN)
    pinMode(FLAME_PIN, INPUT);
#endif
}



static void event_probe_yes(lv_obj_t* obj, lv_event_t event) {
    if(event == LV_EVENT_RELEASED) {
        if(flame_ctrl.flame_status == FLAME_END) {
            
        }else {
            if(mks_ui_page.mks_ui_page != MKS_UI_Ready) {
                mks_ui_page.mks_ui_page = MKS_UI_PAGE_LOADING;
                mks_clean_current_page(mks_global.mks_src);
                mks_draw_ready();
            }else {
                common_popup_com_del();
            }
        }
    }
}

void mks_flame_run() {
#ifdef FLAME_PIN

    // if(!flame_status->get()) return;  

    switch(flame_ctrl.flame_status) {

        case FLAME_INIT:
            flame_ctrl.is_woring = false;
            flame_ctrl.tick_start = 0;
            flame_ctrl.tick_end = 0;
            flame_ctrl.flame_status = FLAME_RUN;
        break;

        case FLAME_RUN: 
            if(digitalRead(FLAME_PIN) == LOW) {
                flame_ctrl.flame_status = FLAME_WAIT;
            }
        break;

        case FLAME_WAIT: 
            flame_ctrl.tick_end = millis();
            if((flame_ctrl.tick_end - flame_ctrl.tick_start) > FLAME_DELAY_TIME) {
                if(digitalRead(FLAME_PIN) == LOW) {
                    flame_ctrl.is_woring = true;
                    
                    if((sys.state == State::Cycle) || (sys.state == State::Hold))  {  // 正在打印中
                        uint16_t buf_cmd[]={0x18};
                        closeFile();
                        MKS_GRBL_CMD_SEND(buf_cmd);
                    }
                    
                    mks_draw_common_popup_info_com( "Error", 
                                                    "Machine accident", 
                                                    "A flame alarm appears",
                                                    event_probe_yes);

                    flame_ctrl.flame_status = FLAME_ALAEM;
                }else{
                    flame_ctrl.is_woring = false;
                    flame_ctrl.flame_status = FLAME_INIT;
                }
            }
        break;

        case FLAME_ALAEM:
            if(digitalRead(FLAME_PIN) != LOW) {
                flame_ctrl.flame_status = FLAME_END;
            }
        break;

        case FLAME_END:
            flame_ctrl.is_woring = false;
            flame_ctrl.flame_status = FLAME_INIT;
        break;
    }
#endif
}



