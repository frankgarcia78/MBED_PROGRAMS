#include "mbed.h"
#include "PwmIn.h"



// main() runs in its own thread in the OS
int main()
{
    PwmIn pin(PC_7);
    //PwmOut pout(PB_9);
   // pout.period(0.001);
    while (true) {
        /*for (float f = 0.1; f <= 1; f += 0.1)
            for(int j = 0; j < 10; j++)
            {
                pout.write(f); */
                ThisThread::sleep_for(200ms);
                printf("period: %f, pulsewidth: %f, dutyCycle: %f.\n", pin.period(), pin.pulsewidth(), pin.dutycycle());
                ThisThread::sleep_for(200ms);
            }
    }

