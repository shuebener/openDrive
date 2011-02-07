#ifndef __openDrive_SYSTEM_PORT_H
#define __openDrive_SYSTEM_PORT_H

#include "LM3S6965_Bitdef.h"

//Define clocks
#define XTALI       (12000000UL)	// Internal oscillator frequency (12 MHz)
#define XTAL30K     (   30000UL)	// Internal 30K oscillator frequency (30 kHz)
#define XTAL32K     (   32768UL)	// external 32K oscillator frequency (Hibernation Module) (32,768 kHz)
#define PLL_CLK    (400000000UL)	// PLL Clock frequency (400 MHz)


// Run-Mode Clock Configuration (RCC) Settings
#define SYSP_MOSCDIS 0			// Main Oscillator => active
#define SYSP_IOSCDIS 1			// Internal Oscillator => active
#define SYSP_OSCSRC 0			// Oscillator Source => main osc
#define SYSP_XTAL 0xE			// Crystal Value => 8 MHz
#define SYSP_BYPASS 0			// PLL Bypass => inactive
#define SYSP_PWRDN 0			// PLL Power Down => PLL active
#define SYSP_PWMDIV 7			// PWM Unit Clock Divisor [div = 2*2^x; max 64] => clk / 64
#define SYSP_USEPWMDIV 0		// Use PWM Clock Divisor => inactive
#define SYSP_USESYSDIV 1		// Use System Clock Divider => active
#define SYSP_SYSDIV (4-1)		// System Clock Divisor (max 16) => clk / 4
#define SYSP_ACG 0				// Auto Clock Gating


// Run-Mode Clock Configuration 2 (RCC2) Settings
#define SYSP_OSCSRC2 0			// Oscillator Source => main osc
#define SYSP_BYPASS2 0			// Bypass PLL => inactive
#define SYSP_PWRDN2 0			// Power-Down PLL => pll active
#define SYSP_SYSDIV2 (16-1)		// System Clock Divisor (max 64) => clk / 16
#define SYSP_USERCC2 0			// Use RCC2 => inactive




//Do NOT change anything below this line!

#define SYSCTL_RCC_CONFVALUE							\
(														\
	 (SYSP_MOSCDIS		<< SYSCTL_RCC_MOSCDIS) |		\
	 (SYSP_IOSCDIS		<< SYSCTL_RCC_IOSCDIS) |		\
	 (SYSP_OSCSRC		<< SYSCTL_RCC_OSCSRC) |			\
	 (SYSP_XTAL			<< SYSCTL_RCC_XTAL) |			\
	 (SYSP_BYPASS		<< SYSCTL_RCC_BYPASS) |			\
	 (SYSP_PWRDN		<< SYSCTL_RCC_PWRDN) |			\
	 (SYSP_PWMDIV		<< SYSCTL_RCC_PWMDIV) |			\
	 (SYSP_USEPWMDIV	<< SYSCTL_RCC_USEPWMDIV) |		\
	 (SYSP_USESYSDIV	<< SYSCTL_RCC_USESYSDIV) |		\
	 (SYSP_SYSDIV		<< SYSCTL_RCC_SYSDIV) |			\
	 (SYSP_ACG			<< SYSCTL_RCC_ACG)				\
)


#define SYSCTL_RCC2_CONFVALUE							\
(														\
	(SYSP_OSCSRC2		<< SYSCTL_RCC2_OSCSRC2) |		\
	(SYSP_BYPASS2		<< SYSCTL_RCC2_BYPASS2) |		\
	(SYSP_PWRDN2		<< SYSCTL_RCC2_PWRDN2) |		\
	(SYSP_SYSDIV2		<< SYSCTL_RCC2_SYSDIV2) |		\
	(SYSP_USERCC2		<< SYSCTL_RCC2_USERCC2)			\
)


void SystemInit(void);
void SystemClockInit (void);
void SystemUpdateClkVars(void);
uint32_t getOscClk (uint32_t xtal, uint32_t oscSrc);


#endif /* end __openDrive_SYSTEM_PORT_H */
