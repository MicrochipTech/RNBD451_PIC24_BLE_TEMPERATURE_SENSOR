/*******************************************************************************
  Application TempHum13 Click Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_temphum13.c.c

  Summary:
    This file contains the Application for reading temperature from TempeHum13.

  Description:
    This file contains the Application for reading temperature from TempeHum13.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END


#include "app_temphum13.h"
#include <stdbool.h>
//#include "interrupts.h"
//#include "FreeRTOS.h"
//#include "task.h"
#include "../mcc_generated_files/drivers/i2c_simple_master.h"
#include "../mcc_generated_files/delay.h"
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

static uint8_t temphum13_crc( uint16_t input_value );


static uint8_t temphum13_crc( uint16_t input_value );


uint16_t temphum13_get_temperature ( void )
{
    float retval_temperature;
    uint16_t aux_temperature;
    uint8_t aux_buffer[3];
    uint8_t aux_command;
    aux_command = TEMPHUM13_CMD_TRIG_TEMP_MEAS_HOLD;
    i2c_writeNBytes(TEMPHUM13_DEVICE_ADDRESS,&aux_command, 1);
    i2c_readNBytes(TEMPHUM13_DEVICE_ADDRESS,(uint8_t *)aux_buffer, 3);
    
    aux_temperature = aux_buffer[ 0 ];
    aux_temperature <<= 8;
    aux_temperature |= aux_buffer[ 1 ];
    uint16_t temperature;
    if ( aux_buffer[ 2 ] == temphum13_crc( aux_temperature ) )
    {
        aux_temperature &= 0xFFFC;
        retval_temperature = (float)( aux_temperature );
        retval_temperature /= 65536;
        retval_temperature *= 175.72;
        retval_temperature -= 46.85;
        temperature = (uint16_t)(retval_temperature*100);         
    }
    return temperature;
}


uint16_t temphum13_get_humidity ( void )
{
    float retval_humidity;
    uint16_t aux_humidity;
    uint8_t aux_buffer[ 3 ];
    uint8_t aux_command;
    aux_command = TEMPHUM13_CMD_TRIG_HUMI_MEAS_HOLD;
    i2c_writeNBytes(TEMPHUM13_DEVICE_ADDRESS,&aux_command, 1);
    i2c_readNBytes(TEMPHUM13_DEVICE_ADDRESS,(uint8_t *)aux_buffer, 3);
    
    aux_humidity = aux_buffer[ 0 ];
    aux_humidity <<= 8;
    aux_humidity |= aux_buffer[ 1 ];
    uint16_t humidity;
    if ( aux_buffer[ 2 ] == temphum13_crc( aux_humidity ) )
    {
        aux_humidity &= 0xFFFC;
        retval_humidity = ( float )( aux_humidity );
        retval_humidity /= 65536;
        retval_humidity *= 125.0;
        retval_humidity -= 6.0;
        humidity = (uint16_t)(retval_humidity*100);         
    }
    return humidity;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t temphum13_crc ( uint16_t input_value )
{
    char crc[ 8 ];
    uint8_t i;
    char do_invert;
    uint8_t ret_val;
    uint16_t aux_mask;
    char bit_string[ 16 ];
    
    aux_mask = 0x8000;
    
    for ( i = 0; i < 16; i ++ )
    {
        if ( ( ( input_value & aux_mask ) != 0x0000 ) )
        {
            bit_string[ i ] = '1';
        }
        else
        {
            bit_string[ i ] = '0';
        }
        
        aux_mask >>= 1;
    }

    for ( i = 0; i < 8; ++ i )
    {
        crc[ i ] = 0;
    }

    for ( i = 0; i < 16; ++ i )
    {
        do_invert = ( '1' == bit_string[ i ] ) ^ crc[ 7 ];

        crc[ 7 ] = crc[ 6 ];
        crc[ 6 ] = crc[ 5 ];
        crc[ 5 ] = crc[ 4 ] ^ do_invert;
        crc[ 4 ] = crc[ 3 ] ^ do_invert;
        crc[ 3 ] = crc[ 2 ];
        crc[ 2 ] = crc[ 1 ];
        crc[ 1 ] = crc[ 0 ];
        crc[ 0 ] = do_invert;
    }

    ret_val = 0x00;
    aux_mask = 0x0001;
    
    for ( i = 0; i < 8; i ++ )
    {
        if ( ( ( crc[ i ] & 0x01 ) == 0x01 ) )
        {
            ret_val |= aux_mask;
        }
        aux_mask <<= 1;
    }
    
    return ret_val;
}

// ------------------------------------------------------------------------- END

