/*
 * 1.c
 *
 * Created: 10/20/2024 2:05:32 PM
 * Author: T460s
 */

#include <mega32.h>
#include <delay.h>
void main(void)
{
    DDRA.0 = 0; // define direction A
    DDRB.0 = 1;
while (1)
    {
    // Please write your application code here
        PORTB.0 = PINA.0;
        delay_ms(1000);
    }
}