#ifndef LED_TASK_H
#define LED_TASK_H

#include "../draw_ui.h"

extern TaskHandle_t led_task_tcb;

void led_task_init(void);

#endif
