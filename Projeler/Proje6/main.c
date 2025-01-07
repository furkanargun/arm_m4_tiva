#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include "inc/hw_memmap.h"
#include "inc/hw_hibernate.h"
#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"
#include <math.h>
#include "driverlib/fpu.h"

void SetInitSettings();

int main(void) {
	// Sistem saatini ayarla
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Floating Point Unit (FPU) yapılandır
    ConfigureFPU();

    PerformMathOperations();

    while (1) {

    }
    return 0;
}

// Floating Point Unit (FPU) ayarlarını yapar
void ConfigureFPU(void) {
    // FPU'yu etkinleştir
    FPUEnable();

    // FPU yuvarlama modunu ayarla ve alt normal sayıların kullanımını etkinleştir
    FPUStackingEnable();
}

// Floating Point matematiksel işlemleri gerçekleştiren fonksiyon
void PerformMathOperations(void) {
    float num1 = 25.5, num2 = 4.2;
    float sum, difference, product, quotient, sqrtResult;

    // Toplama işlemi
    sum = num1 + num2;

    // Çıkarma işlemi
    difference = num1 - num2;

    // Çarpma işlemi
    product = num1 * num2;

    // Bölme işlemi
    quotient = num1 / num2;

    // Karekök alma
    sqrtResult = sqrt(num1);

    while (1) {

    }
}