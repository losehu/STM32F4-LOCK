#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include <string.h>
/*------------------------------------------------
      按键功能图
		|  1  |  2  |  3  | <-  |
		|  4  |  5  |  6  |  C  |
		|  7  |  8  |  9  | Rest|
		|     |  0  |     |  =  |
------------------------------------------------*/
u16 local=1;  //输入模式
u16 sign=0;  //显示模式
char str1[12];
char str3[12];
char str2[12];
unsigned int  KEYCODE=0;                 //定义按键编码
u16 cnt=0;
void Load_Drow_Dialog(void)
{
    LCD_Clear(WHITE);//清屏
    POINT_COLOR=RED;//设置画笔红色
    LCD_DrawRectangle(69,55,265,132);
    LCD_DrawLine(69,80,265,80);
}
//LCD显示程序
void draw()//显示信息
{
    if(sign<=2)
    {
        Load_Drow_Dialog();
        POINT_COLOR=MAGENTA;//设置字体为黄色
        LCD_ShowString(115,60,200,16,16,"Set Passowd");
        POINT_COLOR=BLUE;//设置字体为蓝色
        LCD_ShowString(71,90,200,16,16,"Password:");
        LCD_ShowString(145,90,200,16,16,str1);
        LCD_ShowString(71,110,200,16,16,"Confirm :");
        LCD_ShowString(145,110,200,16,16,str2);
        if(sign==1)
        {
            POINT_COLOR=RED;
            LCD_ShowString(30,150,400,16,16,"The password is inconsistent！！！");
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
        POINT_COLOR=MAGENTA;//设置字体为黄色
        LCD_ShowString(115,60,200,16,16,"Enter Passowd");
        POINT_COLOR=BLACK;//设置字体为蓝色
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

//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz 168Mhz/4=42，Ft=42*2=84Mhz
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟 
//通用==APB1,高级&&9-11==APB2 
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	//预装载寄存器ARR，更新事件之后传给影子寄存器
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
    TIM_Cmd(TIM3,ENABLE); //使能定时器3

    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
    {
        LED2=!LED2;//D2翻转
        draw();	   //显示信息
    }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

void lock()
{
    if(KEYCODE!='F')//按键值不等于F,有键按下
    {
        if(sign==6)
        {
            if(KEYCODE==12)  //重置
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
            if(KEYCODE<=9)  //输密码
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
            if(KEYCODE==11) //清空
            {
                if(local==1) clr(str1);
                else if(local==2) clr(str2);
                else if(local==3) clr(str3);
            }
            else if(KEYCODE==10)//退格
            {
                if(local==1&&cnt>0)       str1[--cnt]='\0';
                else if(local==2&&cnt>0)  str2[--cnt]='\0';
                else if(local==3&&cnt>0)  str3[--cnt]='\0';
            }
            else if(KEYCODE==15) //确认输入
            {
                cnt=0;
                if(local==1)local++;                   //Comfirm:
                else if(local==2)                      //确定设置密码
                {
                    if(strcmp(str1,str2))     //两次输入密码不一致
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
                    if(strcmp(str1,str3))     //密码错误
                    {
                        local=3;
                        clr(str3);
                        sign=4;
                    }
                    else      //密码正确
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
    delay_init(168);	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
    LED_Init();			     //LED端口初始化
    LCD_Init();
    key_Configuration();//键盘初始化  84MHZ/8400=1000HZ
    TIM3_Int_Init(500 - 1, 8400 - 1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，
    //一个周期是0.1ms，计数500次为50ms
	//1K 1ms 
    draw();	   //显示信息
    POINT_COLOR=RED;
    delay_ms(100);
    while(1)
    {
        KEYCODE=KEY_Scanf();
        lock();
    }
}
