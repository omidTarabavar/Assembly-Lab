/*
 * 2.c
 *
 * Created: 11/2/2024 1:47:05 PM
 * Author: omidt
 */

#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
#include <string.h>
char Buf[32];
void main(void)
{
    int i = 0, j = 0;
    char names[] = "NazaninRz OmidTa SamanBz";
    lcd_init(16);
    lcd_clear();
    
    while (1)
    {
        lcd_clear();
        
        for(i = 0; i < 2; i++)
        {
            for(j = 0; j < 16; j++)
            {
                sprintf(Buf,"%c", names[i * 16 + j]);
                lcd_gotoxy(j,i);
                lcd_puts(Buf);
                delay_ms(150);  
            }
        
        }
    }
}
