#include"MK64F12.h"

void delayMs(int n);
void PORTA_IRQHandler(void);
void PORTC_IRQHandler(void);
int main(void) {
      SIM -> SCGC5 |= 0x2E00; 
			PORTB -> PCR[22] = 0x0100; 
			PORTE -> PCR[26] = 0x0100;
			PORTC -> PCR[6] = 0x0100;
			PTB -> PDDR |= 0x0400000;
			PTE -> PDDR |= 0x04000000; 
			PTB->PDOR |=0x0400000;
			PTE -> PDOR |= 0x04000000;
			PTC -> PDDR &= !0x40;
			__disable_irq(); /* Step 6.2: disable all IRQs */
			PORTC -> PCR[6] &= !0xF0000; /*To set isf(24) */
			PORTC -> PCR[6] |= 0xA0000; 
				/*For falling edge interrupt use 0xA0000 */
			 /*For rising edge interrupt use 0x90000 */
			NVIC -> ISER[1] |= 0x20000000;
      			__enable_irq(); 
			while(1){
				PTB -> PTOR |= 0x400000; /* toggle red LED */
				delayMs(500);
			}
			
} 

void PORTC_IRQHandler(void){
	 int i; /* toggle blue LED (PTB21) three times */
        for (i = 0; i < 3; i++) {
                PTE -> PDOR &= !0x04000000; /* turn on blue LED */
                delayMs(100);
                PTE -> PDOR |= 0x04000000; /* turn off blue LED */
                delayMs(100);
        }
        PORTC -> ISFR = 0x00000040; /* Step clear interrupt flag */
}




void delayMs(int n) {
        int i;
        int j;
        for (i = 0; i < n; i++)
                for (j = 0; j < 7000; j++) {}
									
								}							
									
									
								
								
								
								
								
