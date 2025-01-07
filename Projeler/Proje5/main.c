#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include "inc/hw_memmap.h"
#include "inc/hw_hibernate.h"
#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"

void SetInitSettings();

int main(void) {
	// Başlangıç ayarlarını yapılandır
    SetInitSettings();

    // Hibernation moduna geç
    HibernateRequest();
    

    while (1) {

    }

    return 0;
}

void SetInitSettings(){
	// Sistem saatini yapılandır
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    // Hibernation modülünü etkinleştir
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE));

    // Hibernation modülünü yapılandır
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateRTCEnable();  // RTC'yi etkinleştir
    HibernateRTCSet(0);    // RTC zamanını sıfırla
    HibernateRTCMatchSet(0, 10);  // 10 saniye sonra uyanması için ayarla

    // Uyanma sebebini GPIO ve RTC olarak ayarla
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);

}