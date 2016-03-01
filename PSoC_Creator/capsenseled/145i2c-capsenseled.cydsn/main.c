
#include <project.h>

#define LED_OFF 1
#define LED_ON 0

int flag;

CY_ISR(setFlag)
{
    flag = 1;
    Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
}

int main()
{
    uint32 fingerPos = 0xFFFF;
    uint32 previousPos = 0xFFFF;
    uint32 triggerRead=0;
    
    CyDelay(500);
    
    indicate_Write(1);
    
    
    CyGlobalIntEnable; 
   
    capsense_Start();
    capsense_InitializeAllBaselines();

    I2C_Start();
    
    isr_1_StartEx(setFlag);
    Timer_1_Start();
    
    for(;;)
    {
        if(!capsense_IsBusy()) {
            capsense_ProcessAllWidgets();
            fingerPos = capsense_GetCentroidPos(capsense_LINEARSLIDER0_WDGT_ID);
            if(fingerPos !=0xFFFF)
            {
                // the 10,30,50,70,90 were found empiracally to "feel" right
                (fingerPos>10?led0_Write(LED_ON):led0_Write(LED_OFF));
                (fingerPos>30?led1_Write(LED_ON):led1_Write(LED_OFF));
                (fingerPos>50?led2_Write(LED_ON):led2_Write(LED_OFF));
                (fingerPos>70?led3_Write(LED_ON):led3_Write(LED_OFF));
                (fingerPos>90?led4_Write(LED_ON):led4_Write(LED_OFF));
            }
            else
            {
                led0_Write(LED_OFF); 
                led1_Write(LED_OFF);
                led2_Write(LED_OFF);
                led3_Write(LED_OFF);
                led4_Write(LED_OFF);    
            }
            
            
            capsense_UpdateAllBaselines();
            capsense_ScanAllWidgets();
        
        }
        
        if(fingerPos != previousPos)
        {
            I2C_I2CMasterSendStart(0x08, I2C_I2C_WRITE_XFER_MODE);
            I2C_I2CMasterWriteByte(0);
            I2C_I2CMasterWriteByte(fingerPos);
            I2C_I2CMasterSendStop();
        }
        previousPos = fingerPos;
        
        if(flag)
        {
            flag = 0;
            I2C_I2CMasterSendStart(0x08, I2C_I2C_READ_XFER_MODE);
            I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA);
            blue_Write(!I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA));
            I2C_I2CMasterSendStop();
                        
        }
    }
}
