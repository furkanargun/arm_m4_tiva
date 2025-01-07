#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"     // GPIO_PIN_x tan�mlamalar� i�in
#include "inc/hw_memmap.h"         // Donan�m bellek adresleri i�in
#include "inc/hw_types.h"          // Veri t�rleri i�in
#include "inc/hw_gpio.h"
#include "lcd.h"

volatile uint8_t hour = 0;
volatile uint8_t minute = 0;
volatile uint8_t second = 0;
//bool isFirstTime = true;

void SetInitSettings();
void timerkesmefonksiyonu();

int main(void){
    SetInitSettings();
    lcdIlkAyarlar();
    lcdFonksiyonAyarla(0,1,0);
    SysCtlDelay(50000);

    // LCD ba�lang�� ayarlar�n� yap
    // Sonsuz d�ng�
    while (1) {

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

    // LCD ekran�n 2. sat�r�nda 8. s�tuna git
    lcdGit(2, 8);
    // Saat (hour)
    lcdKarakterYaz('0' + (hour / 10));   // Saatin ilk basama��n� yaz
    lcdKarakterYaz('0' + (hour % 10));   // Saatin ikinci basama��n� yaz
    lcdKarakterYaz(':');                  // Saat ve dakika aras�na ':' ekle

    // Dakika (minute)
    lcdKarakterYaz('0' + (minute / 10)); // Dakikan�n ilk basama��n� yaz
    lcdKarakterYaz('0' + (minute % 10)); // Dakikan�n ikinci basama��n� yaz
    lcdKarakterYaz(':');                  // Dakika ve saniye aras�na ':' ekle

    // Saniye (second)
    lcdKarakterYaz('0' + (second / 10)); // Saniyenin ilk basama��n� yaz
    lcdKarakterYaz('0' + (second % 10)); // Saniyenin ikinci basama��n� yaz
}

void SetInitSettings(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // 40mhz

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
