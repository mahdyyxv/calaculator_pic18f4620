/* 
 * File:   ecu_lcd.h
 * Author: mahdy
 *
 * Created on August 10, 2023, 4:41 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* Section : Includes */
#include "ecu_lcd_cfg.h"
#include "../../Mcal_Layer/GPIO/hal_gpio.h"
/* Section : Macro Declarations */
#define _LCD_CLEAR                  0x01
#define _LCD_RETURN_HOME            0x02
#define _LCD_ENTRY_MODE             0x06
#define _LCD_CURSOR_OFF_DISPLY_ON   0x0C
#define _LCD_CURSOR_OFF_DISPLY_OFF  0x08
#define _LCD_CURSOR_ON_BLINK_ON     0x0F
#define _LCD_CURSOR_ON_BLINK_OFF    0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT    0x1C
#define _LCD_DISPLAY_SHIFT_LEFT     0x18
#define _LCD_8BIT_MODE_2_LINE       0x38
#define _LCD_4BIT_MODE_2_LINE       0x28
#define _LCD_CGRAM_START            0x40
#define _LCD_DDRAM_START            0x80

#define ROW1                        1
#define ROW2                        2
#define ROW3                        3
#define ROW4                        4

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;

typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;
/* Section : Function Prototype */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t * _lcd_config);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t * _lcd_config, uint8 cmd);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t * _lcd_config, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t * _lcd_config, uint8 row, uint8 col, uint8 data);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t * _lcd_config, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t * _lcd_config, uint8 row, uint8 col, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t * _lcd_config, uint8 row
                                         , uint8 col, uint8 _chr[], uint8 mempos);

Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t * _lcd_config);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t * _lcd_config, uint8 cmd);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t * _lcd_config, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t * _lcd_config, uint8 row, uint8 col, uint8 data);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t * _lcd_config, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t * _lcd_config, uint8 row, uint8 col, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t * _lcd_config, uint8 row,
                                         uint8 col, uint8 _chr[], uint8 mempos);

Std_ReturnType convert_byte_to_str(uint8 value, uint8 *str);
Std_ReturnType convert_short_to_str(uint16 value, uint8 *str);
Std_ReturnType convert_int_to_str(uint32 value, uint8 *str);
#endif	/* ECU_LCD_H */

