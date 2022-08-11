
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "GPIOconfig.h"




void input_envent_callback (int pin)
{
   if(pin == GPIO_NUM_0)
   {
        static int x =0 ;
        gpio_set_level(GPIO_NUM_13,x);
        x = 1-x;       

   }

}

void app_main(void)
{
    output_io_creat(GPIO_NUM_13);
    input_io_create(GPIO_NUM_0 , H_to_L);
 
    input_set_callback(input_envent_callback);
    while(1)
    {
        output_io_toggle(GPIO_NUM_13);

    }

    
}
