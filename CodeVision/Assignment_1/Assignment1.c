/*
 * Assignment1.c
 *
 * Created: 10/26/2024 11:17:03 AM
 * Author: omidt
 */

#include <mega32.h>
#include <delay.h>
char Data = 0;
char Seven_Segment(char Input_data){
    char K;
    switch(Input_data){
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
        
void initial_sevenSegments(int Data){
    int yekan = Data % 10;
    int dahgan = Data / 10; 
    PORTC = Seven_Segment(dahgan);
    PORTD = Seven_Segment(yekan);
} 

void main(void)
{
    DDRA = 0x00;
    DDRC = 0xFF;
    DDRD = 0xFF;
    PORTC = 0x00;
    PORTD = 0x00;
    
while (1)
    {
    // Please write your application code here
        if(PINA.1 == 0){
            if(PINA.0 == 0){
                if(Data < 99){
                    Data++;
                }
                initial_sevenSegments(Data); 
                delay_ms(1000);
            }
            else if(PINA.0 == 1){
                if(Data > 0){
                    Data--;
                }
                initial_sevenSegments(Data);
                delay_ms(1000);    
            }
        }
        else{
            if(PINA.0 == 0){
                delay_ms(1000);
            }
            else if(PINA.0 == 1){
                Data = 0;
                initial_sevenSegments(Data);
                delay_ms(1000);
            }
        }
    }
}
