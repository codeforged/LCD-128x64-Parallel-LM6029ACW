#include <Adafruit_GFX.h>
#include <LM6029ACW.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>

#define ser Serial

//            CS1 RES RS WR RD DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// LM6029ACW lcd(26, 28, 30, 32, 34, 50, 48, 46, 44, 42, 40, 38, 36);
LM6029ACW lcd(
  PB0,  // CS
  PB1,  // RES
  PB2,  // RS
  PB10, // WR
  PB11, // RD
  PA7,  // DB7
  PA6,  // DB6
  PA5,  // DB5
  PA4,  // DB4
  PA3,  // DB3
  PA2,  // DB2
  PA1,  // DB1
  PA0   // DB0
);

#define backLitePin 7
#define vddPin 52

LM6029ACW_GFX gfx(lcd);

void setup() {
  ser.begin(115200);
  while (!ser);
  ser.print(rand()*1000);
  ser.print(" Bismillah ");
  ser.println(HIGH);

  pinMode(backLitePin, OUTPUT);
  analogWrite(backLitePin, 60);
  pinMode(vddPin, OUTPUT);
  digitalWrite(vddPin, 1);  
  lcd.initLCDM();
  lcd.setContrast(29); // Set contrast level
  gfx.setFont(&FreeSerif9pt7b);
}

// (Silakan ganti dengan bitmap asli jika ada, ini hanya placeholder kosong)

// Logo Adafruit GFX 16x16 px (sudah tersedia di Adafruit_GFX, namanya adafruitlogo_bmp)
const unsigned char PROGMEM adafruit_logo16 [] = {
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00001111, 0b11100000,
  0b00011111, 0b11110000,
  0b00111111, 0b11111000,
  0b01111111, 0b11111100,
  0b01111111, 0b11111100,
  0b01111111, 0b11111100,
  0b01111111, 0b11111100,
  0b00111111, 0b11111000,
  0b00011111, 0b11110000,
  0b00001111, 0b11100000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000
};

#define USE_PAGING 0// 1 = paging, 0 = full update

static uint8_t page = 0;
static bool frameReady = true;

void loop() {
  static uint32_t lastFpsMillis = 0, frameCount = 0, fps = 0;
  static int x = 0, dx = 2;

#if USE_PAGING
  // Paging: update semua page sekaligus dalam 1 loop (fair comparison)
  // Render frame baru ke buffer
  gfx.fillScreen(0);
  // Animasi lebih kompleks
  gfx.drawCircle(x, 32, 10, 1);
  gfx.drawRect(x, 20, 20, 30, 1);
  gfx.drawLine(x, 0, 127 - x, 63, 1);
  gfx.drawLine(0, x, 127, 63 - x, 1);
  for (int i = 0; i < 8; i++) {
    gfx.drawRect(10 + i * 10, 10 + i, 20, 10, 1);
    gfx.drawCircle(64, 32, 5 + i, 1);
  }
  // Tampilkan logo Adafruit di pojok kiri atas
  gfx.drawBitmap(0, 0, adafruit_logo16, 16, 16, 1);
  // Tampilkan logo STM32 di tengah
  // gfx.drawBitmap(32, 0, stm32_logo, 64, 32, 1);
  // Teks bergerak
  int textX = (x) % 128 - 20;
  // gfx.setFont(&FreeMonoBold12pt7b);
  gfx.setFont(&FreeSans9pt7b);
  gfx.setCursor(textX, 60);
  gfx.print("Test");
  char fpsStr[16];
  sprintf(fpsStr, "%2dfps P", fps); // P = paging
  gfx.setFont();
  gfx.setCursor(80, 0);
  gfx.setTextColor(1);
  gfx.setTextSize(1);
  gfx.print(fpsStr);
  // Update semua page sekaligus
  for (uint8_t p = 0; p < 8; p++) {
    lcd.updatePage(p);
  }
  x += dx;
  if (x > 118) dx = -dx;
  if (x < 10) dx = 2;
  frameCount++;
  if (millis() - lastFpsMillis >= 1000) {
    fps = frameCount;
    frameCount = 0;
    lastFpsMillis = millis();
  }
  delay(15);
#else
  // Cara biasa: update full buffer setiap frame
  gfx.fillScreen(0);
  // Animasi lebih kompleks
  gfx.drawCircle(x, 32, 10, 1);
  gfx.drawRect(x, 20, 20, 30, 1);
  gfx.drawLine(x, 0, 127 - x, 63, 1);
  gfx.drawLine(0, x, 127, 63 - x, 1);
  for (int i = 0; i < 8; i++) {
    gfx.drawRect(10 + i * 10, 10 + i, 20, 10, 1);
    gfx.drawCircle(64, 32, 5 + i, 1);
  }
  gfx.drawBitmap(0, 0, adafruit_logo16, 16, 16, 1);
  // gfx.drawBitmap(32, 0, stm32_logo, 64, 32, 1);
  int textX = (x) % 128 - 20;
  gfx.setFont(&FreeMonoBold12pt7b);
  gfx.setCursor(textX, 60);
  gfx.print("Test");
  char fpsStr[16];
  sprintf(fpsStr, "%2dfps F", fps); // F = full
  gfx.setFont();
  gfx.setCursor(80, 0);
  gfx.setTextColor(1);
  gfx.setTextSize(1);
  gfx.print(fpsStr);
  gfx.display();
  x += dx;
  if (x > 118) dx = -dx;
  if (x < 10) dx = 2;
  frameCount++;
  if (millis() - lastFpsMillis >= 1000) {
    fps = frameCount;
    frameCount = 0;
    lastFpsMillis = millis();
  }
  delay(15);
#endif
}