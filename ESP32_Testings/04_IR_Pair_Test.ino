// Single KY-005 + KY-022 Pair Test

#define IR_TX_PIN 17
#define IR_RX_PIN 4
#include <IRremote.hpp>



unsigned long lastTransmission = 0;

const unsigned long TRANSMIT_INTERVAL = 100;

void setup() {
    Serial.begin(115200);

    IrReceiver.begin(
        IR_RX_PIN,
        DISABLE_LED_FEEDBACK
    );

    IrSender.begin(IR_TX_PIN);

    Serial.println();
    Serial.println("Single IR Pair Test Started");
    Serial.println("Testing transmitter and receiver.");
}

void loop() {
    // Transmit an IR message periodically.
    if (millis() - lastTransmission >= TRANSMIT_INTERVAL) {
        lastTransmission = millis();

        IrSender.sendNEC(0x00, 0x2C, 0);
    }

    // Check whether the receiver decodes a signal.
    if (IrReceiver.decode()) {
        Serial.println("IR signal detected!");

        IrReceiver.printIRResultShort(&Serial);

        IrReceiver.resume();
    }
}
