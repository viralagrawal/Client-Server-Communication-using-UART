#include "stdio.h"
#include"uart.h"
#include"lpc17xx_uart.h"
#include"string.h"
#include"LPC17xx.h"
#include"timer.h"

unsigned char buf[3];

#define millisecond 1000

void rn171_cmd(char*);
void rn171_ack(void);


int main(void)
{

        char opencmd[30];
        char const *argv[2];
    UARTInit(3, 9600);

        rn171_cmd("$$$");
        rn171_cmd("factory RESET");
        rn171_cmd("reboot");
        //sleep(3);

        delayMs(0,3*millisecond);
        rn171_cmd("$$$");
        rn171_cmd("set wlan ssid CMPE242");
        rn171_cmd("set wlan auth 4");
        //usleep(260*milisecond);
        //delayMs(0,100);


        //usleep(260*milisecond);
        //rn171_cmd("set ip loca");
        delayMs(0,1500);
        rn171_cmd("set wlan join 1");
                delayMs(0,1000);
        rn171_cmd("set wlan phrase cmpecmpe");
        delayMs(0,500);
        rn171_cmd("save");
        rn171_cmd("reboot");
    	//    sleep(3);
        delayMs(0,3*millisecond);
        rn171_cmd("$$$");
        delayMs(0,30*millisecond);
        rn171_cmd("open 54.187.158.123 3400");
	delayMs(0,30*millisecond);
	rn171_cmd("CMPE_240_VIRAL_8220");
    	//    usleep(260*milisecond);
    	delayMs(0,1000);

	return 0;
}

void rn171_cmd(char* cmd)
{

     UARTSend(3,cmd,(strlen(cmd)) );
     //usleep(260*milisecond);
     delayMs(0,260);
     UART_SendByte(LPC_UART3,0xd);
}

void rn171_ack(void)
{
    int i;
    char rec;
    for (i = 1;i < 5; i++)
        {
            rec=UART_ReceiveByte(LPC_UART3);
            printf("%c",rec);
        }
}

