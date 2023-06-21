#include "led_task.h"

#define LED_TASK_STACK                  4096*2
#define LED_TASK_PRO                    3          
#define LED_TASK_CORE                   1


TaskHandle_t led_task_tcb = NULL;

void led_task(void *parg) { 

    while(1) {
        bsp_led_run();
        delay(100);
    }
}

void led_task_init(void) {
    #ifdef LED_PIN 
        xTaskCreatePinnedToCore(led_task,             // task
                                "LED task",           // name for task
                                LED_TASK_STACK,       // size of task stack
                                NULL,                   // parameters
                                LED_TASK_PRO,         // priority
                                &led_task_tcb,
                                LED_TASK_CORE         // must run the task on same core
                                                        // core
        );
    #endif
}
