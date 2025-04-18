#ifndef DS3231_REGISTERS_HPP
#define DS3231_REGISTERS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace DS3231 {

    struct CONTROL {
        std::uint8_t eosc : 1;
        std::uint8_t bbsqw : 1;
        std::uint8_t conv : 1;
        std::uint8_t r : 2;
        std::uint8_t intcn : 1;
        std::uint8_t a2ie : 1;
        std::uint8_t a1ie : 1;
    } PACKED;

    struct STATUS {
        std::uint8_t osf : 1;
        std::uint8_t : 3;
        std::uint8_t en32khz : 1;
        std::uint8_t bsy : 1;
        std::uint8_t a2f : 1;
        std::uint8_t a1f : 2;
    } PACKED;

    struct AGING_OFFSET {
        std::uint8_t offset : 8;
    } PACKED;

    struct TEMP {
        std::uint16_t temp : 10;
        std::uint8_t : 6;
    } PACKED;

    struct SECOND {
        std::uint8_t : 1;
        std::uint8_t dec_second : 3;
        std::uint8_t second : 4;
    } PACKED;

    struct MINUTE {
        std::uint8_t : 1;
        std::uint8_t tens_minute : 3;
        std::uint8_t minute : 4;
    } PACKED;

    struct HOUR {
        std::uint8_t : 1;
        std::uint8_t sys_12_n24 : 1;
        std::uint8_t nAM_PM : 1;
        std::uint8_t tens_hour : 4;
        std::uint8_t hour : 4;
    } PACKED;

    struct DAY {
        std::uint8_t : 5;
        std::uint8_t day : 3;
    } PACKED;

    struct DATE {
        std::uint8_t : 2;
        std::uint8_t tens_date : 2;
        std::uint8_t date : 4;
    } PACKED;

    struct MONTH_CENTURY {
        std::uint8_t century : 1;
        std::uint8_t : 2;
        std::uint8_t tens_month : 1;
        std::uint8_t month : 4;
    } PACKED;

    struct YEAR {
        std::uint8_t tens_year : 4;
        std::uint8_t year : 4;
    } PACKED;

    struct ALARM1_SECOND {
        std::uint8_t a1m1 : 1;
        std::uint8_t tens_second : 3;
        std::uint8_t second : 4;
    } PACKED;

    struct ALARM1_MINUTE {
        std::uint8_t a1m1 : 1;
        std::uint8_t tens_minute : 3;
        std::uint8_t minute : 4;
    } PACKED;

    struct ALARM1_HOUR {
        std::uint8_t a1m3 : 1;
        std::uint8_t sys_12_n24 : 1;
        std::uint8_t nAM_PM : 1;
        std::uint8_t tens_hour : 1;
        std::uint8_t hour : 4;
    } PACKED;

    struct ALARM1_DAY {
        std::uint8_t a1m4 : 1;
        std::uint8_t DY_nDT : 1;
        std::uint8_t tens_date : 2;
        std::uint8_t day : 4;
    } PACKED;

    struct ALARM1_DATE {
        std::uint8_t a1m4 : 1;
        std::uint8_t DY_nDT : 1;
        std::uint8_t tens_date : 2;
        std::uint8_t date : 4;
    } PACKED;

    struct ALARM2_MINUTE {
        std::uint8_t a2m2 : 1;
        std::uint8_t tens_minute : 3;
        std::uint8_t minute : 4;
    } PACKED;

    struct ALARM2_HOUR {
        std::uint8_t a2m3 : 1;
        std::uint8_t sys_12_n24 : 1;
        std::uint8_t nAM_PM : 1;
        std::uint8_t tens_hour : 1;
        std::uint8_t hour : 4;
    } PACKED;

    struct ALARM2_DAY {
        std::uint8_t a2m4 : 1;
        std::uint8_t DY_nDT : 1;
        std::uint8_t tens_date : 2;
        std::uint8_t date : 4;
    } PACKED;

    struct ALARM2_DATE {
        std::uint8_t a2m4 : 1;
        std::uint8_t DY_nDT : 1;
        std::uint8_t tens_date : 2;
        std::uint8_t date : 4;
    } PACKED;

}; // namespace DS3231

#undef PACKED

#endif // DS3231_REGISTERS_HPP