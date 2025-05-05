#include "main.h"
#include "ds3231.hpp"
#include "i2c.h"
#include "usart.h"
#include <cassert>
#include <utility>

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_USART2_UART_Init();

    using namespace ds3231;

    auto aging_offset = AGING_OFFSET{};

    auto control = CONTROL{};

    auto status = STATUS{};

    auto interface =
        Interface{.user = &hi2c1,
                  .init = nullptr,
                  .deinit = nullptr,
                  .write =
                      [](void* const user,
                         std::uint8_t const address,
                         std::uint8_t const* const data,
                         std::size_t const size) {
                          auto handle = static_cast<I2C_HandleTypeDef*>(user);
                          assert(HAL_OK == HAL_I2C_Mem_Write(handle,
                                                             SLAVE_ADDRESS << 1,
                                                             address,
                                                             I2C_MEMADD_SIZE_8BIT,
                                                             const_cast<std::uint8_t* const>(data),
                                                             size,
                                                             100));
                      },
                  .read =
                      [](void* const user,
                         std::uint8_t const address,
                         std::uint8_t* const data,
                         std::size_t const size) {
                          auto handle = static_cast<I2C_HandleTypeDef*>(user);
                          assert(HAL_OK == HAL_I2C_Mem_Read(handle,
                                                            SLAVE_ADDRESS << 1,
                                                            address,
                                                            I2C_MEMADD_SIZE_8BIT,
                                                            data,
                                                            size,
                                                            100));
                      },
                  .delay = [](void* const user, std::uint32_t const delay) { HAL_Delay(delay); }};

    auto ds3231 = DS3231{.interface = interface};

    auto config = Config{};

    ds3231.initialize(config);

    while (1) {
    }
}
