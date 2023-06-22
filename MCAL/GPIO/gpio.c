/**
 ** @file                   gpio.c
 ** @brief                  This is header file for GPIO for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

#include "gpio.h"

/*used for simulator --> Map range to be added 0x40000000, 0x400fffff*/

/***********Pointer to function*********************/
static  void(*fptr_A)(void);
static  void(*fptr_B)(void);
static  void(*fptr_C)(void);
static  void(*fptr_D)(void);
static  void(*fptr_E)(void);
static  void(*fptr_F)(void);
/**************************************************/

/****************Glopal Pins for interrupt*********/
//static volatile uint8_t portA_pin=PIN_TOTAL;
//static volatile uint8_t portB_pin=PIN_TOTAL;
//static volatile uint8_t portC_pin=PIN_TOTAL;
//static volatile uint8_t portD_pin=PIN_TOTAL;
//static volatile uint8_t portE_pin=PIN_TOTAL;
//static volatile uint8_t portF_pin=PIN_TOTAL;

/*GPIO Registers****************/
/********************************/
#define GPIO_APB
#ifdef GPIO_APB
#define GPIO_OFFSET(x)              (x<4?((0x40004000)+((x)*0x1000)):((0x40024000)+((x-4)*0x1000)))

#define GPIO_LOCK_PATTERN           (0x4C4F434B)
#define GPIO_UNLOCK_PATTERN         (2)
//#define GPIO_PORE_A_OFFSET        (0x40004000)
//#define GPIO_PORE_B_OFFSET        (0x40005000)
//#define GPIO_PORE_C_OFFSET        (0x40006000)
//#define GPIO_PORE_D_OFFSET        (0x40007000)
//#define GPIO_PORE_E_OFFSET        (0x40024000)
//#define GPIO_PORE_F_OFFSET        (0x40025000)
#elif GPIO_AHB
#error "Not Supported Yet"
#else
#error "Please choose a bus for GPIOs"
#endif



/*******Registers MAP**********/
#define RCGCGPIO                   *((volatile uint32_t*)((0x400FE000)+0x608))

#define GPIODATA(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x3FC))
#define GPIODIR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x400))
#define GPIOIS(x)                  *((volatile uint32_t*)(GPIO_OFFSET(x)+0x404))
#define GPIOIBE(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x408))
#define GPIOIEV(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x40C))
#define GPIOIM(x)                  *((volatile uint32_t*)(GPIO_OFFSET(x)+0x410))
#define GPIORIS(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x414))
#define GPIOMIS(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x418))
#define GPIOICR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x41C))
#define GPIOAFSEL(x)               *((volatile uint32_t*)(GPIO_OFFSET(x)+0x420))
#define GPIODR2R(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x500))
#define GPIODR4R(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x504))
#define GPIODR8R(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x508))	
#define GPIOODR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x50C))
#define GPIOPUR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x510))
#define GPIOPDR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x514))
#define GPIOSLR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x518))
#define GPIODEN(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x51C))
#define GPIOLOCK(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x520))
#define GPIOCR(x)                  *((volatile uint32_t*)(GPIO_OFFSET(x)+0x524))
#define GPIOAMSEL(x)               *((volatile uint32_t*)(GPIO_OFFSET(x)+0x528))
#define GPIOPCTL(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x52C))	
#define GPIOADCCTL(x)              *((volatile uint32_t*)(GPIO_OFFSET(x)+0x530))
#define GPIODMACTL(x)              *((volatile uint32_t*)(GPIO_OFFSET(x)+0x534))
#define GPIOPeriphID4(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFD0))
#define GPIOPeriphID5(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFD4))
#define GPIOPeriphID6(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFD8))
#define GPIOPeriphID7(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFDC))
#define GPIOPeriphID0(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFE0))
#define GPIOPeriphID1(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFE4))
#define GPIOPeriphID2(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFE8))
#define GPIOPeriphID3(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFEC))
#define GPIOPCellID0(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFF0))
#define GPIOPCellID1(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFF4))
#define GPIOPCellID2(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFF8))
#define GPIOPCellID3(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFFC))
	

/**********************************************************************************************/

#define PORT_LOCK_VALUE							(uint32_t)(0x4C4F434B)
#define BIT_MASKING_OFFSET					(uint8_t)(2)
#define PCTL_PIN_MASK								(uint32_t)(0x0000000F)
#define PCTL_PIN_BIT_NUM						(uint8_t)(4)
#define MIN_PCTL_VAL								(uint8_t)(1)
#define MAX_PCTL_VAL								(uint8_t)(15)


