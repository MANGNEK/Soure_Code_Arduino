#define RELAY_PIN  D3 // Chân điều khiển relay
#define BUTTON_PIN D4    // Chân kết nối với nút nhấn
#define DEBOUNCE_DELAY 50  // Thời gian trễ chống nhiễu

bool relayState = LOW;  // Trạng thái hiện tại của relay
bool lastButtonState = LOW; // Trạng thái cuối cùng của nút nhấn
bool currentButtonState = LOW; // Trạng thái hiện tại của nút nhấn
unsigned long lastDebounceTime = 0; // Thời gian cuối cùng trạng thái thay đổi

void setup() {
  pinMode(RELAY_PIN, OUTPUT);   // Thiết lập chân relay là ngõ ra
  pinMode(BUTTON_PIN, INPUT);   // Thiết lập chân nút nhấn là ngõ vào
  digitalWrite(RELAY_PIN, relayState); // Khởi tạo trạng thái ban đầu của relay
  Serial.begin(9600); // Thiết lập tốc độ truyền Serial
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);
  Serial.print("Data D4 : "); Serial.println(reading);

  // Kiểm tra xem trạng thái nút nhấn đã thay đổi chưa
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Nếu trạng thái nút nhấn ổn định trong một khoảng thời gian
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // Nếu trạng thái của nút nhấn đã thay đổi
    if (reading != currentButtonState) {
      currentButtonState = reading;

      // Nếu nút nhấn được nhấn (từ LOW sang HIGH)
      if (currentButtonState == HIGH) {
        relayState = !relayState; // Đảo trạng thái của relay
        if(relayState == LOW){
          Serial.println("Turn Off Relay");
        } else {
          Serial.println("Turn On Relay");
        }
        digitalWrite(RELAY_PIN, relayState);
      }
    }
  }

  lastButtonState = reading;
}
