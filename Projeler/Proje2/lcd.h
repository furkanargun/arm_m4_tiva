/*
 * lcd.h
 *
 *  Created on: 10 Kas 2024
 *      Author: Argun
 */

#ifndef LCD_H_
#define LCD_H_

#define LCDPORT GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS  GPIO_PIN_0
#define E   GPIO_PIN_1
#define D4  GPIO_PIN_4
#define D5  GPIO_PIN_5
#define D6  GPIO_PIN_6
#define D7  GPIO_PIN_7

extern void lcdKomut(unsigned char);

extern void lcdKarakterYaz(unsigned char);

extern void lcdIlkAyarlar();
// Giriþ kipini seç 0 0 0 0 0 0 0 1    I/D S 40um
// Ekran aç kapa 0 0 0 0 0 0 0 1 D C B  40us
// Kursör kaydýr 0 0 0 0 0 1 S/C R/L * * 40us

extern void lcdFonksiyonAyarla(unsigned char, unsigned char, unsigned char);

extern void LCDTemizle();

extern void lcdGit(unsigned char, unsigned char);
#endif /* LCD_H_ */
