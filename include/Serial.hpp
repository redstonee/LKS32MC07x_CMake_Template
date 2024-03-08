#pragma once

#include "lks32mc07x_lib.h"

enum Radix
{
    BIN = 2,
    OCT = 8,
    DEC = 10,
    HEX = 16
};

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
        is.IRQEna = UART_IRQEna_SendOver | UART_IRQEna_RcvOver;
        UART_Init(_uart, &is);
    }

    void print(long num, Radix radix = DEC)
    {
        char str[20];
        itoa(num, str, radix);
        print(str);
    }

    void print(const char str[])
    {
        auto len = strlen(str);
        while (len--)
        {
            UART_SendData(_uart, *str++);
            while (!UART_GetIRQFlag(_uart, UART_IF_SendOver))
                ;
            UART_ClearIRQFlag(_uart, UART_IF_SendOver);
        }
    }

    void println()
    {
        print("\r\n");
    }

    void println(const char str[])
    {
        print(str);
        println();
    }

    void println(long num, Radix radix = DEC)
    {
        print(num, radix);
        println();
    }
};