/*******************************************************************************
* File Name: SCB2_miso_m.h  
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

#if !defined(CY_PINS_SCB2_miso_m_H) /* Pins SCB2_miso_m_H */
#define CY_PINS_SCB2_miso_m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SCB2_miso_m_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SCB2_miso_m_Write(uint8 value) ;
void    SCB2_miso_m_SetDriveMode(uint8 mode) ;
uint8   SCB2_miso_m_ReadDataReg(void) ;
uint8   SCB2_miso_m_Read(void) ;
uint8   SCB2_miso_m_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SCB2_miso_m_DRIVE_MODE_BITS        (3)
#define SCB2_miso_m_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SCB2_miso_m_DRIVE_MODE_BITS))

#define SCB2_miso_m_DM_ALG_HIZ         (0x00u)
#define SCB2_miso_m_DM_DIG_HIZ         (0x01u)
#define SCB2_miso_m_DM_RES_UP          (0x02u)
#define SCB2_miso_m_DM_RES_DWN         (0x03u)
#define SCB2_miso_m_DM_OD_LO           (0x04u)
#define SCB2_miso_m_DM_OD_HI           (0x05u)
#define SCB2_miso_m_DM_STRONG          (0x06u)
#define SCB2_miso_m_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SCB2_miso_m_MASK               SCB2_miso_m__MASK
#define SCB2_miso_m_SHIFT              SCB2_miso_m__SHIFT
#define SCB2_miso_m_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SCB2_miso_m_PS                     (* (reg32 *) SCB2_miso_m__PS)
/* Port Configuration */
#define SCB2_miso_m_PC                     (* (reg32 *) SCB2_miso_m__PC)
/* Data Register */
#define SCB2_miso_m_DR                     (* (reg32 *) SCB2_miso_m__DR)
/* Input Buffer Disable Override */
#define SCB2_miso_m_INP_DIS                (* (reg32 *) SCB2_miso_m__PC2)


#if defined(SCB2_miso_m__INTSTAT)  /* Interrupt Registers */

    #define SCB2_miso_m_INTSTAT                (* (reg32 *) SCB2_miso_m__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SCB2_miso_m_DRIVE_MODE_SHIFT       (0x00u)
#define SCB2_miso_m_DRIVE_MODE_MASK        (0x07u << SCB2_miso_m_DRIVE_MODE_SHIFT)


#endif /* End Pins SCB2_miso_m_H */


/* [] END OF FILE */
