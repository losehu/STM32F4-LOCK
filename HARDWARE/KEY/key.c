#include "key.h"
#include "delay.h"

/**
  ******************************************************************************
  * @file    key.c
  * @author  songqijiang
  * @version V1.0.0
  * @date    6-Aug-2019
  * @brief   This file contains some board support package's functions for the KEY.
  *            
  ******************************************************************************
  * @attention
  *
  * None
	*
  ******************************************************************************
  */
/**
  * @brief  Initialize the RCC of the 8 GPIO line.
  * @param  None  
  * @retval None
  */
void key_Configuration(void)
{
	
	
		GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(C1_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(C2_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(C3_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(C4_GPIO_CLK, ENABLE);

	RCC_AHB1PeriphClockCmd(R1_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(R2_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(R3_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(R4_GPIO_CLK, ENABLE);

	

	//键盘 行
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=R1_PIN;
	GPIO_Init(R1_GPIO_PORT,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=R2_PIN;
	GPIO_Init(R2_GPIO_PORT,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=R3_PIN;
	GPIO_Init(R3_GPIO_PORT,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=R4_PIN;
	GPIO_Init(R4_GPIO_PORT,&GPIO_InitStructure);


    //列
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	 
	
	GPIO_InitStructure.GPIO_Pin=C1_PIN;
	GPIO_Init(C1_GPIO_PORT,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=C2_PIN;
	GPIO_Init(C2_GPIO_PORT,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=C3_PIN;
	GPIO_Init(C3_GPIO_PORT,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=C4_PIN;
	GPIO_Init(C4_GPIO_PORT,&GPIO_InitStructure);	
	
	
}
	
	/**
  * @brief  detect whether the key was pressed down
  * @param  None no key press retun ‘F’
  * @retval None
  */
unsigned char KEY_Scanf(void)
{
  //第一行
  Hang_00_L;
  Hang_01_H;
  Hang_02_H;
  Hang_03_H;

  if(Lie_00_V==0)
  {
  	delay_ms(jpys);
	if(Lie_00_V==0)
  	{
		while(Lie_00_V==0);
		return 1;
			
  	}
  }

  if(Lie_01_V==0)
  {
  	delay_ms(jpys);
	if(Lie_01_V==0)
  	{
			while(Lie_01_V==0);
						return 2;
  	}
  }

  if(Lie_02_V==0)
  {
  	delay_ms(jpys);
	if(Lie_02_V==0)
  	{
		while(Lie_02_V==0);
			return 3;	
  	}
  }

  if(Lie_03_V==0)
  {
  	delay_ms(jpys);
	if(Lie_03_V==0)
  	{
			while(Lie_03_V==0);
	//		printf("A\r\n");
						return 10;
  	}
  }


  //第二行
  Hang_00_H;
  Hang_01_L;
  Hang_02_H;
  Hang_03_H;

  if(Lie_00_V==0)
  {
  	delay_ms(jpys);
	if(Lie_00_V==0)
  	{
		  while(Lie_00_V==0);
						return 4;
  	}
  }

  if(Lie_01_V==0)
  {
  	delay_ms(jpys);
	if(Lie_01_V==0)
  	{
			while(Lie_01_V==0);
					return 5;
  	}
  }

  if(Lie_02_V==0)
  {
  	delay_ms(jpys);
	if(Lie_02_V==0)
  	{
			while(Lie_02_V==0);
						return 6;
  	}
  }

  if(Lie_03_V==0)
  {
  	delay_ms(jpys);
	if(Lie_03_V==0)
  	{
			while(Lie_03_V==0);
						return 11;
  	}
  }

  //第三行
  Hang_00_H;
  Hang_01_H;
  Hang_02_L;
  Hang_03_H;

  if(Lie_00_V==0)
  {
  	delay_ms(jpys);
	if(Lie_00_V==0)
  	{
			while(Lie_00_V==0);
						return 7;
  	}
  }

  if(Lie_01_V==0)
  {
  	delay_ms(jpys);
	if(Lie_01_V==0)
  	{
			while(Lie_01_V==0);
						return 8;
  	}
  }

  if(Lie_02_V==0)
  {
  	delay_ms(jpys);
	if(Lie_02_V==0)
  	{
			while(Lie_02_V==0);
						return 9;
  	}
  }

  if(Lie_03_V==0)
  {
  	delay_ms(jpys);
	if(Lie_03_V==0)
  	{
			while(Lie_03_V==0);
						return 12;
  	}
  }

  //第四行
  Hang_00_H;
  Hang_01_H;
  Hang_02_H;
  Hang_03_L;

  if(Lie_00_V==0)
  {
  	delay_ms(jpys);
	if(Lie_00_V==0)
  	{
			while(Lie_00_V==0);
					return 13;//‘*’
  	}
  }

  if(Lie_01_V==0)
  {
  	delay_ms(jpys);
	if(Lie_01_V==0)
  	{
			while(Lie_01_V==0);
			return 0;
  	}
  }

  if(Lie_02_V==0)
  {
  	delay_ms(jpys);
	if(Lie_02_V==0)
  	{
			while(Lie_02_V==0);
			return 14;//'*';
  	}
  }

  if(Lie_03_V==0)
  {
  	delay_ms(jpys);
	if(Lie_03_V==0)
  	{
			while(Lie_03_V==0);			
			return 15;//'=';
  	}
  }
return 'F';
}







