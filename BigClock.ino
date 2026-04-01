#include <LiquidCrystal.h>

#define BTN_H  2
#define BTN_M  3

// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

uint8_t LT[]  = {B00111,B01111,B11111,B11111,B11111,B11111,B11111,B11111};
uint8_t UB[]  = {B11111,B11111,B11111,B00000,B00000,B00000,B00000,B00000};
uint8_t RT[]  = {B11100,B11110,B11111,B11111,B11111,B11111,B11111,B11111};
uint8_t LL[]  = {B11111,B11111,B11111,B11111,B11111,B11111,B01111,B00111};
uint8_t LB[]  = {B00000,B00000,B00000,B00000,B00000,B11111,B11111,B11111};
uint8_t LR[]  = {B11111,B11111,B11111,B11111,B11111,B11111,B11110,B11100};
uint8_t UMB[] = {B11111,B11111,B11111,B00000,B00000,B00000,B11111,B11111};
uint8_t LMB[] = {B11111,B00000,B00000,B00000,B00000,B11111,B11111,B11111};

const uint8_t digits[10][6] = {
  {0,1,2, 3,4,5},    // 0
  {1,2,32, 32,5,32}, // 1
  {6,6,2, 3,7,7},    // 2
  {6,6,2, 7,7,5},    // 3
  {3,4,2, 32,32,5},  // 4
  {255,6,6, 7,7,5},  // 5
  {0,6,6, 3,7,5},    // 6
  {1,1,2, 32,0,32},  // 7
  {0,6,2, 3,7,5},    // 8
  {0,6,2, 32,32,5},  // 9
};

void writeDigit(int digit, int col) {
  lcd.setCursor(col, 0);
  lcd.write(digits[digit][0]);
  lcd.write(digits[digit][1]);
  lcd.write(digits[digit][2]);
  lcd.setCursor(col, 1);
  lcd.write(digits[digit][3]);
  lcd.write(digits[digit][4]);
  lcd.write(digits[digit][5]);
}

int h = 0, m = 0, s = 0;
unsigned long lastTick = 0;
bool colonOn = true;

void drawColon(bool visible) {
  lcd.setCursor(7, 0);
  lcd.write(visible ? (byte)165 : ' ');
  lcd.setCursor(7, 1);
  lcd.write(visible ? (byte)165 : ' ');
}

void drawClock() {
  writeDigit(h / 10, 0);
  writeDigit(h % 10, 4);
  drawColon(colonOn);
  writeDigit(m / 10, 8);
  writeDigit(m % 10, 12);
}

void setup() {
  pinMode(BTN_H, INPUT_PULLUP);
  pinMode(BTN_M, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.createChar(0, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
  lcd.clear();
  drawClock();
}

void loop() {
  if (digitalRead(BTN_H) == LOW) {
    h = (h + 1) % 24;
    s = 0; lastTick = millis();
    drawClock();
    delay(200);
  }
  if (digitalRead(BTN_M) == LOW) {
    m = (m + 1) % 60;
    s = 0; lastTick = millis();
    drawClock();
    delay(200);
  }
  if (millis() - lastTick >= 1000) {
    lastTick = millis();
    s++;
    if (s >= 60) { s = 0; m++; }
    if (m >= 60) { m = 0; h++; }
    if (h >= 24) { h = 0; }
    colonOn = !colonOn;
    drawClock();
  }
}
