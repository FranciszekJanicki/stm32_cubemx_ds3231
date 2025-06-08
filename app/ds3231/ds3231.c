#include "ds3231.h"
#include <assert.h>
#include <string.h>

static ds3231_err_t ds3231_bus_init(ds3231_t const* ds3231)
{
    assert(ds3231);

    if (ds3231->interface.bus_init) {
        return ds3231->interface.bus_init(ds3231->interface.bus_user);
    }

    return DS3231_ERR_NULL;
}

static ds3231_err_t ds3231_bus_deinit(ds3231_t const* ds3231)
{
    assert(ds3231);

    if (ds3231->interface.bus_deinit) {
        return ds3231->interface.bus_deinit(ds3231->interface.bus_user);
    }

    return DS3231_ERR_NULL;
}

static ds3231_err_t ds3231_bus_write(ds3231_t const* ds3231,
                                     uint8_t write_address,
                                     uint8_t const* write_data,
                                     size_t write_size)
{
    assert(ds3231);

    if (ds3231->interface.bus_write) {
        return ds3231->interface.bus_write(ds3231->interface.bus_user,
                                           write_address,
                                           write_data,
                                           write_size);
    }

    return DS3231_ERR_NULL;
}

static ds3231_err_t ds3231_bus_read(ds3231_t const* ds3231,
                                    uint8_t read_address,
                                    uint8_t* read_data,
                                    size_t read_size)
{
    assert(ds3231);

    if (ds3231->interface.bus_read) {
        return ds3231->interface.bus_read(ds3231->interface.bus_user,
                                          read_address,
                                          read_data,
                                          read_size);
    }

    return DS3231_ERR_NULL;
}

ds3231_err_t ds3231_initialize(ds3231_t* ds3231,
                               ds3231_config_t const* config,
                               ds3231_interface_t const* interface)
{
    assert(ds3231 && config && interface);

    memset(ds3231, 0, sizeof(*ds3231));
    memcpy(&ds3231->config, config, sizeof(*config));
    memcpy(&ds3231->interface, interface, sizeof(*interface));

    return ds3231_bus_init(ds3231);
}

ds3231_err_t ds3231_deinitialize(ds3231_t* ds3231)
{
    assert(ds3231);

    ds3231_err_t err = ds3231_bus_deinit(ds3231);

    memset(ds3231, 0, sizeof(*ds3231));

    return err;
}

ds3231_err_t ds3231_get_temp_data_scaled(ds3231_t const* ds3231, float* scaled)
{
    assert(ds3231 && scaled);

    int16_t raw = {};

    ds3231_err_t err = ds3231_get_temp_data_raw(ds3231, &raw);

    *scaled = (float)raw * DS3231_TEMP_SCALE;

    return err;
}

ds3231_err_t ds3231_get_temp_data_raw(ds3231_t const* ds3231, int16_t* raw)
{
    assert(ds3231 && raw);

    ds3231_temp_reg_t reg = {};

    ds3231_err_t err = ds3231_get_temp_reg(ds3231, &reg);

    *raw = reg.temp;

    // sign extend to 16 bits
    if (*raw & (1 << 9)) {
        *raw |= 0xFC00;
    }

    return err;
}

ds3231_err_t ds3231_get_time_data(ds3231_t const* ds3231, ds3231_time_t* time)
{
    assert(ds3231 && time);

    ds3231_err_t err = ds3231_get_century_data(ds3231, &time->century);
    err |= ds3231_get_year_data(ds3231, &time->year);
    err |= ds3231_get_month_data(ds3231, &time->month);
    err |= ds3231_get_date_data(ds3231, &time->date);
    err |= ds3231_get_day_data(ds3231, &time->day);
    err |= ds3231_get_hour_data(ds3231, &time->hour);
    err |= ds3231_get_minute_data(ds3231, &time->minute);
    err |= ds3231_get_second_data(ds3231, &time->second);

    return err;
}

ds3231_err_t ds3231_get_century_data(ds3231_t const* ds3231, uint8_t* century)
{
    assert(ds3231 && century);

    ds3231_month_century_reg_t reg = {};

    ds3231_err_t err = ds3231_get_month_century_reg(ds3231, &reg);

    *century = reg.century;

    return err;
}

ds3231_err_t ds3231_get_year_data(ds3231_t const* ds3231, uint8_t* year)
{
    assert(ds3231 && year);

    ds3231_year_reg_t reg = {};

    ds3231_err_t err = ds3231_get_year_reg(ds3231, &reg);

    *year = reg.ten_year * 10U + reg.year;

    return err;
}

ds3231_err_t ds3231_get_month_data(ds3231_t const* ds3231, uint8_t* month)
{
    assert(ds3231 && month);

    ds3231_month_century_reg_t reg = {};

    ds3231_err_t err = ds3231_get_month_century_reg(ds3231, &reg);

    *month = reg.ten_month * 10U + reg.month;

    return err;
}

