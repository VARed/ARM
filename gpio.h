/****************************************************************************
 *   $Id:: gpio.h 4067 2010-07-30 02:23:08Z usb00423                        $
 *   Project: NXP LPC11xx software example
 *
 *   Description:
 *     This file contains definition and prototype for GPIO.
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
#include "type.h"
#include "lpc11xx.h"
#ifndef __GPIO_H 
#define __GPIO_H

#define PORT0		0
#define PORT1		1
#define PORT2		2
#define PORT3		3


static LPC_GPIO_TypeDef (* const LPC_GPIO[4]) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3 };


void GPIOInit( void );
unsigned int GIOGetValue(uint32_t portNum);
void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal );
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir );

#endif /* end __GPIO_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
