#include "usart.h"
#include <stdio.h>

// 串口初始化
void usart_Init(u32 bound) 
{
  GPIO_InitTypeDef GPIO_InitStructure;     // GPIO 端口设置
  USART_InitTypeDef USART_InitStructure;   // 串口
  // NVIC_InitTypeDef NVIC_InitStructure;     // NVIC 中断向量
  RCC_APB2PeriphClockCmd(USARTx_Clock | USARTx_Port_Clock, ENABLE);  // //使能USARTx，GPIOA时钟

  // TX
  GPIO_InitStructure.GPIO_Pin = USARTx_TX_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // 复用推挽输出
  GPIO_Init(USARTx_GPIOx, &GPIO_InitStructure);     
  
  // RX
  GPIO_InitStructure.GPIO_Pin = USARTx_RX_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_Init(USARTx_GPIOx, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = bound;  // 串口波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;  // 8 位
  USART_InitStructure.USART_Parity = USART_Parity_No;       // N 无校验位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;  // 1 位停止位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // 串口收发模式

  USART_Init(USARTx_, &USART_InitStructure);        // 初始化串口
  USART_DMACmd(USARTx_, USART_DMAReq_Rx, ENABLE);   // 使能串口1的DMA发送
}

/*****************************************************
*function:	写字符文件函数
*param1:	输出的字符
*param2:	文件指针
*return:	输出字符的ASCII码
******************************************************/
int fputc(int ch, FILE *f)
{
	while(USART_GetFlagStatus(USARTx_, USART_FLAG_TC) == RESET);		//等待上次发送结束
	USART_SendData(USARTx_, (unsigned char)ch);				//发送数据到串口
	return ch;
}