ds3231_err_t ds3231_get_date_data(ds3231_t const* ds3231, uint8_t* date)
{
    assert(ds3231 && date);

    ds3231_date_reg_t reg = {};

    ds3231_err_t err = ds3231_get_date_reg(ds3231, &reg);

    *date = reg.ten_date * 10U + reg.date;

    return err;
}

ds3231_err_t ds3231_get_day_data(ds3231_t const* ds3231, uint8_t* day)
{
    assert(ds3231 && day);

    ds3231_day_reg_t reg = {};

    ds3231_err_t err = ds3231_get_day_reg(ds3231, &reg);

    *day = reg.day;

    return err;
}

ds3231_err_t ds3231_get_hour_data(ds3231_t const* ds3231, uint8_t* hour)
{
    assert(ds3231 && hour);

    ds3231_hour_reg_t reg = {};

    ds3231_err_t err = ds3231_get_hour_reg(ds3231, &reg);

    *hour = reg.ten_hour * 10U + reg.hour;

    return err;
}

ds3231_err_t ds3231_get_minute_data(ds3231_t const* ds3231, uint8_t* minute)
{
    assert(ds3231 && minute);

    ds3231_minute_reg_t reg = {};

    ds3231_err_t err = ds3231_get_minute_reg(ds3231, &reg);

    *minute = reg.ten_minute * 10U + reg.minute;

    return err;
}

ds3231_err_t ds3231_get_second_data(ds3231_t const* ds3231, uint8_t* second)
{
    assert(ds3231 && second);

    ds3231_second_reg_t reg = {};

    ds3231_err_t err = ds3231_get_second_reg(ds3231, &reg);

    *second = reg.ten_second * 10U + reg.second;

    return err;
}

ds3231_err_t ds3231_get_control_reg(ds3231_t const* ds3231, ds3231_control_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_CONTROL, &data, sizeof(data));

    reg->eosc = (data >> 7U) & 0x01U;
    reg->bbsqw = (data >> 6U) & 0x01U;
    reg->conv = (data >> 5U) & 0x01U;
    reg->r = (data >> 3U) & 0x03U;
    reg->intcn = (data >> 2U) & 0x01U;
    reg->a2ie = (data >> 1U) & 0x01U;
    reg->a1ie = data & 0x01U;

    return err;
}

ds3231_err_t ds3231_set_control_reg(ds3231_t const* ds3231, ds3231_control_reg_t const* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    data |= (reg->eosc & 0x01U) << 7U;
    data |= (reg->bbsqw & 0x01U) << 6U;
    data |= (reg->conv & 0x01U) << 5U;
    data |= (reg->r & 0x03U) << 3U;
    data |= (reg->intcn & 0x01U) << 2U;
    data |= (reg->a2ie & 0x01U) << 1U;
    data |= reg->a1ie & 0x01U;

    return ds3231_bus_write(ds3231, DS3231_REG_ADDR_CONTROL, &data, sizeof(data));
}

ds3231_err_t ds3231_get_status_reg(ds3231_t const* ds3231, ds3231_status_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_STATUS, &data, sizeof(data));

    reg->osf = (data >> 7U) & 0x01U;
    reg->en32khz = (data >> 3U) & 0x01U;
    reg->bsy = (data >> 2U) & 0x01U;
    reg->a2f = (data >> 1U) & 0x01U;
    reg->a1f = data & 0x01U;

    return err;
}

ds3231_err_t ds3231_set_status_reg(ds3231_t const* ds3231, ds3231_status_reg_t const* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_STATUS, &data, sizeof(data));

    data &= ~((0x01U << 7U) | (0x01U << 3U) | (0x01U << 2U) | (0x01U << 1U) | (0x01U));

    data |= (reg->osf & 0x01U) << 7U;
    data |= (reg->en32khz & 0x01U) << 3U;
    data |= (reg->bsy & 0x01U) << 2U;
    data |= (reg->a2f & 0x01U) << 1U;
    data |= reg->a1f & 0x01U;

    err |= ds3231_bus_write(ds3231, DS3231_REG_ADDR_STATUS, &data, sizeof(data));

    return err;
}

ds3231_err_t ds3231_get_aging_offset_reg(ds3231_t const* ds3231, ds3231_aging_offset_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_AGING_OFFSET, &data, sizeof(data));

    reg->offset = (int8_t)(data & 0xFF);

    return err;
}

ds3231_err_t ds3231_set_aging_offset_reg(ds3231_t const* ds3231,
                                         ds3231_aging_offset_reg_t const* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    data |= (uint8_t)(reg->offset & 0xFF);

    return ds3231_bus_write(ds3231, DS3231_REG_ADDR_AGING_OFFSET, &data, sizeof(data));
}

ds3231_err_t ds3231_get_temp_reg(ds3231_t const* ds3231, ds3231_temp_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data[2] = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_TEMP_MSB, data, sizeof(data));

    reg->temp = (int16_t)(((data[0] & 0xFF) << 2) | ((data[1] >> 6) & 0x03));

    return err;
}

