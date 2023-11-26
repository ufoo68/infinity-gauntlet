#include <M5StickCPlus.h>
#include <Audio.h>

#define ANALOG_PIN 33   // アナログセンサーのピン番号
#define LED_PIN 32      // LEDのデジタルピン番号
#define THRESHOLD 700   // 閾値

// 関数の宣言
void drawMeter(int value);

void setup() {
  M5.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // アナログセンサーの値を取得
  int sensorValue = analogRead(ANALOG_PIN);

  // メーター表示
  drawMeter(sensorValue);

  // LEDの制御
  if (sensorValue > THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);  // 閾値を超えたらLED点灯
  } else {
    digitalWrite(LED_PIN, LOW);   // 閾値を下回ったらLED消灯
  }

  delay(100);
}

void drawMeter(int value) {
  M5.Lcd.fillScreen(TFT_BLACK);  // 背景を黒でクリア

  // メーターの描画
  M5.Lcd.drawRoundRect(60, 20, 20, 200, 5, TFT_WHITE);  // メーターの外側の枠

  // メーターの値に基づいて色を変更
  uint16_t color = TFT_GREEN;
  if (value < 300) {
    color = TFT_RED;
  } else if (value < 700) {
    color = TFT_YELLOW;
  }

  // メーターのバーを描画
  int barHeight = map(value, 0, 4095, 0, 200);
  M5.Lcd.fillRect(60, 220 - barHeight, 20, barHeight, color);

  // 数値を表示
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(5, 5);
  M5.Lcd.printf("%d", value);
}
