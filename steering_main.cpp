#include "mbed.h"

// Create a DigitalOutput object to toggle an LED whenever data is received.
static DigitalOut led(LED1);
static DigitalOut led1(LED2);

// Create a UnbufferedSerial object with a default baud rate.
static UnbufferedSerial serial_port(PC_12, PD_2); //connects Arduino to Nucleo
static UnbufferedSerial serial_port1(PE_8, PE_7); //connects nucleo to Servo

void Arduino_to_Nucleo()
{
    char c;
    int num;
    
    led = !led;

    if (serial_port.read(&c, 4)) {
    num = c - '0';
        serial_port.write(&num, 4);
    }
}

void Nucleo_to_Arduino()
{
    int d;

    led1 = !led1;

    if (serial_port1.read(&d, 4)) {

        serial_port1.write(&d, 4);

    }
}

int main(void)
{

    serial_port.baud(9600);
    serial_port.format(8,SerialBase::None,1);
    serial_port1.baud(9600);
    serial_port1.format(8,SerialBase::None,1);



    serial_port.attach(&Arduino_to_Nucleo, SerialBase::RxIrq);
    serial_port1.attach(&Nucleo_to_Arduino, SerialBase::RxIrq);
}
