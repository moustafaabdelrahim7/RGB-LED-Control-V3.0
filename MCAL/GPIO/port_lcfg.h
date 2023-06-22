

#ifndef port_lcfg_H_
#define port_lcfg_H_
typedef enum 
{
	PORT_PIN_DEN=0,
	PORT_PIN_ANEN=1,
	INVALID_PORT_PIN_MODE=2
}	enu_port_pin_mode_t;



typedef enum 
{
	PIN_LOW=0,
	PIN_HIGH=1,
	INVALID_PIN_LEVEL=2
}	enu_port_pin_level_t;


typedef enum 
{
	PIN_INPUT=0,
	PIN_OUTPUT=1,
	INVALID_PIN_DIR=2	
}	enu_port_pin_direction_t;



typedef enum 
{
	PIN_PUR=0,
	PIN_PDR=1,
	PIN_ODR=2,
	INVALID_PIN_ATTACH=3
	
}	enu_port_pin_internal_attach_t;



typedef enum 
{
	PIN_CUR_2MA=0,
	PIN_CUR_4MA=1,
	PIN_CUR_8MA=2,
	INVALID_PIN_CUR=2
	
}	enu_port_pin_output_current_t;



typedef enum 
{
	PORT_A=0,
	PORT_B=1,
	PORT_C=2,
	PORT_D=3,
	PORT_E=4,
	PORT_F=5,
	INVALID_PORT_NUM=6
}	enu_port_num_t;



typedef enum 
{
	PORT_PIN_0=0,
	PORT_PIN_1=1,
	PORT_PIN_2=2,
	PORT_PIN_3=3,
	PORT_PIN_4=4,
	PORT_PIN_5=5,
	PORT_PIN_6=6,
	PORT_PIN_7=7,
	INVALID_PORT_PIN_NUM=8
}	enu_port_pin_num_t;

typedef enum 
{
	PIN_FALLING_EDGE=0,
	PIN_RISING_EDGE=1,
	PIN_BOTH_EDGES=2,
	PIN_LOW_LEVEL=3,
	PIN_HIGH_LEVEL=4,
	PIN_NO_INTERRUPT=5
}	enu_port_PIN_INT_SENSE_t;


typedef struct
{
	enu_port_pin_mode_t							enu_port_pin_mode;
	enu_port_pin_level_t						enu_port_pin_level;
	enu_port_pin_direction_t				enu_port_pin_direction;
	enu_port_pin_internal_attach_t	enu_port_pin_internal_attach;
	enu_port_pin_output_current_t		enu_port_pin_output_current;
	enu_port_num_t									enu_port_num;
	enu_port_pin_num_t							enu_port_pin_num;
	enu_port_PIN_INT_SENSE_t				enu_port_PIN_INT_SENSE;
} str_port_config_t;


#endif

