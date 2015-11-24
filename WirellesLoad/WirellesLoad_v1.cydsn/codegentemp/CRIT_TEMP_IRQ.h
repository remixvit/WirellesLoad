/*******************************************************************************
* File Name: CRIT_TEMP_IRQ.h  
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

#if !defined(CY_PINS_CRIT_TEMP_IRQ_H) /* Pins CRIT_TEMP_IRQ_H */
#define CY_PINS_CRIT_TEMP_IRQ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CRIT_TEMP_IRQ_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    CRIT_TEMP_IRQ_Write(uint8 value) ;
void    CRIT_TEMP_IRQ_SetDriveMode(uint8 mode) ;
uint8   CRIT_TEMP_IRQ_ReadDataReg(void) ;
uint8   CRIT_TEMP_IRQ_Read(void) ;
uint8   CRIT_TEMP_IRQ_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CRIT_TEMP_IRQ_DRIVE_MODE_BITS        (3)
#define CRIT_TEMP_IRQ_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CRIT_TEMP_IRQ_DRIVE_MODE_BITS))

#define CRIT_TEMP_IRQ_DM_ALG_HIZ         (0x00u)
#define CRIT_TEMP_IRQ_DM_DIG_HIZ         (0x01u)
#define CRIT_TEMP_IRQ_DM_RES_UP          (0x02u)
#define CRIT_TEMP_IRQ_DM_RES_DWN         (0x03u)
#define CRIT_TEMP_IRQ_DM_OD_LO           (0x04u)
#define CRIT_TEMP_IRQ_DM_OD_HI           (0x05u)
#define CRIT_TEMP_IRQ_DM_STRONG          (0x06u)
#define CRIT_TEMP_IRQ_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define CRIT_TEMP_IRQ_MASK               CRIT_TEMP_IRQ__MASK
#define CRIT_TEMP_IRQ_SHIFT              CRIT_TEMP_IRQ__SHIFT
#define CRIT_TEMP_IRQ_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CRIT_TEMP_IRQ_PS                     (* (reg32 *) CRIT_TEMP_IRQ__PS)
/* Port Configuration */
#define CRIT_TEMP_IRQ_PC                     (* (reg32 *) CRIT_TEMP_IRQ__PC)
/* Data Register */
#define CRIT_TEMP_IRQ_DR                     (* (reg32 *) CRIT_TEMP_IRQ__DR)
/* Input Buffer Disable Override */
#define CRIT_TEMP_IRQ_INP_DIS                (* (reg32 *) CRIT_TEMP_IRQ__PC2)


#if defined(CRIT_TEMP_IRQ__INTSTAT)  /* Interrupt Registers */

    #define CRIT_TEMP_IRQ_INTSTAT                (* (reg32 *) CRIT_TEMP_IRQ__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define CRIT_TEMP_IRQ_DRIVE_MODE_SHIFT       (0x00u)
#define CRIT_TEMP_IRQ_DRIVE_MODE_MASK        (0x07u << CRIT_TEMP_IRQ_DRIVE_MODE_SHIFT)


#endif /* End Pins CRIT_TEMP_IRQ_H */


/* [] END OF FILE */
