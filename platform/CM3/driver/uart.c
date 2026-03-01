/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* printf() output uses the UART.  These constants define the addresses of the
 * required UART registers. */
#define UART0_ADDRESS                         ( 0x40004000UL )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK                        ( 1UL )

void prvUARTInit(void)
{
    UART0_BAUDDIV = 16;
    UART0_CTRL = 1;
}

int __write( int iFile,
             char * pcString,
             int iStringLength )
{
    int iNextChar;

    /* Avoid compiler warnings about unused parameters. */
    ( void ) iFile;

    /* Output the formatted string to the UART. */
    for( iNextChar = 0; iNextChar < iStringLength; iNextChar++ )
    {
        while( ( UART0_STATE & TX_BUFFER_MASK ) != 0 )
        {
        }

        UART0_DATA = *pcString;
        pcString++;
    }

    return iStringLength;
}