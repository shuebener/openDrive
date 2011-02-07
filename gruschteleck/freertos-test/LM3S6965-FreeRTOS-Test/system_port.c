

#include <stdint.h>
#include <math.h>
#include "lm3s_cmsis.h"
#include "LM3S6965_Bitdef.h"
#include "system_port.h"


uint32_t SysP_SystemFrequency         = XTALI;				// System Clock Frequency (Core Clock)
uint32_t SysP_SystemFrequency_PwmClk  = XTALI;				// PWM clock
uint32_t SysP_SystemFrequency_AdcClk  = PLL_CLK/25;			// ADC clock
uint32_t SysP_SystemFrequency_CanClk  = PLL_CLK/50;			// CAN clock


void SystemInit(void) {

}

void SystemClockInit (void) {
	// PLL Clock Setup
	uint32_t i;    
	
	// set default values
	SYSCTL->RCC2 = (0x1 << SYSCTL_RCC2_OSCSRC2) |		// Oscillator Source => internal
	               (1 << SYSCTL_RCC2_BYPASS2) |			// Bypass PLL
                   (1 << SYSCTL_RCC2_PWRDN2) |			// Power-Down PLL
                   (0xF << SYSCTL_RCC2_SYSDIV2) |		// System Clock Divisor => Clk / 16
                   (0 << SYSCTL_RCC2_USERCC2);			// Do not Use RCC2

	SYSCTL->RCC = (1 << SYSCTL_RCC_MOSCDIS) |			// MainOSC disabled
	              (0 << SYSCTL_RCC_IOSCDIS) |			// IntOSC enabled
	              (0x1 << SYSCTL_RCC_OSCSRC) |			// OscSrc => internal
	              (0xB << SYSCTL_RCC_XTAL) |			// Xtal Freq => 6 MHz
	              (1 << SYSCTL_RCC_BYPASS) |			// PLL Bypass
	              (1 << SYSCTL_RCC_PWRDN) |				// PLL Power Down
	              (0x7 << SYSCTL_RCC_PWMDIV) |			// PWM Unit Clock Divisor => Clk / 64
	              (0 << SYSCTL_RCC_USEPWMDIV) |			// Disable PWM Clock Divisor
	              (0 << SYSCTL_RCC_USESYSDIV) |			// Disable System Clock Divider
	              (0xF << SYSCTL_RCC_SYSDIV) |			// System Clock Divisor => Clk / 16
	              (0 << SYSCTL_RCC_ACG);				// Auto Clock Gating

	
	// Set RCC/RCC2 with disabled PLL, active Bypass & USESYSDIV reset
	SYSCTL->RCC  = (SYSCTL_RCC_CONFVALUE  | (1 << SYSCTL_RCC_BYPASS) | (1 << SYSCTL_RCC_PWRDN)) & ~(1UL << SYSCTL_RCC_USESYSDIV);		
	SYSCTL->RCC2 = (SYSCTL_RCC2_CONFVALUE | (1 << SYSCTL_RCC2_BYPASS2) | (1 << SYSCTL_RCC2_PWRDN2));										
	for (i = 0; i < 1000; i++);


	// Set RCC/RCC2 with active Bypass & USESYSDIV reset
	SYSCTL->RCC  = (SYSCTL_RCC_CONFVALUE  | (1 << SYSCTL_RCC_BYPASS)) & ~(1UL << SYSCTL_RCC_USESYSDIV);										
	SYSCTL->RCC2 = (SYSCTL_RCC2_CONFVALUE | (1 << SYSCTL_RCC2_BYPASS2));																    
	for (i = 0; i < 1000; i++);																							


	// Set RCC/RCC2 with active Bypass
	SYSCTL->RCC  = (SYSCTL_RCC_CONFVALUE  | (1 << SYSCTL_RCC_BYPASS));																	


	// wait until PLL is locked (if active)
	if ((
		((SYSCTL_RCC_CONFVALUE  & (1UL << SYSCTL_RCC_PWRDN)) == 0) && ((SYSCTL_RCC2_CONFVALUE & (1UL << SYSCTL_RCC2_USERCC2)) == 0)
	) || (
		((SYSCTL_RCC2_CONFVALUE & (1UL << SYSCTL_RCC2_PWRDN2)) == 0) && ((SYSCTL_RCC2_CONFVALUE & (1UL << SYSCTL_RCC2_USERCC2)) != 0)
	)) {
				
		while ((SYSCTL->RIS & (1UL << SYSCTL_RIS_PLLLRIS)) != (1UL << SYSCTL_RIS_PLLLRIS));										
	}


	// Set RCC/RCC2
	SYSCTL->RCC  = (SYSCTL_RCC_CONFVALUE);
	SYSCTL->RCC2 = (SYSCTL_RCC2_CONFVALUE);	
	for (i = 0; i < 10000; i++);

    SystemUpdateClkVars();
}

