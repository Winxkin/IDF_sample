
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "GPIOconfig.h"

void input_envent_callback (int pin)
{
  

}

void app_main(void)
{

    input_io_create(GPIO_NUM_0,L_to_H);
    
    input_set_callback(input_envent_callback);

    
}
