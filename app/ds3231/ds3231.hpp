#ifndef DS3231_HPP
#define DS3231_HPP

#include "ds3231_config.hpp"
#include "ds3231_registers.hpp"

namespace DS3231 {

    struct DS3231 {
    public:
        DS3231() noexcept = default;
        DS3231(I2CDevice&& i2c_device, Config const& config) noexcept;

        DS3231(DS3231 const& other) = delete;
        DS3231(DS3231&& other) noexcept = default;

        DS3231& operator=(DS3231 const& other) = delete;
        DS3231& operator=(DS3231&& other) noexcept = default;

        ~DS3231() noexcept;

    private:
        void write_byte(this DS3231 const& self, std::uint8_t const address, std::uint8_t const data) noexcept;

        template <std::size_t SIZE>
        void write_bytes(this DS3231 const& self,
                         std::uint8_t const address,
                         std::array<std::uint8_t, SIZE> const data) noexcept;

        std::uint8_t read_byte(this DS3231 const& self, std::uint8_t const address) noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(this DS3231 const& self, std::uint8_t const address) noexcept;

        void initialize(this DS3231& self, Config const& config) noexcept;
        void deinitialize(this DS3231& self) noexcept;

        CONTROL get_control_register(this DS3231 const& self) noexcept;
        void set_control_register(this DS3231 const& self, CONTROL const control) noexcept;

        STATUS get_status_register(this DS3231 const& self) noexcept;
        void set_status_register(this DS3231 const& self, STATUS const status) noexcept;

        AGING_OFFSET get_aging_offset_register(this DS3231 const& self) noexcept;
        void set_aging_offset_register(this DS3231 const& self, AGING_OFFSET const aging_offset) noexcept;

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

        bool initialized_ = false;

        I2CDevice i2c_device_ = {};
    };

    template <std::size_t SIZE>
    inline void DS3231::write_bytes(this DS3231 const& self,
                                    std::uint8_t const address,
                                    std::array<std::uint8_t, SIZE> const data) noexcept
    {
        self.i2c_device_.write_bytes(address, data);
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, SIZE> DS3231::read_bytes(this DS3231 const& self,
                                                             std::uint8_t const address) noexcept
    {
        return self.i2c_device_.read_bytes<SIZE>(address);
    }

}; // namespace DS3231

#endif // DS3231_HPP