#include "lpc11xx.h"
#include "gpio.h"
#include "led.h"
#include "type.h"
#include "timer.h"

uint8_t ID[][11]={2,0,1,8,5,2,2,8,0,0,5,
				  2,0,1,8,5,2,2,8,0,0,3,
				  2,0,1,8,5,2,2,8,0,0,4};

int main()
{ 
	uint8_t i,j;
	GPIOInit( );
	T16B0_init();
	LED_check();
	while(1)
	{ 
		for(j=0;j<3;j++)
			for(i=0;i<11;i++)
				if((i/3)<((j==1)?3:2))
					LED_show(i/3+((j==0)?0:((j==1)?2:5)),ID[j][i]);
				else
					LED_show(7+j,ID[j][i]);	
	}		
}
