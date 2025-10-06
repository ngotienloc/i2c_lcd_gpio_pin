#ifndef __LCD_H
#define __LCD_H

#include "main.h"
#include "i2c.h"
#define lcd_addr 0x27
#define lcd_bl 0x08 
void lcd_init(); 
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str); 
#endif