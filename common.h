
/**
 ** @file                   common.h
 ** @brief                  This is header file for common usage macros and defintions
 ** @author                 Mohamed Sayed
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */


#ifndef COMMON_H_
#define COMMON_H_


/*********************************************************************************/
/* Includes***********************************************************************/
/*********************************************************************************/
#include "stdint.h"

#define  SUCCESS               	 (0)
#define  ERROR                 		 (1)
#define  INVALID_INPUT        		  (2)
#define  NULL              			 ((void*)0)
#ifndef  TRUE
 #define TRUE                   (1u)
#endif

#ifndef FALSE
 #define FALSE                  (0u)
#endif

/***********************************************************************************/
/* Typedef**************************************************************************/
/***********************************************************************************/

typedef unsigned char             boolean;
/***********************************************************************************/
/*Bit Operations********************************************************************/
/***********************************************************************************/

#define read_bit(reg,bit_idx)   (0UL!=((reg) & (1UL <<(bit_idx))))

#define set_bit(reg,bit_idx)    (reg|=(1 << bit_idx))

#define clear_bit(reg,bit_idx)  (reg&=(~(1 <<(bit_idx))))

#define toggel_bit(reg,bit_idx) (reg^=(1UL <<(bit_idx)))


#endif /* COMMON_H_ */


