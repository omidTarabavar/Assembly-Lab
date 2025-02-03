/*
 * as3.c
 *
 * Created: 11/23/2024 5:44:19 PM
 * Author: omidt
 */
#include <mega32.h>
#include <alcd.h>
#include <delay.h>

unsigned char scan[4] = {0xFE, 0xFD, 0xFB, 0xF7};
char pressedKey = 0;
char arrkey[16] = {
    '7', '8', '9', '/',
    '4', '5', '6', '*',
    '1', '2', '3', '-',
    'C', '0', '=', '+'
};
#define c1 PINB.4
#define c2 PINB.5
#define c3 PINB.6
#define c4 PINB.7
#define keypad_port PORTB

void keypad()
{
    unsigned char r,c;
    delay_us(10);
    for (r=0; r<4; r++){
            c=255;
            keypad_port=scan[r];
            delay_us(10);
            if(c1==0) pressedKey=arrkey[(r*4)+0];
            if(c2==0) pressedKey=arrkey[(r*4)+1];
            if(c3==0) pressedKey=arrkey[(r*4)+2];
            if(c4==0) pressedKey=arrkey[(r*4)+3];   
    }
}

interrupt [2] void my_int()
{
    #asm("cli")
    keypad();
    DDRB=0X0F;
    keypad_port=0XF0;
    if(pressedKey != 0)
    {
        if (pressedKey == 'C') lcd_clear();
        else lcd_putchar(pressedKey);
        pressedKey = 0;
    }
    
    #asm ("sei")
}

void main(void)
{
    lcd_init(16);
    lcd_clear();
    lcd_puts("Start");
    delay_ms(1000);
    lcd_clear();
    
    #asm("sei")
    GICR |= (1 << INT0);
    MCUCR |= (1 << ISC01) | (0 << ISC00);
    DDRB=0X0F;
    keypad_port=0XF0;
    while (1) {
           
    }
}
