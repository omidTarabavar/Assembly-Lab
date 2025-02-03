#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
char Buf[16];
char Din,Count=0;
void main(void) {
    UCSRA=0x00;
    UCSRB=0x10;
    UCSRC=0xA6;
    UBRRH=0x00;
    UBRRL=0x0C;  // tebghe in 4800 hastesh baud rate
    lcd_init(16);
    lcd_clear();
    lcd_puts("No Data");
    while (1){
        Din = getchar();
        if(Din == 'C'){
            lcd_clear();
            Count = 0;
        }
        else{
            lcd_clear();
            lcd_putchar(Din);
            lcd_gotoxy(0,1);
            Count++;
            sprintf(Buf,"Count = %d",Count);
            lcd_puts(Buf);
        }
        

    }
}