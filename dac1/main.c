/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stm8l15x.h>

/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Fdac 10000 // частота модуляции Гц
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	volatile int16_t c=2047; // сдвиг по амплитуде
	volatile int16_t ampl=0; // амплитуда начальная 
						int16_t ampl_max=2047; // максимальная амплитуда
	uint8_t flag;
	uint16_t t_line=0;
	uint16_t 	t1=30,//время роста амлиитуды ,c
						t2=30, // время удержания ,c
						t3=240; // время спада ,c
						n1=1, // период роста
						n2=2, // период удержания
						n3=3, // период падения
						Nt=0; // номер периода
	
	volatile static @near uint16_t s[200]= // расчитанные амплитуды
	{
	2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047,
2047

	};

const int16_t sin_tab[]= // таблица синусов
{
	0,
64,
128,
192,
256,
320,
383,
446,
509,
571,
632,
693,
753,
812,
871,
929,
986,
1042,
1096,
1150,
1203,
1254,
1304,
1353,
1401,
1447,
1492,
1535,
1577,
1617,
1656,
1693,
1728,
1761,
1793,
1823,
1852,
1878,
1903,
1925,
1946,
1965,
1982,
1997,
2010,
2021,
2030,
2037,
2042,
2045,
2047,
2045,
2042,
2037,
2030,
2021,
2010,
1997,
1982,
1965,
1946,
1925,
1903,
1878,
1852,
1823,
1793,
1761,
1728,
1693,
1656,
1617,
1577,
1535,
1492,
1447,
1401,
1353,
1304,
1254,
1203,
1150,
1096,
1042,
986,
929,
871,
812,
753,
693,
632,
571,
509,
446,
383,
320,
256,
192,
128,
64,
0,
-65,
-129,
-193,
-257,
-321,
-384,
-447,
-510,
-572,
-633,
-694,
-754,
-813,
-872,
-930,
-987,
-1043,
-1097,
-1151,
-1204,
-1255,
-1305,
-1354,
-1402,
-1448,
-1493,
-1536,
-1578,
-1618,
-1657,
-1694,
-1729,
-1762,
-1794,
-1824,
-1853,
-1879,
-1904,
-1926,
-1947,
-1966,
-1983,
-1998,
-2011,
-2022,
-2031,
-2038,
-2043,
-2046,
-2047,
-2046,
-2043,
-2038,
-2031,
-2022,
-2011,
-1998,
-1983,
-1966,
-1947,
-1926,
-1904,
-1879,
-1853,
-1824,
-1794,
-1762,
-1729,
-1694,
-1657,
-1618,
-1578,
-1536,
-1493,
-1448,
-1402,
-1354,
-1305,
-1255,
-1204,
-1151,
-1097,
-1043,
-987,
-930,
-872,
-813,
-754,
-694,
-633,
-572,
-510,
-447,
-384,
-321,
-257,
-193,
-129,
-65

};

	// Увеличиение период на 1
	void period_inc(void)
	{
		Nt++;
	}
	
	// расчет значений для заданной амплитуды и сдвига
void solve(int16_t amp, int16_t c)
{
	uint8_t i;
	int32_t mul;
	for (i=0; i<200; i++)
	{
		disableInterrupts();
		mul=(int32_t)sin_tab[i];
		mul=(int32_t)amp*mul;
		mul=mul/2047+(int32_t)c;
		s[i]=(uint16_t)mul;
		enableInterrupts();
	}
}
// Расчет периодов роста удержания и падеиня
uint16_t solve_period(uint16_t t)
{
uint32_t temp;
temp=(uint32_t)Fdac*(uint32_t)t;
temp=temp/2047;
return (uint16_t)temp;
}

// получить расчитанное значение из расчитанной таблицы синусов
uint16_t tab(uint8_t sh)
{
return s[sh];
}

void main(void)
{
	//CLK_SYSCLKSourceSwitchCmd(ENABLE); // разрешаем изменение тактирования
   //CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI); //Выбор источн. тактирования
   CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1); // Предделитель
   //CLK_SYSCLKSourceSwitchCmd(DISABLE); // Запрет изменения ист. тактиров
   
	 // настраиваем ножку контроллера на в вывод
	GPIO_Init(GPIOC, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast); 
	GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_FL_No_IT);
  // настроиваем пин РС4 на выход частоты процессора деленного на 64
	CLK_CCOConfig(CLK_CCOSource_HSI, CLK_CCODiv_64); //
	
	//------Настройка таймера-------///
	//Включаем тактирование таймера
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
	// На всякий случай сбрасываем все настройки таймера
	TIM4_DeInit();
	// настраивем пределитель таймера на 256 и ограничиваем счет 124
	TIM4_TimeBaseInit(TIM4_Prescaler_32,
                       49);
	//Разрешаем Прервание таймера по переполнению
	TIM4_ITConfig(TIM4_IT_Update, ENABLE);
	// Включаем счет
	TIM4_Cmd(ENABLE);
	//----------------------------------------------
	
	CLK_PeripheralClockConfig(CLK_Peripheral_DAC, ENABLE);
	DAC_Init(DAC_Channel_1,
              DAC_Trigger_Software,
              DAC_OutputBuffer_Enable);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	
	
	// hfcxb
	//solve(ampl,c);
	n1=solve_period(t1);
	n2=solve_period(t2);
	n3=solve_period(t3);
	//Включаем глобальное разрешение прерывания
	enableInterrupts();
		
	/* Infinite loop */
  while (1)
  {
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)==0) 
			{
				while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)==0);
				GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
				flag=1;
				t_line=0;
				while(flag)
				{
					switch(flag)
					{
					case 1: 
							if (Nt>n1) 	{
													Nt=0;
													solve(ampl,c);
													ampl++;
													if (ampl>ampl_max) 	{
																							ampl=ampl_max;
																							flag=2;
																							}
													}
						break;
					case 2:
							if (Nt>Fdac) {
															Nt=0;
															t_line++;
															if (t_line>t2) flag=3;
														}
						break;
					case 3:
						if (Nt>n3) 	{
													Nt=0;
													ampl--;
													solve(ampl,c);
													if (ampl== 0) {	
																					flag=0;
																					t_line=0;
																				}
												}
					
						break;
					}
				}
			
				GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
			}		
		
	}
	
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
