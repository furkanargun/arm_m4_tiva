/*
 * lcd.c
 *
 *  Created on: 10 Kas 2024
 *      Author: Argun
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"          // Veri t�rleri i�in
#include "inc/hw_memmap.h"         // Donan�m bellek adresleri i�in
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "lcd.h"

void lcdKomut(uint8_t cmd)
{
    // RS = 0 (Komut g�nderiliyor)
    GPIOPinWrite(LCDPORT, RS, 0);

    // Komutun y�ksek nibble'�n� g�nder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (cmd & 0xF0));
    LCD_EnablePulse();

    // Komutun d���k nibble'�n� g�nder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (cmd << 4));
    LCD_EnablePulse();

    if (cmd < 4)
        SysCtlDelay(50000); // Uzun komutlar i�in bekleme (�rne�in ekran temizleme)
    else
        SysCtlDelay(20000); // K�sa komutlar i�in bekleme
}

void lcdKarakterYaz(unsigned char data)
{
    // RS = 1 (Veri g�nderiliyor)
    GPIOPinWrite(LCDPORT, RS, RS);

    // Verinin y�ksek nibble'�n� g�nder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (data & 0xF0));
    LCD_EnablePulse();

    // Verinin d���k nibble'�n� g�nder
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (data << 4));
    LCD_EnablePulse();

    SysCtlDelay(10000); // Veri g�nderme sonras�nda k�sa bekleme
}

void lcdIlkAyarlar(){
    SysCtlDelay(50000);
    SysCtlPeripheralEnable(LCDPORTENABLE);
    //GPIOPinTypeGPIOOutput(LCDPORT, RS | E | D4 | D5 | D6 | D7);
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

    SysCtlDelay(50000);


    // ayarlar devam
    // lcd komut kullan
    lcdKomut(0x06); // giri� kipi     // Giri� modu ayar� (soldan sa�a)
    //lcdKomut(0x0E); // Ekran a� kapa  // Ekran a��k, kurs�r kapal�
    lcdKomut(0x0C); // Ekran a� kapa  // Ekran a��k, kurs�r kapal�
    lcdKomut(0x18); // Kurs�r kayd�r
    LCDTemizle();

    //lcdKomut(0x18); // Kurs�r kayd�r
}
// Giri� kipini se� 0 0 0 0 0 0 0 1    I/D S 40um
// Ekran a� kapa    0 0 0 0 1 D C B  40us
// Kurs�r kayd�r    0 0 0 1 S/C R/L * * 40us

void lcdFonksiyonAyarla(unsigned char DL, unsigned char N, unsigned char F){
//LCD komutu kullan
// dl = 0-1 4 bit i�in 0
// n = 0-1 2sat�r oldu�u i�in 1
// f = 0-1 5x7piksel lcd i�in f=0
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
        address = 0x80 + col; // �lk sat�r
    } else if (row == 2) {
        address = 0xC0 + col; // �kinci sat�r
    }
    lcdKomut(address);
}

void LCD_EnablePulse(){
    // E pinine darbe g�nder
    GPIOPinWrite(LCDPORT, E, E);
    SysCtlDelay(100); // K�sa gecikme (yakla��k 1 �s)
    GPIOPinWrite(LCDPORT, E, 0);
    SysCtlDelay(100); // K�sa gecikme
}
