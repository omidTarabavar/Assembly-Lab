/*
 * 5.c
 *
 * Created: 11/10/2024 1:43:59 PM
 * Author: omidt
 */

#include <io.h>
#include <mega32.h>
#include <delay.h>
interrupt [2] void my_int()
{
    #asm("cli")
    PORTB.0 = 1;
    delay_ms(1000);
    PORTB.0 = 0;
    delay_ms(1000);
    #asm ("sei")

}

void main(void)
{
    #asm("sei")
    DDRB.0 = 1;    GICR |= (1 << INT0);
    MCUCR |= (1 << ISC01) | (0 << ISC00);
    while (1)
    {
        // Please write your application code here

    }
}
