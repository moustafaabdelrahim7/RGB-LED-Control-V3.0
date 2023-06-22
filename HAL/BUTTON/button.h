#ifndef BUTTON_H_
#define BUTTON_H_

#include "gpio.h"


uint8_t BUTTON_READ	(enu_port_pin_num_t enu_port_pin_num, enu_port_num_t enu_port_num);
void BUTTON_INIT(const str_port_config_t*str_port_configPTR);


#endif /* BUTTON_H_ */

