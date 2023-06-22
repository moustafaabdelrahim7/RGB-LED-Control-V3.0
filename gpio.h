/**
 ** @file                   gpio.h
 ** @brief                  This is header file for GPIO for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef GPIO_H_
#define GPIO_H_
#include "port_lcfg.h"
#include "common.h"
#include "TM4C123.h"

/**************************************Macros************************************/

/*************************Accroding to misra rules*******************************/
#define port_pin_num			4

void GPIO_INIT_PIN(const str_port_config_t*str_port_configPTR);

void GPIO_SET_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num);

void GPIO_CLEAR_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num);

void GPIO_TOGGEL_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num);

void GPIO_INTERRUPT_SET_MASKING(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num);

void GPIO_INTERRUPT_CLEAR(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num);

uint8_t GPIO_READ_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num);







#endif /* GPIO_H_ */




