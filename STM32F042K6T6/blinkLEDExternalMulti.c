#include "stm32f0xx_hal.h"

// Function prototypes
static void SystemClock_Config(void);
static void Error_Handler(void);
static void GPIO_Init(void);

int main(void)
{
    // Initialize HAL library
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize GPIO
    GPIO_Init();

    while (1)
    {
        // Toggle external LEDs connected to PA0 and PA1 alternately
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);

        // Delay for a while
        HAL_Delay(500); // Delay 500ms
    }
}

// System Clock Configuration
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    // Configure the oscillator (HSI)
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    // Configure the system clock (HSI as clock source)
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

// GPIO Initialization
void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure PA0 and PA1 as outputs
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// Error Handler
void Error_Handler(void)
{
    // User code can go here to handle errors
    while(1)
    {
    }
}
