#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f4xx.h" 
#include "sys.h" 
#include "stdio.h"
#include "misc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
/**
  ******************************************************************************
  * @file    key.h
  * @author  liyang; songqijiang
  * @version V1.0.0
  * @date    23-Jan-2019
  * @brief   This file contains some board support package's definition for the KEY.
  *            
  ******************************************************************************
  * @attention
  *ɨ�跽��
  * ��������Ϊ������͵�ƽ�����������루�����ⲿ����ʱ���ָߵ�ƽ����
  * ��⵽�������£���ʱͨ������еĵ�ƽ����Ӷ���֪��һ���а��������£�
  * Ȼ��ȷ���а��������º�����Ϊ������͵�ƽ�����������룻
  * ͨ������еĵ�ƽ����Ӷ���֪��һ���а��������£�
  * ���ͨ������ƽ�е�����ֱ���ཻ��һ�㡱ԭ����֪���屻���µİ���
	*��Ӧ�Ķ˿��ǣ�[PC4��PA6��PA4��PA2]��[PA0��PC2��PC0��PF9]����Ӧ��Row1, Row2, Row3, Row4
	*Column1, Column2, Column3, Column4�� 4*4��Ĥ�����ӿڣ��������棬������R1-R4��C1-C4��
	 */
	  	/*------------------------------------------------
          ����ֵ������������ɨ��ֵ
           ���Ը�����Ҫ�ı䷵��ֵ

  			| 1 | 2 | 3 | 10|  
  			| 4 | 5 | 6 | 11|  
  			| 7 | 8 | 9 | 12|  
  			| 14| 0 | 15| 13|

  ******************************************************************************
  */
// Row1, Row2, Row3, Row4
#define R1_PIN             GPIO_Pin_4
#define R1_GPIO_PORT       GPIOC
#define R1_GPIO_CLK        RCC_AHB1Periph_GPIOC

#define R2_PIN             GPIO_Pin_6
#define R2_GPIO_PORT       GPIOA
#define R2_GPIO_CLK        RCC_AHB1Periph_GPIOA

#define R3_PIN             GPIO_Pin_4
#define R3_GPIO_PORT       GPIOA
#define R3_GPIO_CLK        RCC_AHB1Periph_GPIOA

#define R4_PIN             GPIO_Pin_2
#define R4_GPIO_PORT       GPIOA
#define R4_GPIO_CLK        RCC_AHB1Periph_GPIOA

// Column1, Column2, Column3, Column4
#define C1_PIN             GPIO_Pin_0
#define C1_GPIO_PORT       GPIOA
#define C1_GPIO_CLK        RCC_AHB1Periph_GPIOA

#define C2_PIN             GPIO_Pin_2
#define C2_GPIO_PORT       GPIOC
#define C2_GPIO_CLK        RCC_AHB1Periph_GPIOC

#define C3_PIN             GPIO_Pin_0
#define C3_GPIO_PORT       GPIOC
#define C3_GPIO_CLK        RCC_AHB1Periph_GPIOC

#define C4_PIN             GPIO_Pin_9
#define C4_GPIO_PORT       GPIOF
#define C4_GPIO_CLK        RCC_AHB1Periph_GPIOF

// detect and output
#define Hang_00_L GPIO_ResetBits(R1_GPIO_PORT,R1_PIN)
#define Hang_00_H GPIO_SetBits(R1_GPIO_PORT,R1_PIN)

#define Hang_01_L GPIO_ResetBits(R2_GPIO_PORT,R2_PIN)
#define Hang_01_H GPIO_SetBits(R2_GPIO_PORT,R2_PIN)

#define Hang_02_L GPIO_ResetBits(R3_GPIO_PORT,R3_PIN)
#define Hang_02_H GPIO_SetBits(R3_GPIO_PORT,R3_PIN)

#define Hang_03_L GPIO_ResetBits(R4_GPIO_PORT,R4_PIN)
#define Hang_03_H GPIO_SetBits(R4_GPIO_PORT,R4_PIN)

#define Lie_00_V GPIO_ReadInputDataBit(C1_GPIO_PORT,C1_PIN)
#define Lie_01_V GPIO_ReadInputDataBit(C2_GPIO_PORT,C2_PIN)
#define Lie_02_V GPIO_ReadInputDataBit(C3_GPIO_PORT,C3_PIN)
#define Lie_03_V GPIO_ReadInputDataBit(C4_GPIO_PORT,C4_PIN)

#define jpys 20
void key_Configuration(void);
unsigned char KEY_Scanf(void);
#endif
