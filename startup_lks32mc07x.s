.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */
  
/* Call the clock system initialization function.*/
  bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors
g_pfnVectors:
    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word 0
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler
    
    .word TIMER0_IRQHandler
    .word TIMER1_IRQHandler
    .word TIMER2_IRQHandler
    .word TIMER3_IRQHandler

    .word QEP0_IRQHandler
    .word QEP1_IRQHandler
    .word I2C0_IRQHandler
    .word SPI0_IRQHandler

    .word GPIO_IRQHandler
    .word HALL0_IRQHandler
    .word UART0_IRQHandler
    .word UART1_IRQHandler

    .word DSP0_IRQHandler
    .word CMP_IRQHandler
    .word ADC0_IRQHandler
    .word ADC1_IRQHandler

    .word MCPWM0_IRQHandler
    .word MCPWM1_IRQHandler
    .word DMA0_IRQHandler
    .word CAN0_IRQHandler

    .word SIF0_IRQHandler
    .word WAKE_IRQHandler
    .word SW_IRQHandler
    .word PWRDN_IRQHandler

    .word CL0_IRQHandler
    .word 0
    .word 0
    .word 0

    .word 0
    .word 0
    .word 0
    .word 0

    .weak NMI_Handler
    .thumb_set NMI_Handler,Default_Handler

    .weak HardFault_Handler
    .thumb_set HardFault_Handler,Default_Handler

    .weak SVC_Handler
    .thumb_set SVC_Handler,Default_Handler

    .weak PendSV_Handler
    .thumb_set PendSV_Handler,Default_Handler

    .weak SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler

    .weak TIMER0_IRQHandler
    .thumb_set TIMER0_IRQHandler,Default_Handler

    .weak TIMER1_IRQHandler
    .thumb_set TIMER1_IRQHandler,Default_Handler

    .weak TIMER2_IRQHandler
    .thumb_set TIMER2_IRQHandler,Default_Handler

    .weak TIMER3_IRQHandler
    .thumb_set TIMER3_IRQHandler,Default_Handler

    .weak QEP0_IRQHandler
    .thumb_set QEP0_IRQHandler,Default_Handler

    .weak QEP1_IRQHandler
    .thumb_set QEP1_IRQHandler,Default_Handler

    .weak I2C0_IRQHandler
    .thumb_set I2C0_IRQHandler,Default_Handler

    .weak SPI0_IRQHandler
    .thumb_set SPI0_IRQHandler,Default_Handler

    .weak GPIO_IRQHandler
    .thumb_set GPIO_IRQHandler,Default_Handler

    .weak HALL0_IRQHandler
    .thumb_set HALL0_IRQHandler,Default_Handler

    .weak UART0_IRQHandler
    .thumb_set UART0_IRQHandler,Default_Handler

    .weak UART1_IRQHandler
    .thumb_set UART1_IRQHandler,Default_Handler

    .weak DSP0_IRQHandler
    .thumb_set DSP0_IRQHandler,Default_Handler

    .weak CMP_IRQHandler
    .thumb_set CMP_IRQHandler,Default_Handler

    .weak ADC0_IRQHandler
    .thumb_set ADC0_IRQHandler,Default_Handler

    .weak ADC1_IRQHandler
    .thumb_set ADC1_IRQHandler,Default_Handler

    .weak MCPWM0_IRQHandler
    .thumb_set MCPWM0_IRQHandler,Default_Handler

    .weak MCPWM1_IRQHandler
    .thumb_set MCPWM1_IRQHandler,Default_Handler

    .weak DMA0_IRQHandler
    .thumb_set DMA0_IRQHandler,Default_Handler

    .weak CAN0_IRQHandler
    .thumb_set CAN0_IRQHandler,Default_Handler

    .weak SIF0_IRQHandler
    .thumb_set SIF0_IRQHandler,Default_Handler

    .weak WAKE_IRQHandler
    .thumb_set WAKE_IRQHandler,Default_Handler

    .weak SW_IRQHandler
    .thumb_set SW_IRQHandler,Default_Handler

    .weak PWRDN_IRQHandler
    .thumb_set PWRDN_IRQHandler,Default_Handler

    .weak CL0_IRQHandler
    .thumb_set CL0_IRQHandler,Default_Handler