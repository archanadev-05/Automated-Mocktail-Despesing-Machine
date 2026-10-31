// KY-005 IR Transmitter Test
// ESP32 + Arduino-IRremote 4.x

#include <IRremote.hpp>

#define IR_TX_PIN 17

void setup() {
    Serial.begin(115200);

    IrSender.begin(IR_TX_PIN);

    Serial.println("KY-005 Transmitter Test Started");
}

void loop() {
    Serial.println("Transmitting IR signal...");

    IrSender.sendNEC(0x00, 0x2C, 0);

    delay(2000);
}