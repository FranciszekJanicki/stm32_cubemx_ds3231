#ifndef DS3231_DS3231_H
#define DS3231_DS3231_H

#include "ds3231_config.h"
#include "ds3231_registers.h"

typedef struct {
    ds3231_config_t config;
    ds3231_interface_t interface;
} ds3231_t;

ds3231_err_t ds3231_initialize(ds3231_t* ds3231,
                               ds3231_config_t const* config,
                               ds3231_interface_t const* interface);
ds3231_err_t ds3231_deinitialize(ds3231_t* ds3231);


ds3231_err_t ds3231_get_temp_data_scaled(ds3231_t const* ds3231, float* scaled);
ds3231_err_t ds3231_get_temp_data_raw(ds3231_t const* ds3231, int16_t* raw);

ds3231_err_t ds3231_get_time_data(ds3231_t const* ds3231, ds3231_time_t* time);

ds3231_err_t ds3231_get_century_data(ds3231_t const* ds3231, uint8_t* century);
ds3231_err_t ds3231_get_year_data(ds3231_t const* ds3231, uint8_t* year);
ds3231_err_t ds3231_get_month_data(ds3231_t const* ds3231, uint8_t* month);
ds3231_err_t ds3231_get_date_data(ds3231_t const* ds3231, uint8_t* date);
ds3231_err_t ds3231_get_day_data(ds3231_t const* ds3231, uint8_t* day);
ds3231_err_t ds3231_get_hour_data(ds3231_t const* ds3231, uint8_t* hour);
ds3231_err_t ds3231_get_minute_data(ds3231_t const* ds3231, uint8_t* minute);
ds3231_err_t ds3231_get_second_data(ds3231_t const* ds3231, uint8_t* second);

ds3231_err_t ds3231_get_control_reg(ds3231_t const* ds3231, ds3231_control_reg_t* reg);
ds3231_err_t ds3231_set_control_reg(ds3231_t const* ds3231, ds3231_control_reg_t const* reg);

ds3231_err_t ds3231_get_status_reg(ds3231_t const* ds3231, ds3231_status_reg_t* reg);
ds3231_err_t ds3231_set_status_reg(ds3231_t const* ds3231, ds3231_status_reg_t const* reg);

ds3231_err_t ds3231_get_aging_offset_reg(ds3231_t const* ds3231, ds3231_aging_offset_reg_t* reg);
ds3231_err_t ds3231_set_aging_offset_reg(ds3231_t const* ds3231,
                                         ds3231_aging_offset_reg_t const* reg);

ds3231_err_t ds3231_get_temp_reg(ds3231_t const* ds3231, ds3231_temp_reg_t* reg);
ds3231_err_t ds3231_get_second_reg(ds3231_t const* ds3231, ds3231_second_reg_t* reg);
ds3231_err_t ds3231_get_minute_reg(ds3231_t const* ds3231, ds3231_minute_reg_t* reg);
ds3231_err_t ds3231_get_hour_reg(ds3231_t const* ds3231, ds3231_hour_reg_t* reg);
ds3231_err_t ds3231_get_day_reg(ds3231_t const* ds3231, ds3231_day_reg_t* reg);
ds3231_err_t ds3231_get_date_reg(ds3231_t const* ds3231, ds3231_date_reg_t* reg);
ds3231_err_t ds3231_get_month_century_reg(ds3231_t const* ds3231, ds3231_month_century_reg_t* reg);
ds3231_err_t ds3231_get_year_reg(ds3231_t const* ds3231, ds3231_year_reg_t* reg);

ds3231_err_t ds3231_get_alarm1_second_reg(ds3231_t const* ds3231, ds3231_alarm1_second_reg_t* reg);
ds3231_err_t ds3231_get_alarm1_minute_reg(ds3231_t const* ds3231, ds3231_alarm1_minute_reg_t* reg);
ds3231_err_t ds3231_get_alarm1_hour_reg(ds3231_t const* ds3231, ds3231_alarm1_hour_reg_t* reg);
ds3231_err_t ds3231_get_alarm1_day_reg(ds3231_t const* ds3231, ds3231_alarm1_date_reg_t* reg);
ds3231_err_t ds3231_get_alarm1_date_reg(ds3231_t const* ds3231, ds3231_alarm1_date_reg_t* reg);

ds3231_err_t ds3231_get_alarm2_minute_reg(ds3231_t const* ds3231, ds3231_alarm2_minute_reg_t* reg);
ds3231_err_t ds3231_get_alarm2_hour_reg(ds3231_t const* ds3231, ds3231_alarm2_hour_reg_t* reg);
ds3231_err_t ds3231_get_alarm2_day_reg(ds3231_t const* ds3231, ds3231_alarm2_day_reg_t* reg);
ds3231_err_t ds3231_get_alarm2_date_reg(ds3231_t const* ds3231, ds3231_alarm2_date_reg_t* reg);

#endif // DS3231_DS3231_H