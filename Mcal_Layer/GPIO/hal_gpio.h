/* 
 * File:   hal_gpio.h
 * Author: mahdy
 *
 * Created on August 1, 2023, 4:25 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/* Section : Includes */
#include <pic18f4620.h>
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"
/* Section : Macro Declarations */
#define BIT_MASK                    (uint8)1
#define PIN_MAX_NUM                 8
#define PORT_MAX_NUM                5

#define PORT_MASK                   0xFF
/* Section : Macro Functions Declarations */
#define HWREG(ADDR)                 (*((volatile uint8 *)(ADDR)))

#define SET_BIT(REG, BIT_POS)       (REG |= (BIT_MASK << BIT_POS))
#define CLEAR_BIT(REG, BIT_POS)     (REG &= ~(BIT_MASK << BIT_POS))
#define TOGGLE_BIT(REG, BIT_POS)    (REG ^= (BIT_MASK << BIT_POS))
#define READ_BIT(REG, BIT_POS)      ( (REG >> BIT_POS) & BIT_MASK )

/* Section : Data Type Declarations */

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum
{
    GPIO_OUTPUT = 0,
    GPIO_INPUT
}direction_t;

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    
}pin_index_t;

typedef enum
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;

typedef struct
{
    uint8 port      : 3; /* @ref port_index_t */
    uint8 pin       : 3; /* @ref port_index_t */
    uint8 direction : 1; /* @ref port_index_t */ 
    uint8 logic     : 1;
}pin_config_t;
/* Section : Function Prototype */

Std_ReturnType gpio_pin_direction_init(const pin_config_t * _pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config, direction_t *dic_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config, logic_t _logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config, logic_t *_logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config);

Std_ReturnType gpio_port_direction_init(port_index_t port, uint8 status);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

