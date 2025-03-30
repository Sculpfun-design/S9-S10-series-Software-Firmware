#ifndef __mks_draw_other_h
#define __mks_draw_other_h

#include "MKS_draw_lvgl.h"

typedef struct {

    lv_obj_t *imgbtn_back;
    lv_obj_t *imgbtn_roller_sw;

    lv_obj_t *imgbtn_flame_sw;
    lv_obj_t *imgbtn_gyro_sw;

    lv_obj_t *imgbtn_safty_sw;

    lv_obj_t *label_back;
    lv_obj_t *label_roller_sw;
    lv_obj_t *label_flame_sw;
    lv_obj_t *label_gyro_sw;

    lv_obj_t *label_safty_sw;


}OTHER_PAGE_T;

void mks_clear_other(void);
void draw_other(void);

#endif
