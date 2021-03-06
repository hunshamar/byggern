#include "adc_driver.h"
#include "joystick.h"
#include "pwm_driver.h"




void joystick_init(){

    x_offset = 132; // RECIEVED.data[0];
    y_offset = 132; //RECIEVED.data[1];

}


int joystick_get_raw_x(){
    return RECIEVED.data[0];
}

int joystick_get_raw_y(){ //Position directly from the joystick
    return RECIEVED.data[1];
}


int joystick_get_x(){ //changes the joystick signal from 100 to -100

    int x = ((double)(RECIEVED.data[0]) - x_offset);

    if (x >= 0){
        x /= 0.74;
    }
    else{
        x /= 1.4;
    }
    if (x < 5 && x > -5)
        x = 0;

    if (x < -100)
        x = -100;
    if (x > 100)
        x = 100;

    return x;
}

int joystick_get_y(){ 
    int y = ((double)(RECIEVED.data[1]) - y_offset);

    if (y >= 0){
        y /= 0.77;
    }
    else{
        y /= 1.4;
    }
    if (y < 5 && y > -5)
        y = 0;

    if (y < -100)
        y = -100;
    if (y > 100)
        y = 100;

    return y;
}


char* dir_to_string(dir d){ //Easy to detect direction of the joystick
    if (d == 0) return "N";
    if (d == 1) return "R";
    if (d == 2) return "L";
    if (d == 3) return "U";
    if (d == 4) return "D";
    else return "error";
}



int joystick_get_angle(){ //Calculates the angle of the joystick
    
    int x = joystick_get_x();
    int y = joystick_get_y();

    if (y == 0){
        double y = 0.000001;
    }

    int angle = atan(((double)(y))/((double)(x))) * 180 / 3.14159265;

    if (x < 0){
        angle += 180;
    }
    if (angle < 0){
        angle += 360;
    }
    return angle;
}


dir joystick_get_direction(){ //Defines the direction of the joystick
    int x = joystick_get_x();
    int y = joystick_get_y();

    if (x < 80 && x > -80 && y < 80 && y > -80)
        return NEUTRAL;

    int angle = joystick_get_angle(x,y);

    if ((angle <= 360 && angle >= 315) || (angle >= 0 && angle <= 45))
        return RIGHT;
    if (angle > 45 && angle < 135)
        return UP;
    if (angle >= 135 && angle <= 225)
        return LEFT;
    if (angle > 225 && angle < 315)
        return DOWN;
    else
        return NEUTRAL;
}


int joystick_get_button_status(){
    return RECIEVED.data[2];
}


int slider_get_left_pos(){
    return RECIEVED.data[3];
}

int slider_get_right_pos(){    
    return RECIEVED.data[4];
}

int slider_get_left_button_status(){

    return RECIEVED.data[6];
}

int slider_get_right_button_status(){

    return RECIEVED.data[5];
}

void joystick_to_pwm(int x){
    int p = (x+100)/2; //fra 0 til 100%

    int a = ((double)(PWMMAX-PWMMIN))*((double)p)/100.0+PWMMIN;

    pwm_signal(a);
}
