/*******************************************************************************
* File Name: NRF_CSN.h  
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

#if !defined(CY_PINS_NRF_CSN_H) /* Pins NRF_CSN_H */
#define CY_PINS_NRF_CSN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "NRF_CSN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    NRF_CSN_Write(uint8 value) ;
void    NRF_CSN_SetDriveMode(uint8 mode) ;
uint8   NRF_CSN_ReadDataReg(void) ;
uint8   NRF_CSN_Read(void) ;
uint8   NRF_CSN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NRF_CSN_DRIVE_MODE_BITS        (3)
#define NRF_CSN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - NRF_CSN_DRIVE_MODE_BITS))

#define NRF_CSN_DM_ALG_HIZ         (0x00u)
#define NRF_CSN_DM_DIG_HIZ         (0x01u)
#define NRF_CSN_DM_RES_UP          (0x02u)
#define NRF_CSN_DM_RES_DWN         (0x03u)
#define NRF_CSN_DM_OD_LO           (0x04u)
#define NRF_CSN_DM_OD_HI           (0x05u)
#define NRF_CSN_DM_STRONG          (0x06u)
#define NRF_CSN_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define NRF_CSN_MASK               NRF_CSN__MASK
#define NRF_CSN_SHIFT              NRF_CSN__SHIFT
#define NRF_CSN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NRF_CSN_PS                     (* (reg32 *) NRF_CSN__PS)
/* Port Configuration */
#define NRF_CSN_PC                     (* (reg32 *) NRF_CSN__PC)
/* Data Register */
#define NRF_CSN_DR                     (* (reg32 *) NRF_CSN__DR)
/* Input Buffer Disable Override */
#define NRF_CSN_INP_DIS                (* (reg32 *) NRF_CSN__PC2)


#if defined(NRF_CSN__INTSTAT)  /* Interrupt Registers */

    #define NRF_CSN_INTSTAT                (* (reg32 *) NRF_CSN__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define NRF_CSN_DRIVE_MODE_SHIFT       (0x00u)
#define NRF_CSN_DRIVE_MODE_MASK        (0x07u << NRF_CSN_DRIVE_MODE_SHIFT)


#endif /* End Pins NRF_CSN_H */


/* [] END OF FILE */
