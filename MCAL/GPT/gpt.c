

#include "gpt.h"



/*GPT Registers****************/
/********************************/

#define GPT_OFFSET(x)              (x<8?((0x40030000)+((x)*0x1000)):((0x4004C000)+((x-8)*0x1000)))



/*******Registers MAP**********/
/*Timer Clock register*/
#define RCGCTIMER                  *((volatile uint32_t*)(0x400FE000+0x604))
#define RCGCWTIMER                 *((volatile uint32_t*)(0x400FE000+0x65C))

#define GPTMCFG(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x000))
#define GPTMTAMR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x004))
#define GPTMTBMR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x008))
#define GPTMCTL(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x00C))
#define GPTMSYNC(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x010))
#define GPTMIMR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x018))
#define GPTMRIS(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x01C))
#define GPTMMIS(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x020))
#define GPTMICR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x024))
#define GPTMTAILR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x028))
#define GPTMTBILR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x02C))
#define GPTMTAMATCHR(x)            *((volatile uint32_t*)(GPT_OFFSET(x)+0x030))
#define GPTMTBMATCHR(x)            *((volatile uint32_t*)(GPT_OFFSET(x)+0x034))	
#define GPTMTAPR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x038))
#define GPTMTBPR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x03C))
#define GPTMTAPMR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x040))
#define GPTMTBPMR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x044))
#define GPTMTAR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x048))
#define GPTMTBR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x04C))
#define GPTMTAV(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x050))
#define GPTMTBV(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x054))
#define GPTMRTCPD(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x058))	
#define GPTMTAPS(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x05C))
#define GPTMTBPS(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x060))
#define GPTMTAPV(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x064))
#define GPTMTBPV(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x068))
#define GPTMPP(x)                  *((volatile uint32_t*)(GPT_OFFSET(x)+0xFC0))

/*Timer A Bits*/
#define TAEN                        0
#define TACDIR                      4
#define TAILD                       8
#define TAWOT                       6
#define TATOIM                      0
#define TATOCINT                    0
/*Timer B Bits*/
#define TBEN                        8
#define TBCDIR                      4
#define TBILD                       8
#define TBWOT                       6
#define TBTOIM                      8
#define TBTOCINT                    8


#define PRESCALER_MASK             0xff
                                                   

	

/**********************************************************************************************/

/**Pointer to Function***/
/*Timer_A**/
/*Basic Timer**/
static  void(*gpt_fptr_Timer0A)(void)=NULL;

static  void(*gpt_fptr_Timer0B)(void)=NULL;


