#include "debug.h"


/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "test.h"


void vTaskCode( void * pvParameters ) {

	( void ) pvParameters;


    portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while(1) {

		debug_printf("TestTask\n");

		//Delay für 1000ms
		vTaskDelayUntil(&xLastWakeTime, ( 10000 / portTICK_RATE_MS ) );
	}
}


void vStartTestTask( unsigned portBASE_TYPE uxPriority ) {
	static unsigned char ucParameterToPass;
	xTaskHandle xHandle;

	portBASE_TYPE test;
	test = xTaskCreate( vTaskCode, (signed char *) "Test", testSTACK_SIZE, &ucParameterToPass, uxPriority, &xHandle );

	if(test == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY) {
		debug_printf("errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY\n");		
	}

	return;
} 