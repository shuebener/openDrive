#include "debug.h"

#include "lm3s_cmsis.h"
#include "LM3S6965_Bitdef.h"

#include "FreeRTOS.h"
#include "task.h"

#include "system_port.h"
#include "test.h"
#include "uart_port.h"


extern uint32_t SysP_SystemFrequency;
extern uint32_t SysP_SystemFrequency_PwmClk;
extern uint32_t SysP_SystemFrequency_AdcClk;
extern uint32_t SysP_SystemFrequency_CanClk;


int main(void) {

	SystemClockInit();
    UARTPort_Init();

	debug_printf("\nSystemFrequency: %dHz\nSystemFrequency_PwmClk: %dHz\nSystemFrequency_AdcClk: %dHz\nSystemFrequency_CanClk: %dHz\n", SysP_SystemFrequency, SysP_SystemFrequency_PwmClk, SysP_SystemFrequency_AdcClk, SysP_SystemFrequency_CanClk);

	vStartTestTask(mainTEST_TASK_PRIORITY);

	vTaskStartScheduler();

	for( ;; );
	return 0;
}