/**
    \file embedded.c
    \author George Brown
    \date 2017-06-14T22:05:27+0100
    \brief Example UART interrupts for an AVR using circular buffers.
*/

#include <avr/io.h>
#include "circular.h"

circular_t rx_buffer, tx_buffer;

void init_uart0(void)
{
    #define BAUD 9600
    #include <util/setbaud.h>
    
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
    #if USE_2X
        UCSRA |= _BV(U2X);
    #else
        UCSRA &= ~_BV(U2X);
    #endif
    // Enable RX interrupt, and the hardware. TX interrupt is started in code.
    UCSRB = _BV(RXCIE) | _BV(RXEN) | _BV(TXEN);
    // Set 8 data, no parity, 1 stop.
    UCSRC = _BV(UCSZ1) | _BV(UCSZ0);
    return;
}

/// Receive Interrupt
ISR(USART_RX_vect)
{
    // Receive the character, discard if there's no room.
    (void)buffer_put(&rx_buffer, UDR);
    return;
}

/// Transmit Complete Interrupt
ISR(USART_UDRE_vect)
{
    uint8_t data;
    uint8_t status = BUFFER_OK;

    // Try and get data from the buffer.
    status = buffer_get(&tx_buffer, &data);

    if(BUFFER_OK == status)
    {
        // Transmit the data if ok.
        UDR = data;
    }
    // If it's empty, turn off the interrupt until we have more data.
    else if(BUFFER_EMPTY == status)
    {
        UCSRB &= ~_BV(UDRIE);
    }
    return;
}

