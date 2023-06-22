#include "common.h"

typedef enum 
{
	gpt_cha_0=0,
	gpt_cha_1=1,
	gpt_cha_2=2,
	gpt_cha_3=3,
	gpt_cha_4=4,
	gpt_cha_5=5,
	gpt_cha_6=6,
	gpt_cha_7=7,
	gpt_cha_8=8,
	gpt_cha_9=9,
	gpt_cha_10=10,
	gpt_cha_11=11,
}	enu_GPT_CHA_t;

typedef enum 
{
	GPT_ONE_SHOT_MODE=0,
	GPT_PERIODIC_MODE=1,
	GPT_RTC_MODE=2,
	GPT_EDGE_COUNT_MODE=3,
	GPT_INPUT_EDGE_MODE=4,
	GPT_PWM_MODE=5,
	
}	enu_GPT_MODE_t;

typedef enum 
{
	GPT_CONCATENATED_OPERATION=0,
	GPT_INDIVIDUAL_OPERATION=1,
	GPT_RTC_OPERATION=2,

}	enu_GPT_MODULE_OPERATION_t;

typedef enum 
{
	GPT_WITH_INT=0,
	GPT_WITHOUT_INT=1,

}	enu_GPT_INT_OPERATION_t;


typedef enum 
{
		GPT_FREQ_16_MHZ=0,
}	enu_GPT_FREQ_t;

typedef enum 
{
		GPT_MODEL_A=0,
		GPT_MODEL_B=1,
}	enu_GPT_MODEL_t;

typedef enum 
{
		GPT_COUNT_UP=0,
		GPT_COUNT_DOWN=1,
}	enu_GPT_COUNT_DIR_t;

typedef enum 
{
		INVALID_GPT=0,
		VALID_GPT=1,
}	enu_GPT_ERROR_t;

typedef struct
{
	enu_GPT_CHA_t											enu_GPT_CHA;
	enu_GPT_MODE_t										enu_GPT_MODE;
	enu_GPT_MODULE_OPERATION_t 				enu_GPT_MODULE_OPERATION;
	uint64_t 													u64_time_ms;
	enu_GPT_INT_OPERATION_t						enu_GPT_INT_OPERATION;
	enu_GPT_MODEL_t										enu_GPT_MODEL;
	enu_GPT_COUNT_DIR_t								enu_GPT_COUNT_DIR;
	uint16_t                          u16_GPT_PRESCALLER;
}STR_GPT_CONFIG_T;

/********************************************************************************************************/

/********************************Macros***********************************************************/
#define    CONCATENATED_VALUE               0x0
#define    INDIVADUAL_VALUE                 0x4

#define    ONESHOT_PATTERN                  0x1
#define    PERIODIC_MODE_PATTERN            0x2





