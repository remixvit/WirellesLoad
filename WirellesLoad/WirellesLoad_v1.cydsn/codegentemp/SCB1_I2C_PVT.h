/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_SCB1_H)
#define CY_SCB_I2C_PVT_SCB1_H

#include "SCB1_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 SCB1_state; /* Current state of I2C FSM */

#if(SCB1_I2C_SLAVE_CONST)
    extern volatile uint8 SCB1_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * SCB1_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  SCB1_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  SCB1_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * SCB1_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  SCB1_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  SCB1_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  SCB1_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   SCB1_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (SCB1_I2C_SLAVE_CONST) */

#if(SCB1_I2C_MASTER_CONST)
    extern volatile uint16 SCB1_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  SCB1_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * SCB1_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  SCB1_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  SCB1_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * SCB1_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  SCB1_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  SCB1_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  SCB1_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (SCB1_I2C_MASTER_CONST) */

#if (SCB1_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*SCB1_customAddressHandler) (void);
#endif /* (SCB1_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(SCB1_SCB_MODE_I2C_CONST_CFG)
    void SCB1_I2CInit(void);
#endif /* (SCB1_SCB_MODE_I2C_CONST_CFG) */

void SCB1_I2CStop(void);
void SCB1_I2CSaveConfig(void);
void SCB1_I2CRestoreConfig(void);

#if(SCB1_I2C_MASTER_CONST)
    void SCB1_I2CReStartGeneration(void);
#endif /* (SCB1_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_SCB1_H) */


/* [] END OF FILE */
