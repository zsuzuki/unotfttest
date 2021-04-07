#pragma once

#include <Arduino.h>
#include "font.h"

namespace DRAW9486
{
#define LCD_RD A0
#define LCD_WR A1
#define LCD_RS A2
#define LCD_CS A3
#define LCD_REST A4

#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

#define TS_MINX 906
#define TS_MAXX 116

#define TS_MINY 92
#define TS_MAXY 952

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define DRAW_H 0

    void Lcd_Writ_Bus(unsigned char d)
    {
        PORTD = (PORTD & B00000011) | ((d)&B11111100);
        PORTB = (PORTB & B11111100) | ((d)&B00000011);
        *(portOutputRegister(digitalPinToPort(LCD_WR))) &= ~digitalPinToBitMask(LCD_WR);
        *(portOutputRegister(digitalPinToPort(LCD_WR))) |= digitalPinToBitMask(LCD_WR);
    }

    void Lcd_Write_Com(unsigned char VH)
    {
        *(portOutputRegister(digitalPinToPort(LCD_RS))) &= ~digitalPinToBitMask(LCD_RS); //LCD_RS=0;
        Lcd_Writ_Bus(VH);
    }

    void Lcd_Write_Data(unsigned char VH)
    {
        *(portOutputRegister(digitalPinToPort(LCD_RS))) |= digitalPinToBitMask(LCD_RS); //LCD_RS=1;
        Lcd_Writ_Bus(VH);
    }

    void Lcd_Write_Com_Data(unsigned char com, unsigned char dat)
    {
        Lcd_Write_Com(com);
        Lcd_Write_Data(dat);
    }

    void Address_set(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
    {
        Lcd_Write_Com(0x2a);
        Lcd_Write_Data(x1 >> 8);
        Lcd_Write_Data(x1);
        Lcd_Write_Data(x2 >> 8);
        Lcd_Write_Data(x2);
        Lcd_Write_Com(0x2b);
        Lcd_Write_Data(y1 >> 8);
        Lcd_Write_Data(y1);
        Lcd_Write_Data(y2 >> 8);
        Lcd_Write_Data(y2);
        Lcd_Write_Com(0x2c);
    }

    void LCD_init()
    {
        for (int p = 0; p < 10; p++)
        {
            pinMode(p, OUTPUT);
        }
        pinMode(A0, OUTPUT);
        pinMode(A1, OUTPUT);
        pinMode(A2, OUTPUT);
        pinMode(A3, OUTPUT);
        pinMode(A4, OUTPUT);
        digitalWrite(A0, HIGH);
        digitalWrite(A1, HIGH);
        digitalWrite(A2, HIGH);
        digitalWrite(A3, HIGH);
        digitalWrite(A4, HIGH);

        digitalWrite(LCD_REST, HIGH);
        delay(5);
        digitalWrite(LCD_REST, LOW);
        delay(15);
        digitalWrite(LCD_REST, HIGH);
        delay(15);

        digitalWrite(LCD_CS, HIGH);
        digitalWrite(LCD_WR, HIGH);
        digitalWrite(LCD_CS, LOW); //CS

        Lcd_Write_Com(0xF9);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x08);
        Lcd_Write_Com(0xC0);
        Lcd_Write_Data(0x19);
        Lcd_Write_Data(0x1A);
        Lcd_Write_Com(0xC1);
        Lcd_Write_Data(0x45);
        Lcd_Write_Data(0X00);
        Lcd_Write_Com(0xC2);
        Lcd_Write_Data(0x33);
        Lcd_Write_Com(0xC5);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x28);
        Lcd_Write_Com(0xB1);
        Lcd_Write_Data(0x90);
        Lcd_Write_Data(0x11);
        Lcd_Write_Com(0xB4);
        Lcd_Write_Data(0x02);
        Lcd_Write_Com(0xB6);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x42);
        Lcd_Write_Data(0x3B);
        Lcd_Write_Com(0xB7);
        Lcd_Write_Data(0x07);
        Lcd_Write_Com(0xE0);
        Lcd_Write_Data(0x1F);
        Lcd_Write_Data(0x25);
        Lcd_Write_Data(0x22);
        Lcd_Write_Data(0x0B);
        Lcd_Write_Data(0x06);
        Lcd_Write_Data(0x0A);
        Lcd_Write_Data(0x4E);
        Lcd_Write_Data(0xC6);
        Lcd_Write_Data(0x39);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x00);
        Lcd_Write_Com(0xE1);
        Lcd_Write_Data(0x1F);
        Lcd_Write_Data(0x3F);
        Lcd_Write_Data(0x3F);
        Lcd_Write_Data(0x0F);
        Lcd_Write_Data(0x1F);
        Lcd_Write_Data(0x0F);
        Lcd_Write_Data(0x46);
        Lcd_Write_Data(0x49);
        Lcd_Write_Data(0x31);
        Lcd_Write_Data(0x05);
        Lcd_Write_Data(0x09);
        Lcd_Write_Data(0x03);
        Lcd_Write_Data(0x1C);
        Lcd_Write_Data(0x1A);
        Lcd_Write_Data(0x00);
        Lcd_Write_Com(0xF1);
        Lcd_Write_Data(0x36);
        Lcd_Write_Data(0x04);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x3C);
        Lcd_Write_Data(0x0F);
        Lcd_Write_Data(0x0F);
        Lcd_Write_Data(0xA4);
        Lcd_Write_Data(0x02);
        Lcd_Write_Com(0xF2);
        Lcd_Write_Data(0x18);
        Lcd_Write_Data(0xA3);
        Lcd_Write_Data(0x12);
        Lcd_Write_Data(0x02);
        Lcd_Write_Data(0x32);
        Lcd_Write_Data(0x12);
        Lcd_Write_Data(0xFF);
        Lcd_Write_Data(0x32);
        Lcd_Write_Data(0x00);
        Lcd_Write_Com(0xF4);
        Lcd_Write_Data(0x40);
        Lcd_Write_Data(0x00);
        Lcd_Write_Data(0x08);
        Lcd_Write_Data(0x91);
        Lcd_Write_Data(0x04);
        Lcd_Write_Com(0xF8);
        Lcd_Write_Data(0x21);
        Lcd_Write_Data(0x04);
        Lcd_Write_Com(0x36);
        Lcd_Write_Data(0x48);
        Lcd_Write_Com(0x3A);
        Lcd_Write_Data(0x55);

        Lcd_Write_Com(0x11); //Exit Sleep
        delay(120);
        Lcd_Write_Com(0x29); //Display on
    }

    void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
    {
        unsigned int i, j;
        Lcd_Write_Com(0x02c); //write_memory_start
        digitalWrite(LCD_RS, HIGH);
        digitalWrite(LCD_CS, LOW);
        l = l + x;
        Address_set(x, y, l, y);
        j = l * 2;
        for (i = 1; i <= j; i++)
        {
            Lcd_Write_Data(c >> 8);
            Lcd_Write_Data(c);
        }
        digitalWrite(LCD_CS, HIGH);
    }

    void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
    {
        unsigned int i, j;
        Lcd_Write_Com(0x02c); //write_memory_start
        digitalWrite(LCD_RS, HIGH);
        digitalWrite(LCD_CS, LOW);
        l = l + y;
        Address_set(x, y, x, l);
        j = l * 2;
        for (i = 1; i <= j; i++)
        {
            Lcd_Write_Data(c >> 8);
            Lcd_Write_Data(c);
        }
        digitalWrite(LCD_CS, HIGH);
    }

