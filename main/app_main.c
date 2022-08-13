
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "GPIOconfig.h"
#include "delay.h"
#include "uart.h"

void loopTask(void *pvParameters)
{
    while(1)
    {
        sentdata(UART_NUM_0,"write serial \n");
        delay_s(2);
    }
}



void cleardata (uint8_t *data, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        *data = 0;
        data++;
    }
}

void checkdata(uint8_t *data,int length)
{
    if(data[0] == 0x44 && data[1] == 0x48)
    {
        uart_write_bytes(UART_NUM_0,data,length);
    }
}


void RxTask (void *pvParameters)
{
    uint8_t data[128];
    int length = 0;
    while(1)
    {
        ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_0, (size_t*)&length));
        length = uart_read_bytes(UART_NUM_0, data, length, 100);
        checkdata(data,length);
        cleardata(data,length);
    }
}

void recieveddata()
{
    sentdata(UART_NUM_0,"rx serial \n");
}

void app_main(void)
{
    
    start_uart_init(UART_NUM_0);
    setcallback_uart(recieveddata);
//    xTaskCreate(loopTask,"lopptask",1024, NULL, 4, NULL);
    xTaskCreate(RxTask,"RxTask",1024, NULL, 4, NULL);
}
