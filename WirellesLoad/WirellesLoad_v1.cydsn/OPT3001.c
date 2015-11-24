/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <OPT3001.h>

uint8 OPT_IsReady(void)
{
    uint16 Val;
    if(I2C_ReadRegister(OPT3001_I2C_ADDRESS, REG_CONFIGURATION, &Val))
    {
        if(Val & CONFIG_CRF)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}
void OPT_Enable(uint8 enable);

uint8 I2C_ReadRegister(uint8 ADR, uint8 Reg, uint16 *RetValue)
{
    /*Read 16bit Register in i2c slave adress*/
    uint8 Status;
    volatile uint8 Buf[2];
    volatile uint8 Iter = 0;
    while((Status !=0) && (Iter < 10))
    {
        Status = I2C_I2CMasterSendStart(ADR, I2C_I2C_WRITE_XFER_MODE);
        Iter++;
    }    
    if(Status == I2C_I2C_MSTR_NO_ERROR)
    {
        I2C_I2CMasterWriteByte(Reg);
        Status = I2C_I2CMasterSendRestart(ADR,I2C_I2C_READ_XFER_MODE);
        if(Status == I2C_I2C_MSTR_NO_ERROR)
            {
                Buf[0] = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
                Buf[1] = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA);
                (*RetValue) = (Buf[0]<<8) | Buf[1];
                I2C_I2CMasterSendStop();
                return 1;
            }
            else
            {
                return 0;
            }
    }
    else
    {
        return 0;
    }
}

uint8 I2C_WriteRegister(uint8 ADR, uint8 Reg, uint16 *RetValue)
{
    /*Read 16bit Register in i2c slave adress*/
    volatile uint8 Status = 1;
    volatile uint8 Buf[2];
    volatile uint8 Iter = 0;
    while((Status !=0) && (Iter < 10))
    {
        Status = I2C_I2CMasterSendStart(ADR,I2C_I2C_WRITE_XFER_MODE);
        Iter++;
    }    

    Buf[0] = ((*RetValue)>>8);
    Buf[1] = (uint8)(*RetValue);
    I2C_I2CMasterWriteByte(Reg);
    I2C_I2CMasterWriteByte(Buf[0]);
    I2C_I2CMasterWriteByte(Buf[1]);
    Status = I2C_I2CMasterSendStop();
    
    if(Status == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8 OPT_ReadResult(uint32 *Result)
{
  uint16_t exponent;
  uint16 raw;
  uint8 success;
    
  if(OPT_IsReady() != 1)
  {
    return 0;
  }

  success = I2C_ReadRegister(OPT3001_I2C_ADDRESS, REG_CONFIGURATION, &raw);

  if(success)
  {
    success = I2C_ReadRegister(OPT3001_I2C_ADDRESS, REG_RESULT, &raw);
  }

  if(success) 
  {
    /*Convert to LUX*/
	//extract result & exponent data from raw readings
    (*Result) = raw&0x0FFF;
	exponent = (raw>>12)&0x000F;
    
    //convert raw readings to LUX
    switch(exponent){
		case 0: //*0.015625
			(*Result) = (*Result)>>6;
			break;
		case 1: //*0.03125
			(*Result) = (*Result)>>5;
			break;
		case 2: //*0.0625
			(*Result) = (*Result)>>4;
			break;
		case 3: //*0.125
			(*Result) = (*Result)>>3;
			break;
		case 4: //*0.25
			(*Result) = (*Result)>>2;
			break;
		case 5: //*0.5
			(*Result) = (*Result)>>1;
			break;
		case 6:
			(*Result) = (*Result);
			break;
		case 7: //*2
			(*Result) = (*Result)<<1;
			break;
		case 8: //*4
			(*Result) = (*Result)<<2;
			break;
		case 9: //*8
			(*Result) = (*Result)<<3;
			break;
		case 10: //*16
			(*Result) = (*Result)<<4;
			break;
		case 11: //*32
			(*Result) = (*Result)<<5;
			break;
	}
    return 1;
    
  } 
  else 
  {
    return 0;
  }

  return 0;
}

uint8 OPT_StartConvert()
{
    uint16 Buf;
    if(I2C_ReadRegister(OPT3001_I2C_ADDRESS, REG_CONFIGURATION, &Buf))
    {
        Buf |= (1<<9);
        if(I2C_WriteRegister(OPT3001_I2C_ADDRESS, REG_CONFIGURATION, &Buf))
        {
            return 1;
        }
    }
    return 0;
}

char *OPT_GetResultString(volatile uint32 *Lux)
{
    uint32 Result;
    uint8 *St;
    char Current;
    volatile uint8 Scroll = 0;
    volatile uint8 Buf[15];
    Buf[14] = (char)'\0';
    char Out_Str[25] = "Brightness: ";
    const char Lux_Str[3] = "Lx";
    const char Error_Str[15] = "OPT Error Read";
    
    if(OPT_ReadResult(&Result))
    {
        (*Lux) = Result;
        BCD_Ulong(Result);
        
        St = BCD_GetPointerBuf();
        Current = *St;
        
            while(Current != (char)'\0')
            {
                Buf[Scroll] = St[Scroll];
                Scroll++;
                Current = St[Scroll];
            }
        
        Scroll = 0;
        Current = Buf[Scroll];
        
            while(Current == (char)' ')
            {
                Scroll++;
                Current = Buf[Scroll];
            }
        
        strncat(Out_Str, &Buf[Scroll],7);
        strncat(Out_Str, Lux_Str,3);
        for(Scroll = 0;Scroll < 25;Scroll++)
        {
            OPT_Out_String[Scroll] = Out_Str[Scroll];
        }
        
    }
    else
    {
        for(Scroll = 0;Scroll < 25;Scroll++)
        {
            OPT_Out_String[Scroll] = Error_Str[Scroll];
        }
    }
    return OPT_Out_String;
    
}

uint16 OPT_Status(int type);

/* [] END OF FILE */
