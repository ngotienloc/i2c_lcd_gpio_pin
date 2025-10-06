#include "lcd.h"

void lcd_send_cmd(char cmd){
    uint8_t data_u, data_l; 
    uint8_t data[4]; 
    data_u = (cmd & 0xF0); 
    data_l = ((cmd << 4) & 0xF0); 
    data[0] = data_u | lcd_bl | 0x04; 
    data[1] = data_u | lcd_bl | 0x00; 
    data[2] = data_l | lcd_bl | 0x04; 
    data[3] = data_l | lcd_bl | 0x00; 
    i2c_master_transmit(lcd_addr, data, 4); 
}

void lcd_send_data(char data_){
    uint8_t data_u, data_l; 
    uint8_t data[4]; 
    data_u = (data_ & 0xF0); 
    data_l = ((data_ << 4) & 0xF0); 
    data[0] = data_u | lcd_bl | 0x05; 
    data[1] = data_u | lcd_bl | 0x01; 
    data[2] = data_l | lcd_bl | 0x05; 
    data[3] = data_l | lcd_bl | 0x01; 
    i2c_master_transmit(lcd_addr, data, 4); 
}
void lcd_init(){
    HAL_Delay(50); 
    lcd_send_cmd(0x30); 
    HAL_Delay(5); 
    lcd_send_cmd(0x30); 
    HAL_Delay(1);
    lcd_send_cmd(0x30); 
    HAL_Delay(10); 
    lcd_send_cmd(0x20); // 4 bit mode
    lcd_send_cmd(0x28); // 2 dots
    lcd_send_cmd(0x0C); // Led, Bl 
    lcd_send_cmd(0x06); // right 
    lcd_send_cmd(0x01); // clear display         
}

void lcd_send_string(char* str){
    while(*str){
        lcd_send_data(*str);
        str++; 
    }
}