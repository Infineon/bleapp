
#include <project.h>

#define LED_OFF 1
#define LED_ON 0

int main()
{
    CyGlobalIntEnable; 
    capsense_Start();
    capsense_InitializeAllBaselines();
    uart_Start();
   
    for(;;)
    {
        if(!capsense_IsBusy()) {
            capsense_ProcessAllWidgets();
            uint32 rval = capsense_GetCentroidPos(capsense_LINEARSLIDER0_WDGT_ID);
            if(rval !=0xFFFF)
            {
                // the 10,30,50,70,90 were found empiracally to "feel" right
                (rval>10?led0_Write(LED_ON):led0_Write(LED_OFF));
                (rval>30?led1_Write(LED_ON):led1_Write(LED_OFF));
                (rval>50?led2_Write(LED_ON):led2_Write(LED_OFF));
                (rval>70?led3_Write(LED_ON):led3_Write(LED_OFF));
                (rval>90?led4_Write(LED_ON):led4_Write(LED_OFF));
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
            if(!uart_SpiUartGetTxBufferSize())
                uart_SpiUartWriteTxData(rval);
        }  
        if(uart_SpiUartGetRxBufferSize())
            blue_Write(!uart_SpiUartReadRxData());
    }
}
