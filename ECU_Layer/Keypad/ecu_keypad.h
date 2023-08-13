/* 
 * File:   ecu_keypad.h
 * Author: mahdy
 *
 * Created on August 8, 2023, 2:40 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "ecu_keypad_cfg.h"
#include "../../Mcal_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */

#define ECU_KEYPAD_ROW      4
#define ECU_KEYPAD_COLUMN   4

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef struct
{
    pin_config_t keypad_row[ECU_KEYPAD_ROW];
    pin_config_t keypad_col[ECU_KEYPAD_COLUMN];      
}keypad_t;
/* Section : Function Prototype */

Std_ReturnType keypad_initialization(const keypad_t* keypad_config);
Std_ReturnType keypad_get_value(const keypad_t* keypad_config, uint8 *value);

#endif	/* ECU_KEYPAD_H */

