/*
 * 2.c
 *
 * Created: 10/20/2024 2:57:29 PM
 * Author: T460s
 */


#include <mega32.h>
#include <delay.h>
char Data = 0;
char Seven_Segment(char Input_Data){
    char K;
    switch (Input_Data){
        case 0: K=0x7E; return K; break;
        case 1: K=0x0C; return K; break;
        case 2: K=0xB6; return K; break;
        case 3: K=0x9E; return K; break;
        case 4: K=0xCC; return K; break;
        case 5: K=0xDA; return K; break;
        case 6: K=0xFA; return K; break;
        case 7: K=0x4E; return K; break;
        case 8: K=0xFE; return K; break;
        case 9: K=0xDE; return K; break;
        default: K=0x00; return K; break;
    } 
}

void main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
    while (1)
        {
        // Please write your application code here
        PORTB = Seven_Segment(Data);
        delay_ms(1000);
        if(Data == 9)
            Data = 0;
        else
            Data++;
        
        }
}
