/**
    \file circular.h
    \author George Brown
    \date 2017-06-12T21:28:21+0100
    \brief Definitions for circular buffers of fixed length.
*/

#ifndef _CIRCULAR_H_
#define _CIRCULAR_H_

    #define BUFFER_LENGTH 256

    #define BUFFER_FULL 1
    #define BUFFER_EMPTY 1
    #define BUFFER_OK 0

    /// Circular buffer structure.
    typedef struct
    {
        uint8_t read, write, overwrite;
        uint8_t buffer[BUFFER_LENGTH];
    }circular_t;

    /// Put a byte in the buffer.
    uint8_t buffer_put(circular_t* buffer, uint8_t byte);
    /// Get a byte from the buffer.
    uint8_t buffer_get(circular_t* buffer, uint8_t* byte);
    /// Put a string into the buffer.
    uint8_t buffer_put_string(circular_t* buffer, uint8_t* string);
    /// Get the number of free bytes in the buffer.
    uint8_t buffer_free(circular_t* buffer);
    /// Get the number of bytes waiting in the buffer.
    uint8_t buffer_used(circular_t* buffer);

#endif //_CIRCULAR_H_