void GPIO_INIT_PIN(const str_port_config_t*str_port_configPTR)
{
	uint8_t u8_lv_PinCounter=0;
	if(str_port_configPTR!=NULL)
	{
			for(u8_lv_PinCounter=0;	u8_lv_PinCounter<port_pin_num;	u8_lv_PinCounter++)
			{
					enu_port_num_t	port_num=str_port_configPTR[u8_lv_PinCounter].enu_port_num;
					
					enu_port_pin_num_t	pin_num=str_port_configPTR[u8_lv_PinCounter].enu_port_pin_num;
					
				
							set_bit(RCGCGPIO,port_num);
					
					/*set the direction*/
					if(	str_port_configPTR[u8_lv_PinCounter].enu_port_pin_direction	==	PIN_OUTPUT)
					{
						
								set_bit(GPIODIR(port_num),pin_num);
								
								/*configure the pin level*/
								if(	str_port_configPTR[u8_lv_PinCounter].enu_port_pin_level	==	PIN_HIGH)
								{
									set_bit(GPIODATA(port_num),pin_num);
								}
								else if( str_port_configPTR[u8_lv_PinCounter].enu_port_pin_level	==	PIN_LOW)
								{
									clear_bit(GPIODATA(port_num),pin_num);
								}
								else
								{
									/*error handlin*/
								}
								
								/*define o/p current*/
								switch (str_port_configPTR[u8_lv_PinCounter].enu_port_pin_output_current)
								{
										case PIN_CUR_2MA:
										{
											set_bit(GPIODR2R(port_num),pin_num);
											break;
										}
											
										case PIN_CUR_4MA:
										{
											set_bit(GPIODR4R(port_num),pin_num);
											break;
										}
										
										case PIN_CUR_8MA:
										{
											set_bit(GPIODR8R(port_num),pin_num);
											break;
										}
										
										default:
										{
											/*error handline*/
											break;
										}
								}
					}
					else if(str_port_configPTR[u8_lv_PinCounter].enu_port_pin_direction	==	PIN_INPUT)
					{
								clear_bit(GPIODIR(port_num),pin_num);
								switch	(str_port_configPTR[u8_lv_PinCounter].enu_port_pin_internal_attach)
								{
									case PIN_PUR:
									{
											
										clear_bit(GPIOPDR(port_num),pin_num);
										clear_bit(GPIOODR(port_num),pin_num);
										set_bit(GPIOPUR(port_num),pin_num);
									
										break;
										
									}
									case PIN_PDR:
									{
										clear_bit(GPIOODR(port_num),pin_num);
										clear_bit(GPIOPUR(port_num),pin_num);
										set_bit(GPIOPDR(port_num),pin_num);
										break;
									}
									case PIN_ODR:
									{
										set_bit(GPIOODR(port_num),pin_num);
										break;
									}
									case INVALID_PIN_ATTACH:
									{
										break;	/*HANDLE ERROR*/
									}
								
								}
									/*configure the pin level*/
								if(	str_port_configPTR[u8_lv_PinCounter].enu_port_pin_level	==	PIN_HIGH)
								{
									set_bit(GPIODATA(port_num),pin_num);
								}
								else if( str_port_configPTR[u8_lv_PinCounter].enu_port_pin_level	==	PIN_LOW)
								{
									clear_bit(GPIODATA(port_num),pin_num);
								}
								else
								{
									/*error handlin*/
								}

					}
					else
					{
						/*handle error*/
						break;
					}
				
					
					
					/*configure pin mode*/
					if(str_port_configPTR[u8_lv_PinCounter].enu_port_pin_mode	==	PORT_PIN_DEN)
					{
							/*disable alternative func*/
							clear_bit(GPIOAFSEL(port_num),pin_num);
							/*enable digital moode*/
							set_bit(GPIODEN(port_num),pin_num);
							/*disable analog moode*/
							clear_bit(GPIOAMSEL(port_num),pin_num);

					}
					else if(str_port_configPTR[u8_lv_PinCounter].enu_port_pin_mode	==	PORT_PIN_ANEN)
					{
						/*hanlde the analog cases */
					}
					else
					{
						/*handle error*/
						break;
					}
					
					/*HANDLING GPIO INTERRUPT*/
					if(str_port_configPTR[u8_lv_PinCounter].enu_port_PIN_INT_SENSE !=PIN_NO_INTERRUPT)
					{
							/*configuring all possabiliteis of sense control*/
							switch (str_port_configPTR[u8_lv_PinCounter].enu_port_PIN_INT_SENSE)
							{
									case PIN_FALLING_EDGE:
									{
										/*choosing edge sensitive */
										clear_bit(GPIOIS(port_num),pin_num);
										/*to be able to choose one type of edges*/
										clear_bit(GPIOIBE(port_num),pin_num);
										/*to choose the right edge*/
										clear_bit(GPIOIEV(port_num),pin_num);
										break;
									}
									case PIN_RISING_EDGE:
									{
										/*choosing edge sensitive */
										clear_bit(GPIOIS(port_num),pin_num);
										/*to be able to choose one type of edges*/
										clear_bit(GPIOIBE(port_num),pin_num);
										/*to choose the right edge*/
										set_bit(GPIOIEV(port_num),pin_num);
										break;
									}
									case PIN_BOTH_EDGES:
									{
										/*choosing edge sensitive */
										clear_bit(GPIOIS(port_num),pin_num);
										/*to choose both edges*/
										set_bit(GPIOIBE(port_num),pin_num);
										break;
									}
									case PIN_LOW_LEVEL:
									{
										/*choosing level sensitive */
										set_bit(GPIOIS(port_num),pin_num);
										/*to be able to choose one type of level*/
										clear_bit(GPIOIBE(port_num),pin_num);
										/*to choose the right level*/
										clear_bit(GPIOIEV(port_num),pin_num);
										break;
									}
									case PIN_HIGH_LEVEL:
									{
										/*choosing level sensitive */
										set_bit(GPIOIS(port_num),pin_num);
										/*to be able to choose one type of level*/
										clear_bit(GPIOIBE(port_num),pin_num);
										/*to choose the right edge*/
										set_bit(GPIOIEV(port_num),pin_num);
										break;
									}
									case PIN_NO_INTERRUPT:
									{
										/*do nothing*/
										break;
									}
									default:
									{
										/*eroor handling*/
										break;
									
									}
								
							}
					
							GPIO_INTERRUPT_SET_MASKING(port_num,pin_num);
					}
					else
					{
						/*do nothing*/
					}
					/*TO SENT INTERRPUT TO INTERRUPT CONTROLLER*/
				
			}
	}
	else
	{
		/*error hadling*/
	}

}



