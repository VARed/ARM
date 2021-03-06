#include "gpio.h"
#include "led.h"
#include "timer.h"
uint8_t dot[][32] = {	
					0x00,0x40,0x41,0x41,0x4F,0x52,0x64,0x01,
					0x06,0x00,0xFF,0x04,0x02,0x01,0x00,0x00,
					0x80,0x80,0x02,0x01,0xFE,0x20,0x40,0x80,
					0x02,0x01,0xFE,0x00,0x00,0x80,0xC0,0x00,//��
					0x00,0x22,0x22,0x3F,0x62,0x22,0x10,0x12,
					0x12,0xFF,0x12,0x12,0x16,0x32,0x10,0x00,
					0x00,0x08,0x0C,0xF8,0x10,0x50,0x40,0x40,
					0x40,0xFF,0x40,0x44,0x42,0xFC,0x40,0x00,//��
					0x44,0x44,0x54,0x55,0x55,0xF5,0x55,0x5F,
					0x55,0xF5,0x55,0x57,0x55,0xC4,0x44,0x00,
					0x00,0x01,0x05,0xF5,0x55,0x55,0x55,0xFF,
					0x55,0x55,0x55,0xF5,0x05,0x01,0x00,0x00,//��
					0x00,0x00,0x3F,0x22,0x22,0x22,0x22,0xFF,
					0x22,0x22,0x22,0x22,0x7F,0x20,0x00,0x00,
					0x04,0x18,0x00,0x3C,0x02,0x02,0x22,0xDA,
					0x02,0x02,0x02,0x0E,0x00,0x10,0x0C,0x00,//��
					0x22,0x2C,0x28,0x28,0x29,0xF9,0x2A,0x2C,
					0x2A,0xF9,0x29,0x28,0x28,0x6A,0x2C,0x00,
					0x40,0x42,0x82,0xA2,0x2A,0xA6,0xA2,0xFE,
					0xA2,0xA6,0x2A,0xA2,0x86,0xC2,0x80,0x00,//��
					0x01,0x01,0x02,0x04,0x08,0x10,0x20,0xC0,
					0x20,0x10,0x09,0x04,0x02,0x03,0x02,0x00,
					0x00,0x02,0x02,0x82,0x82,0x82,0x82,0xFE,
					0x82,0x82,0x82,0x82,0x06,0x02,0x00,0x00,//��
					0x24,0x24,0x24,0x25,0x7F,0xC5,0x44,0x00,
					0x24,0x12,0x00,0xFF,0x00,0x01,0x00,0x00,
					0x08,0x10,0x60,0x80,0xFF,0x00,0x80,0x40,
					0x40,0x40,0x40,0xFF,0x80,0x80,0x80,0x00,//��
					0x00,0x07,0x09,0x12,0x22,0x22,0x21,0x20,
					0x20,0x21,0x22,0x22,0x12,0x09,0x07,0x00,
					0x00,0xF8,0x04,0x02,0x01,0x11,0x09,0x09,
					0x09,0x09,0x11,0x01,0x02,0x04,0xF8,0x00,//Ц
					0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x00,
					0x00,0x00,0x10,0x10,0x1F,0x10,0x10,0x00,
					0x00,0x00,0x00,0xE0,0x00,0x00,0x08,0x08,
					0x08,0x08,0x00,0x00,0xE0,0x00,0x00,0x00,//��
					0x00,0x0F,0x10,0x21,0x4D,0x4D,0x40,0x40,
					0x40,0x40,0x4D,0x4D,0x21,0x10,0x0F,0x00,
					0x00,0xF0,0x08,0xC4,0x22,0x12,0x92,0x92,
					0x92,0x92,0x12,0x22,0xC4,0x08,0xF0,0x00//Ц
					};

