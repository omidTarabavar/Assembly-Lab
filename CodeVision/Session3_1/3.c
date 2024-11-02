/*
 * 3.c
 *
 * Created: 10/27/2024 2:17:38 PM
 * Author: omidt
 */


#include <mega32.h>
#include <delay.h>
#include <alcd.h>
char Data;
void main(void)
{
    lcd_init(16);
    lcd_clear();
    while (1)
    {
    // Please write your application code here
        lcd_gotoxy(0,0);
        lcd_putchar(Data+48);
        if (Data == 9) Data = 0;
        else Data++;
        delay_ms(1000);       
    }
}