#if DRAW_H
    void LineH(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
    {
        H_line(x, y, l, c);
    }
    void LineV(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
    {
        V_line(x, y, l, c);
    }
#else
    void LineH(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
    {
        V_line(y, x, l, c);
    }
    void LineV(unsigned int x, unsigned int y, unsigned int l, unsigned int c)
    {
        H_line(y, x, l, c);
    }
#endif

    void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c)
    {
#if DRAW_H
        H_line(x, y, w, c);
        H_line(x, y + h, w, c);
        V_line(x, y, h, c);
        V_line(x + w, y, h, c);
#else
        H_line(y, x, h, c);
        H_line(y, x + w, h, c);
        V_line(y, x, w, c);
        V_line(y + h, x, w, c);
#endif
    }

    void Fill(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c)
    {
#if DRAW_H
        unsigned int i;
        for (i = 0; i < h; i++)
        {
            H_line(x, y + i, w, c);
        }
#else
        unsigned int i;
        for (i = 0; i < w; i++)
            H_line(y, x + i, h, c);
#endif
    }
    constexpr int RGB(int r, int g, int b)
    {
        return r << 11 | g << 5 | b;
    }
    void LCD_clear(unsigned int j = RGB(0, 0, 0))
    {
        unsigned int i, m;
        Address_set(0, 0, 320, 480);
        //Lcd_Write_Com(0x02c); //write_memory_start
        //digitalWrite(LCD_RS,HIGH);
        digitalWrite(LCD_CS, LOW);

        for (i = 0; i < 320; i++)
            for (m = 0; m < 480; m++)
            {
                Lcd_Write_Data(j >> 8);
                Lcd_Write_Data(j);
            }
        digitalWrite(LCD_CS, HIGH);
    }

    //
    void print(const char *str, int px, int py, int color = 0xffff, int bg = 0)
    {
#if DRAW_H
        px = 320 - px - 8;
#else
        // py = 320 - py;
#endif
        for (; *str != '\0'; str++)
        {
            int ch = *str;
            if (ch >= ' ' && ch <= '~')
            {
                ch = FontMap[ch - ' '];
            }
            else
            {
                ch = SF_SP;
            }

            const u8 *font = SimpleFont[ch];
            for (int y = 0; y < 8; y++)
            {
                u8 hl = font[y];
                Lcd_Write_Com(0x02c);
                digitalWrite(LCD_RS, HIGH);
                digitalWrite(LCD_CS, LOW);
#if DRAW_H
                Address_set(px, py + y, px + 8, py + y);
#else
                Address_set(py + y, px, py + y, px + 8);
#endif
                for (int x = 0; x < 8; x++)
                {
#if DRAW_H
                    bool draw = hl & 1;
#else
                    bool draw = hl & 0x80;
#endif
                    uint16_t c = draw ? color : bg;
                    Lcd_Write_Data(c >> 8);
                    Lcd_Write_Data(c);
#if DRAW_H
                    hl >>= 1;
#else
                    hl <<= 1;
#endif
                }
                digitalWrite(LCD_CS, HIGH);
            }
#if DRAW_H
            px -= 8;
#else
            px += 8;
#endif
        }
    }
}
