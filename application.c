/* 
 * File:   application.c
 * Author: mahdy
 *
 * Created on August 1, 2023, 3:35 PM
 */

#include "application.h"
uint8 smile[] = {
  0x00,
  0x00,
  0x0A,
  0x00,
  0x11,
  0x11,
  0x0E,
  0x00
};

uint8 keypad_value = 0;
Std_ReturnType ret = E_NOT_OK;
sint64 number1 = 0;
sint64 number2 = 0;
sint64 result = 0;
float float_res = 0;
uint8 string[100]="";
uint8 counter = 0, counter2 = 0;
uint8 operator = ' ';
uint8 number_str[11] = "";
uint8 flag = 0;
uint8 result_str[20] = "";
uint8 *ptr;
int main(void) {
    application_init();
    memset(string , '\0', 100);
    memset(number_str, '\0', 11);
    memset(result_str, '\0', 20);
    ret = lcd_4bit_send_string_pos(&lcd_2, 1,4, "Welcome To My");
    ret = lcd_4bit_send_string_pos(&lcd_2, 2,5, "Calculator");
    ret = lcd_4bit_send_custom_char(&lcd_2, 2,16, smile, 0);
    __delay_ms(2000);
    ret = lcd_4bit_send_command(&lcd_2, _LCD_CLEAR);
    while(1)
    {
        keypad_get_value(&keypad, &keypad_value);
       // ret = lcd_4bit_send_string_pos(&lcd_2, 1,1, "hii");
        if(keypad_value != 0)
        {
            if('=' == keypad_value)
            {
                number2 = strtoll(number_str, &ptr, 10);
                //lcd_4bit_send_string_pos(&lcd_2, 4,1, number_str);
                memset(number_str, '\0', 11);
                switch(operator)
                {
                    case '+' : result = number1 + number2; break;
                    case '-' : result = number1 - number2; break;
                    case '/' : float_res = (float)number1 / (float)number2; break;
                    case '*' : result = number1 * number2; break;
                    default  : strcpy(result_str, "Can't do operation"); break;
                }
                if(strcmp(result_str, "Can't do operation") == 0)
                {
                    lcd_4bit_send_string_pos(&lcd_2, 3,1, result_str);
                }
                else
                {
                    if(operator == '/')
                    {
                        sprintf(result_str, "%.3f", float_res);
                        lcd_4bit_send_string_pos(&lcd_2, 3,1, result_str);
                    }
                    else
                    {
                        sprintf(result_str, "%ld", result);
                        lcd_4bit_send_string_pos(&lcd_2, 3,1, result_str);
                    }
                }
            }
            else if ( '#' == keypad_value){
                ret = lcd_4bit_send_command(&lcd_2, _LCD_CLEAR);
                memset(string , '\0', 100);
                memset(number_str, '\0', 11);
                memset(result_str, '\0', 20);
                result = 0;
                number1 = 0;
                number2 = 0;
                counter = 0;
                counter2 = 0;
                flag = 0;
            }
            else if( ('+' == keypad_value) || ('*' == keypad_value) || ('/' == keypad_value) || ('-' == keypad_value) )
            {
                
                operator = keypad_value;
                number1 = strtoll(number_str, &ptr, 10);
                //lcd_4bit_send_string_pos(&lcd_2, 2,1, number_str);
                //convert(number_str, &number1);
                memset(number_str, '\0', 11);
                flag = 1;
                string[counter] = keypad_value;
                counter++;
            }
            else
            {
                string[counter] = keypad_value;
                
                if(flag == 0)
                {
                    number_str[counter] = keypad_value;
                }
                else{
                    number_str[counter2] = keypad_value;
                    counter2++;
                }
                counter++;
                
            }    
            ret = lcd_4bit_send_string_pos(&lcd_2, 1,1, string);        
            keypad_value = 0;
        }
    }
    return (EXIT_SUCCESS);
}

void application_init(void)
{
    ecu_layer_init();
}

//
//sint32 power(sint32 number, uint8 power)
//{
//	uint32 x = 1;
//	uint8 cnt = 0;
//	for(cnt = 0; cnt < power; cnt++)
//	{
//		x *= number;
//	}
//	return x;
//}
//void convert(uint8 * str, sint64 *x)
//{
//	uint8 cnt;
//	for(cnt = (strlen(str)-1); cnt>=0; cnt--)
//	{
//		*x += ((str[cnt] - 48) * (power(10, (strlen(str) - cnt-1))));
//	}
//}
