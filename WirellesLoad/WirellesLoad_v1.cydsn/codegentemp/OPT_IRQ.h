/*******************************************************************************
* File Name: OPT_IRQ.h  
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

#if !defined(CY_PINS_OPT_IRQ_H) /* Pins OPT_IRQ_H */
#define CY_PINS_OPT_IRQ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "OPT_IRQ_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    OPT_IRQ_Write(uint8 value) ;
void    OPT_IRQ_SetDriveMode(uint8 mode) ;
uint8   OPT_IRQ_ReadDataReg(void) ;
uint8   OPT_IRQ_Read(void) ;
uint8   OPT_IRQ_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define OPT_IRQ_DRIVE_MODE_BITS        (3)
#define OPT_IRQ_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - OPT_IRQ_DRIVE_MODE_BITS))

#define OPT_IRQ_DM_ALG_HIZ         (0x00u)
#define OPT_IRQ_DM_DIG_HIZ         (0x01u)
#define OPT_IRQ_DM_RES_UP          (0x02u)
#define OPT_IRQ_DM_RES_DWN         (0x03u)
#define OPT_IRQ_DM_OD_LO           (0x04u)
#define OPT_IRQ_DM_OD_HI           (0x05u)
#define OPT_IRQ_DM_STRONG          (0x06u)
#define OPT_IRQ_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define OPT_IRQ_MASK               OPT_IRQ__MASK
#define OPT_IRQ_SHIFT              OPT_IRQ__SHIFT
#define OPT_IRQ_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OPT_IRQ_PS                     (* (reg32 *) OPT_IRQ__PS)
/* Port Configuration */
#define OPT_IRQ_PC                     (* (reg32 *) OPT_IRQ__PC)
/* Data Register */
#define OPT_IRQ_DR                     (* (reg32 *) OPT_IRQ__DR)
/* Input Buffer Disable Override */
#define OPT_IRQ_INP_DIS                (* (reg32 *) OPT_IRQ__PC2)


#if defined(OPT_IRQ__INTSTAT)  /* Interrupt Registers */

    #define OPT_IRQ_INTSTAT                (* (reg32 *) OPT_IRQ__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define OPT_IRQ_DRIVE_MODE_SHIFT       (0x00u)
#define OPT_IRQ_DRIVE_MODE_MASK        (0x07u << OPT_IRQ_DRIVE_MODE_SHIFT)


#endif /* End Pins OPT_IRQ_H */


/* [] END OF FILE */