uint8_t number[][8] = {	
						0x00,0x7E,0x83,0x8D,0xB1,0xC1,0x7E,0x00,//0
                        0x00,0x00,0x41,0xFF,0x01,0x00,0x00,0x00,//1
	                    0x00,0x9F,0x91,0x91,0x91,0x91,0xF1,0x00,//2
	                    0x00,0x91,0x91,0x91,0x91,0x91,0xFF,0x00,//3
	                    0x00,0xF0,0x10,0x10,0x10,0x10,0xFF,0x00,//4
	                    0x00,0xF1,0x91,0x91,0x91,0x91,0x9F,0x00,//5
						0x00,0xFF,0x91,0x91,0x91,0x91,0x9F,0x00,//6
						0x00,0x80,0x80,0x80,0x80,0x80,0xFF,0x00,//7
						0x00,0xFF,0x91,0x91,0x91,0x91,0xFF,0x00,//8
						0x00,0xF1,0x91,0x91,0x91,0x91,0xFF,0x00,//9
					  };

void LED_line(uint8_t dotnum,uint8_t data)
{
	uint8_t i;
	for(i=0;i<9;i++)
	{
		if(i!=3&&i!=8)
		{			
			GPIOSetValue(PORT1,i,data>>7);
			data<<=1;
		}
		if(i==8)
		{
			GPIOSetValue(PORT2,i,data>>7);
			data<<=1;
		}
	}
	switch(dotnum)
	{
		case 1:
			 GPIOSetValue(PORT2,3,0);
			 GPIOSetValue(PORT2,3,1);
			 GPIOSetValue(PORT2,3,0);
			 break;
		case 2:
			 GPIOSetValue(PORT3,0,0);
			 GPIOSetValue(PORT3,0,1);
			 GPIOSetValue(PORT3,0,0);
			 break;
		case 3:
			 GPIOSetValue(PORT0,11,0);
			 GPIOSetValue(PORT0,11,1);
			 GPIOSetValue(PORT0,11,0);
			 break;
		case 4:
			 GPIOSetValue(PORT2,11,0);
			 GPIOSetValue(PORT2,11,1);
			 GPIOSetValue(PORT2,11,0);
			 break;	
		case 5:
			 GPIOSetValue(PORT1,10,0);
			 GPIOSetValue(PORT1,10,1);
			 GPIOSetValue(PORT1,10,0);
			 break;
	}		
}
void LED_column(uint8_t data)
{
	uint8_t i;
	for(i=0;i<9;i++)
	{
		if(i!=3&&i!=8)
		{			
			GPIOSetValue(PORT1,i,data>>7);
			data<<=1;
		}
		if(i==8)
		{
			GPIOSetValue(PORT2,i,data>>7);
			data<<=1;
		}
	}
	GPIOSetValue(PORT3,1,0);
	GPIOSetValue(PORT3,1,1);
	GPIOSetValue(PORT3,1,0);	
}

void LED_clean(void)
{
	LED_line(1,0x00);
	LED_line(4,0x00);
 	LED_line(2,0x00);
 	LED_line(3,0x00);
 	LED_line(5,0x00);
	LED_column(0x00);
}

void LED_show(uint8_t data16X16,uint8_t data8X8)
{
	uint8_t i,j;
	T16B0_delay_ms(1000);
	while (LPC_TMR16B0->TCR & 0x01)
	{
		for(i=0;i<40;i+=1)
		{
			LED_clean();
			LED_column((0x80>>(i%8)));
			for(j=0;j<20;j++)
			{				
				(i/8==0)?LED_line(1,number[data8X8][i]):LED_line(i/8+1,dot[data16X16][i-8]);
			}
		}
		LED_clean();
	}
}

void LED_check(void)
{
	uint8_t i;
	LED_column(0xff);
	for(i=0;i<24;i++)
	{	
		T16B0_delay_ms(50);
		while (LPC_TMR16B0->TCR & 0x01)
		{
			LED_line(1,(0x80>>(i%8))&((i<8)?0xff:0x00));
			LED_line(2,(0x80>>(i%8))&((i>=8&&i<16)?0xff:0x00));
			LED_line(3,(0x80>>(i%8))&((i>=8&&i<16)?0xff:0x00));
			LED_line(4,(0x80>>(i%8))&((i>=16&&i<24)?0xff:0x00));
			LED_line(5,(0x80>>(i%8))&((i>=16&&i<24)?0xff:0x00));
		}
	}
}
