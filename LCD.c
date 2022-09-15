/* p3_1.c: Initialize and display "Hello 8bits" on the LCD using 8-bit data mode.* The following pins are usedRS: PTD0,   EN: PTD2, RW: PTD3D0: PTC16,D1: PTC17D2: PTB9,D3: PTA1D4: PTB23, D5: PTA2D6: PTC2, D7: PTC3* This program does not poll the status of the LCD.* It uses delay to wait out the time LCD controller is busy.* Timing is more relax than the HD44780 datasheet to accommodate the* variations among the LCD modules.* You may want to adjust the amount of delay for your LCD controller.*/ #include"MK64F12.h"
#include"MK64F12.h"
void delayMs(int n);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
int main(void) {
        LCD_init();
        for (;;) {
                LCD_command(1); /* clear display */
                delayMs(500);
                LCD_command(0x80); /* set cursor at first line */
                LCD_data('H'); /* write the word */
                LCD_data('e');
                LCD_data('l');
                LCD_data('l');
                LCD_data('o');
                LCD_data(' ');
                LCD_data('8');
                LCD_data('b');
                LCD_data('i');
                LCD_data('t');
                LCD_data('s');
                delayMs(500);
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







