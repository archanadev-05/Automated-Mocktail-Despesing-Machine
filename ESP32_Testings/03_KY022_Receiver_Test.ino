// KY-022 IR Receiver Test
// ESP32 + Arduino-IRremote 4.x

#include <IRremote.hpp>

#define IR_RX_PIN 4

void setup() {
    Serial.begin(115200);

    IrReceiver.begin(IR_RX_PIN, DISABLE_LED_FEEDBACK);

    Serial.println("KY-022 Receiver Test Started");
    Serial.println("Waiting for an IR signal...");
}

void loop() {
    if (IrReceiver.decode()) {

        Serial.println("IR signal received!");

        IrReceiver.printIRResultShort(&Serial);

        IrReceiver.resume();
    }
}