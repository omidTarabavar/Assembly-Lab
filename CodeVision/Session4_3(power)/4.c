/*
 * 4.c
 *
 * Created: 11/3/2024 1:44:56 PM
 * Author: omidt
 */

#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>
#include <math.h>
unsigned char scan[4]={0XFE,0XFD,0XFB,0XF7};
char Key, State=0, Operand;
char Buf1[5], Buf0[5],Buf[16];
int Num0=0, Num1=0, Result;
char arrkey[16]=
{
 '1','2','3','/',
 '4','5','6','*',
 '7','8','9','-',
 'C','0','=','+'
};

#define c1 PINB.4
#define c2 PINB.5
#define c3 PINB.6
#define c4 PINB.7
#define keypad_port PORTB


int power(int a, int b)
{
    int i;
    int result = 1;
    for(i = 1; i <=b; i++)
    {
        result *= a;
    }
    return result;

}

char keypad(){
    unsigned char r,c,k;
    DDRB=0X0F;
    keypad_port=0XFF;
    while(1){
        for (r=0; r<4; r++){
            c=255;
            keypad_port=scan[r];
            delay_us(10);
            if(c1==0) c=0; if(c2==0) c=1; if(c3==0) c=2; if(c4==0) c=3;
            if (c!=255){
                k=arrkey[(r*4)+c];
                while(c1==0); while(c2==0); while(c3==0); while(c4==0);
                delay_ms(50);
                return k;
            }
        }
    }
}

void main(void)
{
    lcd_init(16);
    lcd_clear();
    lcd_puts("Start");
    delay_ms(1000);
    lcd_clear();
    while (1)
    {
        Key=keypad();
        switch (State) 
        {
            case 0:
            if (Key == 'C') 
            {
                Num0=0; Num1=0; Operand=''; lcd_clear(); lcd_putchar('0');
            }
            else if ((Key == '+') | (Key == '-') | (Key == '/') | (Key == '*')) 
            {
                Operand = Key; lcd_clear(); lcd_puts(Buf1);
                lcd_putchar(' '); lcd_putchar(Key); lcd_putchar(' '); State =1;
            }
            else 
            {
                Num1 = Num1 * 10 + Key - 48; lcd_clear();
                sprintf(Buf1,"%d",Num1); lcd_puts(Buf1);
            }
            break;
            case 1:
            if (Key == 'C') 
            {
                Num0=0; Num1=0; Operand=''; lcd_clear(); lcd_putchar('0'); State = 0;
            }
            else if ((Key == '1') | (Key == '2') | (Key == '3') | (Key == '4')| (Key == '5') | (Key == '6') | (Key == '7') | (Key == '8')
                | (Key == '9') | (Key == '0')) 
            {
                Num0 = Num0 * 10 + Key - 48; lcd_gotoxy(0,0); lcd_puts(Buf1);
                lcd_putchar(' '); lcd_putchar(Operand); lcd_putchar(' ');
                sprintf(Buf0,"%d",Num0); lcd_puts(Buf0);
            }
            else if (Key == '=')
            {
                lcd_putchar(' '); lcd_putchar(Key); lcd_gotoxy(0,1);
                if (Operand == '+') 
                {
                    Result = Num1 + Num0; sprintf(Buf,"%d",Result); lcd_puts(Buf);
                }
                else if (Operand == '-') 
                {
                    Result = Num1 - Num0; sprintf(Buf,"%d",Result); lcd_puts(Buf);
                }
                else if (Operand == '/') 
                {
                    if (Num1 == 0) 
                    {
                        Result = 1; lcd_puts("Nan");
                    }
                    else 
                    {
                        Result = power(Num1,Num0); 
                        sprintf(Buf,"%d",Result); lcd_puts(Buf);
                    }
                }
                else if (Operand == '*') 
                {
                    Result = Num1 * Num0 ; sprintf(Buf,"%d",Result); lcd_puts(Buf);
                }
                    State = 0; Num0 = 0; Num1 = Result; sprintf(Buf1,"%d",Num1);
            }
            break;
        }
    }
}