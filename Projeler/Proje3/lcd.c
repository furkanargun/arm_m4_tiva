/*
 * lcd.c
 *
 *  Created on: 10 Kas 2024
 *      Author: Argun
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"          // Veri türleri için
#include "inc/hw_memmap.h"         // Donaným bellek adresleri için
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "lcd.h"

void lcdKomut(uint8_t cmd)
{
    // RS = 0 (Komut gönderiliyor)
    GPIOPinWrite(LCDPORT, RS, 0);

    // Komutun yüksek nibble'ýný gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (cmd & 0xF0));
    LCD_EnablePulse();

    // Komutun düþük nibble'ýný gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (cmd << 4));
    LCD_EnablePulse();

    if (cmd < 4)
        SysCtlDelay(50000); // Uzun komutlar için bekleme (örneðin ekran temizleme)
    else
        SysCtlDelay(20000); // Kýsa komutlar için bekleme
}

void lcdKarakterYaz(unsigned char data)
{
    // RS = 1 (Veri gönderiliyor)
    GPIOPinWrite(LCDPORT, RS, RS);

    // Verinin yüksek nibble'ýný gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (data & 0xF0));
    LCD_EnablePulse();

    // Verinin düþük nibble'ýný gönder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (data << 4));
    LCD_EnablePulse();

    SysCtlDelay(10000); // Veri gönderme sonrasýnda kýsa bekleme
}

void lcdIlkAyarlar(){
    SysCtlDelay(50000);
    SysCtlPeripheralEnable(LCDPORTENABLE);
    //GPIOPinTypeGPIOOutput(LCDPORT, RS | E | D4 | D5 | D6 | D7);
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

    SysCtlDelay(50000);


    // ayarlar devam
    // lcd komut kullan
    lcdKomut(0x06); // giriþ kipi     // Giriþ modu ayarý (soldan saða)
    //lcdKomut(0x0E); // Ekran aç kapa  // Ekran açýk, kursör kapalý
    lcdKomut(0x0C); // Ekran aç kapa  // Ekran açýk, kursör kapalý
    lcdKomut(0x18); // Kursör kaydýr
    LCDTemizle();

    //lcdKomut(0x18); // Kursör kaydýr
}
// Giriþ kipini seç 0 0 0 0 0 0 0 1    I/D S 40um
// Ekran aç kapa    0 0 0 0 1 D C B  40us
// Kursör kaydýr    0 0 0 1 S/C R/L * * 40us

void lcdFonksiyonAyarla(unsigned char DL, unsigned char N, unsigned char F){
//LCD komutu kullan
// dl = 0-1 4 bit için 0
// n = 0-1 2satýr olduðu için 1
// f = 0-1 5x7piksel lcd için f=0
    if (DL == 0) {
        if(N== 0){
            if(F==0){
                lcdKomut(0x20);
            } else{
                lcdKomut(0x24);
            }
        } else{
            if(F==0){
                lcdKomut(0x28);
            } else{
                lcdKomut(0x2c);
            }
        }
    } else {
        if(N== 0){
            if(F==0){
                lcdKomut(0x30);
            } else{
                lcdKomut(0x34);
            }
        } else{
            if(F==0){
                lcdKomut(0x38);
            } else{
                lcdKomut(0x3c);
            }
        }
    }
}

void LCDTemizle(){
    lcdKomut(0x01);
    SysCtlDelay(50000);
}

void lcdGit(unsigned char row, unsigned char col){
    unsigned char address;
    if (row == 1) {
        address = 0x80 + col; // Ýlk satýr
    } else if (row == 2) {
        address = 0xC0 + col; // Ýkinci satýr
    }
    lcdKomut(address);
}

void LCD_EnablePulse(){
    // E pinine darbe gönder
    GPIOPinWrite(LCDPORT, E, E);
    SysCtlDelay(100); // Kýsa gecikme (yaklaþýk 1 µs)
    GPIOPinWrite(LCDPORT, E, 0);
    SysCtlDelay(100); // Kýsa gecikme
}
