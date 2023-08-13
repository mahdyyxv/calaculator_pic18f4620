/* 
 * File:   ecu_lcd.c
 * Author: mahdy
 *
 * Created on August 10, 2023, 4:41 PM
 */

#include "ecu_lcd.h"
static Std_ReturnType lcd_send_4bit(const lcd_4bit_t * _lcd_config, uint8 _data_cmd);
static Std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t * _lcd_config);
static Std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t * _lcd_config);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t * _lcd_config, uint8 row, uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t * _lcd_config, uint8 row, uint8 column);

/******************************************************************************************************************************
 
 4BIT mode APIs
 
******************************************************************************************************************************/


/**
 * 
 * @param _lcd_config
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t * _lcd_config)
{
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_cnt = 0;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if( (gpio_pin_direction_init(&(_lcd_config -> lcd_rs))) &&
            (gpio_pin_direction_init(&(_lcd_config -> lcd_en))) )
        {
            for(l_data_pins_cnt = 0; l_data_pins_cnt < 4; l_data_pins_cnt++)
            {
                if( !(gpio_pin_direction_init(&(_lcd_config -> lcd_data[l_data_pins_cnt]))) )
                {
                    ret = E_NOT_OK;
                    break;
                }
            }
            __delay_ms(20);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_8BIT_MODE_2_LINE);
            __delay_ms(5);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_8BIT_MODE_2_LINE);
            __delay_us(150);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_8BIT_MODE_2_LINE);
            
            

            ret &= lcd_4bit_send_command(_lcd_config , _LCD_CLEAR);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_RETURN_HOME);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_ENTRY_MODE);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_CURSOR_OFF_DISPLY_ON);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_DDRAM_START);
            ret &= lcd_4bit_send_command(_lcd_config , _LCD_4BIT_MODE_2_LINE);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param cmd
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t * _lcd_config, uint8 cmd)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        ret = gpio_pin_write_logic(&(_lcd_config -> lcd_rs), GPIO_LOW);
        ret &= lcd_send_4bit(_lcd_config, (cmd >> 4));
        ret &= lcd_4bit_send_enable(_lcd_config);
        ret &= lcd_send_4bit(_lcd_config, cmd);
        ret &= lcd_4bit_send_enable(_lcd_config);
        __delay_ms(1);
        ret = gpio_pin_write_logic(&(_lcd_config -> lcd_rs), GPIO_HIGH);
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param data
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t * _lcd_config, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd_config -> lcd_rs), GPIO_HIGH);
        ret &= lcd_send_4bit(_lcd_config, (data >> 4));
        ret &= lcd_4bit_send_enable(_lcd_config);
        ret &= lcd_send_4bit(_lcd_config, data);
        ret &= lcd_4bit_send_enable(_lcd_config);
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param row
 * @param col
 * @param data
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t * _lcd_config, uint8 row, uint8 col, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_4bit_set_cursor(_lcd_config, row, col);
        ret &= lcd_4bit_send_char_data(_lcd_config, data);
    }
    
    return ret;
    
}

/**
 * 
 * @param _lcd_config
 * @param str
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t * _lcd_config, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret &= lcd_4bit_send_char_data(_lcd_config, *str);
            *str++;
        }
        
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param row
 * @param col
 * @param str
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t * _lcd_config, uint8 row, uint8 col, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd_config || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret &= lcd_4bit_set_cursor(_lcd_config, row, col);
        ret &= lcd_4bit_send_string(_lcd_config, str);
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param row
 * @param col
 * @param _chr
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t * _lcd_config, uint8 row, uint8 col, uint8 _chr[], uint8 mempos)
{
    Std_ReturnType ret = E_OK;
    uint8 l_cnt = 0;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        lcd_4bit_send_command(_lcd_config, (_LCD_CGRAM_START + (mempos * 8)));
        for(l_cnt = 0 ; l_cnt < 8 ; l_cnt++)
        {
            lcd_4bit_send_char_data(_lcd_config, _chr[l_cnt]);
        }
        lcd_4bit_send_char_data_pos(_lcd_config, row, col, mempos); 
    }
    
    return ret;
}

/******************************************************************************************************************************
 
 8BIT mode APIs
 
******************************************************************************************************************************/


