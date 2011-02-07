#ifndef __LM3S6965_Bitdef_H 
#define __LM3S6965_Bitdef_H



// Register 4: Raw Interrupt Status (RIS), offset 0x050
#define SYSCTL_RIS_BORRIS 1					// Brown-Out Reset Raw Interrupt Status (default: 0)
#define SYSCTL_RIS_PLLLRIS 6				// PLL Lock Raw Interrupt Status (default: 0)

// Register 8: Run-Mode Clock Configuration (RCC), offset 0x060
#define SYSCTL_RCC_MOSCDIS 0				// Main Oscillator Disable (default: 1)
#define SYSCTL_RCC_IOSCDIS 1				// Internal Oscillator Disable (default: 0)
#define SYSCTL_RCC_OSCSRC 4					// Oscillator Source (default: 0x1)
#define SYSCTL_RCC_XTAL 6					// Crystal Value (default: 0xB)
#define SYSCTL_RCC_BYPASS 11				// PLL Bypass (default: 1)
#define SYSCTL_RCC_PWRDN 13					// PLL Power Down (default: 1)
#define SYSCTL_RCC_PWMDIV 17				// PWM Unit Clock Divisor (default: 0x7)
#define SYSCTL_RCC_USEPWMDIV 20				// Enable PWM Clock Divisor (default: 0)
#define SYSCTL_RCC_USESYSDIV 22				// Enable System Clock Divider (default: 0)
#define SYSCTL_RCC_SYSDIV 23				// System Clock Divisor (default: 0xF)
#define SYSCTL_RCC_ACG 27					// Auto Clock Gating (default: 0)


// Register 9: XTAL to PLL Translation (PLLCFG), offset 0x064
#define SYSCTL_PLLCFG_R 0					// PLL R Value
#define SYSCTL_PLLCFG_F 5					// PLL F Value


// Register 10: Run-Mode Clock Configuration 2 (RCC2), offset 0x070
#define SYSCTL_RCC2_OSCSRC2 4				// Oscillator Source (default: 0x1)
#define SYSCTL_RCC2_BYPASS2 11				// Bypass PLL (default: 1)
#define SYSCTL_RCC2_PWRDN2 13				// Power-Down PLL (default: 1)
#define SYSCTL_RCC2_SYSDIV2 23				// System Clock Divisor (default: 0x0F)
#define SYSCTL_RCC2_USERCC2 31				// Use RCC2 (default: 0)




/**************************************************************/
/* Universal Asynchronous Receivers/Transmitters (UARTs)      */
/**************************************************************/

// Register 1: UART Data (UARTDR), offset 0x000
// UARTn->DR
#define UARTn_DR_DATA 0						// Data Transmitted or Received
#define UARTn_DR_FE 8						// UART Framing Error
#define UARTn_DR_PE 9						// UART Parity Error
#define UARTn_DR_BE 10						// UART Break Error
#define UARTn_DR_OE 11						// UART Overrun Error


// Register 2: UART Receive Status/Error Clear (UARTRSR/UARTECR), offset 0x004
// UARTn->RSR / UARTn->ECR
#define UARTn_RSR_FE 0						// UART Framing Error
#define UARTn_RSR_PE 1						// UART Parity Error
#define UARTn_RSR_BE 2						// UART Break Error
#define UARTn_RSR_OE 3						// UART Overrun Error
#define UARTn_ECR_DATA 0					// Error Clear


// Register 3: UART Flag (UARTFR), offset 0x018
// UARTn->FR
#define UARTn_FR_BUSY 3						// UART Busy
#define UARTn_FR_RXFE 4						// UART Receive FIFO Empty
#define UARTn_FR_TXFF 5						// UART Transmit FIFO Full
#define UARTn_FR_RXFF 6						// UART Receive FIFO Full
#define UARTn_FR_TXFE 7						// UART Transmit FIFO Empty


// Register 4: UART IrDA Low-Power Register (UARTILPR), offset 0x020
// UARTn->ILPR
#define UARTn_ILPR_ILPDVSR 0				// IrDA Low-Power Divisor


// Register 5: UART Integer Baud-Rate Divisor (UARTIBRD), offset 0x024
// UARTn->IBRD
#define UARTn_IBRD_DIVINT 0					// Integer Baud-Rate Divisor (default: 0x0000)


// Register 6: UART Fractional Baud-Rate Divisor (UARTFBRD), offset 0x028
// UARTn->FBRD
#define UARTn_FBRD_DIVFRAC 0				// Fractional Baud-Rate Divisor (default: 0x000)


