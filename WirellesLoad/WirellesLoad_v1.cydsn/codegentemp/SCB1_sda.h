/*******************************************************************************
* File Name: SCB1_sda.h  
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

#if !defined(CY_PINS_SCB1_sda_H) /* Pins SCB1_sda_H */
#define CY_PINS_SCB1_sda_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SCB1_sda_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SCB1_sda_Write(uint8 value) ;
void    SCB1_sda_SetDriveMode(uint8 mode) ;
uint8   SCB1_sda_ReadDataReg(void) ;
uint8   SCB1_sda_Read(void) ;
uint8   SCB1_sda_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SCB1_sda_DRIVE_MODE_BITS        (3)
#define SCB1_sda_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SCB1_sda_DRIVE_MODE_BITS))

#define SCB1_sda_DM_ALG_HIZ         (0x00u)
#define SCB1_sda_DM_DIG_HIZ         (0x01u)
#define SCB1_sda_DM_RES_UP          (0x02u)
#define SCB1_sda_DM_RES_DWN         (0x03u)
#define SCB1_sda_DM_OD_LO           (0x04u)
#define SCB1_sda_DM_OD_HI           (0x05u)
#define SCB1_sda_DM_STRONG          (0x06u)
#define SCB1_sda_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SCB1_sda_MASK               SCB1_sda__MASK
#define SCB1_sda_SHIFT              SCB1_sda__SHIFT
#define SCB1_sda_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SCB1_sda_PS                     (* (reg32 *) SCB1_sda__PS)
/* Port Configuration */
#define SCB1_sda_PC                     (* (reg32 *) SCB1_sda__PC)
/* Data Register */
#define SCB1_sda_DR                     (* (reg32 *) SCB1_sda__DR)
/* Input Buffer Disable Override */
#define SCB1_sda_INP_DIS                (* (reg32 *) SCB1_sda__PC2)


#if defined(SCB1_sda__INTSTAT)  /* Interrupt Registers */

    #define SCB1_sda_INTSTAT                (* (reg32 *) SCB1_sda__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SCB1_sda_DRIVE_MODE_SHIFT       (0x00u)
#define SCB1_sda_DRIVE_MODE_MASK        (0x07u << SCB1_sda_DRIVE_MODE_SHIFT)


#endif /* End Pins SCB1_sda_H */


/* [] END OF FILE */
