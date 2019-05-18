#include "stm32f10x.h"
#include "usart.h"
#include "usart_dma.h"
#include <stdio.h>
#include <string.h>

void delay(void);

u8 USART_RX_BUF[1024]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 

int main(void) 
{
	
	usart_Init(115200);    //���ڳ�ʼ��Ϊ115200
	DMA_Config(DMA1_Channel5, (u32)&USART1->DR, (u32)USART_RX_BUF, 1024);//DMA1ͨ��5,����Ϊ����1��DR�Ĵ���,�洢��ΪSendBuff,����35��
	printf("%s\r\n", "���Դ����������"); //��ӡ
	while (1)
	{
		if(USART_RX_BUF[0])
		{
			delay(); //��DMA�������պ������ݵ�ͬʱ,Ҳ�������������� 
			printf("%s\r\n", USART_RX_BUF); //��ӡ
			memset(USART_RX_BUF, 0, 1024);    //�������
			DMA_Enable(DMA1_Channel5, 1024);//��ʼһ��DMA���䣡
		}
	}
	
}


void delay(void) {
	for(int i=0; i<1000; i++) {
		for(int j=0; j< 500; j++);
	}
}

