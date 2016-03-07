
#include <stdio.h>
#include <stdlib.h>
#include <stm32f30x.h>
#include "diag/Trace.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

//GPIO_InitTypeDef GPIO_Setup;
GPIO_InitTypeDef GPIO_InitStruct;

#define LED_green_ON() 	GPIO_SetBits(GPIOC, GPIO_Pin_11);
#define LED_green_OFF()	GPIO_ResetBits(GPIOC, GPIO_Pin_11);

#define LED_red_ON() 	GPIO_SetBits(GPIOC, GPIO_Pin_10);
#define LED_red_OFF() 	GPIO_ResetBits(GPIOC, GPIO_Pin_10);

#define DC_mainKey_ON() 	loadInstruction(23,1);
#define DC_mainKey_OFF() 	loadInstruction(23,0);

#define DC_mainSwitch_ON() 	loadInstruction(2,1);
#define DC_mainSwitch_OFF()	loadInstruction(2,0);

#define DC_emergency_ON()	loadInstruction(20,1);
#define DC_emergency_OFF()	loadInstruction(20,0);

#define DC_brake_ON()		loadInstruction(1,0);
#define DC_brake_OFF()		loadInstruction(1,1);

#define DC_mode1_ON()		loadInstruction(21,1);
#define DC_mode1_OFF()		loadInstruction(21,0);

#define DC_mode2_ON()		loadInstruction(17,1);
#define DC_mode2_OFF()		loadInstruction(17,0);

#define DC_front_ON()		loadInstruction(19,1);
#define DC_front_OFF()		loadInstruction(19,0);

#define DC_back_ON()		loadInstruction(18,1);
#define DC_back_OFF()		loadInstruction(18,0);


int value=0;

