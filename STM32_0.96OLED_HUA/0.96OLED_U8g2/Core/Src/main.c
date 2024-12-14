/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32_u8g2.h"
#include "test.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE BEGIN PV */
/* 奈(0) */
static const unsigned char nai0[] = {
    0x40, 0x00, 0x40, 0x00, 0xFE, 0x3F, 0x20, 0x02, 0x10, 0x04, 0x0C, 0x18, 0xF3, 0x67, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0x3F, 0x80, 0x00, 0x88, 0x08, 0x88, 0x10, 0x84, 0x20, 0xA2, 0x20, 0x40, 0x00
};

/* 奈(1) */
static const unsigned char nai1[] = {
    0x40, 0x00, 0x40, 0x00, 0xFE, 0x3F, 0x20, 0x02, 0x10, 0x04, 0x0C, 0x18, 0xF3, 0x67, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0x3F, 0x80, 0x00, 0x88, 0x08, 0x88, 0x10, 0x84, 0x20, 0xA2, 0x20, 0x40, 0x00
};

/* 生(2) */
static const unsigned char sheng[] = {
    0x80, 0x00, 0x88, 0x00, 0x88, 0x00, 0x88, 0x00, 0xFC, 0x3F, 0x84, 0x00, 0x82, 0x00, 0x81, 0x00,
    0x80, 0x00, 0xFC, 0x1F, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xFF, 0x7F, 0x00, 0x00
};

/* 日(3) */
static const unsigned char ri[] = {
    0x00, 0x00, 0xF8, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xF8, 0x0F,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xF8, 0x0F, 0x08, 0x08
};

/* 快(4) */
static const unsigned char kuai[] = {
    0x08, 0x02, 0x08, 0x02, 0x08, 0x02, 0xC8, 0x1F, 0x18, 0x12, 0x2A, 0x12, 0x0A, 0x12, 0x0A, 0x12,
    0xE9, 0x7F, 0x08, 0x02, 0x08, 0x05, 0x08, 0x05, 0x88, 0x08, 0x88, 0x08, 0x48, 0x10, 0x28, 0x60
};

/* 乐(5) */
static const unsigned char le[] = {
    0x00, 0x04, 0x00, 0x0F, 0xF8, 0x00, 0x08, 0x00, 0x88, 0x00, 0x84, 0x00, 0x84, 0x00, 0xFC, 0x3F,
    0x80, 0x00, 0x90, 0x04, 0x90, 0x08, 0x88, 0x10, 0x84, 0x20, 0x82, 0x20, 0xA0, 0x00, 0x40, 0x00
};
/* USER CODE END PV */ 
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  unsigned int x = 0; // 初始横坐标设置为0
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  u8g2_t u8g2;
  u8g2Init(&u8g2);  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // 清屏
    u8g2_ClearBuffer(&u8g2);

    // 更新横坐标x，实现左右滑动
    if (x <= -16 * 6) // 6个汉字，每个汉字宽度为16像素，负值使得字符从右向左移动
    {
        x--; // 向左移动
    }
    else if (x > 128) // 如果x超过OLED屏幕宽度，从左端开始
    {
        x = 128; // 重置x为屏幕宽度，实现循环滑动
    }

    // 设置字体
    u8g2_SetFont(&u8g2, u8g2_font_ncenB12_tf);

    // 绘制汉字“奈奈生日快乐”
    u8g2_DrawXBMP(&u8g2, x, 0, 16, 16, nai0); // 奈
    u8g2_DrawXBMP(&u8g2, x + 16, 0, 16, 16, nai1); // 奈
    u8g2_DrawXBMP(&u8g2, x + 32, 0, 16, 16, sheng); // 生
    u8g2_DrawXBMP(&u8g2, x + 48, 0, 16, 16, ri); // 日
    u8g2_DrawXBMP(&u8g2, x + 64, 0, 16, 16, kuai); // 快
    u8g2_DrawXBMP(&u8g2, x + 80, 0, 16, 16, le); // 乐

    // 发送缓冲区数据到OLED
    u8g2_SendBuffer(&u8g2);
    /* USER CODE END 3 */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
