#include "mbed.h"

void steering(float rad) {
    static UnbufferedSerial serial_port(PC_12, PD_2); //this line calls the UART ports 
    float pi = 3.14159265; //making the constant pi
    float full_circle; //this is the constant 2*pi
    float unit_per_rad; //this is the consant 127/(2pi), this is needed for the conversion
    float out_f; //this is the output in float form
    int out_i; // this is the output in int form, this is needed because the servo only reads int
    int buf = 225; // this is the buffer decimal, this must be sent before any new change in position
    serial_port.baud(9600); // this sets the baud rate
    serial_port.format(8,SerialBase::None,1); // this sets the format for the the UART communication 
    full_circle = 2 * pi;
    unit_per_rad = 127/full_circle;
    out_f = rad * unit_per_rad; //this math is not correct but stopped becuase we are changing servo's
    out_i = round(out_f); //this rounds the float output to the nearest integer 
    serial_port.write(&buf, 1); //writes the buffer bit needed to send position
    serial_port.write(&out_i, 1); // writes the position
}
