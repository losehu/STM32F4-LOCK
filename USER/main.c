#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include <string.h>
/*------------------------------------------------
      ��������ͼ
		|  1  |  2  |  3  | <-  |
		|  4  |  5  |  6  |  C  |
		|  7  |  8  |  9  | Rest|
		|     |  0  |     |  =  |
------------------------------------------------*/
u16 local=1;  //����ģʽ
u16 sign=0;  //��ʾģʽ
char str1[12];
char str3[12];
char str2[12];
unsigned int  KEYCODE=0;                 //���尴������
u16 cnt=0;
void Load_Drow_Dialog(void)
{
    LCD_Clear(WHITE);//����
    POINT_COLOR=RED;//���û��ʺ�ɫ
    LCD_DrawRectangle(69,55,265,132);
    LCD_DrawLine(69,80,265,80);
}
//LCD��ʾ����
void draw()//��ʾ��Ϣ
{
    if(sign<=2)
    {
        Load_Drow_Dialog();
        POINT_COLOR=MAGENTA;//��������Ϊ��ɫ
        LCD_ShowString(115,60,200,16,16,"Set Passowd");
        POINT_COLOR=BLUE;//��������Ϊ��ɫ
        LCD_ShowString(71,90,200,16,16,"Password:");
        LCD_ShowString(145,90,200,16,16,str1);
        LCD_ShowString(71,110,200,16,16,"Confirm :");
        LCD_ShowString(145,110,200,16,16,str2);
        if(sign==1)
        {
            POINT_COLOR=RED;
            LCD_ShowString(30,150,400,16,16,"The password is inconsistent������");
            sign=0;
            delay_ms(1500);
        }
        if(sign==2)
        {
            POINT_COLOR=GREEN;
            LCD_ShowString(30,150,400,16,16,"OK!Password set successfully!!!");
            sign++;
            delay_ms(1500);
        }
    }
    else if(sign>2&&sign!=6)
    {
        Load_Drow_Dialog();
        POINT_COLOR=MAGENTA;//��������Ϊ��ɫ
        LCD_ShowString(115,60,200,16,16,"Enter Passowd");
        POINT_COLOR=BLACK;//��������Ϊ��ɫ
        LCD_ShowString(71,100,250,16,16,"Password:");
        LCD_ShowString(145,100,250,16,16,str3);
        if(sign==4)
        {
            POINT_COLOR=RED;
            LCD_ShowString(30,150,400,16,16,"Wrong password!!!");
            delay_ms(1500);
            sign--;
        }
        if(sign==5)
        {
            POINT_COLOR=GREEN;
            LCD_ShowString(30,150,400,16,16,"The password is correct!!!");
            delay_ms(1500);
            sign++;
        }

    }
    else if(sign==6)
    {
        LCD_Init();
        POINT_COLOR=GREEN;
        LCD_ShowString(115,60,200,16,16,"Unlocked");
    }
}
void clr(char *p)
{
    int j;
    for(j=strlen(p); j>=0; j--)
    {
        p[j]='\0';
    }
    cnt=0;
}

//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz 168Mhz/4=42��Ft=42*2=84Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ�� 
//ͨ��==APB1,�߼�&&9-11==APB2 
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	//Ԥװ�ؼĴ���ARR�������¼�֮�󴫸�Ӱ�ӼĴ���
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
    TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3

    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
    {
        LED2=!LED2;//D2��ת
        draw();	   //��ʾ��Ϣ
    }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}

void lock()
{
    if(KEYCODE!='F')//����ֵ������F,�м�����
    {
        if(sign==6)
        {
            if(KEYCODE==12)  //����
            {
                local=1;
                sign=0;
                clr(str1);
                clr(str2);
                clr(str3);
            }
        }
        else
        {
            if(KEYCODE<=9)  //������
            {
                if(local==1)
                {
                    if(cnt<10)  str1[cnt++]=48+KEYCODE;
                }
                else if(local==2)
                {
                    if(cnt<10) str2[cnt++]=48+KEYCODE;
                }
                else if(local==3)
                {
                    if(cnt<10) str3[cnt++]=48+KEYCODE;
                }
            }
            if(KEYCODE==11) //���
            {
                if(local==1) clr(str1);
                else if(local==2) clr(str2);
                else if(local==3) clr(str3);
            }
            else if(KEYCODE==10)//�˸�
            {
                if(local==1&&cnt>0)       str1[--cnt]='\0';
                else if(local==2&&cnt>0)  str2[--cnt]='\0';
                else if(local==3&&cnt>0)  str3[--cnt]='\0';
            }
            else if(KEYCODE==15) //ȷ������
            {
                cnt=0;
                if(local==1)local++;                   //Comfirm:
                else if(local==2)                      //ȷ����������
                {
                    if(strcmp(str1,str2))     //�����������벻һ��
                    {
                        local=1;
                        clr(str1);
                        clr(str2);
                        sign=1;
                    }
                    else
                    {
                        local=3;
                        sign=2;
                    }
                }
                else if(local==3)
                {
                    if(strcmp(str1,str3))     //�������
                    {
                        local=3;
                        clr(str3);
                        sign=4;
                    }
                    else      //������ȷ
                    {
                        local=100;
                        cnt=100;
                        sign=5;
                    }
                }
            }
        }
    }
}
int main(void)
{
    delay_init(168);	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
    LED_Init();			     //LED�˿ڳ�ʼ��
    LCD_Init();
    key_Configuration();//���̳�ʼ��  84MHZ/8400=1000HZ
    TIM3_Int_Init(500 - 1, 8400 - 1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�
    //һ��������0.1ms������500��Ϊ50ms
	//1K 1ms 
    draw();	   //��ʾ��Ϣ
    POINT_COLOR=RED;
    delay_ms(100);
    while(1)
    {
        KEYCODE=KEY_Scanf();
        lock();
    }
}
