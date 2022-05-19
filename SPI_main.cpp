#include "mbed.h"

SPI spi(PD_6, PC_11, PC_10); // mosi, miso, sclk
DigitalOut cs(PA_4);

uint16_t EncoderByteData = 0;
uint16_t Encoderposition_last = 0;
uint8_t temp[2];
uint16_t Steps;
void wait_ms(int us);


uint8_t SPI_T (uint8_t SPITransmit)//Repetive SPI transmit sequence
{
    uint8_t SPI_temp = 0;  //vairable to hold recieved data
    cs=0;     //select spi device
    SPI_temp = spi.write(SPITransmit);//send and recieve
    cs=1;//deselect spi device
    return(SPI_temp);      //return recieved byte
}

void start()
{
    uint8_t recieved = 0xA5;//just a temp vairable
    EncoderByteData  = 0;//reset position vairable 
    cs=0;  
    SPI_T(0x10);//issue read command     
    ThisThread::sleep_for(1ms);//give time to read. Timmig is critical
    
    while (recieved != 0x10) //loop while encoder is not ready to send
    { 
     recieved = SPI_T(0x00); //cleck again if encoder is still working
     ThisThread::sleep_for(1ms); //again,give time to read. Timmig is critical
    }
 
     temp[0] = SPI_T(0x00); //Recieve MSB
     temp[1] = SPI_T(0x00); // recieve LSB      
     cs=1;
        
     temp[0] &=~ 0xF0;//mask out the first 4 bits
     EncoderByteData  = temp[0] << 8; //shift MSB to correct EncoderByteData in EncoderByteData message
     EncoderByteData  += temp[1]; // add LSB to EncoderByteData message to complete message            
     ThisThread::sleep_for(1ms);//again,give time to read. Timmig is critical
}

int main()
{  
    spi.format(8,0);
    spi.frequency(8000000);
    
 while(true)
    {
    if (EncoderByteData != Encoderposition_last) //if nothing has changed dont wast time sending position
    {
      Encoderposition_last = EncoderByteData ; //set last position to current position         
    }
    else
    {   
      start(); //if something has changed in position, catch it
    } 
        Steps = EncoderByteData;        
       //pc.printf("Data = %d \n", EncoderByteData ); //actual byte reading
        printf("Data = %03d \n", Steps/16 );
    }
    
}