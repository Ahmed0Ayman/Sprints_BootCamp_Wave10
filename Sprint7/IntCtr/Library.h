#ifndef __LIBRARY__H_
#define __LIBRARY__H_

#include <stdbool.h>
#include <stdlib.h>


typedef enum {Bit_0 ,Bit_1 ,Bit_2 ,Bit_3 , Bit_4 ,Bit_5 ,Bit_6 ,Bit_7 ,
							Bit_8 ,Bit_9 ,Bit_10 ,Bit_11 , Bit_12 ,Bit_13 ,Bit_14 ,Bit_15 ,
							Bit_16 ,Bit_17 ,Bit_18 ,Bit_19 , Bit_20 ,Bit_21 ,Bit_22 ,Bit_23 ,
							Bit_24 ,Bit_25 ,Bit_26 ,Bit_27 , Bit_28 ,Bit_29 ,Bit_30 ,Bit_31 }Bit_Num_t ; 


							
typedef enum { E_OK , E_NOK }Error_t;



static inline void SetBit(unsigned volatile long   Reg ,Bit_Num_t  BitNum)
{
		Reg   |= BitNum ;		
}



static inline void  ClrBit(unsigned volatile long   Reg ,Bit_Num_t  BitNum)
{
		Reg &= ~BitNum ;
}



static inline bool GetBit(unsigned volatile int  Reg ,Bit_Num_t  BitNum)
{
		return (Reg & BitNum );
}



/****************************************************
*										STD_TYPES												*
****************************************************/

typedef  unsigned int uint32;


typedef  unsigned short int uint16;



typedef  signed int int32;


typedef  signed short int int16;



typedef  unsigned char uint8;


typedef  signed char int8;



void static inline CpuDriver_EnableglobalInterrupt(void)
{
	__asm__ 	inline volatile ( " CPSIE   i  ");
}



void static inline  CpuDriver_DisableglobalInterrupt(void)
{
 __asm__ 	inline volatile ( " CPSID   i  ");
}


void  CpuDriver_StartCriticalSection(void);



void CpuDriver_StopCriticalSection(void);




#endif	 /* __LIBRARY__H_ */