/***********************************************************************************/

void GPIO_SET_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num)
{
		if( (enu_port_num<INVALID_PORT_NUM) && (enu_port_pin_num<INVALID_PORT_PIN_NUM))
		{	
			set_bit(GPIODATA(enu_port_num),enu_port_pin_num);
		}
		else
		{
		/*handle error state*/	
		}

}

/**************************************************************************************/
void GPIO_CLEAR_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num)
{
		if( (enu_port_num<INVALID_PORT_NUM) && (enu_port_pin_num<INVALID_PORT_PIN_NUM))
		{	
			clear_bit(GPIODATA(enu_port_num),enu_port_pin_num);
		}
		else
		{
		/*handle error state*/	
		}
}


/*****************************************************************************************/
void GPIO_TOGGEL_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num)
{
			if( (enu_port_num<INVALID_PORT_NUM) && (enu_port_pin_num<INVALID_PORT_PIN_NUM))
			{	
				toggel_bit(GPIODATA(enu_port_num),enu_port_pin_num);
			}
			else
			{
			/*handle error state*/	
			}
}

/*****************************************************************************************/
uint8_t GPIO_READ_PIN	(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num)
{
	uint8_t STATUS=9;
			if( (enu_port_num<INVALID_PORT_NUM) && (enu_port_pin_num<INVALID_PORT_PIN_NUM))
			{	
				 STATUS=read_bit(GPIODATA(enu_port_num),enu_port_pin_num);
			}
			else
			{
			/*handle error state*/	
			}
			return STATUS;
}

/*********************************************************************************************/


static void GPIO_INTERRUPT_SET_MASKING(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num)
{
	set_bit(GPIOIM(enu_port_num),enu_port_pin_num);
}

/************************************************************************************************/
			
						/*TO BE USED AT THE END OF A HANDLER*/
static void GPIO_INTERRUPT_CLEAR(enu_port_num_t enu_port_num,enu_port_pin_num_t enu_port_pin_num)
{
	set_bit(GPIOICR(enu_port_num),enu_port_pin_num);
}

