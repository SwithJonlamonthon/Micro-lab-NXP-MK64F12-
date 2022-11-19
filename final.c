#include <MK64F12.h>
void LED(void);
void Buzzer(void);
int main(void){
	LED();
	SIM->SCGC5 |= (1<<SIM_SCGC5_PORTC_SHIFT)| (1<<SIM_SCGC5_PORTB_SHIFT);;
	PORTB->PCR[23] = 1<< PORT_PCR_MUX_SHIFT;
	PORTC->PCR[3] = 1<< PORT_PCR_MUX_SHIFT;
	PORTC->PCR[12] = 1<< PORT_PCR_MUX_SHIFT;
	PTC -> PDOR |= 1 << 3 | 1 << 12 ;
	PTB -> PDOR = 1 << 23;
	
	PTC-> PDOR = (PTD ->PDIR & 0x08) >>3;
	
	
	

}



void LED(void){
	SIM->SCGC5 |= (1<<SIM_SCGC5_PORTB_SHIFT) |  (1<<SIM_SCGC5_PORTD_SHIFT);
	PORTB->PCR[3] = 1<< PORT_PCR_MUX_SHIFT;
	PORTD->PCR[0] = 1<< PORT_PCR_MUX_SHIFT;
	PTB->PDDR = 0x08;
	PTD-> PDDR = 1;
	
	while(1){
		PTD->PDOR = (PTB->PDIR & 0x08) >> 3;
	
	}


}


void Buzzer(void){
	SIM->SCGC5 |= (1<<SIM_SCGC5_PORTB_SHIFT) |  (1<<SIM_SCGC5_PORTA_SHIFT);
	PORTB->PCR[3] = 1<< PORT_PCR_MUX_SHIFT;
	PORTA->PCR[1] = 1<< PORT_PCR_MUX_SHIFT;
	PTB->PDDR = 0x08;
	PTA-> PDDR = 1<<1;
	/*
	while(1){
		PTA->PDOR = (PTB->PDIR & 0x08) >> 2;
	
	}
	*/



}


















