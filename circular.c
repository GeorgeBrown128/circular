/**
    \file circular.c
    \author George Brown
    \date 2017-06-12T21:28:16+0100
    \brief Code for the circular_t circular buffer.
*/

#include "circular.h"

uint8_t buffer_put(circular_t* buffer, uint8_t byte)
{
    // Check if there's room for any more data in the buffer.
    if(((buffer->write+1)%BUFFER_LENGTH) == buffer->read)
        return BUFFER_FULL;

    buffer->write = (buffer->write+1)%BUFFER_LENGTH;
    buffer->data[buffer->write] = byte;
    return BUFFER_OK;
}

uint8_t buffer_get(circular_t* buffer, uint8_t* byte)
{
    // Check if there's data left to read.
    if(buffer->read == buffer->write)
        return BUFFER_EMPTY;

    buffer->read = (buffer->read+1)%BUFFER_LENGTH;
    *byte = buffer->data[buffer->read];
    return BUFFER_OK;
}

uint8_t buffer_put_string(circular_t* buffer, uint8_t* data)
{
    uint8_t idx, status;

    // For character in string.
    for(idx = 0; data[idx]; idx++){
        // Put the character in the buffer.
        status = buffer_put(buffer, data[idx]);
        if(BUFFER_FULL == status)
            // Fall over and return with the buffer full error code.
            return BUFFER_FULL;
    }
    return BUFFER_OK;
}

uint8_t buffer_used(circular_t* buffer)
{
    // Detect if the buffer has overrun once.
    if(buffer->write < buffer->read){
        return((buffer->write+BUFFER_LENGTH)-buffer->read);
    }
    return(buffer->write-buffer->read);
}

uint8_t buffer_free(circular_t* buffer)
{
    return (BUFFER_LENGTH - buffer_used(buffer));
}

