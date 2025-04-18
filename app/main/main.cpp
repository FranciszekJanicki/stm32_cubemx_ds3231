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

    auto i2c_device = I2CDevice{};
    i2c_device.bus_scan();

    auto aging_offset = AGING_OFFSET{.offset = 0};

    auto control = CONTROL{};

    auto status = STATUS{};

    auto config = Config{.control = control, .status = status, .aging_offset = aging_offset};

    auto ds3231 = DS3231{std::move(i2c_device), config};

    while (1) {
    }
}
