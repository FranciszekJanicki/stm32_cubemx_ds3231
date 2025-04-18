#ifndef DS3231_CONFIG_HPP
#define DS3231_CONFIG_HPP

#include "ds3231_registers.hpp"
#include "i2c_device.hpp"
#include <cstdint>

namespace DS3231 {

    using I2CDevice = STM32_Utility::I2CDevice;

    enum struct RA : std::uint8_t {
        SECOND = 0x00,
        MINUTE = 0x01,
        HOUR = 0x02,
        DAY = 0x03,
        DATE = 0x04,
        MONTH_CENTURY = 0x05,
        YEAR = 0x06,
        ALARM1_SECOND = 0x07,
        ALARM1_MINUTE = 0x08,
        ALARM1_HOUR = 0x09,
        ALARM1_DAY = 0x0A,
        ALARM1_DATE = 0x0A,
        ALARM2_MINUTE = 0x0B,
        ALARM2_HOUR = 0x0C,
        ALARM2_DAY = 0x0D,
        ALARM2_DATE = 0x0D,
        CONTROL = 0x0E,
        STATUS = 0x0F,
        AGING_OFFSET = 0x10,
        TEMP_MSB = 0x11,
        TEMP_LSB = 0x12,
    };

    enum struct Alarm1 : std::uint8_t {
        EVERY_SECOND = 0b1111,
        SEC_MATCH = 0b1110,
        MIN_SEC_MATCH = 0b1100,
        HR_MIN_SEC_MATCH = 0b1000,
        DATE_HR_MIN_SEC_MATCH = 0b0000,
        DAY_HR_MIN_SEC_MATCH = 0b0000,
    };

    enum struct Alarm2 : std::uint8_t {
        EVERY_MINUTE = 0b111,
        MIN_MATCH = 0b110,
        HR_MIN_MATCH = 0b100,
        DATE_HR_MIN_MATCH = 0b000,
        DAY_HR_MIN_MATCH = 0b000,
    };

    enum struct RateSelect : std::uint8_t {
        RATE_1HZ0 = 0b00,
        RATE_1KHZ024 = 0b01,
        RATE_4KHZ096 = 0b10,
        RATE_8KHZ192 = 0b11,
    };

    struct Config {
        CONTROL control = {};
        STATUS status = {};
        AGING_OFFSET aging_offset = {};
    };

}; // namespace DS3231

#endif // DS3231_CONFIG_HPP