/******************************************************************************/
enu_GPT_ERROR_t timer_init( STR_GPT_CONFIG_T* STR_PTR_GPT_CONFIG)
{
	uint8_t uint8_tstatus=SUCCESS;

									/*SET THE TIMER CLK*/
	if (STR_PTR_GPT_CONFIG->enu_GPT_CHA>=0 && STR_PTR_GPT_CONFIG->enu_GPT_CHA<=5 )
	{
		set_bit(RCGCTIMER,STR_PTR_GPT_CONFIG->enu_GPT_CHA);
	}
	else if (STR_PTR_GPT_CONFIG->enu_GPT_CHA>5 && STR_PTR_GPT_CONFIG->enu_GPT_CHA<=11 )
	{
		set_bit(RCGCWTIMER,STR_PTR_GPT_CONFIG->enu_GPT_CHA);
	}
	else
	{
			/*ERROR HANDLING*/
		
	}
/*************************************************************************************/	
					/*DISABLE TIMERS BEFORE START SO YOU WILL NOT PRODUCE A BUS FAULT*/
	clear_bit(GPTMCTL(STR_PTR_GPT_CONFIG->enu_GPT_CHA),TAEN);			//MODEL A
	clear_bit(GPTMCTL(STR_PTR_GPT_CONFIG->enu_GPT_CHA),TBEN);			//MODEL B
/*************************************************************************************/	
	
			/*SET THE MODULE TYPE OF OPERATION */
	
	if (STR_PTR_GPT_CONFIG->enu_GPT_MODULE_OPERATION == GPT_INDIVIDUAL_OPERATION)
	{
		

		  GPTMCFG(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=INDIVADUAL_VALUE;
		
	}
	
	else if (STR_PTR_GPT_CONFIG->enu_GPT_MODULE_OPERATION == GPT_CONCATENATED_OPERATION)
	{
			
			GPTMCFG(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=CONCATENATED_VALUE;
		
	}
	else if (STR_PTR_GPT_CONFIG->enu_GPT_MODULE_OPERATION == GPT_RTC_OPERATION)
	{
			
		/*TO BE HANDLED*/
		
	}
	else
	{
		/*ERROR HANDLING */
	}
/*************************************************************************************/		


	if ((STR_PTR_GPT_CONFIG->enu_GPT_MODULE_OPERATION == GPT_INDIVIDUAL_OPERATION) 
		   && 	(STR_PTR_GPT_CONFIG->enu_GPT_MODEL==GPT_MODEL_A))
	{
						/*set the direction of counting*/
						if (STR_PTR_GPT_CONFIG->enu_GPT_COUNT_DIR == GPT_COUNT_UP)
						{
							clear_bit(GPTMTAMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA),TACDIR);
						}
						else if (STR_PTR_GPT_CONFIG->enu_GPT_COUNT_DIR == GPT_COUNT_UP)
						{
							set_bit(GPTMTAMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA),TACDIR);
						}
						else
						{
							/*error handling*/	
						}
				/*************************************************************************/
									/*set the timer mode*/
					if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_ONE_SHOT_MODE)
					{
							GPTMTAMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=ONESHOT_PATTERN;
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_PERIODIC_MODE)  
					{
						GPTMTAMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=PERIODIC_MODE_PATTERN;
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_RTC_MODE)  
					{
						/*to be handlled*/
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_EDGE_COUNT_MODE)  
					{
						/*to be handlled*/
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_INPUT_EDGE_MODE)  
					{
						/*to be handlled*/
					}
					else 
					{
						/*error handling*/
					}
				
					/***********************************************************************/	
						
									/*configuring the prescaler*/
				
							GPTMTAPR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=STR_PTR_GPT_CONFIG->u16_GPT_PRESCALLER&PRESCALER_MASK;				
						
								/*Load the timer with the required value*/
						
							GPTMTAILR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=(uint16_t)STR_PTR_GPT_CONFIG->u64_time_ms;
		}
		else if ((STR_PTR_GPT_CONFIG->enu_GPT_MODULE_OPERATION == GPT_INDIVIDUAL_OPERATION) 
		   && 	(STR_PTR_GPT_CONFIG->enu_GPT_MODEL==GPT_MODEL_A))
		{
		
		
				/*set the direction of counting*/
						if (STR_PTR_GPT_CONFIG->enu_GPT_COUNT_DIR == GPT_COUNT_UP)
						{
							clear_bit(GPTMTBMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA),TBCDIR);
						}
						else if (STR_PTR_GPT_CONFIG->enu_GPT_COUNT_DIR == GPT_COUNT_UP)
						{
							set_bit(GPTMTBMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA),TBCDIR);
						}
						else
						{
							/*error handling*/	
						}
						/*************************************************************************/
									/*set the timer mode*/
					if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_ONE_SHOT_MODE)
					{
							GPTMTBMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=ONESHOT_PATTERN;
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_PERIODIC_MODE)  
					{
						GPTMTBMR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=PERIODIC_MODE_PATTERN;
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_RTC_MODE)  
					{
						/*to be handlled*/
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_EDGE_COUNT_MODE)  
					{
						/*to be handlled*/
					}
					else if (STR_PTR_GPT_CONFIG->enu_GPT_MODE==GPT_INPUT_EDGE_MODE)  
					{
						/*to be handlled*/
					}
					else 
					{
						/*error handling*/
					}
				
					/***********************************************************************/		
									/*configuring the prescaler*/
							GPTMTBPR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=STR_PTR_GPT_CONFIG->u16_GPT_PRESCALLER&PRESCALER_MASK;					
								/*Load the timer with the required value*/
							GPTMTBILR(STR_PTR_GPT_CONFIG->enu_GPT_CHA)=(uint16_t)STR_PTR_GPT_CONFIG->u64_time_ms;
			/***********************************************************************/	
				
					
				
		}
	
	else if ( STR_PTR_GPT_CONFIG->enu_GPT_MODULE_OPERATION == GPT_CONCATENATED_OPERATION)
	{
		/*TO BE HANDDLED*/
	}
	else if ( STR_PTR_GPT_CONFIG->enu_GPT_MODULE_OPERATION == GPT_RTC_OPERATION)
		{
			/*TO BE HANDDLED*/
		}
		else
		{
			/*error handling*/
		}

}


enu_GPT_ERROR_t timer_start( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL)
{

	  if (enu_GPT_MODEL==GPT_MODEL_A)
		{
			set_bit(GPTMCTL(enu_GPT_CHA),TAEN);
		}
	  else if (enu_GPT_MODEL==GPT_MODEL_B)
		{
			set_bit(GPTMCTL(enu_GPT_CHA),TBEN);
		}
	  else
		{
		/*error handling*/
		}

}

