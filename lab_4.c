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

/*lcd2*/


/* p3_1.c: Initialize and display "Hello 8bits" on the LCD using 8-bit data mode.* The following pins are usedRS: PTD0,   EN: PTD2, RW: PTD3D0: PTC16,D1: PTC17D2: PTB9,D3: PTA1D4: PTB23, D5: PTA2D6: PTC2, D7: PTC3* This program does not poll the status of the LCD.* It uses delay to wait out the time LCD controller is busy.* Timing is more relax than the HD44780 datasheet to accommodate the* variations among the LCD modules.* You may want to adjust the amount of delay for your LCD controller.*/ #include"MK64F12.h"
#include"MK64F12.h"
void delayMs(int n);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
int main(void) {
	LCD_init();
	for(;;){
		int i;
		char name [20] = "SwithFuckyeah";
		LCD_command(0x80);
		for(i = 0; i < 20;i++){
			LCD_data(name[i]);
		}
	
	}
        
}
void LCD_init(void) {
        SIM -> SCGC5 |= 0x1E00; /* enable clock to Port A, B, C, and D*/
        PORTC -> PCR[16] = 0x100; /* make PTC16 pin as GPIO */
        PORTC -> PCR[17] = 0x100; /* make PTC17 pin as GPIO */
        PORTB -> PCR[9] = 0x100; /* make PTB9 pin as GPIO */
        PORTA -> PCR[1] = 0x100; /* make PTA1 pin as GPIO */
        PORTB -> PCR[23] = 0x100; /* make PTB23 pin as GPIO */
        PORTA -> PCR[2] = 0x100; /* make PTA2 pin as GPIO */
        PORTC -> PCR[2] = 0x100; /* make PTC2 pin as GPIO */
        PORTC -> PCR[3] = 0x100; /* make PTC3 pin as GPIO */
        PORTD -> PCR[0] = 0x100; /* make PTCD0 pin as GPIO */
        PORTD -> PCR[2] = 0x100; /* make PTC2 pin as GPIO */
        PORTD -> PCR[3] = 0x100; /* make PTD3 pin as GPIO */
        PTC -> PDDR |= 0x3000C; /* make PTC2, 3, 16, and 17 as output pins */
        PTB -> PDDR |= 0x800200; /* make PTB9 and 23 as output pins */
        PTA -> PDDR |= 0x06; /* make PTA2 as output pins */
        PTD -> PDDR |= 0x0D; /* make PTD0, 2, and 3 as output pins */
        delayMs(30); /* initialization sequence */
        LCD_command(0x30);
        delayMs(10);
        LCD_command(0x30);
        delayMs(1);
        LCD_command(0x30);
        LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
        LCD_command(0x08); /* display off, cursor off */
        LCD_command(0x01); /* clear screen, move cursor to home */
        LCD_command(0x06); /* move cursor right */
        LCD_command(0x0F); /* turn on display, cursor blinking */
}
void LCD_command(unsigned char command) {
                /* RS and R/W */
                PTD -> PDOR = 0x00; /* RS = 0 (PTD0) and R/W = 0 (PTD3)*/ /*RS: PTD0,   EN: PTD2, RW: PTD3D0: PTC16,D1: PTC17D2: PTB9,D3: PTA1D4: PTB23, D5: PTA2D6: PTC2, D7: PTC3*/
                PTB -> PDOR = ((command & 0x04) << 7) | ((command & 0x10) << 19); /* D2, D4 */
                PTA -> PDOR = ((command & 0x08) >> 2) | ((command & 0x20) >> 3); /* D3, D5 */
                PTC -> PDOR = ((command & 0x03) << 16) | ((command & 0xC0) >> 4); /* D0, D1, D6, D7 */ /* pulse E  */
                PTD -> PDOR |= 0x04; /* EN = 1 (PTD2)*/
                delayMs(1);
                PTD -> PDOR &= ~(0x04); /* EN = 0 (PTD2)*/ 
}
void LCD_data(unsigned char data){
                        /* RS and R/W */
                        PTD -> PDOR = 0x01; /* RS = 1 (PTD0) and R/W = 0 (PTD3)*/ /* RS: PTD0,   EN: PTD2, RW: PTD3D0: PTC16,D1: PTC17D2: PTB9,D3: PTA1D4: PTB23, D5: PTA2D6: PTC2, D7: PTC3*/
                        PTB -> PDOR = ((data & 0x04) << 7) | ((data & 0x10) << 19); /* D2, D4 */
                        PTA -> PDOR = ((data & 0x08) >> 2) | ((data & 0x20) >> 3); /* D3, D5 */
                        PTC -> PDOR = ((data & 0x03) << 16) | ((data & 0xC0) >> 4); /* D0, D1, D6, D7 */ /* pulse E  */
                        PTD -> PDOR |= 0x04; /* EN = 1 (PTD2)*/
                        delayMs(1);
                        PTD -> PDOR &= ~(0x04); /* EN = 0 (PTD2)*/
                        delayMs(1);
} 

void delayMs(int n){
       int i;
       int j;
       for (i = 0; i < n; i++){
           for (j = 0; j < 7000; j++) {
                 __NOP();
                                }
                }
}		