void SystemUpdateClkVars(void) {
	/* Determine clock frequency according to clock register values */    
	uint32_t SYSCTL_RCC  = SYSCTL->RCC;
	uint32_t SYSCTL_RCC2 = SYSCTL->RCC2;
	uint32_t CLK = 0;
	
	if (SYSCTL_RCC2 & (1UL << SYSCTL_RCC2_USERCC2)) { 
		// RCC2 is used

		if (SYSCTL_RCC2 & (1UL << SYSCTL_RCC2_BYPASS2)) { 	
			//clocksrc used as clk
			CLK = getOscClk( ((SYSCTL_RCC >> SYSCTL_RCC_XTAL) & 0x0F), ((SYSCTL_RCC2 >> SYSCTL_RCC2_OSCSRC2) & 0x07) );
		} else {
			//pll used as clk
			CLK = PLL_CLK / 2;
		}
    
		if (SYSCTL_RCC & (1UL << SYSCTL_RCC_USESYSDIV)) {	
			//sysdiv2 is used
			SysP_SystemFrequency = CLK / (((SYSCTL_RCC2 >> SYSCTL_RCC2_SYSDIV2) & (0x3F)) + 1);
		} else {
			SysP_SystemFrequency = CLK;
		}

	} else {
		//RCC is used
																			
		if(SYSCTL_RCC & (1UL << SYSCTL_RCC_BYPASS)) {
			//clocksrc used as clk
			CLK = getOscClk( ((SYSCTL_RCC >> SYSCTL_RCC_XTAL) & 0x0F), ((SYSCTL_RCC >> SYSCTL_RCC_OSCSRC) & 0x03) );
		} else {
			//pll used as clk
			CLK = PLL_CLK / 2;
		}

		if (SYSCTL_RCC & (1UL << SYSCTL_RCC_USESYSDIV)) {
			//sysdiv is used
			SysP_SystemFrequency = CLK / (((SYSCTL_RCC >> SYSCTL_RCC_SYSDIV) & 0x0F) + 1);
		} else {
			SysP_SystemFrequency = CLK;
		}
	}


	// get pwmclk
	if(SYSCTL_RCC & (1UL << SYSCTL_RCC_USEPWMDIV)) {
        uint32_t pwmdiv = 2 * pow(2, ((SYSCTL_RCC >> SYSCTL_RCC_PWMDIV) & 0x07));
		if(pwmdiv > 64) {pwmdiv = 64;}

		SysP_SystemFrequency_PwmClk = SysP_SystemFrequency / pwmdiv;
	} else {
		SysP_SystemFrequency_PwmClk = SysP_SystemFrequency;
	}

	// get adcclk
    if (SYSCTL_RCC2 & (1UL << SYSCTL_RCC2_USERCC2)) {
		if(SYSCTL_RCC2 & (1UL << SYSCTL_RCC2_PWRDN2)) {
			SysP_SystemFrequency_AdcClk = CLK;
		} else {
			SysP_SystemFrequency_AdcClk = PLL_CLK / 25;
		}
	} else {
		if(SYSCTL_RCC & (1UL << SYSCTL_RCC_PWRDN)) {
			SysP_SystemFrequency_AdcClk = CLK;
		} else {
			SysP_SystemFrequency_AdcClk = PLL_CLK / 25;
		}
	}
    
	// get canclk
	SysP_SystemFrequency_CanClk = PLL_CLK / 50;

}


uint32_t getOscClk (uint32_t xtal, uint32_t oscSrc) {
  uint32_t oscClk = XTALI;

  switch (oscSrc) {                      /* switch OSCSRC */
    case 0:                              /* MOSC Main oscillator */
      switch (xtal) {                    /* switch XTAL */
        case 0x0:
          oscClk = 1000000UL;
          break;
        case 0x1:
          oscClk = 1843200UL;
          break;
        case 0x2:
          oscClk = 2000000UL;
          break;
        case 0x3:
          oscClk = 2457600UL;
          break;
        case 0x4:
          oscClk = 3579545UL;
          break;
        case 0x5:
          oscClk = 3686400UL;
          break;
        case 0x6:
          oscClk = 4000000UL;
          break;
        case 0x7:
          oscClk = 4096000UL;
          break;
        case 0x8:
          oscClk = 4915200UL;
          break;
        case 0x9:
          oscClk = 5000000UL;
          break;
        case 0xA:
          oscClk = 5120000UL;
          break;
        case 0xB:
          oscClk = 6000000UL;
          break;
        case 0xC:
          oscClk = 6144000UL;
          break;
        case 0xD:
          oscClk = 7372800UL;
          break;
        case 0xE:
          oscClk = 8000000UL;
          break;
        case 0xF:
          oscClk = 8192000UL;
          break;
       }
      break;
    case 1:                         /* IOSC Internal oscillator */
      oscClk = XTALI;
      break;
    case 2:                         /* IOSC/4 Internal oscillator/4 */
      oscClk = XTALI/4;
      break;
    case 3:                         /* 30kHz internal oscillator  */
      oscClk = XTAL30K;
      break;
  }

  return oscClk;
}