ds3231_err_t ds3231_get_second_reg(ds3231_t const* ds3231, ds3231_second_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_SECOND, &data, sizeof(data));

    reg->ten_second = (data >> 4U) & 0x07U;
    reg->second = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_minute_reg(ds3231_t const* ds3231, ds3231_minute_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_MINUTE, &data, sizeof(data));

    reg->ten_minute = (data >> 4U) & 0x07U;
    reg->minute = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_hour_reg(ds3231_t const* ds3231, ds3231_hour_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_HOUR, &data, sizeof(data));

    reg->sys_12_n24 = (data >> 6U) & 0x01U;
    reg->n_am_pm = (data >> 5U) & 0x01U;
    reg->ten_hour = (data >> 4U) & 0x01U;
    reg->hour = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_day_reg(ds3231_t const* ds3231, ds3231_day_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_DAY, &data, sizeof(data));

    reg->day = data & 0x07U;

    return err;
}

ds3231_err_t ds3231_get_date_reg(ds3231_t const* ds3231, ds3231_date_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_DATE, &data, sizeof(data));

    reg->ten_date = (data >> 4U) & 0x0FU;
    reg->date = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_month_century_reg(ds3231_t const* ds3231, ds3231_month_century_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_MONTH_CENTURY, &data, sizeof(data));

    reg->century = (data >> 7U) & 0x01U;
    reg->ten_month = (data >> 4U) & 0x01U;
    reg->month = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_year_reg(ds3231_t const* ds3231, ds3231_year_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_YEAR, &data, sizeof(data));

    reg->ten_year = (data >> 4U) & 0x0FU;
    reg->year = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm1_second_reg(ds3231_t const* ds3231, ds3231_alarm1_second_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM1_SECOND, &data, sizeof(data));

    reg->a1m1 = (data >> 7U) & 0x01U;
    reg->ten_second = (data >> 4U) & 0x07U;
    reg->second = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm1_minute_reg(ds3231_t const* ds3231, ds3231_alarm1_minute_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM1_MINUTE, &data, sizeof(data));

    reg->a1m1 = (data >> 7U) & 0x01U;
    reg->ten_minute = (data >> 4U) & 0x07U;
    reg->minute = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm1_hour_reg(ds3231_t const* ds3231, ds3231_alarm1_hour_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM1_HOUR, &data, sizeof(data));

    reg->a1m3 = (data >> 7U) & 0x01U;
    reg->sys_12_n24 = (data >> 6U) & 0x01U;
    reg->n_am_pm = (data >> 5U) & 0x01U;
    reg->ten_hour = (data >> 4U) & 0x01U;
    reg->hour = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm1_day_reg(ds3231_t const* ds3231, ds3231_alarm1_date_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM1_DAY, &data, sizeof(data));

    reg->a1m4 = (data >> 7U) & 0x01U;
    reg->dy_n_dt = (data >> 6U) & 0x01U;
    reg->ten_date = (data >> 4U) & 0x03U;
    reg->date = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm1_date_reg(ds3231_t const* ds3231, ds3231_alarm1_date_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM1_DATE, &data, sizeof(data));

    reg->a1m4 = (data >> 7U) & 0x01U;
    reg->dy_n_dt = (data >> 6U) & 0x01U;
    reg->ten_date = (data >> 4U) & 0x03U;
    reg->date = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm2_minute_reg(ds3231_t const* ds3231, ds3231_alarm2_minute_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM2_MINUTE, &data, sizeof(data));

    reg->a2m2 = (data >> 7U) & 0x01U;
    reg->ten_minute = (data >> 4U) & 0x07U;
    reg->minute = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm2_hour_reg(ds3231_t const* ds3231, ds3231_alarm2_hour_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM2_HOUR, &data, sizeof(data));

    reg->a2m3 = (data >> 7U) & 0x01U;
    reg->sys_12_n24 = (data >> 6U) & 0x01U;
    reg->n_am_pm = (data >> 5U) & 0x01U;
    reg->ten_hour = (data >> 4U) & 0x01U;
    reg->hour = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm2_day_reg(ds3231_t const* ds3231, ds3231_alarm2_day_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM2_DAY, &data, sizeof(data));

    reg->a2m4 = (data >> 7U) & 0x01U;
    reg->dy_n_dt = (data >> 6U) & 0x01U;
    reg->ten_day = (data >> 4U) & 0x03U;
    reg->day = data & 0x0FU;

    return err;
}

ds3231_err_t ds3231_get_alarm2_date_reg(ds3231_t const* ds3231, ds3231_alarm2_date_reg_t* reg)
{
    assert(ds3231 && reg);

    uint8_t data = {};

    ds3231_err_t err = ds3231_bus_read(ds3231, DS3231_REG_ADDR_ALARM2_DATE, &data, sizeof(data));

    reg->a2m4 = (data >> 7U) & 0x01U;
    reg->dy_n_dt = (data >> 6U) & 0x01U;
    reg->ten_date = (data >> 4U) & 0x03U;
    reg->date = data & 0x0FU;

    return err;
}
