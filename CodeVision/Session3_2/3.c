/*
 * 3.c
 *
 * Created: 10/27/2024 2:52:04 PM
 * Author: omidt
 */


#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
char Data;
char Buf[32];
void main(void)
{
    lcd_init(16);
     lcd_clear();
     lcd_puts("Start");
     delay_ms(5000);
     lcd_clear();
    while (1)
    {
        // Please write your application code here
        sprintf(Buf,"%d",Data);
        lcd_puts("Counting");
        lcd_gotoxy(0,1);
        lcd_puts(Buf);
        Data++;
        delay_ms(1000);
        lcd_clear();
    }
}
