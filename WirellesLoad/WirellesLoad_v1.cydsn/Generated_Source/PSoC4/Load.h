/*******************************************************************************
* File Name: Load.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Load_H) /* Pins Load_H */
#define CY_PINS_Load_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Load_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Load_Write(uint8 value) ;
void    Load_SetDriveMode(uint8 mode) ;
uint8   Load_ReadDataReg(void) ;
uint8   Load_Read(void) ;
uint8   Load_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Load_DRIVE_MODE_BITS        (3)
#define Load_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Load_DRIVE_MODE_BITS))

#define Load_DM_ALG_HIZ         (0x00u)
#define Load_DM_DIG_HIZ         (0x01u)
#define Load_DM_RES_UP          (0x02u)
#define Load_DM_RES_DWN         (0x03u)
#define Load_DM_OD_LO           (0x04u)
#define Load_DM_OD_HI           (0x05u)
#define Load_DM_STRONG          (0x06u)
#define Load_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Load_MASK               Load__MASK
#define Load_SHIFT              Load__SHIFT
#define Load_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Load_PS                     (* (reg32 *) Load__PS)
/* Port Configuration */
#define Load_PC                     (* (reg32 *) Load__PC)
/* Data Register */
#define Load_DR                     (* (reg32 *) Load__DR)
/* Input Buffer Disable Override */
#define Load_INP_DIS                (* (reg32 *) Load__PC2)


#if defined(Load__INTSTAT)  /* Interrupt Registers */

    #define Load_INTSTAT                (* (reg32 *) Load__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Load_DRIVE_MODE_SHIFT       (0x00u)
#define Load_DRIVE_MODE_MASK        (0x07u << Load_DRIVE_MODE_SHIFT)


#endif /* End Pins Load_H */


/* [] END OF FILE */
