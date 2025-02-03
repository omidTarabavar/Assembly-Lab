/*
 * 1.c
 *
 * Created: 1/29/2025 7:30:37 AM
 * Author: omidt
 */

#include <io.h>
#include <mega32.h>

void main(void)
{
TCCR0 = 0x6A;
OCR0 = 0x7F;
DDRB.3 = 1;
while (1)
    {
    // Please write your application code here

    }
}
