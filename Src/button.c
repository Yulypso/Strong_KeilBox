#include "button.h"
#include "stm32f1xx_ll_exti.h"

void Button_init(BUTTON_TypeDef *button, GPIO_TypeDef * port, uint8_t pn,
		uint8_t pl) {
	
	//initialisation d'un boutons avec les caracteristiques passées en parametre
	button->gpioPort = port;
	button->pin = pn;
	button->pull = pl;

	//déterminer le numéro du port 0--> GPIOA, 1-->GPIOB, etc.
	uint8_t nb_port;
	nb_port = ((uint32_t) port - GPIOA_BASE) / 0x400;
	
			RCC->APB2ENR|=(1<<(nb_port+2));
	//configuration de la pin en entrée
			if(	button->pin<8)
	button->gpioPort->CRL &= ~(3 << 4 * pn);
else 
		button->gpioPort->CRH &= ~(3 << 4 * pn);
	
//configuration du type de pull
			if (button->pull==LL_GPIO_PULL_NO) //CF1 CNF0=01
			{
					if(	button->pin<8)
						button->gpioPort->CRL |= (1 << (4 * pn+2));
						else 
						button->gpioPort->CRH |= (1 << (4 * pn+2));
			}	
			if (button->pull==LL_GPIO_PD) //CF1 CNF0=10, ODR=0
			{
					if(	button->pin<8){
						button->gpioPort->CRL &=~ (3 << (4 * pn+2));
						button->gpioPort->CRL |= (2 << (4 * pn+2));
					}
						else {
						button->gpioPort->CRH &=~ (3 << (4 * pn+2));	
						button->gpioPort->CRH |= (2 << (4 * pn+2));
						}
						
						button->gpioPort->ODR&=~(1<<pn);
						
			}	
			
			if (button->pull==LL_GPIO_PU) //CF1 CNF0=10, ODR=1
			{
					if(	button->pin<8){
						button->gpioPort->CRL &=~ (3 << (4 * pn+2));
						button->gpioPort->CRL |= (2 << (4 * pn+2));
					}
						else {
						button->gpioPort->CRH &=~ (3 << (4 * pn+2));	
						button->gpioPort->CRH |= (2 << (4 * pn+2));
						}
						button->gpioPort->ODR|=(1<<pn);					
			}			
}


uint8_t Button_State(BUTTON_TypeDef *button) {
	if((button->gpioPort->IDR & (1<<button->pin))? 1:0 == 1) {
		return 1; //si bouton appuyé = 1
	}
	else {
		return 0; //sinon 0
	}
}

