/*
 * as4.c
 *
 * Created: 12/12/2024 3:31:27 AM
 * Author: omidt
 */


#include <mega32.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

unsigned char scan[4]={0XFE,0XFD,0XFB,0XF7};
char pressedKey = 0;
volatile int turns = 1;
volatile int start = 0;
volatile int min1 = 1, min2 = 1;
volatile int sec1 = 0, sec2 = 0;
volatile int milsec1 = 0, milsec2 = 0;
volatile int decimal_counter = 100;
char s[16];
char arrkey[16]=
{
    '7','8','9','/',
    '4','5','6','*',
    '1','2','3','-',
    'C','0','=','+'
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
        if (pressedKey == '1' && start == 0) turns = 1;
        if (pressedKey == '2' && start == 0) turns = 2;
        if (pressedKey == '1' && start == 1) turns = 2;
        if (pressedKey == '2' && start == 1) turns = 1;
        if (pressedKey == 'C')
        {
            if(start == 0){
                min1 = 1, min2 = 1;
                sec1 = 0, sec2 = 0;
                milsec1 = 0, milsec2 = 0;
                decimal_counter = 100;
                start = 1; 
            }
            else{
                start = 0;

                sprintf(s,"%d:%d.%d %d:%d.%d", min1, sec1, milsec1, min2, sec2, milsec2);
                lcd_clear();
                lcd_puts(s);
                lcd_gotoxy(0,1);
                lcd_puts("Timer stopped.");  
            }
        }
        pressedKey = 0;
    }
    
    #asm ("sei")
}





void main(void)
{ 
    TCCR0 = (1 << WGM01) | (1 << WGM00);  // Normal mode
    TCCR0 |= (1 << CS02) | (1 << CS00);    // Prescaler of 1024
    lcd_init(16);
    lcd_clear();
   
   #asm("sei")
   GICR |= (1 << INT0);
   MCUCR |= (1 << ISC01) | (0 << ISC00);
   DDRB=0X0F;
   keypad_port=0XF0;
   
   lcd_puts("Start");
    while (1)
    {
        if(start == 1)
        {
            delay_ms(1);
            if(turns == 1)
            {
                milsec1 -= 1;
                if(milsec1 <= 0)
                {
                    sec1 -= 1;
                    milsec1 = 99;
                }
                if (sec1 < 0)
                {
                    min1 -= 1;
                    sec1 = 59;
                }
                if (min1 < 0) 
                {
                    min1 = 0; sec1 = 0; milsec1 = 0;
                    sprintf(s,"%d:%d.%d %d:%d.%d", min1, sec1, milsec1, min2, sec2, milsec2);
                    lcd_clear();
                    lcd_puts(s);
                    lcd_gotoxy(0,1);
                    lcd_puts("Player 2 Wins!");
                    start = 0;
                    break;
                }

            }
            if (turns == 2)
            {
                milsec2 -= 1;
                if(milsec2 <= 0)
                {
                    sec2 -= 1;
                    milsec2 = 99;
                }
                if (sec2 < 0)
                {
                    min2 -= 1;
                    sec2 = 59;
                }
                if (min2 < 0) 
                {
                    min2 = 0; sec2 = 0; milsec2 = 0;
                    sprintf(s,"%d:%d.%d %d:%d.%d", min1, sec1, milsec1, min2, sec2, milsec2);
                    lcd_clear();
                    lcd_puts(s);
                    lcd_gotoxy(0,1);
                    lcd_puts("Player 1 Wins!");
                    start = 0;
                    break;
                }

            }
            sprintf(s,"%d:%d.%d %d:%d.%d", min1, sec1, milsec1, min2, sec2, milsec2);
            lcd_clear();
            lcd_puts(s);
        }    
        
    }
}
