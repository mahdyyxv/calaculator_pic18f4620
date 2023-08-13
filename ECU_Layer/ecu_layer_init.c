/* 
 * File:   ecu_layer_init.c
 * Author: mahdy
 *
 * Created on August 8, 2023, 4:46 PM
 */


#include "ecu_layer_init.h"
lcd_4bit_t lcd_2=
{
    /*Control pin*/
    .lcd_rs.port                = PORTD_INDEX,
    .lcd_rs.pin                 = PIN2,
    .lcd_rs.logic               = GPIO_LOW,
    .lcd_rs.direction           = GPIO_OUTPUT,

    .lcd_en.port                = PORTD_INDEX,
    .lcd_en.pin                 = PIN3,
    .lcd_en.logic               = GPIO_LOW,
    .lcd_en.direction           = GPIO_OUTPUT,
    /*Data pin*/
    
    .lcd_data[0].port           = PORTD_INDEX,
    .lcd_data[0].pin            = PIN4,
    .lcd_data[0].logic          = GPIO_LOW,
    .lcd_data[0].direction      = GPIO_OUTPUT,
    
    .lcd_data[1].port           = PORTD_INDEX,
    .lcd_data[1].pin            = PIN5,
    .lcd_data[1].logic          = GPIO_LOW,
    .lcd_data[1].direction      = GPIO_OUTPUT,
    
    .lcd_data[2].port           = PORTD_INDEX,
    .lcd_data[2].pin            = PIN6,
    .lcd_data[2].logic          = GPIO_LOW,
    .lcd_data[2].direction      = GPIO_OUTPUT,
    
    .lcd_data[3].port           = PORTD_INDEX,
    .lcd_data[3].pin            = PIN7,
    .lcd_data[3].logic          = GPIO_LOW,
    .lcd_data[3].direction      = GPIO_OUTPUT
    
};
//
//lcd_8bit_t lcd_1=
//{
//    /*Control pin*/
//    .lcd_rs.port                = PORTC_INDEX,
//    .lcd_rs.pin                 = PIN0,
//    .lcd_rs.logic               = GPIO_LOW,
//    .lcd_rs.direction           = GPIO_OUTPUT,
//
//    .lcd_en.port                = PORTC_INDEX,
//    .lcd_en.pin                 = PIN1,
//    .lcd_en.logic               = GPIO_LOW,
//    .lcd_en.direction           = GPIO_OUTPUT,
//    /*Data pin*/
//    
//    .lcd_data[0].port           = PORTC_INDEX,
//    .lcd_data[0].pin            = PIN2,
//    .lcd_data[0].logic          = GPIO_LOW,
//    .lcd_data[0].direction      = GPIO_OUTPUT,
//    
//    .lcd_data[1].port           = PORTC_INDEX,
//    .lcd_data[1].pin            = PIN3,
//    .lcd_data[1].logic          = GPIO_LOW,
//    .lcd_data[1].direction      = GPIO_OUTPUT,
//    
//    .lcd_data[2].port           = PORTC_INDEX,
//    .lcd_data[2].pin            = PIN4,
//    .lcd_data[2].logic          = GPIO_LOW,
//    .lcd_data[2].direction      = GPIO_OUTPUT,
//    
//    .lcd_data[3].port           = PORTC_INDEX,
//    .lcd_data[3].pin            = PIN5,
//    .lcd_data[3].logic          = GPIO_LOW,
//    .lcd_data[3].direction      = GPIO_OUTPUT,
//    
//    .lcd_data[4].port           = PORTC_INDEX,
//    .lcd_data[4].pin            = PIN6,
//    .lcd_data[4].logic          = GPIO_LOW,
//    .lcd_data[4].direction      = GPIO_OUTPUT,
//    
//    .lcd_data[5].port           = PORTC_INDEX,
//    .lcd_data[5].pin            = PIN7,
//    .lcd_data[5].logic          = GPIO_LOW,
//    .lcd_data[5].direction      = GPIO_OUTPUT,
//    
//    .lcd_data[6].port           = PORTD_INDEX,
//    .lcd_data[6].pin            = PIN0,
//    .lcd_data[6].logic          = GPIO_LOW,
//    .lcd_data[6].direction      = GPIO_OUTPUT,
//    
//    .lcd_data[7].port           = PORTD_INDEX,
//    .lcd_data[7].pin            = PIN1,
//    .lcd_data[7].logic          = GPIO_LOW,
//    .lcd_data[7].direction      = GPIO_OUTPUT
//    
//};
keypad_t keypad = {
    /*ROW CONFIGURATION*/
    .keypad_row[0].port         = PORTC_INDEX,
    .keypad_row[0].pin          = PIN0,
    .keypad_row[0].logic        = GPIO_LOW,
    .keypad_row[0].direction    = GPIO_OUTPUT,
    
    .keypad_row[1].port         = PORTC_INDEX,
    .keypad_row[1].pin          = PIN1,
    .keypad_row[1].logic        = GPIO_LOW,
    .keypad_row[1].direction    = GPIO_OUTPUT,
    
    .keypad_row[2].port         = PORTC_INDEX,
    .keypad_row[2].pin          = PIN2,
    .keypad_row[2].logic        = GPIO_LOW,
    .keypad_row[2].direction    = GPIO_OUTPUT,
    
    .keypad_row[3].port         = PORTC_INDEX,
    .keypad_row[3].pin          = PIN3,
    .keypad_row[3].logic        = GPIO_LOW,
    .keypad_row[3].direction    = GPIO_OUTPUT,
    
    /*COLUMN CONFIGURATION*/
    .keypad_col[0].port         = PORTC_INDEX,
    .keypad_col[0].pin          = PIN4,
    .keypad_col[0].logic        = GPIO_LOW,
    .keypad_col[0].direction    = GPIO_INPUT,
    
    .keypad_col[1].port         = PORTC_INDEX,
    .keypad_col[1].pin          = PIN5,
    .keypad_col[1].logic        = GPIO_LOW,
    .keypad_col[1].direction    = GPIO_INPUT,
    
    .keypad_col[2].port         = PORTC_INDEX,
    .keypad_col[2].pin          = PIN6,
    .keypad_col[2].logic        = GPIO_LOW,
    .keypad_col[2].direction    = GPIO_INPUT,
    
    .keypad_col[3].port         = PORTC_INDEX,
    .keypad_col[3].pin          = PIN7,
    .keypad_col[3].logic        = GPIO_LOW,
    .keypad_col[3].direction    = GPIO_INPUT 
};

void ecu_layer_init(void)
{
    keypad_initialization(&keypad);
    lcd_4bit_initialize(&lcd_2);
//    lcd_8bit_initialize(&lcd_1);
}