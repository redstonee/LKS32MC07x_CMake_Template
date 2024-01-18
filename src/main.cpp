#include "lks32mc07x_lib.h"
#include "system_lks32mc07x.h"

int main(void)
{

    GPIO_InitTypeDef gis;
    GPIO_StructInit(&gis);
    gis.GPIO_Mode = GPIO_Mode_OUT;
    gis.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_0;
    GPIO_Init(GPIO0, &gis);

    gis.GPIO_Pin = GPIO_Pin_6;
    gis.GPIO_Mode = GPIO_Mode_IN;
    gis.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIO0, &gis);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF4_UART);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF4_UART);

    UART_InitTypeDef uis;
    UART_StructInit(&uis);
    uis.BaudRate = 115200;
    UART_Init(UART0, &uis);

    while (1)
    {
        if (UART_GetIRQFlag(UART0, UART_IF_SendOver))
            UART_ClearIRQFlag(UART0, UART_IF_SendOver);
        UART_SendData(UART0, 'a');
        while (!UART_GetIRQFlag(UART0, UART_IF_SendOver))
            ;
        delay1ms(1000);
    }
}
