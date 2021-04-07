#include <Arduino.h>
#include <draw9486.h>

void getNumberDec(int &num, const char *&p)
{
  for (int i = 0; i < 3; i++)
  {
    num *= 10;
    num += (*p++) - '0';
  }
}
void getNumberHex(int &num, const char *&p)
{
  for (int i = 0; i < 4; i++)
  {
    num <<= 4;
    switch (char n = *p++)
    {
    case '0' ... '9':
      num += n - '0';
      break;
    case 'a' ... 'f':
      num += n - 'a' + 10;
      break;
    case 'A' ... 'F':
      num += n - 'A' + 10;
      break;
    default:
      break;
    }
  }
}

void printString(const char *p, size_t sz)
{
  if (sz > 14)
  {
    int x = 0, y = 0;
    getNumberDec(x, p);
    getNumberDec(y, p);
    int c = 0, b = 0;
    getNumberHex(c, p);
    getNumberHex(b, p);
    DRAW9486::print(p, x, y, c, b);
  }
}

void drawRect(const char *p, size_t sz)
{
  if (sz != 17)
    return;

  int n[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; i++)
    getNumberDec(n[i], p);
  int c = 0;
  getNumberHex(c, p);
  DRAW9486::Rect(n[0], n[1], n[2], n[3], c);
}

void drawFill(const char *p, size_t sz)
{
  if (sz != 17)
    return;

  int n[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; i++)
    getNumberDec(n[i], p);
  int c = 0;
  getNumberHex(c, p);
  DRAW9486::Fill(n[0], n[1], n[2], n[3], c);
}

void drawHline(const char *p, size_t sz)
{
  if (sz != 14)
    return;

  int n[3] = {0, 0, 0};
  for (int i = 0; i < 3; i++)
    getNumberDec(n[i], p);
  int c = 0;
  getNumberHex(c, p);
  DRAW9486::LineH(n[0], n[1], n[2], c);
}

void drawVline(const char *p, size_t sz)
{
  if (sz != 14)
    return;

  int n[3] = {0, 0, 0};
  for (int i = 0; i < 3; i++)
    getNumberDec(n[i], p);
  int c = 0;
  getNumberHex(c, p);
  DRAW9486::LineV(n[0], n[1], n[2], c);
}

//
//
//
void setup()
{
  Serial.begin(115200);
  DRAW9486::LCD_init();
  DRAW9486::LCD_clear();
  DRAW9486::print("Hello,World", 0, 0);
  Serial.print("#Screen:480,320#");
  Serial.flush();
}

//
//
//
void loop()
{
  if (Serial.available())
  {
    char buff[64];
    auto sz = Serial.readBytesUntil('\n', buff, sizeof(buff));
    switch (buff[0])
    {
    case '#':
      buff[sz] = '\0';
      printString(buff + 1, sz);
      break;
    case '!':
      drawRect(buff + 1, sz);
      break;
    case '$':
      drawFill(buff + 1, sz);
      break;
    case '-':
      drawHline(buff + 1, sz);
      break;
    case '|':
      drawVline(buff + 1, sz);
      break;
    }
    Serial.print("#Complete#");
    Serial.flush();
  }

  delay(20);
}
