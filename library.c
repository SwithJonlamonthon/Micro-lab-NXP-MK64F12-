/* Program 1_1.c Toggling LED in C using Keil header file * register definitions(MK64F12.h).* This program toggles green LED for 2second ON and 2second OFF.* The green LED is connected to PTB26.* The LEDs are low active (a '0' turns ON the LED).*/ 

#include"MK64F12.h"

void delayMs(int n);
void ledpin(int a , int b);
void formation4(int x);
int keypad()


int main(void) {
       	SIM->SCGC5 |= 0x0A00;
				PORTA->PCR[4] = 0x0100;
				PORTC->PCR[6] = 0x0100;
				PTC->PDDR &= !0x40;
				PTA->PDDR &= !0x10;
        while(1){
					if(PTC->PDIR & 0x40){/*when the board is turn on and button is not press*/
						ledpin(0,2);
					
					}
					else{/* button is press */
						ledpin(1,2);
					
					
					}
					if(PTA->PDIR & 0x10){
						ledpin(0,3);
					
					}else{
						ledpin(1,3);
					
					}
					
					
					
					
						
							

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
int keypad(){
	int col,i,x,value = 0;
	SIM->SCGC5 |= 0x0800;
	PORTC->PCR[0] = 0x100;
	PORTC->PCR[1] = 0x100;
	PORTC->PCR[2] = 0x100;
	PORTC->PCR[3] = 0x100;
	PORTC->PCR[8] = 0x100;
	PORTC->PCR[9] = 0x100;
	PORTC->PCR[10] = 0x100;
	PTC->PDDR = 0x000F; /*Set ptc0-ptc3 as input and ptc8-ptc10 as output*/
	PTC->PDOR = 0x000F;/*init all output as a 1*/
	while(1){
		col = 0x0700;
		for(i = 0;i < 4;i++){
			PTC->PDOR = !(0x01 << i);
			delayUS(10);
			col = PTC->PDIR &0x0700;
			if(col ==0x600){
				value = (i * 3)+ 1;
				
				}
			else if(col == 0x500){
				value = (i * 3)+ 2;
				
				}
			else if(col == 0x300){
				value = (i * 3)+ 3;
				
				}
			else{
				value = 0;
				
				}
		return value;
					
			
		}
			
		
	}
	
	
}
