#include "stm32f103xb.h"

typedef struct
{
GPIO_TypeDef * gpioPort;//port correspondant à la led 
uint8_t pin;//pin correspondant à la led 

}LED_TypeDef;//structure d'une led

void Led_init(LED_TypeDef *led, GPIO_TypeDef * port, uint8_t pn);//initialisation d'une led

void Led_turnOn(LED_TypeDef *led);//allumer une led passée en parametre
void Led_turnOff(LED_TypeDef *led);//eteindre une led passée en parametre
void Led_toggle(LED_TypeDef *led);//inverser l'etat d'une led passée en parametre

uint8_t Led_isOn(LED_TypeDef *led);//retourne 1 si la led passée en parametre est allumée, 0 sinon
uint8_t Led_isOff(LED_TypeDef *led);//retourne 1 si la led passée en parametre est éteinte, 0 sinon

