/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>
#include <stdio.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

uint8_t SERCOM1Buffer[100] = "Hello Everyone!!";

void delay_ms(uint16_t ms)
{
    for (uint16_t t = 0; t < ms; t++)
    {
        TC0_TimerStart();
        while ( !TC0_TimerPeriodHasExpired() );
        TC0_TimerStop();
    }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    SERCOM1_USART_Write( &SERCOM1Buffer, sizeof(SERCOM1Buffer) );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        if ( !PORT_PinRead(SW_PIN) )
        {
            delay_ms(200);
            YLED_Toggle();
            sprintf((char*)SERCOM1Buffer, "Yellow LED Toggle\r\n");
            SERCOM1_USART_Write(&SERCOM1Buffer, sizeof(SERCOM1Buffer));
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

