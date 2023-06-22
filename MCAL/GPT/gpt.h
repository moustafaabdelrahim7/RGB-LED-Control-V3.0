/**
 ** @file                   gpt.h
 ** @brief                  This is header file for GPT for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef GPT_H_
#define GPT_H_
 #include "gpt_lcfg.h"
 #include "common.h"
 #include "TM4C123.h"
 
 
/*********************************Timers**********************************************************/






/*---------------------------------------------------------/
/- APIs IMPLEMENTATION -----------------------------------/
/---------------------------------------------------------*/

enu_GPT_ERROR_t timer_init( STR_GPT_CONFIG_T* STR_PTR_GPT_CONFIG);

enu_GPT_ERROR_t timer_start( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL);

enu_GPT_ERROR_t timer_stop( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL);

enu_GPT_ERROR_t timer_int_enable( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL);

enu_GPT_ERROR_t timer_int_disable( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL);

enu_GPT_ERROR_t timer_interrupt_setcallback(enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL,void(*gpt_Fptr)(void));

void timer_load(uint32_t u32_a_load_value,enu_GPT_CHA_t enu_a_GPT_CHA,enu_GPT_MODEL_t enu_a_GPT_MODEL);
 

 
 
 #endif /* GPT_H_ */
 
 
 
 
 
 