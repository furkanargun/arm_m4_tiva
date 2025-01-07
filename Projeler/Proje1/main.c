#include <stdint.h>
#include <stdbool.h>
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


void setinitsettings();

 int main(void){
    setinitsettings();

    // LCD baþlangýç ayarlarýný yap
    lcdIlkAyarlar();

    lcdFonksiyonAyarla(0,1,0);
    SysCtlDelay(50000);
    // 1. satýr, 7. sütuna git (1. satýr, 7. sütun)
    lcdGit(1, 7);
    SysCtlDelay(50000);
    // "A" harfini yaz
    lcdKarakterYaz('A');

    // Sonsuz döngü
    while (1) {

    }

    return 0;
}

void setinitsettings(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // Saat Yapýlandýrmasý
}
