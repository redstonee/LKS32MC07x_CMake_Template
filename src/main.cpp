#include "lks32mc07x_lib.h"
#include "system_lks32mc07x.h"
#include "Serial.hpp"
#include <string>

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

    HWSerial Serial(UART0, 115200);
    std::string fuckStr = "Fuck The World!";

    while (1)
    {
        GPIO_SetBits(GPIO0, GPIO_Pin_0);
        Serial.println(fuckStr);
        GPIO_ResetBits(GPIO0, GPIO_Pin_0);
        delay1ms(1000);
    }
}
