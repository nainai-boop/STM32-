#include "stm32f10x.h"                  // Device header
#include "OLED.h"
//编码格式：UTF-8

int main(void)
{
	  
	  OLED_Init();
	  
	  OLED_ShowChinese(28,0,"奈奈团子");
	  OLED_Printf(0,16,OLED_8X16,"%d",6);
	  OLED_Printf(8,16,OLED_8X16,"%d",3);
	  OLED_Printf(16,16,OLED_8X16,"%d",2);
	  OLED_Printf(24,16,OLED_8X16,"%d",2);
	  OLED_Printf(32,16,OLED_8X16,"%d",0);
	  OLED_Printf(40,16,OLED_8X16,"%d",2);
	  OLED_Printf(48,16,OLED_8X16,"%d",0);
	  OLED_Printf(56,16,OLED_8X16,"%d",6);
	  OLED_Printf(64,16,OLED_8X16,"%d",0);
	  OLED_Printf(72,16,OLED_8X16,"%d",2);
	  OLED_Printf(80,16,OLED_8X16,"%d",1);
	  OLED_Printf(88,16,OLED_8X16,"%d",4);
	
	  OLED_Update();

	
	while (1)
	{
		
	}
}
