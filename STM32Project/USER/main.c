#include "stm32f10x.h"
#include "usart.h"
#include "usart_dma.h"
#include <stdio.h>
#include <string.h>

void delay(void);

u8 USART_RX_BUF[1024]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 

int main(void) 
{
	
	usart_Init(115200);    //串口初始化为115200
	DMA_Config(DMA1_Channel5, (u32)&USART1->DR, (u32)USART_RX_BUF, 1024);//DMA1通道5,外设为串口1的DR寄存器,存储器为SendBuff,长度35，
	printf("%s\r\n", "测试串口输出方法"); //打印
	while (1)
	{
		if(USART_RX_BUF[0])
		{
			delay(); //让DMA继续接收后面数据的同时,也能跑跑其它进程 
			printf("%s\r\n", USART_RX_BUF); //打印
			memset(USART_RX_BUF, 0, 1024);    //清空数组
			DMA_Enable(DMA1_Channel5, 1024);//开始一次DMA传输！
		}
	}
	
}


void delay(void) {
	for(int i=0; i<1000; i++) {
		for(int j=0; j< 500; j++);
	}
}

