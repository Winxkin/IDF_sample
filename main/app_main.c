
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "GPIOconfig.h"
#include "delay.h"


#define BIT_PRESS_short (1 << 0)
#define BIT_PRESS_normal (1 << 1)
#define BIT_PRESS_long (1 << 2)

static EventGroupHandle_t xCreatedEventGroup;

void vTask1(void * pvParameters )
{

    while(1)
    {
        
         EventBits_t uxBits;
         const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;

                    /* Wait a maximum of 100ms for either bit 0 or bit 4 to be set within
                    the event group.  Clear the bits before exiting. */
        uxBits = xEventGroupWaitBits(
                                xCreatedEventGroup,   /* The event group being tested. */
                                BIT_PRESS_short | BIT_PRESS_normal | BIT_PRESS_long, /* The bits within the event group to wait for. */
                                pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
                                pdFALSE,       /* Don't wait for both bits, either bit will do. */
                                xTicksToWait );/* Wait a maximum of 100ms for either bit to be set. */

        if(uxBits & BIT_PRESS_short)
        {
             printf("press short \n");
        }
        else if (uxBits & BIT_PRESS_normal)
        {
            printf("press normal \n");
        }
        else if (uxBits & BIT_PRESS_long)
        {
            printf("press long \n");
        }
    
    }
}


void input_io_callback (int pin, uint64_t tick)
{
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    if(pin == GPIO_NUM_0)
    {   
        int press_ms = tick * portTICK_PERIOD_MS;
        if(press_ms < 1000)
        {
            //press_short;
            xEventGroupSetBitsFromISR(
                              xCreatedEventGroup,   /* The event group being updated. */
                              BIT_PRESS_short, /* The bits being set. */
                              &xHigherPriorityTaskWoken );


        }
        else if (press_ms < 3000 && press_ms >= 1000)
        {
            //press normal
            xEventGroupSetBitsFromISR(
                              xCreatedEventGroup,   /* The event group being updated. */
                              BIT_PRESS_normal, /* The bits being set. */
                              &xHigherPriorityTaskWoken );


        }
        else 
        {
            //press long
            


        }
    }
 
}

void timeout_callback (int pin)
{
    if(pin == GPIO_NUM_0)
    {
        printf("Timeout ! \n");
      // output_io_toggle(GPIO_NUM_2);
    }
}


void app_main(void)
{
    xCreatedEventGroup = xEventGroupCreate();
    creatxtimer();
    // xTaskCreate(vTask1, "vTask1", 1024, NULL, 4, NULL);
    output_io_creat(GPIO_NUM_2);
    input_io_create(GPIO_NUM_0,ANY_EDLE);
    input_set_callback(input_io_callback);   
    timeout_set_callback(timeout_callback);
    xTaskCreate(vTask1, "vTask1", 2048, NULL, 4, NULL);
    
}
