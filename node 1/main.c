
#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include "Uart_driver.h"
#include <util/delay.h>
#include "SRAM.h"
#include "adc_driver.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi_driver.h"
#include "mcp2515.h"
#include "interrupt.h"

#include "can_driver.h"


int main(){
    
    //Initializing modules
    uart_init(9600);
    SRAM_init();
    joystick_init();
    can_init();
    interrupt_init();
    sei();
    
    //Declare variables
    /*
    message msg;
    msg.ID = 1;
    msg.length = 7;
    int i = 0;
    */

    printf("HEI \n\r");
    while(1){

    
    if(mcp2515_check_bit(MCP_CANINTF,0)){
        message recieved = can_read();
        printf("Mottatt can: %d %d \n\r", recieved.data[0],recieved.data[1]);
    }
    /*
    msg.data[0] = read_adc_channel(CHANNEL_1); //x
    msg.data[1] = read_adc_channel(CHANNEL_2); //y
    msg.data[2] = joystick_get_button_status(); //joystickknapp
    msg.data[3] = slider_get_left_pos();
    msg.data[4] = slider_get_right_pos();
    msg.data[5] = slider_get_left_button_status();
    msg.data[6]MCP_CANINTE = slider_get_right_button_status();
    

    _delay_ms(17); //sender ish 60 hz

    can_write(msg);
    
    printf("sender X: %d Y: %d \n\r", msg.data[0], msg.data[1], msg.data[2]);
    */



    //printf("  mottatt x: %d \n\r", can_read().data[0]);
   }

    
    

/*send_voltage
int asd = 0;
while(1){
    can_write(msg); 
    asd+=1;
    if (asd%1000 == 0){
        printf("sender\n\r");
        asd = 0;
    }
}*/

    //direction where = get_direction(get_joy_coords_x,get_joy_coords_y);
    



    //oled_init();
    //spi_init();
    /*
    while(1){
        //mcp2515_write(0x0F,'i');
        //printf("HER ERN: %c \n\r", mcp2515_read(0x0F));
        
        mcp2515_read_status();

    }*/


    //menu();

    //while(1){

        //can_init();
        //oled_write_to_pixel(20,20);
        /*
        for (int i = 0; i<64;i++){
            _delay_ms(20);
            oled_write_data(i,0x00);
        }

        for (int i = 64; i<128;i++){
            _delay_ms(20);
            oled_write_data(i,0xFF);
        }*/

        /*
        int x =  get_joy_coords_x(cs);
        int y =  get_joy_coords_y(cs);

        printf("slider pos: %d\n\r", get_right_slider_pos());

        
        printf("Joystick. X = %d  Y= %d     ", x, y);



        printf("Angle: %d   ", get_angle(x, y));

        printf("Direction is: %s\n\r", dir_to_string(get_direction(x,y)));   //(get_joy_coords_x(cs), get_joy_coords_y(cs)));

        */
         // {0b01111100,0b01111110,0b00010011,0b00010011,0b01111110,0b01111100,0b00000000,0b00000000}

     
    //}

    //adc_test();
    //printf(" SVEIS ");
    //_delay_ms(2000);
    //SRAM_test();
    //_delay_ms(3000);
    /*
    while(1){a
        char letter = 0;
        while(letter ==0){
            letter = uart_recieve();
    }   
        letter+= ('A'-'a');
        uart_transmit(letter);
}
*/
    /*
    while(1){

        uart_transmit('b');
        _delay_ms(1000);
    }*/

    //inputs
    //DDRA = 0x00;

    //Gjør til output
    //DDRB = 0xFF;

    /*while(1){if(y <= 10 && y >= -10){
        where.y = NEUTRAL;
    }  
    else if(y > 0){
        where.y = RIGHT;
    }
    else if(y > 0 ){
        where.y = LEFT;
    }
}
        PORTB = (1 << PB1);
        _delay_ms(1000);

        PORTB = (0 << PB1);
        _delay_ms(1000);
    }*/
    return 0;
}