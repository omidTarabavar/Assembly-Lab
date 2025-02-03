/*
 * s7_1.c
 *
 * Created: 11/24/2024 2:16:33 PM
 * Author: omidt
 */

#include <io.h>
#include <delay.h>
void main(void)
{
    int i = 10;
    TCCR0 = 0b01101011;
    TCNT0 = 0;
    OCR0 = 128;
    DDRB.3 = 1;
while (1)
    {
    // Please write your application code here
    
    for(i = 10; i < 250; i++)
    {
        OCR0 = i;
        delay_ms(50);
    }
    
    
    for(i = 250; i >= 10; i--)
    {
        OCR0 = i;
        delay_ms(50);
    
    }
    
    }
}
