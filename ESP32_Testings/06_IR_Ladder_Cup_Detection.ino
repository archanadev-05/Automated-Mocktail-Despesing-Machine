// Three-Level IR Ladder Cup Detection


#define IR_SENSOR_1 4
#define IR_SENSOR_2 16
#define IR_SENSOR_3 18

// Change this after measuring the actual receiver outputs.
// LOW: a blocked beam produces LOW.
// HIGH: a blocked beam produces HIGH.
#define BLOCKED_LEVEL LOW

struct IRLadder {
    bool level1;
    bool level2;
    bool level3;
};

IRLadder readIRLadder() {
    IRLadder state;

    state.level1 =
        digitalRead(IR_SENSOR_1) == BLOCKED_LEVEL;

    state.level2 =
        digitalRead(IR_SENSOR_2) == BLOCKED_LEVEL;

    state.level3 =
        digitalRead(IR_SENSOR_3) == BLOCKED_LEVEL;

    return state;
}

void printCupState(const IRLadder &state) {
    Serial.print("Level 1: ");
    Serial.print(state.level1 ? "BLOCKED" : "CLEAR");

    Serial.print(" | Level 2: ");
    Serial.print(state.level2 ? "BLOCKED" : "CLEAR");

    Serial.print(" | Level 3: ");
    Serial.println(state.level3 ? "BLOCKED" : "CLEAR");

    if (!state.level1 &&
        !state.level2 &&
        !state.level3) {

        Serial.println("State: NO BEAMS BLOCKED");
    }
    else if (state.level1 &&
             !state.level2 &&
             !state.level3) {

        Serial.println("State: LEVEL 1");
    }
    else if (state.level1 &&
             state.level2 &&
             !state.level3) {

        Serial.println("State: LEVEL 1 + LEVEL 2");
    }
    else if (state.level1 &&
             state.level2 &&
             state.level3) {

        Serial.println("State: ALL THREE LEVELS");
    }
    else {
        Serial.println("State: OTHER SENSOR PATTERN");
    }

    Serial.println("-----------------------------");
}

void setup() {
    Serial.begin(115200);

    pinMode(IR_SENSOR_1, INPUT);
    pinMode(IR_SENSOR_2, INPUT);
    pinMode(IR_SENSOR_3, INPUT);

    Serial.println();
    Serial.println("IR Ladder Cup Detection Started");
    Serial.println("NodeMCU ESP-32S");
}

void loop() {
    IRLadder state = readIRLadder();

    printCupState(state);

    delay(300);
}