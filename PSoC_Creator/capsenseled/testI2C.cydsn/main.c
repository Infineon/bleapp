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
#include <project.h>

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    I2C_Start();

    uint8 count=0;
    
    CyDelay(1000);
    
   
    
    for(;;)
    {
        /* Place your application code here. */
    
         I2C_I2CMasterSendStart(0x08,I2C_I2C_WRITE_XFER_MODE);
    I2C_I2CMasterWriteByte(0);
    I2C_I2CMasterWriteByte(count);
    I2C_I2CMasterSendStop();
    
        
        blue_Write(rx_Read());
        blue_Write(!blue_Read());
        count = count + 1; 
        CyDelay(1000);
        
        
    }
}

/* [] END OF FILE */
