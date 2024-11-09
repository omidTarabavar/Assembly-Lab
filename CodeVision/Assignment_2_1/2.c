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
int i = 0;

char names[] = "SamanBz NazaninRz OmidTa        ";
void init_lcd()
{

    for(i = 0;i < 32; i++)
    {
        int row = i / 16;
        int col = i % 16;
        
        sprintf(Buf,"%c", names[i]);
        lcd_gotoxy(col,row);
        lcd_puts(Buf);
        delay_ms(150);
    }
    
    
    
}



void main(void)
{
    
    lcd_init(16);
    lcd_clear();
    init_lcd();
    while (1)
    {
        
            
        
    }
}
