#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

DigitalIn but1(D7);
DigitalIn but2(D6);
DigitalIn but3(D5);
AnalogOut Aout(PA_5);
AnalogIn Ain(A0);
uLCD_4DGL uLCD(D1, D0, D2); 

void wave_gen();
void wave_sample();

Thread thread(osPriorityHigh);
Thread sample(osPriorityAboveNormal);
EventQueue sampleQueue;
int delay = 0;
const int sample_times = 500; 

int main(void)
{
    int temp = 1;

    uLCD.reset();
    thread.start(wave_gen);
    sample.start(callback(&sampleQueue, &EventQueue::dispatch_forever));
    uLCD.locate(0,0);
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.printf("100Hz\n");
    uLCD.textbackground_color(0x000000);
    uLCD.printf("50Hz\n");
    uLCD.textbackground_color(0x000000);
    uLCD.printf("33Hz\n");
    ThisThread::sleep_for(2s);
    while (1) {
        if ((but1 == 1) && (but2 == 0)) {
            temp = 0;
            uLCD.locate(0,0);
            uLCD.textbackground_color(0xFFFFFF);
            uLCD.printf("100Hz\n");
            if (delay == 1) {
                uLCD.textbackground_color(BLUE);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("33Hz\n");
            } else if (delay == 2){
                uLCD.textbackground_color(0x000000);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(BLUE);
                uLCD.printf("33Hz\n");
            } else {
                uLCD.textbackground_color(0x000000);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("33Hz\n");
            }
        } else if ((but1 == 0) && (but2 == 1)) {
            temp = 1;
            uLCD.locate(0,0);
            if (delay == 0) {
                uLCD.textbackground_color(BLUE);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("33Hz\n");
            } else if (delay == 1) {
                uLCD.textbackground_color(0x000000);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("33Hz\n");
            } else {
                uLCD.textbackground_color(0x000000);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(BLUE);
                uLCD.printf("33Hz\n");
            }
        } else if ((but1 == 1) && (but2 == 1)) {
            temp = 2;
            uLCD.locate(0,0);
            if (delay == 0) {
                uLCD.textbackground_color(BLUE);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("33Hz\n");
            } else if (delay == 1) {
                uLCD.textbackground_color(0x000000);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(BLUE);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("33Hz\n");
            } else {
                uLCD.textbackground_color(0x000000);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("33Hz\n");
            }
        }
        if (but3 == 1) {
            delay = temp;
            uLCD.locate(0,0);
            if (delay == 0) {
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("33Hz\n");
            } else if (delay == 1) {
                uLCD.textbackground_color(0x000000);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0x000000);
                uLCD.printf("33Hz\n");
            } else {
                uLCD.textbackground_color(0x000000);
                uLCD.printf("100Hz\n");
                uLCD.textbackground_color(0x000000F);
                uLCD.printf("50Hz\n");
                uLCD.textbackground_color(0xFFFFFF);
                uLCD.printf("33Hz\n");
            }
            ThisThread::sleep_for(2s);
            sampleQueue.call(&wave_sample);
        }
        ThisThread::sleep_for(10ms);
    }
}

void wave_gen()
{
    int i = 0;
    float out = 0, add = 0.101, mns = 0.909;

    while (true) {
        for (i = 0, out = 0; i < 10; i++) {
            if (i < 9) {
                out += add;
            } else {
                out -= mns;
            }
            Aout = out;
            if (delay == 0) {
                ThisThread::sleep_for(1ms);
            } else if (delay == 1) {
                ThisThread::sleep_for(2ms);
            } else {
                ThisThread::sleep_for(3ms);
            }
        }
    }
}

void wave_sample()
{
    int i = 0;
    float ADC_value[sample_times];

    for (i = 0; i < sample_times; i++) {
        ADC_value[i] = Ain;
        ThisThread::sleep_for(2ms);
    }
    for (i = 0; i < sample_times; i++) {
        printf("%f\r\n", ADC_value[i]);
        ThisThread::sleep_for(50ms);
    }
}
