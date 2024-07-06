#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN        27   // Chân IO để kết nối với dãy LED
#define NUM_LEDS       64   // Số lượng LED trong dãy
#define MATRIX_WIDTH   8    // Chiều rộng của ma trận LED
#define MATRIX_HEIGHT  8    // Chiều cao của ma trận LED
#define BRIGHTNESS     51   // Độ sáng giảm xuống 20%

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS); // Đặt độ sáng giảm xuống 20%
  Serial.begin(115200);
  randomSeed(analogRead(0)); // Khởi tạo random seed
}

void loop() {
  // Dịch chuyển tất cả các LED xuống một hàng
  for (int y = MATRIX_HEIGHT - 1; y > 0; y--) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      leds[y * MATRIX_WIDTH + x] = leds[(y - 1) * MATRIX_WIDTH + x];
    }
  }

  // Tạo LED ngẫu nhiên ở hàng trên cùng
  for (int x = 0; x < MATRIX_WIDTH; x++) {
    if (random(10) < 2) { // Tỷ lệ ngẫu nhiên tạo ra LED (có thể điều chỉnh)
      leds[x] = CRGB(random(256), random(256), random(256));
    } else {
      leds[x] = CRGB::Black;
    }
  }

  FastLED.show();
  delay(100); // Điều chỉnh tốc độ mưa rơi
}
