#include "main.h"
#include "ds3231.hpp"
#include "i2c_device.hpp"
#include "usart.h"

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_USART2_UART_Init();

    using namespace DS3231;

    DS3231 ds3231;

    while (1) {
    }
}
