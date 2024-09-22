/* 
 * File:   MCAL_STD_Types.h
 * Author: Yazan Abd-Almajeed
 * Created on July 16, 2023, 12:10 PM
 */

#ifndef _MCAL_STD_Types_H
#define _MCAL_STD_Types_H

/* Section : Includes */
#include "STD_Libraries.h"
#include "Compiler.h"

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */
typedef signed char         sint8;
typedef unsigned char       uint8;
typedef signed short        sint16;
typedef unsigned short      uint16;
typedef signed long         sint32;
typedef unsigned long       uint32;

typedef uint8       Std_Return_Type;

/* Section : Macro Declarations */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01 
#define STD_IDLE        0x00

#define E_OK            (Std_Return_Type)0x01
#define E_NOT_OK        (Std_Return_Type)0x00

#define ZERO_INIT   0

/* Section : Function Declaration */

#endif //_MCAL_STD_Types_H

