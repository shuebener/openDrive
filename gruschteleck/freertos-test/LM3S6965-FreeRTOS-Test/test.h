
#ifndef __openDrive_TEST_H 
#define __openDrive_TEST_H

#define testSTACK_SIZE		configMINIMAL_STACK_SIZE
#define mainTEST_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )

void vStartTestTask( unsigned portBASE_TYPE uxPriority );


#endif /* end __openDrive_TEST_H */

