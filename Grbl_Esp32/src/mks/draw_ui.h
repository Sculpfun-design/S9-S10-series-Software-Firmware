#ifndef __draw_ui_h
#define __draw_ui_h

#include "MKS_draw_lvgl.h"


LV_FONT_DECLARE(dlc32Font);	


// 弹窗事件
// typedef enum {
enum{

    MS_EVENT_HARD_LIMIT = 0,
    MS_EVENT_SOFT_LIMIT,
    MS_EVENT_X_POSTION,
    MS_EVENT_Y_POSTION,
    MS_EVENT_Z_POSTION, // for CNC
    MS_EVENT_XY_POSTION, 
    MS_EVENT_XYZ_POSTION,   // for CNC

    MS_EVENT_SOFT_HOME, 
    MS_EVENT_HARD_HOME,
    MS_EVENT_UNLOCK,

    MS_EVENT_JOY,
    MS_EVENT_ALARM,
    MS_EVENT_SAFEDOOR,
    MS_EVENT_PROBE,

    MS_EVENT_SD_FAIL,
    MS_EVENT_SD_UNCONNECT,

    MS_EVENT_FRAME,

    MS_EVENT_PRINT_COMFRM,
    MS_EVENT_PRINT_STOP,
    MS_EVENT_PRINT_FINSH,
    
    MS_EVENT_WARNING_CPU_TEMP,
};
// }message_event_t;


void mks_global_style_init(void);


#endif
