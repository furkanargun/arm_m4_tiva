#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"     // GPIO_PIN_x tanýmlamalarý için
#include "inc/hw_memmap.h"         // Donaným bellek adresleri için
#include "inc/hw_types.h"          // Veri türleri için
#include "inc/hw_gpio.h"
#include "lcd.h"
#include "driverlib/uart.h"


// Global deðiþkenler
char receivedData[50];
volatile uint8_t hour = 0, minute = 0, second = 0;


void uart_ayari();
void diger_ayar();
void serikesme();
void parseData();
void SetInitSettings();
void saatiGonder();

int saatdizi[8]={1,3,10,4,5,10,3,5};

//volatile uint8_t hour = 0;
//volatile uint8_t minute = 0;
//volatile uint8_t second = 0;

//void SetInitSettings();
//void timerkesmefonksiyonu();

int main(void){
        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
        IntMasterEnable();
        uart_ayari();
        diger_ayar();

        lcdIlkAyarlar();
        SetInitSettings();
        lcdFonksiyonAyarla(0, 1, 0);
        SysCtlDelay(50000);
        LCDTemizle();

        UARTCharPut(UART0_BASE, 'A' );
        //UARTCharPut(UART0_BASE, 'A' );
        while (1) {
            //saatiGonder();
        }
}

void diger_ayar() {
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntRegister(UART0_BASE, serikesme);
}

void uart_ayari() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void serikesme() {
    static uint8_t index = 0;
    char c = UARTCharGet(UART0_BASE);

    if (c == '\n') {
        receivedData[index] = '\0';
        parseData();
        index = 0;
    } else {
        receivedData[index++] = c;
    }
}
void lcdStringYaz(char *data) {
    while (*data) {  // Verinin sonuna kadar gider
        lcdKarakterYaz(*data);  // Her bir karakteri yazdýr
        data++;  // Sonraki karaktere geç
    }
}
void saatiGonder() {
    int i;
    UARTCharPut(UART0_BASE, '$' );
    for (i=0;i<8;i++){
        UARTCharPut(UART0_BASE, saatdizi[i]+48);
        UARTCharPut(UART0_BASE, 'A' );
    }
    UARTCharPut(UART0_BASE, '\n');
}


void parseData() {
    if (receivedData[0] == '#' && receivedData[strlen(receivedData) - 1] == '#') {
        // Metin verisi
        receivedData[strlen(receivedData) - 1] = '\0'; // Son # iþaretini sil
        lcdGit(1, 1);
        lcdStringYaz(receivedData + 1); // Ýlk # iþaretini atla ve string'i yazdýr
    } else if (receivedData[0] == '$' && receivedData[strlen(receivedData) - 1] == '$') {
        receivedData[strlen(receivedData) - 1] = '\0'; // Son $ iþaretini sil
        // Saat verisi
        sscanf(receivedData + 1, "%2d:%2d:%2d", &hour, &minute, &second);
        //lcdGit(2, 1);
        //lcdStringYaz(receivedData + 1); // Saat verisini LCD'ye yazdýr
    }
}

void timerkesmefonksiyonu()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // bayrak temizlendi
    second++;
    if (second == 60) {
        second = 0;
        minute++;
        if (minute == 60) {
            minute = 0;
            hour++;
            if (hour == 24) {
                hour = 0;
            }
        }
    }
    // Saat verisini sürekli gönder
    char timeBuffer[20];
    sprintf(timeBuffer, "%02d:%02d:%02d\n", hour, minute, second);
    int i;
    for (i = 0; i<8; i++) {
        UARTCharPut(UART0_BASE, timeBuffer[i]);
    }

    // LCD ekranýn 2. satýrýnda 8. sütuna git
    lcdGit(2, 8);
    // Saat (hour)
    lcdKarakterYaz('0' + (hour / 10));   // Saatin ilk basamaðýný yaz
    lcdKarakterYaz('0' + (hour % 10));   // Saatin ikinci basamaðýný yaz
    lcdKarakterYaz(':');                  // Saat ve dakika arasýna ':' ekle

    // Dakika (minute)
    lcdKarakterYaz('0' + (minute / 10)); // Dakikanýn ilk basamaðýný yaz
    lcdKarakterYaz('0' + (minute % 10)); // Dakikanýn ikinci basamaðýný yaz
    lcdKarakterYaz(':');                  // Dakika ve saniye arasýna ':' ekle

    // Saniye (second)
    lcdKarakterYaz('0' + (second / 10)); // Saniyenin ilk basamaðýný yaz
    lcdKarakterYaz('0' + (second % 10)); // Saniyenin ikinci basamaðýný yaz
}

void SetInitSettings(){

    // timer ayarlar
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); // down sayc
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()); // 40 000 000 1 sn iin

    // 2 global
    IntMasterEnable();
    IntEnable(INT_TIMER0A);

    // 3yerel interrupt ayarlari
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // bayrak temizlendi
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerkesmefonksiyonu);

    TimerEnable(TIMER0_BASE, TIMER_A); // setb tr0
}
