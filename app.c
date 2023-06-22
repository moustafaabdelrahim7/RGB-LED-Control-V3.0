#include "app.h"
#define LED_30_percent			6000
#define LED_60_percent			12000
#define LED_90_percent			18000

extern const str_port_config_t	str_port_config_arr[3];
extern STR_GPT_CONFIG_T STR_GPT_CONFIG_ptr;
uint8_t u8_gv_Counter=1;

void app_start(void)
{
if((BUTTON_READ(PORT_PIN_4,PORT_F)))
		{
			
					
					if(u8_gv_Counter==1)
					{
						timer_load(LED_30_percent,gpt_cha_0,GPT_MODEL_A);
						timer_start(gpt_cha_0,GPT_MODEL_A);
							u8_gv_Counter++;
					}
					else if(u8_gv_Counter==2)
					{
						timer_load(LED_60_percent,gpt_cha_0,GPT_MODEL_A);
						timer_start(gpt_cha_0,GPT_MODEL_A);	
							u8_gv_Counter++;
					}
					else if(u8_gv_Counter==3)
					{
						timer_load(LED_90_percent,gpt_cha_0,GPT_MODEL_A);
						timer_start(gpt_cha_0,GPT_MODEL_A);
				
							u8_gv_Counter++;
					}
					else if(u8_gv_Counter==4)
					{
						LED_OFF(PORT_F,PORT_PIN_3);
						timer_stop(gpt_cha_0,GPT_MODEL_A);
							u8_gv_Counter=1;
					}
			
			}
}
/*************************************************************************/

void app_init(void)
{
	LED_INIT(str_port_config_arr);
	BUTTON_INIT(str_port_config_arr);
	timer_init(&STR_GPT_CONFIG_ptr);
	timer_interrupt_setcallback(gpt_cha_0,GPT_MODEL_A,timer_callback);
	timer_int_enable(gpt_cha_0,GPT_MODEL_A);
	
}


/*************************************************************************/

	
void timer_callback (void)
{

	LED_TOGGEL(PORT_F,PORT_PIN_3);
}


