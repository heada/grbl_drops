/*
    Copyright (c) 2007 Stefan Engelke <mbox@stefanengelke.de>

    Permission is hereby granted, free of charge, to any person 
    obtaining a copy of this software and associated documentation 
    files (the "Software"), to deal in the Software without 
    restriction, including without limitation the rights to use, copy, 
    modify, merge, publish, distribute, sublicense, and/or sell copies 
    of the Software, and to permit persons to whom the Software is 
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be 
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.

    $Id$
*/

#ifndef _SPI_H_
#define _SPI_H_

#include <avr/io.h>


extern void spi_init();
extern void spi_transfer_sync (uint8_t * dataout, uint8_t * datain, uint8_t len);
extern void spi_transmit_sync (uint8_t * dataout, uint8_t len);
extern uint8_t spi_fast_shift (uint8_t data);


#endif /* _SPI_H_ */
/* USE EXAMPLE
   1 // Allocate buffer array
   2     uint8_t data_buf[1];
   3 // Initialize SPI
   4     spi_init();
   5 // Send 0xFF to spi slave and read 1 byte back to the same array
   6     data_buf[0] = 0xFF;
   7     spi_transfer_sync(data_buf,data_buf,1);
   8 // Show received byte on LEDs
   9     PORTC = ~data_buf[0];
   */