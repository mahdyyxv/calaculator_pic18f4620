/* 
 * File:   application.h
 * Author: mahdy
 *
 * Created on August 2, 2023, 3:09 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
extern keypad_t keypad;
extern lcd_4bit_t lcd_2;
//extern lcd_8bit_t lcd_1;
/* Section : Function Prototype */
void application_init(void);
//sint32 power(sint32 number, uint8 power);
//void convert(uint8 * str, sint64 *x);
#endif	/* APPLICATION_H */

