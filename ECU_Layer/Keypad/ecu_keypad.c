/* 
 * File:   ecu_keypad.c
 * Author: mahdy
 *
 * Created on August 8, 2023, 2:40 PM
 */


#include "ecu_keypad.h"
static const uint8 keypad_elements[ECU_KEYPAD_ROW][ECU_KEYPAD_COLUMN] = {
                                                                            {'7', '8', '9', '/'},
                                                                            {'4', '5', '6', '*'},
                                                                            {'1', '2', '3', '-'},
                                                                            {'#', '0', '=', '+'}
                                                                        };

/**
 * 
 * @param keypad_config
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */

Std_ReturnType keypad_initialization(const keypad_t* keypad_config)
{
    Std_ReturnType ret = E_OK;
    uint8 cnt = 0, flg = 0;
    if(NULL == keypad_config)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(cnt = 0; cnt < ECU_KEYPAD_ROW; cnt++)
        {
            if(gpio_pin_direction_init(&(keypad_config->keypad_row[cnt])))
            {
                continue;
            }
            else
            {
                ret = E_NOT_OK;
                flg = 1;
                break;
            }
        }
        if(flg == 0)
        {
            for(cnt = 0; cnt < ECU_KEYPAD_COLUMN; cnt++)
            {
                if(gpio_pin_direction_init(&(keypad_config->keypad_col[cnt])))
                {
                    continue;
                }
                else
                {
                    ret = E_NOT_OK;
                    flg = 1;
                    break;
                }
            }
        }
    }
    return ret;
}

/**
 * 
 * @param keypad_config
 * @param value
 * @return Status of the function
 *          (E_OK)     : the function done successfully
 *          (E_NOT_OK) : the function has issue
 */
Std_ReturnType  keypad_get_value(const keypad_t* keypad_config, uint8 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 row_counter = 0, column_counter = 0;
    logic_t column_value = 0;
    
    if(NULL == keypad_config || NULL == value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(row_counter = 0; row_counter < ECU_KEYPAD_ROW ; row_counter++)
        {
            gpio_pin_write_logic(&(keypad_config->keypad_row[row_counter]), GPIO_LOW);
        }
        
        for(row_counter = 0; row_counter < ECU_KEYPAD_ROW ; row_counter++)
        {
            gpio_pin_write_logic(&(keypad_config->keypad_row[row_counter]), GPIO_HIGH);
            for(column_counter = 0; column_counter < ECU_KEYPAD_COLUMN ; column_counter++)
            {
                gpio_pin_read_logic(&(keypad_config->keypad_col[column_counter]), &column_value);
                if(GPIO_HIGH == column_value)
                {
                    __delay_ms(10);
                    gpio_pin_read_logic(&(keypad_config->keypad_col[column_counter]), &column_value);
                    if(GPIO_HIGH == column_value)
                    {
                        *value = keypad_elements[row_counter][column_counter];
                        gpio_pin_read_logic(&(keypad_config->keypad_col[column_counter]), &column_value);
                        while(GPIO_HIGH == column_value)
                        {
                            gpio_pin_read_logic(&(keypad_config->keypad_col[column_counter]), &column_value);
                        }
                    }
                    
                    
                }
            }
            gpio_pin_write_logic(&(keypad_config->keypad_row[row_counter]), GPIO_LOW);
        }
        
    }
    return ret;
}