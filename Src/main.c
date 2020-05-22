/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

//inclusion des bibliotheques
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "led.h"
#include "button.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//definitios des variables globales 

	LED_TypeDef ledV; //led verte 
	LED_TypeDef ledR; //led rouge
	LED_TypeDef ledO; //led orange 
	LED_TypeDef ledB; //led blanche
	
	BUTTON_TypeDef buttonA; // button A en pull down
	BUTTON_TypeDef buttonB; // button B en pull down
	BUTTON_TypeDef buttonC; // button C en pull down
	BUTTON_TypeDef buttonD; // button D en pull down
	BUTTON_TypeDef buttonE; // button Valider en pull down
	
	uint8_t current_stateA; //pour récupéré l'état du bouton
	uint8_t current_stateB;
	uint8_t current_stateC;
	uint8_t current_stateD;
	uint8_t current_stateE;
	
	uint8_t box_open;//porte ourverte =1, porte fermée =0

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

//définitions des prototypes de nos fonctions

void Led_Polling(LED_TypeDef *led2); //fait clogoter une led passée en parametre
uint8_t checkCombinaison(uint8_t num);//recupère les entrées des boutons dans des variables pour pouoir les tester par la suite
uint8_t testOpenning(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4, uint8_t num5, uint8_t code1, uint8_t code2, uint8_t code3, 
uint8_t code4, uint8_t code5);//test si la combinaison entrée est la bonne (5 c'est la bonne sinon ce n'est pas la bonne)
 

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) //fonction pricipale
{
  /* USER CODE BEGIN 1 */
	
	//code défini par l'user
		uint8_t code1=5;
		uint8_t code2=5;
		uint8_t code3=5;
		uint8_t code4=5;
		uint8_t code5=5;
	
	//boutons représentant le digicode (prends une valeur entre 0 et 3 A=0, B=1, C=2, D=3, E=4)
		uint8_t num1 =5; 
		uint8_t num2 =5; 
		uint8_t num3 =5; 
		uint8_t num4 =5; 
		uint8_t num5 =5; 
	

	
	uint8_t result=0;//variable stockage
	
	box_open =1;//coffre ouvert à l'origine
	
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled 
  */
  LL_GPIO_AF_Remap_SWJ_NOJTAG();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
//initialisation des Led avec les pin auquels elles sont connectées
		Led_init(&ledV, GPIOA, 6);
		Led_init(&ledR, GPIOA, 7);
		Led_init(&ledO, GPIOA, 8);
		Led_init(&ledB, GPIOA, 9);

//on définit les led comme toutes eteintes au début du code par sécurité
		Led_turnOff(&ledV);
		Led_turnOff(&ledR);
		Led_turnOff(&ledO);
		Led_turnOff(&ledB);
	
//initialisation des boutons avec les pin auquels ils sont connectés en pull down
		Button_init(&buttonA, GPIOB, 1,  LL_GPIO_PD);
		Button_init(&buttonB, GPIOB, 2,  LL_GPIO_PD);
		Button_init(&buttonC, GPIOB, 3,  LL_GPIO_PD);
		Button_init(&buttonD, GPIOB, 4,  LL_GPIO_PD);
		Button_init(&buttonE, GPIOB, 5,  LL_GPIO_PD);

//on récupère l'état des boutons	
		current_stateA = Button_State(&buttonA); 
		current_stateB = Button_State(&buttonB); 
		current_stateC = Button_State(&buttonC); 
		current_stateD = Button_State(&buttonD); 
		current_stateE = Button_State(&buttonE); 
		
		box_open = 1;//laporte est ouverte au lancement du code
		
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)//loop infinie
  {
		
		
		if(box_open == 0)//si la porte est fermée
		{
			while(num1==5 || num2==5 ||num3==5 || num4==5 || num5==5)//tant que l'utilisateur n'a pas tapé 5 fois sur un ou plusieurs boutons
			{
				while(num1==5)//tant que l'utilisateur n'a pas tapé 1 fois sur un bouton
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE);
					
					num1=checkCombinaison(num1);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}
				
				while(num2==5)//tant que l'utilisateur n'a pas tapé 2 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					num2=checkCombinaison(num2);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}
				
				while(num3==5)//tant que l'utilisateur n'a pas tapé 3 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					num3=checkCombinaison(num3);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				
				}
				
				while(num4==5)//tant que l'utilisateur n'a pas tapé 4 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					num4=checkCombinaison(num4);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}
				
				while(num5==5)//tant que l'utilisateur n'a pas tapé 5 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					num5=checkCombinaison(num5);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}
			}
			
			result=testOpenning(num1,num2,num3,num4, num5, code1, code2, code3, code4, code5);//on appelle la fonction qui renvoie le nombre de boutons entrés correcte

			if(result == 5)//si toutes les entrées sont correctes (c'est la bonne séquence)
			{
				//on allume la led verte 3 secondes pour montrer que le code tapé est correcte , toutes les autres led sont eteintes par sécurité
				Led_turnOn(&ledV);
				Led_turnOff(&ledR);
				Led_turnOff(&ledB);
				box_open = 1;// on définit la porte comme ouverte 
				LL_mDelay(3000);
				Led_turnOff(&ledV);
				Led_Polling(&ledO);//la led orange clignote pour simuler l'ouverture de la porte
				
			}	
			else
			{
				//on allume la led rouge 3 secondes pour montrer que le code tapé est faux, toutes les autres led sont eteintes par sécurité
				Led_turnOff(&ledV);
				Led_turnOn(&ledR);
				Led_turnOff(&ledB);
				Led_turnOff(&ledO);
				LL_mDelay(3000);
				Led_turnOff(&ledR);		
				
			}
			//reinitialisation des chiffres entrés pour puvoir retenté d'ouvrir le coffre
				num1=5;
				num2=5;
				num3=5;
				num4=5;
				num5=5;
			
			//reinitialisation du compteur pour pouvoir retenté d'ouvrir le coffre et par sécurité
			result=0;
			
		}
		else //box open == 1 ( la porte est ouverte)
		{
	//on allume la led blanche qui signifie qu'on est en train de changer le code et toutes les autres led sont eteintes par securité
			Led_turnOff(&ledV);
			Led_turnOff(&ledR);
			Led_turnOn(&ledB);
			Led_turnOff(&ledO);
			
			//on réinitialise le code pour que l'utilisateur puisse en saisir un nouveau
			code1=5; 
			code2=5; 
			code3=5; 
			code4=5; 
			code5=5; 

			while(code1==5 || code2==5 || code3==5 || code4==5 || code5==5)//l'utilisateur n'a appuyé sur aucun bouton
			{
				
				while(code1==5)//tant que l'utilisateur n'a pas tapé 1 fois sur un bouton
				{
						//on récupère l'état des boutons	
						current_stateA = Button_State(&buttonA); 
						current_stateB = Button_State(&buttonB); 
						current_stateC = Button_State(&buttonC); 
						current_stateD = Button_State(&buttonD); 
						current_stateE = Button_State(&buttonE); 
						
					code1=checkCombinaison(code1);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
					}
				while (code2==5)//tant que l'utilisateur n'a pas tapé 2 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					code2=checkCombinaison(code2);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}		
			
				while(code3==5)//tant que l'utilisateur n'a pas tapé 3 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					code3=checkCombinaison(code3);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}
				
				while(code4==5)//tant que l'utilisateur n'a pas tapé 4 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					code4=checkCombinaison(code4);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}

				while(code5==5)//tant que l'utilisateur n'a pas tapé 5 fois sur un/des bouton(s)
				{
					//on récupère l'état des boutons	
					current_stateA = Button_State(&buttonA); 
					current_stateB = Button_State(&buttonB); 
					current_stateC = Button_State(&buttonC); 
					current_stateD = Button_State(&buttonD); 
					current_stateE = Button_State(&buttonE); 
					
					code5=checkCombinaison(code5);//on appelle la fonction qui renvoie sur quel bouton on a appuyé
				}
			}

			//on fait clignoter la led orange pour simuler la fermeture de la porte et qon éteind la led blanche pour signaler que l'on sort du mode "changement de code", toutes les autres led sont etientes par securite
			Led_turnOff(&ledV);
			Led_turnOff(&ledR);
			Led_turnOff(&ledB);
			Led_Polling(&ledO);
			Led_turnOff(&ledO);			
			box_open = 0;// porte fermée
		}

		
		/* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
    Error_Handler();  
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_4);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
    
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  
  }
  LL_Init1msTick(16000000);
  LL_SetSystemCoreClock(16000000);
}

/* USER CODE BEGIN 4 */

	//fontion qui fait clignoter une led pendant 5sec
	void Led_Polling(LED_TypeDef *led2){
		for(uint8_t i=0; i<5; i++)
		{
			Led_toggle(led2);
			LL_mDelay(1000); 
		}
	}
	
	//fonction qui recupère les entrées des boutons dans des variables pour pouoir les tester par la suite
	uint8_t checkCombinaison(uint8_t num)
	{
					if(current_stateA==1)
					{
						LL_mDelay(1000);
							if(current_stateA==1)
							{
								num=0;
							}
					}
					else if (current_stateB==1)
					{
						LL_mDelay(1000);
							if(current_stateB==1)
							{
								num=1;
							}
					}
					else if (current_stateC==1)
					{
						LL_mDelay(1000);
							if(current_stateC==1)
							{
								num=2;
							}
					}
					else if (current_stateD==1)
					{
						LL_mDelay(1000);
							if(current_stateD==1)
							{
								num=3;
							}
					}
					else if (current_stateE==1)
					{
						LL_mDelay(1000);
							if(current_stateE==1)
							{
								num=4;
							}
					}
				return num;
	}
	
	//fonction qui test si la combinaison entrée est la bonne (5 c'est la bonne sinon ce n'est pas la bonne)
	uint8_t testOpenning(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4, uint8_t num5, uint8_t code1, uint8_t code2, uint8_t code3,
	uint8_t code4, uint8_t code5)
	{
		uint8_t result=0;
		
		if(num1 == code1) 
			{
				result++;
			}
			if(num2 == code2) 
			{
				result++;
			}
			if(num3 == code3) 
			{
				result++;
			}
			if(num4 == code4) 
			{
				result++;
			}
			if(num5 == code5) 
			{
				result++;
			}
		return result;
	}
	
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
