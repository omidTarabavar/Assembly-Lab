/*
 * as3_1.c
 *
 * Created: 11/24/2024 2:57:44 PM
 * Author: omidt
 */
#include <mega32.h>
#include <alcd.h>
#include <delay.h>
unsigned char scan[4]={0XFE,0XFD,0XFB,0XF7};
char Key;
char arrkey[16]={
'7','8','9','/',
'4','5','6','*',
'1','2','3','-',
'C','0','=','+'};
#define c1 PINB.4
#define c2 PINB.5
#define c3 PINB.6
#define c4 PINB.7
#define keypad_port PORTB
char keypad(){
unsigned char r,c,k;

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
}}}}
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
    #asm("cli") 
    
       Key=keypad();
       if (Key == 'C') lcd_clear();
        else lcd_putchar(Key);

      #asm("sei")
}
void main(void){
lcd_init(16);
lcd_clear();
lcd_puts("Start");
delay_ms(1000);
lcd_clear();

while (1){
//Key=keypad();
DDRB=0X0F;
keypad_port=0XF0;

}}