enu_GPT_ERROR_t timer_stop( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL)
{

	  if (enu_GPT_MODEL==GPT_MODEL_A)
		{
			clear_bit(GPTMCTL(enu_GPT_CHA),TAEN);
		}
	  else if (enu_GPT_MODEL==GPT_MODEL_B)
		{
			clear_bit(GPTMCTL(enu_GPT_CHA),TBEN);
		}
	  else
		{
		/*error handling*/
		}

}

enu_GPT_ERROR_t timer_int_enable( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL)
{
	  if (enu_GPT_MODEL==GPT_MODEL_A)
		{
				set_bit(GPTMIMR(enu_GPT_CHA),TATOIM);
				set_bit(GPTMICR(enu_GPT_CHA),TATOCINT);
				if(enu_GPT_CHA==gpt_cha_0)
				{
					NVIC_EnableIRQ(TIMER0A_IRQn);
					__enable_irq();
				}
				else if(enu_GPT_CHA==gpt_cha_1)
				{
					NVIC_EnableIRQ(TIMER1A_IRQn);
					__enable_irq();
				}
				/*to do the rest of the handlers*/
				else
				{
					/*error handling*/
				}
				
		}
	  else if (enu_GPT_MODEL==GPT_MODEL_B)
		{
				set_bit(GPTMICR(enu_GPT_CHA),TBTOCINT);
				set_bit(GPTMIMR(enu_GPT_CHA),TBTOIM);
				if(enu_GPT_CHA==gpt_cha_0)
				{
					NVIC_EnableIRQ(TIMER0B_IRQn);
					__enable_irq();
				}
				else if(enu_GPT_CHA==gpt_cha_1)
				{
					NVIC_EnableIRQ(TIMER1B_IRQn);
					__enable_irq();
				}
				/*to do the rest of the handlers*/
				else
				{
					/*error handling*/
				}
				
		}
	  else
		{
			/*ERROR HANDLING*/
		}
}



enu_GPT_ERROR_t timer_int_disable( enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL)
{

	  if (enu_GPT_MODEL==GPT_MODEL_A)
		{
			clear_bit(GPTMIMR(enu_GPT_CHA),TATOIM);
		}
	  else if (enu_GPT_MODEL==GPT_MODEL_B)
		{
			clear_bit(GPTMIMR(enu_GPT_CHA),TBTOIM);
		}
	  else
		{
			/*ERROR HANDLING*/
		}
}

enu_GPT_ERROR_t timer_interrupt_setcallback(enu_GPT_CHA_t enu_GPT_CHA,enu_GPT_MODEL_t enu_GPT_MODEL,void(*gpt_Fptr)(void))
{
	  if (enu_GPT_MODEL==GPT_MODEL_A)
		{
				if (gpt_Fptr!= NULL)
				{
					gpt_fptr_Timer0A=gpt_Fptr;
				}
				/*to do handle the rest of the callbacks*/
				else
				{
					/*error handling*/
				}
		 }
	  else if (enu_GPT_MODEL==GPT_MODEL_B)
		{
				if (gpt_Fptr!= NULL)
				{
					gpt_fptr_Timer0B=gpt_Fptr;
				}

					/*to do the rest of the callbacks*/
				else
				{
					/*error handling*/
				}
		}
	  else
		{
		/*error handling*/
		}
}




/*******************************************Timer Handler*******************************************************/



void timer_load(uint32_t u32_a_load_value,enu_GPT_CHA_t enu_a_GPT_CHA,enu_GPT_MODEL_t enu_a_GPT_MODEL)
{
	if(enu_a_GPT_MODEL==GPT_MODEL_A)
	{
		GPTMTAILR(enu_a_GPT_CHA)=(uint16_t)u32_a_load_value;
	}
	else if(enu_a_GPT_MODEL==GPT_MODEL_B)
	{
		GPTMTBILR(enu_a_GPT_CHA)=(uint16_t)u32_a_load_value;
	}
	
	

}
void TIMER0A_Handler(void)
{
	if (gpt_fptr_Timer0A!=NULL)
	{
		gpt_fptr_Timer0A();
		set_bit(GPTMICR(gpt_cha_0),TATOCINT);
	}
	else
	{
		/*ERROR HANDLING*/
	}
}


void TIMER0B_Handler(void)
{
	if (gpt_fptr_Timer0B!=NULL)
	{
		gpt_fptr_Timer0B();
		set_bit(GPTMICR(gpt_cha_0),TBTOCINT);
	}
	else
	{
		/*ERROR HANDLING*/
	}
}

