#include "MK64F12.h"



void LED_set(int s);
void LED_init(void);
int main(void) {
        short int result;
        LED_init();
        SIM -> SCGC5 |= 0x2000; /* Step 2: clock to PORTE (already done in LED_init */
        /*PORTE -> PCR[24] = 0;  Step 3: PTE24 analog input */
        SIM -> SCGC6 |= 0x8000000; /* Step 4: clock to ADC0 */
        ADC0 -> SC2 &= ~0x40; /* Step 5: software trigger */ /* Step 6: clock div by 4, long sample time, single ended 12 bit, bus clock */
        ADC0 -> CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
        while (1) {
                ADC0 -> SC1[0] = 0x1A; /* Step 7: start conversion on channel 17 */
                while (!(ADC0 -> SC1[0] & 0x80)) {
                        /* Step 8: wait for conversion complete */ }
                result = ADC0 -> R[0]; /* Step 9: read conversion result and clear COCO flag */
                LED_set(result); /* Step 9: display result on LED if use internal temperature */
												/*result >> 7 to for use external sensor*/
        }
}
void LED_init(void) {
        SIM -> SCGC5 |= 0x2000; /* enable clock to Port E */
        SIM -> SCGC5 |= 0x0400; /* enable clock to Port B */
        PORTB -> PCR[21] = 0x0100; /* make PTB21 pin as GPIO */
        PORTB -> PCR[22] = 0x0100; /* make PTB22 pin as GPIO */
        PTB -> PDDR |= 0x600000; /* make PTB21, 22 as output pin */
        PORTE -> PCR[26] = 0x0100; /* make PTE26 pin as GPIO */
        PTE -> PDDR |= 0x4000000; /* make PTE26 as output pin */
        PTB -> PSOR = 0x400000; /* turn off red LED */
        PTE -> PSOR = 0x4000000; /* turn off green LED */
        PTB -> PSOR = 0x200000; /* turn off blue LED */
}
void LED_set(int value) {
        if (value & 1) /* use bit 0 of value to control red LED */ PTB -> PCOR = 0x400000; /* turn on red LED */
        else PTB -> PSOR = 0x400000; /* turn off red LED */
        if (value & 2) /* use bit 1 of value to control green LED */ PTE -> PCOR = 0x4000000; /* turn on green LED */
        else PTE -> PSOR = 0x4000000; /* turn off green LED */
        if (value & 4) /* use bit 2 of value to control blue LED */ PTB -> PCOR = 0x200000; /* turn on blue LED */
        else PTB -> PSOR = 0x200000; /* turn off blue LED */
}





