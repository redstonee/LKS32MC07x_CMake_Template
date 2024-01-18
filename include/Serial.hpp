#pragma once

#include "lks32mc07x_lib.h"
#include <string>

class HWSerial
{
private:
    UART_TypeDef *_uart;
    UART_InitTypeDef is;

public:
    HWSerial(UART_TypeDef *uart, uint32_t baudrate)
    {
        _uart = uart;
        UART_StructInit(&is);
        is.BaudRate = baudrate;
        UART_Init(_uart, &is);
    }

    void println(char *str = nullptr)
    {
        while (*str)
        {
            UART_SendData(_uart, *str++);

            while (!UART_GetIRQFlag(_uart, UART_IF_SendOver))
                ;
        }
        UART_SendData(_uart, '\r');
        while (!UART_GetIRQFlag(_uart, UART_IF_SendOver))
            ;
        UART_SendData(_uart, '\n');
        while (!UART_GetIRQFlag(_uart, UART_IF_SendOver))
            ;
    }
    void println(std::string str)
    {
        for (auto c : str)
        {
            UART_SendData(_uart, c);
            while (!UART_GetIRQFlag(_uart, UART_IF_SendOver))
                ;
        }
        println();
    }
};