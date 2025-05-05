#ifndef DS3231_UTILITY_HPP
#define DS3231_UTILITY_HPP

#include <cstdint>

namespace ds3231 {

    struct Time {
        std::uint16_t century;
        std::uint16_t year;
        std::uint16_t month;
        std::uint16_t date;
        std::uint16_t day;
        std::uint16_t hour;
        std::uint16_t minute;
        std::uint16_t second;
    };

}; // namespace ds3231

#endif // DS3231_UTILITY_HPP