#include <project.h>
#include <stdlib.h>

// 16 bit quadrature decoder... the middle is 0x8000
#define QD_RESET (0x8000)
// Scale the QD to RPMs
#define QD_SCALE (5)
// The max compare value for the motor PWM (i.e. full speed)
#define MAXSPEED (100)

int processTachFlag = 0;
int tachLeftNotify = 0;
int tachRightNotify = 0;
int tachLeft = 0;
int tachRight = 0;
int8 speedLeft = 0;
int8 speedRight = 0;

int motorFlag = 0; // this flag is used to turn the motors on/off


// This ISR handles button presses on the user button on the board. This will toggle the motors on/off
CY_ISR(swisr)
{
    motorFlag = 1;
    Control_ClearInterrupt();
    
}

typedef enum motor {
    LEFT,
    RIGHT
} motor;


// This function updates the GATT database with the current speed
void updateSpeed()
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;

    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_MOTORSERVICE_SPEEDLEFT_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *)&speedLeft;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0);
    
    tempHandle.attrHandle = CYBLE_MOTORSERVICE_SPEEDRIGHT_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *)&speedRight;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0);      
}

// Configure the speed into the correct PWM, then call the GATT database speed update function
void setSpeed(motor m, int speed)
{
    int s = abs(speed);
    int dir = (s == speed)?0:1;
    
    if(s > MAXSPEED)
        return;
    
    switch (m)
    {
        case LEFT:
            DIRLEFT_Write(dir);
            PWMLEFT_WriteCompare(s);
            speedLeft = speed;         
        break;
        case RIGHT:
            DIRRIGHT_Write(dir);
            PWMRIGHT_WriteCompare(s);
            speedRight = speed;
        break;
    }
    updateSpeed();      // Update the speeed in the GATT database
}

// This ISR is connected to the periodic interrupt source of 187ms
CY_ISR(tachISR)
{
    processTachFlag = 1;
    tachPwm_ReadStatusRegister(); // clear the interrupt
    
}


// This function updates the GATT database with the values of the tachometer
void updateRpm()
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_MOTORSERVICE_TACHLEFT_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *)&tachLeft;
    tempHandle.value.len = 4; // 4 bytes for integer
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0);
    
    if (tachLeftNotify)
        CyBle_GattsNotification(cyBle_connHandle, &tempHandle);
        
    tempHandle.attrHandle = CYBLE_MOTORSERVICE_TACHRIGHT_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *)&tachRight;
    tempHandle.value.len = 4; // 4 bytes for integer
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0);
    
    if (tachRightNotify)
        CyBle_GattsNotification(cyBle_connHandle, &tempHandle); 
        
}

// This function is called a few times/second and calculates the actual RPMs of the motor
// by reading the quadrature encoder and calculating the RPMs
inline void processTach()
{
    processTachFlag = 0;
    tachLeft =  ( QDLEFT_ReadCounter()  - QD_RESET ) * QD_SCALE;
    tachRight = ( QDRIGHT_ReadCounter() - QD_RESET ) * QD_SCALE;
    QDLEFT_WriteCounter(QD_RESET);
    QDRIGHT_WriteCounter(QD_RESET);
    updateRpm(); // Update the GATT database with the new RPM values
}

// This function handles the BLE Stack
void BleCallBack(uint32 event, void* eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            tachLeftNotify = 0;
            tachRightNotify = 0;
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            ledpwm_Start();
        break;
            
        case CYBLE_EVT_GATT_CONNECT_IND:
            updateRpm();
            updateSpeed();
            ledpwm_Stop();
        break;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_MOTORSERVICE_SPEEDLEFT_CHAR_HANDLE)
                setSpeed(LEFT, (int8)wrReqParam->handleValPair.value.val[0]);
                

            if(wrReqParam->handleValPair.attrHandle == CYBLE_MOTORSERVICE_SPEEDRIGHT_CHAR_HANDLE)
                setSpeed(RIGHT, (int8)wrReqParam->handleValPair.value.val[0]);    
                
            if(wrReqParam->handleValPair.attrHandle == CYBLE_MOTORSERVICE_TACHLEFT_TACHLEFTCCCD_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                tachLeftNotify = wrReqParam->handleValPair.value.val[0] & 0x01;
            }
            
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_MOTORSERVICE_TACHRIGHT_TACHRIGHTCCCD_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                tachRightNotify = wrReqParam->handleValPair.value.val[0] & 0x01;
            }            
            
            CyBle_GattsWriteRsp(cyBle_connHandle);
            
        break;
            
        default:
        break;
    }
}
    
// This function will turn the motors on/off if the user presses the button    
void handleMotor()
{
    static int motorState = 1;
    if(motorFlag)
    {
        if(motorState)
        {
            PWMLEFT_Stop();
            PWMRIGHT_Stop();
        }
        else
        {
            PWMLEFT_Start();
            PWMRIGHT_Start(); 
        }
        motorState = !motorState;
        motorFlag = 0;
    } 
}

int main()
{
           
    CyGlobalIntEnable; /* Enable global interrupts. */

    swint_StartEx(swisr); // start the interrupt handler for the switch
    
    // Get the Motor PWMs going
    PWMLEFT_Start();
    PWMRIGHT_Start();
    setSpeed(LEFT,0);
    setSpeed(RIGHT,0);
    
    // Start the quadrature encoders
    QDLEFT_Start();
    QDRIGHT_Start();
    QDLEFT_TriggerCommand(QDLEFT_MASK, QDLEFT_CMD_RELOAD);
    QDRIGHT_TriggerCommand(QDRIGHT_MASK, QDRIGHT_CMD_RELOAD);
    
    // Start the timer and ISR for the tachometer
    tachPwm_Start();
    tachTimer_StartEx(tachISR);
    
    ledpwm_Start();
    
    // Start the BLE
    CyBle_Start(BleCallBack);

    for(;;)
    {      
        handleMotor();
        
        if(processTachFlag)
            processTach();
            
        CyBle_ProcessEvents();
        CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
    }
}

/* [] END OF FILE */
