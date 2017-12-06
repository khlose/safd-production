/**
  ******************************************************************************
  * File Name          : main.hpp
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define OLED_CS_Pin GPIO_PIN_12
#define OLED_CS_GPIO_Port GPIOB
#define LED_D4_Pin GPIO_PIN_13
#define LED_D4_GPIO_Port GPIOB
#define LED_D5_Pin GPIO_PIN_14
#define LED_D5_GPIO_Port GPIOB
#define WIFI_ENABLE_Pin GPIO_PIN_15
#define WIFI_ENABLE_GPIO_Port GPIOB
#define ARROW_LEFT_Pin GPIO_PIN_9
#define ARROW_LEFT_GPIO_Port GPIOC
#define ARROW_RIGHT_Pin GPIO_PIN_10
#define ARROW_RIGHT_GPIO_Port GPIOA
#define BUTTON_B_Pin GPIO_PIN_11
#define BUTTON_B_GPIO_Port GPIOA
#define BUTTON_A_Pin GPIO_PIN_12
#define BUTTON_A_GPIO_Port GPIOA
#define OLED_DC_Pin GPIO_PIN_2
#define OLED_DC_GPIO_Port GPIOD
#define OLED_RST_Pin GPIO_PIN_5
#define OLED_RST_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define USER_LED_PORT GPIOB
#define LED_D3_PORT USER_LED_PORT
#define LED_D4_PORT USER_LED_PORT
#define LED_D5_PORT USER_LED_PORT

#define LED_D3_PIN GPIO_PIN_12
#define LED_D4_PIN GPIO_PIN_13
#define LED_D5_PIN GPIO_PIN_14

#define UI_SW1_PORT GPIOC
#define UI_SW1_PIN GPIO_PIN_9
#define UI_SW2_PORT GPIOA
#define UI_SW2_PIN GPIO_PIN_8
#define UI_SW3_PORT GPIOA
#define UI_SW3_PIN GPIO_PIN_9
#define UI_SW4_PORT GPIOA
#define UI_SW4_PIN GPIO_PIN_10
#define UI_SW5_PORT GPIOA
#define UI_SW5_PIN GPIO_PIN_11
#define UI_SW6_PORT GPIOA
#define UI_SW6_PIN GPIO_PIN_12

#define BUZZER_PORT GPIOB
#define BUZZER_PIN GPIO_PIN_7

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
