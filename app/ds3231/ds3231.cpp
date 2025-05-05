#include "ds3231.hpp"
#include "ds3231_utility.hpp"
#include <utility>

namespace ds3231 {

    void DS3231::initialize(this DS3231& self, Config const& config) noexcept
    {
        self.set_control_register(config.control);
        self.set_status_register(config.status);
        self.set_aging_offset_register(config.aging_offset);
    }

    void DS3231::deinitialize(this DS3231& self) noexcept
    {
        (void)self;
    }

    Time DS3231::get_time(this DS3231 const& self) noexcept
    {
        return Time{.century = self.get_century(),
                    .year = self.get_year(),
                    .month = self.get_month(),
                    .date = self.get_date(),
                    .day = self.get_day(),
                    .hour = self.get_hour(),
                    .minute = self.get_minute(),
                    .second = self.get_second()};
    }

    std::uint16_t DS3231::get_century(this DS3231 const& self) noexcept
    {
        auto reg = self.get_month_century_register();
        return reg.century ? 21 : 20;
    }

    std::uint16_t DS3231::get_year(this DS3231 const& self) noexcept
    {
        auto reg = self.get_year_register();
        return reg.ten_year * 10U + reg.year;
    }

    std::uint16_t DS3231::get_month(this DS3231 const& self) noexcept
    {
        auto reg = self.get_month_century_register();
        return reg.ten_month * 10U + reg.month;
    }

    std::uint16_t DS3231::get_date(this DS3231 const& self) noexcept
    {
        auto reg = self.get_date_register();
        return reg.ten_date * 10U + reg.date;
    }

    std::uint16_t DS3231::get_day(this DS3231 const& self) noexcept
    {
        auto reg = self.get_day_register();
        return reg.day;
    }

    std::uint16_t DS3231::get_hour(this DS3231 const& self) noexcept
    {
        auto reg = self.get_hour_register();
        return reg.ten_hour * 10U + reg.hour;
    }

    std::uint16_t DS3231::get_minute(this DS3231 const& self) noexcept
    {
        auto reg = self.get_minute_register();
        return reg.ten_minute * 10U + reg.minute;
    }

    std::uint16_t DS3231::get_second(this DS3231 const& self) noexcept
    {
        auto reg = self.get_second_register();
        return reg.ten_second * 10U + reg.second;
    }

    CONTROL DS3231::get_control_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<CONTROL>(
            self.read<sizeof(CONTROL)>(std::to_underlying(RegAddr::CONTROL)));
    }

    void DS3231::set_control_register(this DS3231 const& self, CONTROL const reg) noexcept
    {
        self.write(std::to_underlying(RegAddr::CONTROL),
                   std::bit_cast<std::array<std::uint8_t, sizeof(CONTROL)>>(reg));
    }

    STATUS DS3231::get_status_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<STATUS>(
            self.read<sizeof(STATUS)>(std::to_underlying(RegAddr::STATUS)));
    }

    void DS3231::set_status_register(this DS3231 const& self, STATUS const reg) noexcept
    {
        self.write(std::to_underlying(RegAddr::STATUS),
                   std::bit_cast<std::array<std::uint8_t, sizeof(STATUS)>>(reg));
    }

    AGING_OFFSET DS3231::get_aging_offset_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<AGING_OFFSET>(
            self.read<sizeof(AGING_OFFSET)>(std::to_underlying(RegAddr::AGING_OFFSET)));
    }

    void DS3231::set_aging_offset_register(this DS3231 const& self, AGING_OFFSET const reg) noexcept
    {
        self.write(std::to_underlying(RegAddr::AGING_OFFSET),
                   std::bit_cast<std::array<uint8_t, sizeof(AGING_OFFSET)>>(reg));
    }

    TEMP DS3231::get_temp_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<TEMP>(self.read<sizeof(TEMP)>(std::to_underlying(RegAddr::TEMP_MSB)));
    }

    SECOND DS3231::get_second_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<SECOND>(
            self.read<sizeof(SECOND)>(std::to_underlying(RegAddr::SECOND)));
    }

    MINUTE DS3231::get_minute_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<MINUTE>(
            self.read<sizeof(MINUTE)>(std::to_underlying(RegAddr::MINUTE)));
    }

    HOUR DS3231::get_hour_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<HOUR>(self.read<sizeof(HOUR)>(std::to_underlying(RegAddr::HOUR)));
    }

    DAY DS3231::get_day_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<DAY>(self.read<sizeof(DAY)>(std::to_underlying(RegAddr::DAY)));
    }

    DATE DS3231::get_date_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<DATE>(self.read<sizeof(DATE)>(std::to_underlying(RegAddr::DATE)));
    }

    MONTH_CENTURY DS3231::get_month_century_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<MONTH_CENTURY>(
            self.read<sizeof(MONTH_CENTURY)>(std::to_underlying(RegAddr::MONTH_CENTURY)));
    }

    YEAR DS3231::get_year_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<YEAR>(self.read<sizeof(YEAR)>(std::to_underlying(RegAddr::YEAR)));
    }

    ALARM1_SECOND DS3231::get_alarm1_second_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_SECOND>(
            self.read<sizeof(ALARM1_SECOND)>(std::to_underlying(RegAddr::ALARM1_SECOND)));
    }

    ALARM1_MINUTE DS3231::get_alarm1_minute_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_MINUTE>(
            self.read<sizeof(ALARM1_MINUTE)>(std::to_underlying(RegAddr::ALARM1_MINUTE)));
    }

    ALARM1_HOUR DS3231::get_alarm1_hour_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_HOUR>(
            self.read<sizeof(ALARM1_HOUR)>(std::to_underlying(RegAddr::ALARM1_HOUR)));
    }

    ALARM1_DAY DS3231::get_alarm1_day_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_DAY>(
            self.read<sizeof(ALARM1_DAY)>(std::to_underlying(RegAddr::ALARM1_DAY)));
    }

    ALARM1_DATE DS3231::get_alarm1_date_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_DATE>(
            self.read<sizeof(ALARM1_DATE)>(std::to_underlying(RegAddr::ALARM1_DATE)));
    }

    ALARM2_MINUTE DS3231::get_alarm2_minute_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_MINUTE>(
            self.read<sizeof(ALARM2_MINUTE)>(std::to_underlying(RegAddr::ALARM2_MINUTE)));
    }

    ALARM2_HOUR DS3231::get_alarm2_hour_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_HOUR>(
            self.read<sizeof(ALARM2_HOUR)>(std::to_underlying(RegAddr::ALARM2_HOUR)));
    }

    ALARM2_DAY DS3231::get_alarm2_day_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_DAY>(
            self.read<sizeof(ALARM2_DAY)>(std::to_underlying(RegAddr::ALARM2_DAY)));
    }

    ALARM2_DATE DS3231::get_alarm2_date_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_DATE>(
            self.read<sizeof(ALARM2_DATE)>(std::to_underlying(RegAddr::ALARM2_DATE)));
    }

    void DS3231::init(this DS3231 const& self) noexcept
    {
        if (self.interface.init) {
            self.interface.init(self.interface.user);
        }
    }

    void DS3231::deinit(this DS3231 const& self) noexcept
    {
        if (self.interface.deinit) {
            self.interface.deinit(self.interface.user);
        }
    }

    void DS3231::delay(this DS3231 const& self, std::uint16_t const delay) noexcept
    {
        if (self.interface.delay) {
            self.interface.delay(self.interface.user, delay);
        }
    }

}; // namespace ds3231