/*******************************************************************************
* File Name: SCB2_SPI_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB2_PVT.h"
#include "SCB2_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(SCB2_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 SCB2_rxBufferHead;
    volatile uint32 SCB2_rxBufferTail;
    volatile uint8  SCB2_rxBufferOverflow;
#endif /* (SCB2_INTERNAL_RX_SW_BUFFER_CONST) */

#if(SCB2_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 SCB2_txBufferHead;
    volatile uint32 SCB2_txBufferTail;
#endif /* (SCB2_INTERNAL_TX_SW_BUFFER_CONST) */

#if(SCB2_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 SCB2_rxBufferInternal[SCB2_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SCB2_INTERNAL_RX_SW_BUFFER) */

#if(SCB2_INTERNAL_TX_SW_BUFFER)
    volatile uint8 SCB2_txBufferInternal[SCB2_TX_BUFFER_SIZE];
#endif /* (SCB2_INTERNAL_TX_SW_BUFFER) */


#if(SCB2_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: SCB2_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into SCB2_SpiInit for description.
    *
    *******************************************************************************/
    uint32 SCB2_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (SCB2_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SCB2_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SCB2_CHECK_RX_SW_BUFFER)
        {
            if (SCB2_rxBufferHead != SCB2_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (SCB2_rxBufferTail + 1u);

                if (SCB2_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = SCB2_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                SCB2_rxBufferTail = locTail;

                #if (SCB2_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (SCB2_INTR_RX_MASK_REG & SCB2_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        SCB2_INTR_RX_MASK_REG |= SCB2_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = SCB2_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: SCB2_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 SCB2_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (SCB2_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SCB2_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SCB2_CHECK_RX_SW_BUFFER)
        {
            locHead = SCB2_rxBufferHead;

            if(locHead >= SCB2_rxBufferTail)
            {
                size = (locHead - SCB2_rxBufferTail);
            }
            else
            {
                size = (locHead + (SCB2_INTERNAL_RX_BUFFER_SIZE - SCB2_rxBufferTail));
            }
        }
        #else
        {
            size = SCB2_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SCB2_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiUartClearRxBuffer(void)
    {
        #if (SCB2_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SCB2_DisableInt();

            /* Flush RX software buffer */
            SCB2_rxBufferHead = SCB2_rxBufferTail;
            SCB2_rxBufferOverflow = 0u;

            SCB2_CLEAR_RX_FIFO;
            SCB2_ClearRxInterruptSource(SCB2_INTR_RX_ALL);

            #if (SCB2_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                SCB2_INTR_RX_MASK_REG |= SCB2_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            SCB2_EnableInt();
        }
        #else
        {
            SCB2_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (SCB2_RX_DIRECTION) */


#if(SCB2_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: SCB2_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiUartWriteTxData(uint32 txData)
    {
    #if (SCB2_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SCB2_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SCB2_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((SCB2_txBufferHead == SCB2_txBufferTail) &&
                (SCB2_SPI_UART_FIFO_SIZE != SCB2_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                SCB2_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (SCB2_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (SCB2_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == SCB2_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                SCB2_ClearTxInterruptSource(SCB2_INTR_TX_NOT_FULL);

                SCB2_PutWordInTxBuffer(locHead, txData);

                SCB2_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (SCB2_INTR_TX_MASK_REG & SCB2_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    SCB2_INTR_TX_MASK_REG |= (uint32) SCB2_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (SCB2_SPI_UART_FIFO_SIZE == SCB2_GET_TX_FIFO_ENTRIES)
            {
            }

            SCB2_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: SCB2_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            SCB2_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: SCB2_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 SCB2_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (SCB2_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SCB2_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SCB2_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = SCB2_txBufferTail;

            if (SCB2_txBufferHead >= locTail)
            {
                size = (SCB2_txBufferHead - locTail);
            }
            else
            {
                size = (SCB2_txBufferHead + (SCB2_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = SCB2_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SCB2_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_SpiUartClearTxBuffer(void)
    {
        #if (SCB2_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SCB2_DisableInt();

            /* Flush TX software buffer */
            SCB2_txBufferHead = SCB2_txBufferTail;

            SCB2_INTR_TX_MASK_REG &= (uint32) ~SCB2_INTR_TX_NOT_FULL;
            SCB2_CLEAR_TX_FIFO;
            SCB2_ClearTxInterruptSource(SCB2_INTR_TX_ALL);

            /* Release lock */
            SCB2_EnableInt();
        }
        #else
        {
            SCB2_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (SCB2_TX_DIRECTION) */


/*******************************************************************************
* Function Name: SCB2_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 SCB2_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = SCB2_GetRxInterruptMode();

    SCB2_SetRxInterruptMode(SCB2_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: SCB2_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 SCB2_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = SCB2_GetTxInterruptMode();

    SCB2_SetTxInterruptMode(SCB2_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(SCB2_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SCB2_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (SCB2_ONE_BYTE_WIDTH == SCB2_rxDataBits)
        {
            SCB2_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            SCB2_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            SCB2_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SCB2_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 SCB2_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (SCB2_ONE_BYTE_WIDTH == SCB2_rxDataBits)
        {
            value = SCB2_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) SCB2_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)SCB2_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: SCB2_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SCB2_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (SCB2_ONE_BYTE_WIDTH == SCB2_txDataBits)
        {
            SCB2_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            SCB2_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            SCB2_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SCB2_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 SCB2_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (SCB2_ONE_BYTE_WIDTH == SCB2_txDataBits)
        {
            value = (uint32) SCB2_txBuffer[idx];
        }
        else
        {
            value  = (uint32) SCB2_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) SCB2_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (SCB2_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
