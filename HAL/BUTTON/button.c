
 #include "button.h"
 
 
 
 
uint8_t BUTTON_READ	(enu_port_pin_num_t enu_port_pin_num, enu_port_num_t enu_port_num)
{
	uint8_t u8_l_status=0;

	

	if(!GPIO_READ_PIN(enu_port_num,enu_port_pin_num))
	{
		u8_l_status=1;
		while(!GPIO_READ_PIN(enu_port_num,enu_port_pin_num));	
	}
	
	return u8_l_status;

	
}
/*********************************************************************************************/

void BUTTON_INIT(const str_port_config_t*str_port_configPTR)
{

	GPIO_INIT_PIN(str_port_configPTR);

}
 
 
 