/**
 * 
 * @param _lcd_config
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t * _lcd_config)
{
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_cnt = 0;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if( (gpio_pin_direction_init(&(_lcd_config -> lcd_rs))) &&
            (gpio_pin_direction_init(&(_lcd_config -> lcd_en))) )
        {
            for(l_data_pins_cnt = 0; l_data_pins_cnt < 8; l_data_pins_cnt++)
            {
                if( !(gpio_pin_direction_init(&(_lcd_config -> lcd_data[l_data_pins_cnt]))) )
                {
                    ret = E_NOT_OK;
                    break;
                }
            }
            __delay_ms(20);
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_8BIT_MODE_2_LINE);
            __delay_ms(5);
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_8BIT_MODE_2_LINE);
            __delay_us(150);
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_8BIT_MODE_2_LINE);
            
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_CLEAR);
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_RETURN_HOME);
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_ENTRY_MODE);
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_CURSOR_OFF_DISPLY_ON);
            ret &= lcd_8bit_send_command(_lcd_config , _LCD_DDRAM_START);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param cmd
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t * _lcd_config, uint8 cmd)
{
    Std_ReturnType ret = E_OK;
    uint8 l_dataPin_counter = 0;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd_config -> lcd_rs), GPIO_LOW);
        
        for(l_dataPin_counter = 0; l_dataPin_counter < 8; l_dataPin_counter++)
        {
            ret &= gpio_pin_write_logic(&(_lcd_config -> lcd_data[l_dataPin_counter]),
                    ((cmd >> l_dataPin_counter) & (uint8)0x01));
        }
        ret &= lcd_8bit_send_enable(_lcd_config);
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param data
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t * _lcd_config, uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 l_dataPin_counter = 0;

    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd_config -> lcd_rs), GPIO_HIGH);
        
        for(l_dataPin_counter = 0; l_dataPin_counter < 8; l_dataPin_counter++)
        {
            ret &= gpio_pin_write_logic(&(_lcd_config -> lcd_data[l_dataPin_counter]),
                    ((data >> l_dataPin_counter) & (uint8)0x01));
        }
        ret &= lcd_8bit_send_enable(_lcd_config);
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param row
 * @param col
 * @param data
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t * _lcd_config, uint8 row, uint8 col, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        lcd_8bit_set_cursor(_lcd_config, row, col);
        lcd_8bit_send_char_data(_lcd_config, data);
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param str
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t * _lcd_config, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret &= lcd_8bit_send_char_data(_lcd_config, *str);
            *str++;
        }
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param row
 * @param col
 * @param str
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t * _lcd_config, uint8 row, uint8 col, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd_config || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        lcd_8bit_set_cursor(_lcd_config, row, col);
        lcd_8bit_send_string(_lcd_config, str);
    }
    
    return ret;
}

/**
 * 
 * @param _lcd_config
 * @param row
 * @param col
 * @param _chr
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t * _lcd_config, uint8 row, uint8 col, uint8 _chr[], uint8 mempos)
{
    Std_ReturnType ret = E_OK;
    uint8 l_cnt = 0;
    if(NULL == _lcd_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        lcd_8bit_send_command(_lcd_config, (_LCD_CGRAM_START + (mempos * 8)));
        for(l_cnt = 0 ; l_cnt < 8 ; l_cnt++)
        {
            lcd_8bit_send_char_data(_lcd_config, _chr[l_cnt]);
        }
        lcd_8bit_send_char_data_pos(_lcd_config, row, col, mempos); 
    }
    
    return ret;
}

/******************************************************************************************************************************
 
 Helper APIs
 
******************************************************************************************************************************/



/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_byte_to_str(uint8 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    memset(str, '\0', 4);
    sprintf(str, "%lu", value);
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_short_to_str(uint16 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    memset(str, '\0', 6);
    sprintf(str, "%lu", value);
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_int_to_str(uint32 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    memset(str, '\0', 11);
    sprintf(str, "%lu", value);
    return ret;
}


/**
 * 
 * @param _lcd_config
 * @param _data_cmd
 * @return 
 */
static Std_ReturnType lcd_send_4bit(const lcd_4bit_t * _lcd_config, uint8 _data_cmd)
{
    Std_ReturnType ret = E_OK;
    
    if  (   (gpio_pin_write_logic(&(_lcd_config->lcd_data[0]), ((_data_cmd >> 0) & (uint8)0x01))) &&
            (gpio_pin_write_logic(&(_lcd_config->lcd_data[1]), ((_data_cmd >> 1) & (uint8)0x01))) && 
            (gpio_pin_write_logic(&(_lcd_config->lcd_data[2]), ((_data_cmd >> 2) & (uint8)0x01))) &&
            (gpio_pin_write_logic(&(_lcd_config->lcd_data[3]), ((_data_cmd >> 3) & (uint8)0x01)))
        )
    {
        /*do nothing*/
    }
    else
    {
        ret= E_NOT_OK;
    }
    
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t * _lcd_config)
{
    Std_ReturnType ret = E_OK;
    
    ret &= gpio_pin_write_logic(&(_lcd_config->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret &= gpio_pin_write_logic(&(_lcd_config->lcd_en), GPIO_LOW);
    
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t * _lcd_config, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    column --;
    
    switch(row)
    {
        case ROW1 : ret &= lcd_4bit_send_command(_lcd_config , (0x80 + column)); break;
        case ROW2 : ret &= lcd_4bit_send_command(_lcd_config , (0xC0 + column)); break;
        case ROW3 : ret &= lcd_4bit_send_command(_lcd_config , (0x94 + column)); break;
        case ROW4 : ret &= lcd_4bit_send_command(_lcd_config , (0xD4 + column)); break;
        default   : ret = E_NOT_OK; break; 
    }
    return ret;
}


static Std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t * _lcd_config)
{
    Std_ReturnType ret = E_OK;
    
    ret &= gpio_pin_write_logic(&(_lcd_config->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret &= gpio_pin_write_logic(&(_lcd_config->lcd_en), GPIO_LOW);
    
    return ret;
}


static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t * _lcd_config, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    column --;
    
    switch(row)
    {
        case ROW1 : ret &= lcd_8bit_send_command(_lcd_config , (0x80 + column)); break;
        case ROW2 : ret &= lcd_8bit_send_command(_lcd_config , (0xC0 + column)); break;
        case ROW3 : ret &= lcd_8bit_send_command(_lcd_config , (0x94 + column)); break;
        case ROW4 : ret &= lcd_8bit_send_command(_lcd_config , (0xD4 + column)); break;
        default   : ret = E_NOT_OK; break; 
    }
    return ret;
}

