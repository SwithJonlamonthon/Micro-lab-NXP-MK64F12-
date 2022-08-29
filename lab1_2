/* Program 1_1.c Toggling LED in C using Keil header file * register definitions(MK64F12.h).* This program toggles green LED for 2second ON and 2second OFF.* The green LED is connected to PTB26.* The LEDs are low active (a '0' turns ON the LED).*/ 

#include"MK64F12.h"

void delayMs(int n);
void ledpin(int a , int b);
void formation4(int x);


int main(void) {
       	
        while(1){
					formation4(1);
					}
        
} /* Delay n milliseconds* The CPU core clock is set to MCGFLLCLK at 41.94 MHz ??? in SystemInit().*/
void delayMs(int n){
				int i;
        int j; /* This for-loop takes about 2 seconds */
        for (i = 0; i < n/2; i++){
                for (j = 0; j < 7000; j++) {}
        }
}

void ledpin(int a , int b){  /*This function for RGB LED*/
		
		switch(b){
				case 1:  /*For red led*/
							SIM -> SCGC5 |= 0x400; 
							PORTB -> PCR[22] = 0x0100; 
							PTB -> PDDR |= 0x0400000;
								if (a == 1){
								PTB -> PDOR &= !0x0400000;
								}
								else if(a == 0){
								PTB -> PDOR = 0x0400000; 
								PTB -> PDDR &= !0x0000000; /*set value in portB to 0*/
								}
							
							break;
				case 2:  /*For green led*/
							SIM -> SCGC5 |= 0x2000; 
							PORTE -> PCR[26] = 0x0100; 
							PTE -> PDDR |= 0x04000000; 
								if (a == 1){
									PTE -> PDOR &= !0x04000000;
								}
								else if(a == 0){
									PTE -> PDOR = 0x04000000; 
								}
								
							break;
				case 3:  /*For blue led*/
							SIM -> SCGC5 |= 0x400; 
							PORTB -> PCR[21] = 0x0100; 
							PTB -> PDDR |= 0x0200000; 
 								if (a == 1){
									PTB -> PDOR &= !0x0200000;
								}
								else if(a == 0){
									PTB -> PDOR = 0x0200000;
									PTB -> PDDR &= !0x0000000;/*set value in portB to 0*/
								}
						
							break;
	
					
					
		
			
			
			
			
			}
		
}
void formation4(int x){
	if(x == 1){
		ledpin(1,1);
		delayMs(1000);
		ledpin(0,1);
		delayMs(100);
		ledpin(1,2);
		delayMs(1000);
		ledpin(0,2);
		delayMs(100);
		ledpin(1,3);
		delayMs(1000);
		ledpin(0,3);
		delayMs(100);
	
	
	}

}






