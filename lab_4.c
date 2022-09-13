#include"MK64F12.h"

void UART0_init(void);
void delayMs(int n);
void LED_init(void);
void LED_set(int value);
int main(void) {
      char c;
	UART0_init();
	LED_init();
	while (1) {
        /* Step 9: wait for receive buffer full */
        while (!(UART0 -> S1 & 0x20)) {} /* Step 10 : read the char received */
        c = UART0 -> D;
        LED_set(c);
				while (!(UART0 -> S1 & 0x80)) {}
				UART0 -> D = c;
				while (!(UART0 -> S1 & 0x80)) {}
				UART0 -> D = '\n';
				delayMs(500);
				 
        }
} /* initialize UART0 to transmit at 115200 Baud */

void LED_init(void) {
        SIM -> SCGC5 |= 0x2000; /* enable clock to Port E */
        SIM -> SCGC5 |= 0x0400; /* enable clock to Port B */
        PORTB -> PCR[21] = 0x0100; /* make PTB21 pin as GPIO */
        PORTB -> PCR[22] = 0x0100; /* make PTB22 pin as GPIO */
        PTB -> PDDR |= 0x600000; /* make PTB21, 22 asoutput pin */
        PORTE -> PCR[26] = 0x0100; /* make PTE26 pin as GPIO */
        PTE -> PDDR |= 0x4000000; /* make PTE26 as output pin */
        PTB -> PSOR = 0x400000; /* turn off red LED */
        PTE -> PSOR = 0x4000000; /* turn off green LED */
        PTB -> PSOR = 0x200000; /* turn off blue LED */
} /* turn on or off the LEDs according to bit 2-0 of the value */
void LED_set(int value) {
        if (value & 1) /* use bit 0 of value to control red LED */ PTB -> PCOR = 0x400000; /* turn on red LED */
        else PTB -> PSOR = 0x400000; /* turn off red LED */
        if (value & 2) /* use bit 1 of value to control green LED */ PTE -> PCOR = 0x4000000; /* turn on green LED */
        else PTE -> PSOR = 0x4000000; /* turn off green LED */
        if (value & 4) /* use bit 2 of value to control blue LED */ PTB -> PCOR = 0x200000; /* turn on blue LED */
        else PTB -> PSOR = 0x200000; /* turn off blue LED */
}
void UART0_init(void) {
        /* Step1 : enable clock for UART0 */
        SIM -> SCGC4 |= 0x0400; /* Step 2: setFLL output for UART Baud rate generator and set OUTDIV1 value.However,by default FLL is used andOUTDIV1 = 0. So, no need to do anything for this particular choice. */ /* Step 3: turn off UART0 while changing configurations */
        UART0 -> C2 = 0; /* Step 4: set baud rate = 115200 */
        UART0 -> BDH = 0x00; /* decimal = 0 */
        UART0 -> BDL = 0x0B; /* decimal = 11 */
        UART0 -> C4 = 0x03; /* BRFA */ /* Step 5: set UART frame format: 1 start-bit+ 8-bit data + 1 stop-bit*/
        UART0 -> C1 = 0x00; /* Step 6: enable transmit(TE = 1)*/
        UART0 -> C2 = 0x0C; /* Step 7: enable clock for PORTB (For use tranfer and recieve)*/
        SIM -> SCGC5 |= 0x0400; /* Step 8: make PTB17 as UART0_Tx pin(ALT 3)*/
				PORTB->PCR[17] =0x0300; 
        PORTB -> PCR[16] = 0x0300;
				
} /* Delay n milliseconds */ /* The CPU core clock is set to MCGFLLCLK at 20.47MHz in SystemInit(). */
void delayMs(int n) {
        int i;
        int j;
        for (i = 0; i < n; i++)
                for (j = 0; j < 7000; j++) {
                        __NOP(); /* this function does nothing and it's defined in CMSIS-Core (Cortex-M)*/
                }
}