void init_sys()
{
	//	RCC -> CR = HS

	/* Reset the RCC clock configuration to the default reset state ------------*/
	/* Set HSION bit */
//	RCC->CR |= (uint32_t)0x00000001;

	/* Reset CFGR register */
//	RCC->CFGR &= 0xF87FC00C;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB , ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC , ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF , ENABLE);

	// Input Setup --------------------------------------------------------------------------------------
	/*Configure GPIO pins : PA8 PA9 PA10 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 |  GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB12, PB13, PB14, PB15, PB0, PB1, PB2, PB10, PB11 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 |  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins :  */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 |  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	// Output Setup -------------------------------------------------------------------------------------
	/*Configure GPIO pins : PA3 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0, PB1, PB2, PB10, PB11 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PC10 PC11 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PF4 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);

	// Setting up the PE15;
//	GPIOE -> MODER 		|=  0x40000000;
//	GPIOE -> OTYPER 	&= ~(0x7FFFFFFF);
//	GPIOE -> OSPEEDR 	|=  0xC0000000;
//	GPIOE -> PUPDR		&= ~(0x3FFFFFFF);

	// Setting up the PE10;
//	GPIOE -> MODER 		|=  0x00100000;
//	GPIOE -> OTYPER 	&= ~(0xFFFFFBFF);
//	GPIOE -> OSPEEDR 	|=  0x00300000;
//	GPIOE -> PUPDR		&= ~(0xFFCFFFFF);

	// Setting up the PC10;
//	GPIOC -> MODER 		|=   0xFFDFFFFF;
//	GPIOC -> OTYPER 	&=   0x00000400;
//	GPIOC -> OSPEEDR 	= 0x00300000;
//	GPIOC -> PUPDR		= 0x00000000;
}
void loadInstruction(unsigned int load, unsigned int status)
{
	switch (load)
	{
		case 1:
			if(!status)
				GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			else
				GPIO_SetBits(GPIOA, GPIO_Pin_3);
			break;

		case 2:
			if(!status)
				GPIO_ResetBits(GPIOF, GPIO_Pin_4);
			else
				GPIO_SetBits(GPIOF, GPIO_Pin_4);
			break;

		case 3:
			if(!status)
				GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			else
				GPIO_SetBits(GPIOA, GPIO_Pin_5);
			break;

		case 4:
			if(!status)
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			else
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
			break;

		case 5:
			if(!status)
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
			else
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
			break;

		case 6:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_4);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_4);
			break;

		case 7:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_5);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_5);
			break;

		case 8:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
			break;

		case 9:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
			break;

		case 10:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_2);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_2);
			break;

		case 11:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_10);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
			break;

		case 12:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_11);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_11);
			break;

		case 13:
			if(!status)
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			else
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
			break;

		case 14:
			if(!status)
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			else
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
			break;

		case 15:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_3);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_3);
			break;

		case 16:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_2);
			break;

		case 17:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_1);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_1);
			break;

		case 18:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_0);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_0);
			break;

		// PC14 or PF0
		case 19:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_14);
//				GPIO_ResetBits(GPIOF, GPIO_Pin_0);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_14);
//				GPIO_SetBits(GPIOF, GPIO_Pin_0);
			break;

		case 20:
			if(!status)
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			else
				GPIO_SetBits(GPIOC, GPIO_Pin_13);
			break;

		case 21:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;

		case 22:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_8);
			break;

		case 23:
			if(!status)
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);
			else
				GPIO_SetBits(GPIOB, GPIO_Pin_5);
			break;
	}


}
void delay(int var)
{
	int i, n;
	n = var*1000;

	for (i = 0; i < n; i++)
	{
		__asm__("nop");
	}
}
int readIn(int input)
{
	switch (input)
	{
		case 1:
			value = !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10);
			break;

		case 2:
			value = !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
			break;

		case 3:
			value = !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
			break;

		case 4:
			value = !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
			break;

		case 5:
			value = !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
			break;

		case 6:
			value = !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7);
			break;

		case 7:
			value = !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
			break;

		case 8:
			value = !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
			break;

		case 9:
			value = !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
			break;

		case 10:
			value = !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
			break;

		case 11:
			value = !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
			break;

		default:
			break;
	}

	return value;
}
void init_motorDC()
{
	// Fecha a chave principal
//	DC_mainKey_ON();

	// Habilita ou freio. É função de software
//	DC_brake_OFF();

	// Fecha Emergência (NC)
	DC_emergency_OFF();

	// Modo
	DC_mode1_ON();
	DC_mode2_OFF();
}
void stop_motorDC()
{
	// Fecha a chave principal

	// Habilita ou freio. É função de software

	// Modo 1

	// Modo 2

	// Fecha Emergência (NC)
}

int mode = 0;

int main()
{
	init_sys();
	init_motorDC();

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	int in1, in2, in3;
	while (1)
	{
//		for(i=0; i<nInputs; i++)
//		{
//			input[i] = readIn(i+1);
//		}

		in1 = readIn(1);
		in2 = readIn(2);
		in3 = readIn(3);

		if(in1 || in3)
		{
			LED_red_ON();
			LED_green_OFF();
		}
		else
		{
			LED_red_OFF();
			LED_green_ON();
		}



		if(readIn(1))
		{
			// Led Operação
			loadInstruction(9,1);

			// Fecha a chave principal
			DC_mainKey_ON();

			//
			DC_mainSwitch_ON();
			// Habilita ou freio. É função de software
			DC_brake_OFF();
			// Frente
			DC_front_ON();
		}
		else if(readIn(2))
		{
			// Led Operação
			loadInstruction(9,1);

			// Fecha a chave principal
			DC_mainKey_ON();
			// Habilita ou freio. É função de software
			DC_brake_OFF();
			// Frente
			DC_back_ON();
		}
		else
		{
			// Led Operação
			loadInstruction(9,0);

			// Fecha a chave principal
			DC_mainKey_OFF();

			DC_mainSwitch_OFF();
			// Habilita ou freio. É função de software
			DC_brake_ON();
			// Frente
			DC_front_OFF();
			DC_back_OFF();
		}

//		if(readIn(2))
//		{
//			// Led Operação
//			loadInstruction(9,1);
//
//			// Fecha a chave principal
//			DC_mainKey_ON();
//			// Habilita ou freio. É função de software
//			DC_brake_OFF();
//			// Frente
//			DC_back_ON();
//		}
//		else
//		{
//			// Led Operação
//			loadInstruction(9,0);
//
//			// Fecha a chave principal
//			DC_mainKey_OFF();
//			// Habilita ou freio. É função de software
//			DC_brake_ON();
//			// Ré
//			DC_back_OFF();
//		}
	}

	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
