/****************************************************************************
 *   $Id:: gpio.c 4068 2010-07-30 02:25:13Z usb00423                        $
 *   Project: NXP LPC11xx GPIO example
 *
 *   Description:
 *     This file contains GPIO code example which include GPIO 
 *     initialization, GPIO interrupt handler, and related APIs for 
 *     GPIO access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "LPC11xx.h"			/* LPC11xx Peripheral Registers */
#include "gpio.h"


void GPIOInit( void )
{	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);// 使能IOCON时钟 
	LPC_IOCON->R_PIO1_0 &= ~0x07;
	LPC_IOCON->R_PIO1_0  |= 0x01;//把P1.0脚设置为GPIO
	LPC_IOCON->R_PIO1_1 &= ~0x07;
	LPC_IOCON->R_PIO1_1  |= 0x01;//把P1.1脚设置为GPIO
	LPC_IOCON->R_PIO1_2 &= ~0x07;
	LPC_IOCON->R_PIO1_2  |= 0x01;//把P1.2脚设置为GPIO
	LPC_IOCON->R_PIO0_11 &=~0x07;
	LPC_IOCON->R_PIO0_11 |= 0x01;//把P0.11脚设置为GPIO

	LPC_GPIO0->DIR |= 0x800;//把P0.11设置为输出引脚
	LPC_GPIO1->DIR |= 0x4ff;//把P1.0 P1.1 P1.2 P1.3 P1.4 P1.5 P1.6 P1.7 P1.10设置为输出引脚
	LPC_GPIO2->DIR |= 0xd0c;//把P2.2 P2.3 P2.8 P2.10 P2.11设置为输出引脚
	LPC_GPIO3->DIR |= 0x003;//把P3.0 P3.1设置为输出引脚
}

unsigned int GIOGetValue(uint32_t portNum)
{
	unsigned int value;
	value = LPC_GPIO[portNum]->DATA;
	return value;
}
/*****************************************************************************
** Function name:		GPIOSetValue
**
** Descriptions:		Set/clear a bitvalue in a specific bit position
**						in GPIO portX(X is the port number.)
**
** parameters:			port num, bit position, bit value
** Returned value:		None
**
*****************************************************************************/
void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal )
{
  LPC_GPIO[portNum]->MASKED_ACCESS[(1<<bitPosi)] = (bitVal<<bitPosi);
}

/*****************************************************************************
** Function name:		GPIOSetDir
**
** Descriptions:		Set the direction in GPIO port
**
** parameters:			port num, bit position, direction (1 out, 0 input)
** Returned value:		None
**
*****************************************************************************/
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir )
{
  if(dir)
	LPC_GPIO[portNum]->DIR |= 1<<bitPosi;
  else
	LPC_GPIO[portNum]->DIR &= ~(1<<bitPosi);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
