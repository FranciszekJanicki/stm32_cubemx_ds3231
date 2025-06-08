#ifndef DS3231_DS3231_REGISTERS_H
#define DS3231_DS3231_REGISTERS_H

#include <stdint.h>

typedef struct {
    uint8_t eosc : 1;
    uint8_t bbsqw : 1;
    uint8_t conv : 1;
    uint8_t r : 2;
    uint8_t intcn : 1;
    uint8_t a2ie : 1;
    uint8_t a1ie : 1;
} ds3231_control_reg_t;

typedef struct {
    uint8_t osf : 1;
    uint8_t en32khz : 1;
    uint8_t bsy : 1;
    uint8_t a2f : 1;
    uint8_t a1f : 1;
} ds3231_status_reg_t;

typedef struct {
    int8_t offset : 8;
} ds3231_aging_offset_reg_t;

typedef struct {
    int16_t temp : 10;
} ds3231_temp_reg_t;

typedef struct {
    uint8_t ten_second : 3;
    uint8_t second : 4;
} ds3231_second_reg_t;

typedef struct {
    uint8_t ten_minute : 3;
    uint8_t minute : 4;
} ds3231_minute_reg_t;

typedef struct {
    uint8_t sys_12_n24 : 1;
    uint8_t n_am_pm : 1;
    uint8_t ten_hour : 1;
    uint8_t hour : 4;
} ds3231_hour_reg_t;

typedef struct {
    uint8_t day : 3;
} ds3231_day_reg_t;

typedef struct {
    uint8_t ten_date : 2;
    uint8_t date : 4;
} ds3231_date_reg_t;

typedef struct {
    uint8_t century : 1;
    uint8_t ten_month : 1;
    uint8_t month : 4;
} ds3231_month_century_reg_t;

typedef struct {
    uint8_t ten_year : 4;
    uint8_t year : 4;
} ds3231_year_reg_t;

typedef struct {
    uint8_t a1m1 : 1;
    uint8_t ten_second : 3;
    uint8_t second : 4;
} ds3231_alarm1_second_reg_t;

typedef struct {
    uint8_t a1m1 : 1;
    uint8_t ten_minute : 3;
    uint8_t minute : 4;
} ds3231_alarm1_minute_reg_t;

typedef struct {
    uint8_t a1m3 : 1;
    uint8_t sys_12_n24 : 1;
    uint8_t n_am_pm : 1;
    uint8_t ten_hour : 1;
    uint8_t hour : 4;
} ds3231_alarm1_hour_reg_t;

typedef struct {
    uint8_t a1m4 : 1;
    uint8_t dy_n_dt : 1;
    uint8_t ten_date : 2;
    uint8_t day : 4;
} ds3231_alarm1_day_reg_t;

typedef struct {
    uint8_t a1m4 : 1;
    uint8_t dy_n_dt : 1;
    uint8_t ten_date : 2;
    uint8_t date : 4;
} ds3231_alarm1_date_reg_t;

typedef struct {
    uint8_t a2m2 : 1;
    uint8_t ten_minute : 3;
    uint8_t minute : 4;
} ds3231_alarm2_minute_reg_t;

typedef struct {
    uint8_t a2m3 : 1;
    uint8_t sys_12_n24 : 1;
    uint8_t n_am_pm : 1;
    uint8_t ten_hour : 1;
    uint8_t hour : 4;
} ds3231_alarm2_hour_reg_t;

typedef struct {
    uint8_t a2m4 : 1;
    uint8_t dy_n_dt : 1;
    uint8_t ten_day : 2;
    uint8_t day : 4;
} ds3231_alarm2_day_reg_t;

typedef struct {
    uint8_t a2m4 : 1;
    uint8_t dy_n_dt : 1;
    uint8_t ten_date : 2;
    uint8_t date : 4;
} ds3231_alarm2_date_reg_t;

#endif // DS3231_DS3231_REGISTERS_H