/* 
 * File:   CCP1_CFG.h
 * Author: Yazan Abd-Almajeed
 * Created on September 2, 2023, 11:43 AM
 */

#ifndef CCP1_CFG_H
#define	CCP1_CFG_H

/* ----------------- Includes -----------------*/

/* ----------------- Macro Declarations -----------------*/
#define CCP1_CFG_CAPTURE_MODE_SELECTED  0x00
#define CCP1_CFG_COMPARE_MODE_SELECTED  0x01
#define CCP_CFG_PWM_MODE_SELECTED       0x02

#define CCP1_CFG_SELECTED_MODE  (CCP1_CFG_COMPARE_MODE_SELECTED)
#define CCP2_CFG_SELECTED_MODE  (CCP1_CFG_COMPARE_MODE_SELECTED)

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/

#endif	/* CCP1_CFG_H */

