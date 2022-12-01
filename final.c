#include "MK64F12.h"
void initPort(void);
void PORTB_IRQHandler(void);
void ledpin(int a , int b);	
void delayMs(int n);






int main(void){
	
	initPort();
	
	while(1){
		int i = 1;
		if((PTB->PDIR & 0x08) == 0){
			PTA -> PDDR |= 0x02;
			while((PTB->PDIR & 0x0400) != 0){
					if(i != 5){
						ledpin(1,i);
						delayMs(1000);
						ledpin(0,i);
						i++;
					}
					else{
						i = 1;
					}
					
			}
		
		}
		if((PTB->PDIR & 0x0400) == 0){
			PTA -> PDDR &= !(0x02);
		
		}
	
	
	
	}
	
	






}



void initPort(void){
	SIM->SCGC5 |= (1 <<SIM_SCGC5_PORTA_SHIFT) | (1 << SIM_SCGC5_PORTB_SHIFT) | (1 << SIM_SCGC5_PORTD_SHIFT);
	PORTB -> PCR[3] = 1 << PORT_PCR_MUX_SHIFT;
	PORTB -> PCR[10] = 1 << PORT_PCR_MUX_SHIFT;
	PORTA -> PCR[1] = 1 << PORT_PCR_MUX_SHIFT;
	
	PTB -> PDDR = !(1 << 3);
	PTB -> PDDR = !(1 << 10);
	/*
	__disable_irq(); 
	PORTB -> PCR[10] &= !0xF0000;  
	PORTB -> PCR[10] |= 0xA0000; 
	NVIC -> ISER[1] |= 0x10000000;
  __enable_irq(); 
	*/
	








}



void PORTB_IRQHandler(void){
		if((PTB->PDIR & 0x0400) == 0){
			PTA -> PDDR =0x00;
			PORTB -> ISFR = 0x0400;
		
		}
		
		



}


void ledpin(int a , int b){  /*This function for RGB LED*/
		PORTD -> PCR[0] = 1 << PORT_PCR_MUX_SHIFT;
		PORTD -> PCR[1] = 1 << PORT_PCR_MUX_SHIFT;
		PORTD -> PCR[2] = 1 << PORT_PCR_MUX_SHIFT; 
		PORTD -> PCR[3] = 1 << PORT_PCR_MUX_SHIFT; 
		switch(b){
				case 4:  /*For D1*/
						 if (a == 1){
							 PTD ->PDDR |= (1 << 0);
							
						 }
						 else{
							PTD ->PDDR &= !(1 << 0);
						 
						 }
							 
					
								
							
							break;
				case 1:  /*For D2*/
							 if (a == 1){
							 PTD ->PDDR |= (1 << 1);
							
						 }
						 else{
							PTD ->PDDR &= !(1 << 1);
						 
						 }
							 
							
							
								
							break;
				case 3:  /*For D3*/
						 if (a == 1){
							 PTD ->PDDR |= (1 << 2);
							
						 }
						 else{
							PTD ->PDDR &= !(1 << 2);
						 
						 }
							 
							
						
							break;
				case 2:  /*For D4*/
						 if (a == 1){
							 PTD ->PDDR |= (1 << 3);
							
						 }
						 else{
							PTD ->PDDR &= !(1 << 3);
						 
						 }
							 
						
						break;
	
					
					
		
			
			
			
			
			}
		
}

void delayMs(int n) {
        int i;
        SysTick -> LOAD = 20480 - 1;
        SysTick -> CTRL = 5; 
        for (i = 0; i < n; i++)
                while ((SysTick -> CTRL & 0x10000) == 0) {
                         }
        SysTick -> CTRL = 0; 
}









