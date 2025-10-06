#include "i2c.h"
#include "stdint.h"

void i2c_delay(uint8_t time){
    htim1.Instance->CNT = 0; 
    while(htim1.Instance->CNT < time); 
}

void i2c_start(void){
    SDA_Release();
    SCL_Release();
    i2c_delay(5);
    SDA_Low();
    i2c_delay(5);
    SCL_Low();
}

void i2c_stop(void){
    SDA_Low();
    i2c_delay(5);
    SCL_Release();
    i2c_delay(5);
    SDA_Release();
}

void i2c_write_bit(uint8_t bit){
    if(bit) SDA_Release();
    else    SDA_Low();

    i2c_delay(2);
    SCL_Release();
    i2c_delay(5);
    SCL_Low();
}

uint8_t i2c_read_ack(void){
    uint8_t ack;
    SDA_Release();
    i2c_delay(2);
    SCL_Release();
    i2c_delay(5);
    ack = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    SCL_Low();
    return ack;    
}

uint8_t i2c_write_byte(uint8_t data){
    for(uint8_t i = 0; i < 8; i++){
        i2c_write_bit((data & 0x80) != 0);
        data <<= 1;
    }
    return i2c_read_ack();
}

void i2c_master_transmit(uint8_t slave_addr, uint8_t* data, uint8_t length){
    i2c_start();

    if(i2c_write_byte((slave_addr << 1) | 0) == 0){
        for(uint8_t i = 0; i < length; i++){
            if(i2c_write_byte(data[i]) != 0) break;
        }
    }

    i2c_stop();
}
