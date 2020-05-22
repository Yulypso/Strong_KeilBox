#include "stm32f103xb.h"
#define LL_GPIO_PULL_NO 0
#define LL_GPIO_PD 1
#define LL_GPIO_PU 2
typedef struct
{
GPIO_TypeDef * gpioPort;
uint8_t pin;
uint8_t pull;

}BUTTON_TypeDef;//structure d'un bouton

void Button_init(BUTTON_TypeDef *button, GPIO_TypeDef * port, uint8_t pn, uint8_t pl);//initialisation d'un boutons avec les caracteristiques passées en parametre

uint8_t Button_State(BUTTON_TypeDef *button);//retourne 1 si le bouton en parametre est appuyé,0 sinon

