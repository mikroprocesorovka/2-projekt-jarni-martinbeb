#include "stm8s.h"
#include "milis.h"

#include "delay.h"
#include <stdio.h>
#include "uart1.h"
#include "keypad.h"

#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4

#define IN1_HIGH   GPIO_WriteHigh(GPIOB, GPIO_PIN_5)
#define IN1_LOW  GPIO_WriteLow(GPIOB, GPIO_PIN_5)

#define IN2_HIGH   GPIO_WriteHigh(GPIOB, GPIO_PIN_4)
#define IN2_LOW  GPIO_WriteLow(GPIOB, GPIO_PIN_4)

#define IN3_HIGH   GPIO_WriteHigh(GPIOB, GPIO_PIN_3)
#define IN3_LOW  GPIO_WriteLow(GPIOB, GPIO_PIN_3)

#define IN4_HIGH   GPIO_WriteHigh(GPIOB, GPIO_PIN_2)
#define IN4_LOW  GPIO_WriteLow(GPIOB, GPIO_PIN_2)

int32_t x = 0;

void pravo(void) {
    
    if (x < 500) {
        x += 1;
    }
    else {
    x = 1;
    }
    //1 krok full step
    IN1_HIGH;
    IN2_LOW;
    IN3_LOW;
    IN4_HIGH;
    delay_ms(3);
    //2 krok
    IN1_LOW;
    IN2_LOW;
    IN3_HIGH;
    IN4_HIGH;
    delay_ms(3);
    //3 krok
    IN1_LOW;
    IN2_HIGH;
    IN3_HIGH;
    IN4_LOW;
    delay_ms(3);
    //4 krok
    IN1_HIGH;
    IN2_HIGH;
    IN3_LOW;
    IN4_LOW;
    delay_ms(3);
}

void setup(void){ 

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
    

    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOB, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOB, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_SLOW);

    init_uart1();
    init_milis();
    init_keypad();
}

int main(void){

        int32_t time_key = 0;
        uint8_t key_last = 0;
        uint8_t key_now = 0;
        uint8_t key_pressed = 0;
        
        setup();

        /*------  nekonečná smyčka    ---*/
        while (1) {

            if (milis() - time_key > 50) { 
            time_key = milis();
            key_now = check_keypad();
            if (key_last == 0xFF && key_now != 0xFF) {
                key_pressed = key_now;
                printf("\r");
                printf("Pozice: ");

                
                // nastavení R,G a B kanálu probíhá vždy v 7 krocích.
                
                if (key_pressed == 2) { //nahoru
                    while (x != 500) {
                        pravo();
                        
                    }
                    printf("nahoře\n\t");
                }
                if (key_pressed == 5) { //v levo
                    while (x != 375) {
                        pravo();
                        
                    }
                    printf("v levo\n");
                }
                if (key_pressed == 10) { //dolů
                    while (x != 250) {
                        pravo();
                        
                    } 
                    printf("dole\n");
                }
                if (key_pressed == 7) { //v pravo
                    while (x != 125) {
                        pravo();
                        
                    }
                    printf("v pravo\n");
                }

                if (key_pressed == 3) { // v pravo nahoře
                    while (x != 63) {
                        pravo();
                        
                    }
                    printf("v pravo nahoře\n");
                }
                if (key_pressed == 11) { // v pravo dole
                    while (x != 188) {
                        pravo();
                        
                    }
                    printf("v pravo dole\n");
                }
                if (key_pressed == 9) { // v levo dole
                    while (x != 313) {
                        pravo();
                        
                    }
                    printf("v levo dole\n");
                }
                if (key_pressed == 1) { // v levo nahoře
                    while (x != 438) {
                        pravo();
                        
                    }
                    printf("v levo nahoře\n");
                }
                
            }
            key_last = key_now;
            }
        }
    
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
