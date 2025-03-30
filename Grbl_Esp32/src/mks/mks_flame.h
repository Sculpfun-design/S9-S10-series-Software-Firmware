#ifndef __mks_flame_h__
#define __mks_flame_h__

#include "MKS_draw_lvgl.h"

#define FLAME_DELAY_TIME      1000  // 1s

#define FLAME_USE_INT

typedef enum {

    FLAME_INIT,
    FLAME_RUN,
    FLAME_WAIT,
    FLAME_ALAEM,
    FLAME_END,
}flame_status_t;

typedef struct {
    flame_status_t flame_status;
    bool is_woring = false;

    uint32_t tick_start;
    uint32_t tick_end; 
}flame_t;




void mks_flame_run();

#endif
