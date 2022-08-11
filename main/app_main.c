
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "GPIOconfig.h"
#include "delay.h"

void vTask1(void * pvParameters )
{

    while(1)
    {
        output_io_toggle(GPIO_NUM_2);
    }
    
}

void vTask2(void * pvParameters )
{

    while(1)
    {
        output_io_toggle(GPIO_NUM_4);
    }
    
}



void app_main(void)
{
    output_io_creat(GPIO_NUM_2);
    output_io_creat(GPIO_NUM_4);
    // xTaskCreate(vTask1, "vTask1", 1024, NULL, 4, NULL);
    // xTaskCreate(vTask2, "vTask2", 1024, NULL, 5, NULL);

    while(1)
    {   
       // delay_ms(1);
        gpio_set_level(2,1);
        delay_s(1);
        gpio_set_level(2,0);
        delay_s(1);
    }
   
    
}
