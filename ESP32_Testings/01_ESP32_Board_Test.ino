// ESP32 Board Test

#define LED_PIN 2

void setup() {
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);

    Serial.println();
    Serial.println("ESP32 Board Test Started");
}

void loop() {
    digitalWrite(LED_PIN, HIGH);

    Serial.println("ESP32 is working - LED ON");
    delay(1000);

    digitalWrite(LED_PIN, LOW);

    Serial.println("ESP32 is working - LED OFF");
    delay(1000);
}