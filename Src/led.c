#include "led.h"

void Led_init(LED_TypeDef *led, GPIO_TypeDef * port, uint8_t pn){

	led->gpioPort=port;
	led->pin=pn;

	//déterminer le numéro du port 0--> GPIOA, 1-->GPIOB, etc.
	uint8_t nb_port;
	nb_port=(uint32_t)((uint32_t *)port - GPIOA_BASE)/ (uint32_t)0x400;
	//activation de l'hologe
RCC->APB2ENR|=(1<<(nb_port+2));

	//configuration de la pin en sortie
	if(	led->pin<8){
	led->gpioPort->CRL &= ~(3 << (4 * pn+2));	//CNF1 CNF0 = 00
	led->gpioPort->CRL &= ~(3 << 4 * pn);
	led->gpioPort->CRL |= (1 << 4 * pn);	
	}
else {
	  led->gpioPort->CRH &= ~(3 << (4 * pn+2));	//CNF1 CNF0 = 00
		led->gpioPort->CRH &= ~(3 << 4 * pn);
	  led->gpioPort->CRH |= (1 << 4 * pn);	
}
}


void Led_turnOn(LED_TypeDef *led){//allumer une led passée en parametre
	led->gpioPort->ODR |=(1 << led->pin); 
}


void Led_turnOff(LED_TypeDef *led){//eteindre une led passée en parametre
	led->gpioPort->ODR &=~(1<<led->pin); 
}

void Led_toggle(LED_TypeDef *led){//inverser l'état d'une led passée en parametre
	led->gpioPort->ODR^=(1<<led->pin);
}

uint8_t Led_isOn(LED_TypeDef *led){//retourne 1 si la led passée en parametre est allumée, 0 sinon
	if((led->gpioPort->ODR & (1 << led->pin)) == 0){
		return 1;
	}
	else {
		return 0;
	}
}

uint8_t Led_isOff(LED_TypeDef *led){//retourne 1 si la led passée en parametre est éteinte, 0 sinon
	if((led->gpioPort->ODR & (1 << led->pin)) == 1){
		return 1;
	}
	else {
		return 0;
	}
}
