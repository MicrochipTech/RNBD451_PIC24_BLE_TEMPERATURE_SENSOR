/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  PIC24FJ64GU205
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include <stdio.h>
#include <stdbool.h>
#include "mcc_generated_files/delay.h"
#include "app_tempHum13/app_temphum13.h"
#include "rnbd/rnbd.h"
#include "rnbd/rnbd_interface.h"
#include "string.h"

const char DevName[]="RNBD451_TEMPERATURE";
uint8_t service_uuid=0xC0;
bool Err;
int8_t heart_rate;
char HR_data[2] = ""; 

typedef enum
{
    /* TODO: Define states used by the application state machine. */
    RNBD_INIT,
    RNBD_FACTORY_RESET,
    RNBD_CMD,
    RNBD_CMD1,
    RNBD_SET_NAME,
    RNBD_SET_PROFILE,
    RNBD_REBOOT,
    RNBD_SEND_DATA,    
            
} STATES;

typedef struct
{
    /* The application's current state */
    STATES state;
    
} RNBD_STATE;

RNBD_STATE rnbd_state;

void RNBD_TempHum_example(void)
{
    switch(rnbd_state.state)
    {
        case RNBD_INIT:
        {
            Err=RNBD_Init();
            if(Err)
            {
                Err=false;
                printf("RNBD451_INITIALIZING\r\n");
                rnbd_state.state=RNBD_CMD;        
            }
        }
        break;
        case RNBD_CMD:
        {
            Err=RNBD_EnterCmdMode();
            if(Err)
            {
                Err=false;                
                printf("Entered CMD Mode\r\n");
                rnbd_state.state=RNBD_FACTORY_RESET;
            }
        }
        break;
        case RNBD_FACTORY_RESET:
        {
            Err=RNBD_FactoryReset();
            if(Err)
            {
                Err=false;                
                printf("Factory Reset Done\r\n");
                rnbd_state.state=RNBD_CMD1;
            }
        }
        break;
        case RNBD_CMD1:
        {
            Err=RNBD_EnterCmdMode();
            if(Err)
            {
                Err=false;                
                printf("Entered CMD Mode\r\n");
                rnbd_state.state=RNBD_SET_NAME;
            }
        }
        break;
        case RNBD_SET_NAME:
        {
            Err=RNBD_SetName(DevName,strlen(DevName));
            if(Err)
            {
                Err=false;                
                printf("Device Name Set\r\n");
                rnbd_state.state=RNBD_SET_PROFILE;
            }
        }
        break;
        case RNBD_SET_PROFILE:
        {
            Err=RNBD_SetServiceBitmap(service_uuid);
            if(Err)
            {
                Err=false;                
                printf("Service Bitmap Set\r\n");
                rnbd_state.state=RNBD_REBOOT;
            }
        }        
        break;
        case RNBD_REBOOT:
        {
            Err=RNBD_RebootCmd();
            if(Err)
            {
                Err=false;                
                printf("Reboot Completed\r\n");
                printf("!!! Started Advertising - Scan and Connect RNBD451_TEMPERATURE using MBD App !!!\r\n");
                rnbd_state.state=RNBD_SEND_DATA;
            }
        }
        break;        
        case RNBD_SEND_DATA:
        {
            char buffer[50];
            DELAY_milliseconds(1000);
            double temperature=temphum13_get_temperature();
            printf("TEMPERATURE: %.2f Deg C\r\n",temperature/100);
            sprintf(buffer, "TEMPERATURE: %.2f Deg C\r\n",temperature/100);
            RNBD_SendCmd(buffer,25);
            rnbd_state.state=RNBD_SEND_DATA;  
        }
        break;
    }
}

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    DELAY_milliseconds(5000);
    printf("PIC24 RNBD451 TEMP\r\n");
    rnbd_state.state=RNBD_INIT; 

    while (1)
    {        
        RNBD_TempHum_example();
    }

    return 1;
}
/**
 End of File
*/

