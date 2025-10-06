#ifndef __I2C_H
#define __I2C_H

#include "main.h"

extern TIM_HandleTypeDef htim1;

// Macros điều khiển SDA, SCL
#define SDA_Release() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)
#define SDA_Low()     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)

#define SCL_Release() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET)
#define SCL_Low()     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET)

// Function prototypes
void i2c_delay(uint8_t time);
void i2c_start(void);
void i2c_stop(void);
void i2c_write_bit(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_write_byte(uint8_t data);
void i2c_master_transmit(uint8_t slave_addr, uint8_t* data, uint8_t length); 
#endif /* __I2C_H */
