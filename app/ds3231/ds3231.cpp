#include "ds3231.hpp"

namespace DS3231 {

    DS3231::DS3231(I2CDevice&& i2c_device, Config const& config) noexcept :
        i2c_device_{std::forward<I2CDevice>(i2c_device)}
    {
        this->initialize(config);
    }

    DS3231::~DS3231() noexcept
    {
        this->deinitialize();
    }

    void DS3231::write_byte(this DS3231 const& self, std::uint8_t const address, std::uint8_t const data) noexcept
    {
        self.i2c_device_.write_byte(address, data);
    }

    std::uint8_t DS3231::read_byte(this DS3231 const& self, std::uint8_t const address) noexcept
    {
        return self.i2c_device_.read_byte(address);
    }

    void DS3231::initialize(this DS3231& self, Config const& config) noexcept
    {
        self.set_control_register(config.control);
        self.set_status_register(config.status);
        self.set_aging_offset_register(config.aging_offset);
    }

    void DS3231::deinitialize(this DS3231& self) noexcept
    {}

    CONTROL DS3231::get_control_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<CONTROL>(self.read_byte(std::to_underlying(RA::CONTROL)));
    }

    void DS3231::set_control_register(this DS3231 const& self, CONTROL const control) noexcept
    {
        self.write_byte(std::to_underlying(RA::CONTROL), std::bit_cast<std::uint8_t>(control));
    }

    STATUS DS3231::get_status_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<STATUS>(self.read_byte(std::to_underlying(RA::STATUS)));
    }

    void DS3231::set_status_register(this DS3231 const& self, STATUS const status) noexcept
    {
        self.write_byte(std::to_underlying(RA::STATUS), std::bit_cast<std::uint8_t>(status));
    }

    AGING_OFFSET DS3231::get_aging_offset_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<AGING_OFFSET>(self.read_byte(std::to_underlying(RA::AGING_OFFSET)));
    }

    void DS3231::set_aging_offset_register(this DS3231 const& self, AGING_OFFSET const aging_offset) noexcept
    {
        self.write_byte(std::to_underlying(RA::AGING_OFFSET), std::bit_cast<std::uint8_t>(aging_offset));
    }

    TEMP DS3231::get_temp_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<TEMP>(self.read_bytes<sizeof(TEMP)>(std::to_underlying(RA::TEMP_MSB)));
    }

    SECOND DS3231::get_second_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<SECOND>(self.read_byte(std::to_underlying(RA::SECOND)));
    }

    MINUTE DS3231::get_minute_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<MINUTE>(self.read_byte(std::to_underlying(RA::MINUTE)));
    }

    HOUR DS3231::get_hour_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<HOUR>(self.read_byte(std::to_underlying(RA::HOUR)));
    }

    DAY DS3231::get_day_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<DAY>(self.read_byte(std::to_underlying(RA::DAY)));
    }

    DATE DS3231::get_date_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<DATE>(self.read_byte(std::to_underlying(RA::DATE)));
    }

    MONTH_CENTURY DS3231::get_month_century_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<MONTH_CENTURY>(self.read_byte(std::to_underlying(RA::MONTH_CENTURY)));
    }

    YEAR DS3231::get_year_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<YEAR>(self.read_byte(std::to_underlying(RA::YEAR)));
    }

    ALARM1_SECOND DS3231::get_alarm1_second_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_SECOND>(self.read_byte(std::to_underlying(RA::ALARM1_SECOND)));
    }

    ALARM1_MINUTE DS3231::get_alarm1_minute_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_MINUTE>(self.read_byte(std::to_underlying(RA::ALARM1_MINUTE)));
    }

    ALARM1_HOUR DS3231::get_alarm1_hour_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_HOUR>(self.read_byte(std::to_underlying(RA::ALARM1_HOUR)));
    }

    ALARM1_DAY DS3231::get_alarm1_day_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_DAY>(self.read_byte(std::to_underlying(RA::ALARM1_DAY)));
    }

    ALARM1_DATE DS3231::get_alarm1_date_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM1_DATE>(self.read_byte(std::to_underlying(RA::ALARM1_DATE)));
    }

    ALARM2_MINUTE DS3231::get_alarm2_minute_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_MINUTE>(self.read_byte(std::to_underlying(RA::ALARM2_MINUTE)));
    }

    ALARM2_HOUR DS3231::get_alarm2_hour_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_HOUR>(self.read_byte(std::to_underlying(RA::ALARM2_HOUR)));
    }

    ALARM2_DAY DS3231::get_alarm2_day_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_DAY>(self.read_byte(std::to_underlying(RA::ALARM2_DAY)));
    }

    ALARM2_DATE DS3231::get_alarm2_date_register(this DS3231 const& self) noexcept
    {
        return std::bit_cast<ALARM2_DATE>(self.read_byte(std::to_underlying(RA::ALARM2_DATE)));
    }

}; // namespace DS3231