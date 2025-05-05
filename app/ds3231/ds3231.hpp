#ifndef DS3231_HPP
#define DS3231_HPP

#include "ds3231_config.hpp"
#include "ds3231_registers.hpp"
#include "ds3231_utility.hpp"
#include <array>
#include <cstdint>

namespace ds3231 {

    struct DS3231 {
    public:
        void initialize(this DS3231& self, Config const& config) noexcept;
        void deinitialize(this DS3231& self) noexcept;

        Time get_time(this DS3231 const& self) noexcept;

        std::uint16_t get_century(this DS3231 const& self) noexcept;
        std::uint16_t get_year(this DS3231 const& self) noexcept;
        std::uint16_t get_month(this DS3231 const& self) noexcept;
        std::uint16_t get_date(this DS3231 const& self) noexcept;
        std::uint16_t get_day(this DS3231 const& self) noexcept;
        std::uint16_t get_hour(this DS3231 const& self) noexcept;
        std::uint16_t get_minute(this DS3231 const& self) noexcept;
        std::uint16_t get_second(this DS3231 const& self) noexcept;

        CONTROL get_control_register(this DS3231 const& self) noexcept;
        void set_control_register(this DS3231 const& self, CONTROL const reg) noexcept;

        STATUS get_status_register(this DS3231 const& self) noexcept;
        void set_status_register(this DS3231 const& self, STATUS const reg) noexcept;

        AGING_OFFSET get_aging_offset_register(this DS3231 const& self) noexcept;
        void set_aging_offset_register(this DS3231 const& self, AGING_OFFSET const reg) noexcept;

        TEMP get_temp_register(this DS3231 const& self) noexcept;
        SECOND get_second_register(this DS3231 const& self) noexcept;
        MINUTE get_minute_register(this DS3231 const& self) noexcept;
        HOUR get_hour_register(this DS3231 const& self) noexcept;
        DAY get_day_register(this DS3231 const& self) noexcept;
        DATE get_date_register(this DS3231 const& self) noexcept;
        MONTH_CENTURY get_month_century_register(this DS3231 const& self) noexcept;
        YEAR get_year_register(this DS3231 const& self) noexcept;

        ALARM1_SECOND get_alarm1_second_register(this DS3231 const& self) noexcept;
        ALARM1_MINUTE get_alarm1_minute_register(this DS3231 const& self) noexcept;
        ALARM1_HOUR get_alarm1_hour_register(this DS3231 const& self) noexcept;
        ALARM1_DAY get_alarm1_day_register(this DS3231 const& self) noexcept;
        ALARM1_DATE get_alarm1_date_register(this DS3231 const& self) noexcept;

        ALARM2_MINUTE get_alarm2_minute_register(this DS3231 const& self) noexcept;
        ALARM2_HOUR get_alarm2_hour_register(this DS3231 const& self) noexcept;
        ALARM2_DAY get_alarm2_day_register(this DS3231 const& self) noexcept;
        ALARM2_DATE get_alarm2_date_register(this DS3231 const& self) noexcept;

        Interface interface;

    private:
        void init(this DS3231 const& self) noexcept;
        void deinit(this DS3231 const& self) noexcept;

        template <std::size_t SIZE>
        void write(this DS3231 const& self,
                   std::uint8_t const address,
                   std::array<std::uint8_t, SIZE> const data) noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read(this DS3231 const& self,
                                            std::uint8_t const address) noexcept;

        void delay(this DS3231 const& self, std::uint16_t const delay) noexcept;
    };

    template <std::size_t SIZE>
    inline void DS3231::write(this DS3231 const& self,
                              std::uint8_t const address,
                              std::array<std::uint8_t, SIZE> const data) noexcept
    {
        if (self.interface.write) {
            self.interface.write(self.interface.user, address, data.data(), data.size());
        }
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, SIZE> DS3231::read(this DS3231 const& self,
                                                       std::uint8_t const address) noexcept
    {
        auto data = std::array<std::uint8_t, SIZE>{};
        if (self.interface.write) {
            self.interface.read(self.interface.user, address, data.data(), data.size());
        }

        return data;
    }

}; // namespace ds3231

#endif // DS3231_HPP