// Register 7: UART Line Control (UARTLCRH), offset 0x02C
// UARTn->LCRH
#define UARTn_LCRH_BRK 0					// UART Send Break
#define UARTn_LCRH_PEN 1					// UART Parity Enable
#define UARTn_LCRH_EPS 2					// UART Even Parity Select
#define UARTn_LCRH_STP2 3					// UART Two Stop Bits Select
#define UARTn_LCRH_FEN 4					// UART Enable FIFOs
#define UARTn_LCRH_WLEN 5					// UART Word Length
#define UARTn_LCRH_SPS 7					// UART Stick Parity Select


// Register 8: UART Control (UARTCTL), offset 0x030
// UARTn->CTL
#define UARTn_CTL_UARTEN 0					// UART Enable
#define UARTn_CTL_SIREN 1					// UART SIR Enable
#define UARTn_CTL_SIRLP 2					// UART SIR Low Power Mode
#define UARTn_CTL_LBE 7						// UART Loop Back Enable
#define UARTn_CTL_TXE 8						// UART Transmit Enable
#define UARTn_CTL_RXE 9						// UART Receive Enable


// Register 9: UART Interrupt FIFO Level Select (UARTIFLS), offset 0x034
// UARTn->IFLS
#define UARTn_IFLS_TXIFLSEL	0				// UART Transmit Interrupt FIFO Level Select
#define UARTn_IFLS_RXIFLSEL 3				// UART Receive Interrupt FIFO Level Select


// Register 10: UART Interrupt Mask (UARTIM), offset 0x038
// UARTn->IM
#define UARTn_IM_RXIM 4						// UART Receive Interrupt Mask
#define UARTn_IM_TXIM 5						// UART Transmit Interrupt Mask
#define UARTn_IM_RTIM 6						// UART Receive Time-Out Interrupt Mask
#define UARTn_IM_FEIM 7						// UART Framing Error Interrupt Mask
#define UARTn_IM_PEIM 8						// UART Parity Error Interrupt Mask
#define UARTn_IM_BEIM 9						// UART Break Error Interrupt Mask
#define UARTn_IM_OEIM 10					// UART Overrun Error Interrupt Mask


// Register 11: UART Raw Interrupt Status (UARTRIS), offset 0x03C
// UARTn->RIS
#define UARTn_RIS_RXRIS 4					// UART Receive Raw Interrupt Status
#define UARTn_RIS_TXRIS 5					// UART Transmit Raw Interrupt Status
#define UARTn_RIS_RTRIS 6					// UART Receive Time-Out Raw Interrupt Status
#define UARTn_RIS_FERIS 7					// UART Framing Error Raw Interrupt Status
#define UARTn_RIS_PERIS 8					// UART Parity Error Raw Interrupt Status
#define UARTn_RIS_BERIS 9					// UART Break Error Raw Interrupt Status
#define UARTn_RIS_OERIS 10					// UART Overrun Error Raw Interrupt Status


// Register 12: UART Masked Interrupt Status (UARTMIS), offset 0x040
// UARTn->MIS
#define UARTn_MIS_RXMIS 4					// UART Receive Masked Interrupt Status
#define UARTn_MIS_TXMIS 5					// UART Transmit Masked Interrupt Status
#define UARTn_MIS_RTMIS 6					// UART Receive Time-Out Masked Interrupt Status
#define UARTn_MIS_FEMIS 7					// UART Framing Error Masked Interrupt Status
#define UARTn_MIS_PEMIS 8					// UART Parity Error Masked Interrupt Status
#define UARTn_MIS_BEMIS 9					// UART Break Error Masked Interrupt Status
#define UARTn_MIS_OEMIS 10					// UART Overrun Error Masked Interrupt Status


// Register 13: UART Interrupt Clear (UARTICR), offset 0x044
// UARTn->ICR
#define UARTn_ICR_RXIC 4					// Receive Interrupt Clear
#define UARTn_ICR_TXIC 5					// Transmit Interrupt Clear
#define UARTn_ICR_RTIC 6					// Receive Time-Out Interrupt Clear
#define UARTn_ICR_FEIC 7					// Framing Error Interrupt Clear
#define UARTn_ICR_PEIC 8					// Parity Error Interrupt Clear
#define UARTn_ICR_BEIC 9					// Break Error Interrupt Clear
#define UARTn_ICR_OEIC 10					// Overrun Error Interrupt Clear








#endif /* end __LM3S6965_Bitdef_H */