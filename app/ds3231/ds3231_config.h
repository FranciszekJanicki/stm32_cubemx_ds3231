#ifndef DS3231_DS3231_CONFIG_H
#define DS3231_DS3231_CONFIG_H

#include "ds3231_registers.h"
#include <stddef.h>
#include <stdint.h>

#define DS3231_SLAVE_ADDRESS 0b1101000
#define DS3231_TEMP_SCALE 0.25F

typedef struct {
    uint8_t century;
    uint8_t year;
    uint8_t month;
    uint8_t date;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} ds3231_time_t;

typedef enum {
    DS3231_ERR_OK = 0,
    DS3231_ERR_FAIL = 1 << 0,
    DS3231_ERR_NULL = 1 << 1,
} ds3231_err_t;

typedef enum {
    DS3231_REG_ADDR_SECOND = 0x00,
    DS3231_REG_ADDR_MINUTE = 0x01,
    DS3231_REG_ADDR_HOUR = 0x02,
    DS3231_REG_ADDR_DAY = 0x03,
    DS3231_REG_ADDR_DATE = 0x04,
    DS3231_REG_ADDR_MONTH_CENTURY = 0x05,
    DS3231_REG_ADDR_YEAR = 0x06,
    DS3231_REG_ADDR_ALARM1_SECOND = 0x07,
    DS3231_REG_ADDR_ALARM1_MINUTE = 0x08,
    DS3231_REG_ADDR_ALARM1_HOUR = 0x09,
    DS3231_REG_ADDR_ALARM1_DAY = 0x0A,
    DS3231_REG_ADDR_ALARM1_DATE = 0x0A,
    DS3231_REG_ADDR_ALARM2_MINUTE = 0x0B,
    DS3231_REG_ADDR_ALARM2_HOUR = 0x0C,
    DS3231_REG_ADDR_ALARM2_DAY = 0x0D,
    DS3231_REG_ADDR_ALARM2_DATE = 0x0D,
    DS3231_REG_ADDR_CONTROL = 0x0E,
    DS3231_REG_ADDR_STATUS = 0x0F,
    DS3231_REG_ADDR_AGING_OFFSET = 0x10,
    DS3231_REG_ADDR_TEMP_MSB = 0x11,
    DS3231_REG_ADDR_TEMP_LSB = 0x12,
} ds3231_reg_addr_t;

typedef enum {
    DS3231_ALARM1_EVERY_SECOND = 0b1111,
    DS3231_ALARM1_SEC_MATCH = 0b1110,
    DS3231_ALARM1_MIN_SEC_MATCH = 0b1100,
    DS3231_ALARM1_HR_MIN_SEC_MATCH = 0b1000,
    DS3231_ALARM1_DATE_HR_MIN_SEC_MATCH = 0b0000,
    DS3231_ALARM1_DAY_HR_MIN_SEC_MATCH = 0b0000,
} ds3231_alarm1_t;

typedef enum {
    DS3231_ALARM2_EVERY_MINUTE = 0b111,
    DS3231_ALARM2_MIN_MATCH = 0b110,
    DS3231_ALARM2_HR_MIN_MATCH = 0b100,
    DS3231_ALARM2_DATE_HR_MIN_MATCH = 0b000,
    DS3231_ALARM2_DAY_HR_MIN_MATCH = 0b000,
} ds3231_alarm2_t;

typedef enum {
    DS3231_RATE_SELECT_1HZ0 = 0b00,
    DS3231_RATE_SELECT_1KHZ024 = 0b01,
    DS3231_RATE_SELECT_4KHZ096 = 0b10,
    DS3231_RATE_SELECT_8KHZ192 = 0b11,
} ds3231_rate_select_t;

typedef struct {
} ds3231_config_t;

typedef struct {
    void* bus_user;
    ds3231_err_t (*bus_init)(void*);
    ds3231_err_t (*bus_deinit)(void*);
    ds3231_err_t (*bus_write)(void*, uint8_t, uint8_t const*, size_t);
    ds3231_err_t (*bus_read)(void*, uint8_t, uint8_t*, size_t);
} ds3231_interface_t;

#endif // DS3231_DS3231_CONFIG_H