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
char names[] = "SamanBz NazaninRz OmidTa       ";

void shiftNames(char names[])
{                                                                   
    char lastChar = names[31];
    for(i = 31; i > 0; i--)
    {
        names[i] = names[i-1];          
    }
    names[0] = lastChar;
}


void printNames(char names[])
{
    lcd_clear();
    for(i = 0;i < 32; i++)
    {
        int row = i / 16;
        int col = i % 16;
        
        sprintf(Buf,"%c", names[i]);
        lcd_gotoxy(col,row);
        lcd_puts(Buf);
    }
}

void init(char names[])
{
    for(i = 0;i < 24; i++)
    {
        int row = i / 16;
        int col = i % 16;
        
        sprintf(Buf,"%c", names[i]);
        lcd_gotoxy(col,row);
        lcd_puts(Buf);
        if(i != 23) 
            delay_ms(150);
        else
            lcd_clear();
    }
}

void main(void)
{
    lcd_init(16);
    lcd_clear();
    init(names);    
    while (1)
    {
        printNames(names);
        shiftNames(names);
        delay_ms(400);
    }
    
    
}
