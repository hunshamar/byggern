#include "can_driver.h"


void can_init(){ //initializes the CAN bus

    spi_init();

    mcp2515_reset();
    mcp2515_bit_modify(0b11100000,MCP_CANCTRL,MODE_NORMAL); //Setting the mcp2515 to normal mode
    mcp2515_bit_modify(0x60, MCP_RXB0CTRL, 0b01100000); //recieve buffer 0 control 

    mcp2515_bit_modify(0b1, MCP_CANINTE, 0b00000001); //sets the RX0IE bit in CANINTE and enables the RXOIF flag
}


void can_write(message msg){ //Puts a message on the CAN bus
     

    //Writes the ID of the receiver to the right registers. ID is 11 bits. 8 LSB in the SIDH register, and the MSB in SIDL register
    mcp2515_write(MCP_TXB0SIDH, (uint8_t)(msg.ID >> 3)); //8 MSB
    mcp2515_bit_modify(0b11100000, MCP_TXB0SIDL, (uint8_t)(msg.ID << 5));  //3 LSB

    //Configures the datalength in DLC register.
    mcp2515_bit_modify(0b00001111,MCP_TXB0DLC,msg.length);
    
    //Data transfer. Maximum 8 bytes of data. Writes to register TDXB0D0 through TDXB0D7
    for (int length = 0; length < msg.length; length++){
        mcp2515_write(MCP_TXB0D0 + length, msg.data[length]);
              
    }
    //request to send the message written to the registers on the CAN bus
    mcp2515_rts(1);

}

int can_transmit_complete(){ //Checks the TXB0CTRL flag if transmit is complete
    return mcp2515_check_bit(MCP_TXB0CTRL,3);
}

int can_check_recieved_flag(){ //checks if the can recieved a message
    return mcp2515_check_bit(MCP_CANINTF,0);
}

message can_read(){ //reads a message from the CAN bus
    message msg;
    if(mcp2515_check_bit(MCP_CANINTF,0)){ //Checks if reception of message is complete
        uint8_t ID_high = mcp2515_read(MCP_RXB0SIDH);
        uint8_t ID_low = mcp2515_read(MCP_RXB0SIDL);
        msg.ID = (ID_high << 3) | (ID_low >> 5); //11 bit adress
        //printf("idid: ")

        msg.length = mcp2515_read(MCP_RXB0DLC) & 0x0F; //reading 4 LSB
      

        for (int l = 0; l < msg.length; l++){
            msg.data[l] = mcp2515_read(MCP_RXB0D0 + l);
        }
        mcp2515_bit_modify(0b00000011,MCP_CANINTF,0b00000000);
    }
    else printf("Cannot read from CAN bus \n\r");


    return msg;
}

void can_send_actuator_signals(){
      
    //Declare variables
    message msg;
    msg.ID = 1;
    msg.length = 7;
    msg.data[0] = read_adc_channel(CHANNEL_1); //x
    msg.data[1] = read_adc_channel(CHANNEL_2); //y
    msg.data[2] = joystick_get_button_status(); //joystickknapp
    msg.data[3] = slider_get_left_pos();
    msg.data[4] = slider_get_right_pos();
    msg.data[5] = slider_get_left_button_status();
    msg.data[6] = slider_get_right_button_status();
    
    can_write(msg);
}