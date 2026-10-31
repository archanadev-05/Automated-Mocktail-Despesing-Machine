// Three-Level IR Ladder Cup Detection

#define IR_SENSOR_1 4
#define IR_SENSOR_2 16
#define IR_SENSOR_3 18

// Change if your receiver outputs HIGH when blocked
#define BLOCKED_LEVEL LOW

struct IRLadder {
    bool level1;
    bool level2;
    bool level3;
};

IRLadder readIRLadder() {
    IRLadder state;

    state.level1 = (digitalRead(IR_SENSOR_1) == BLOCKED_LEVEL);
    state.level2 = (digitalRead(IR_SENSOR_2) == BLOCKED_LEVEL);
    state.level3 = (digitalRead(IR_SENSOR_3) == BLOCKED_LEVEL);

    return state;
}

void printCupState(const IRLadder &state) {

    Serial.print("Sensor 1: ");
    Serial.print(state.level1 ? "BLOCKED" : "CLEAR");

    Serial.print(" | Sensor 2: ");
    Serial.print(state.level2 ? "BLOCKED" : "CLEAR");

    Serial.print(" | Sensor 3: ");
    Serial.println(state.level3 ? "BLOCKED" : "CLEAR");

    if (state.level1 && !state.level2 && !state.level3) {

        Serial.println("First beam blocked");
        Serial.println("Small cup detected");

    }
    else if (state.level1 && state.level2 && !state.level3) {

        Serial.println("First and Second beams blocked");
        Serial.println("Medium cup detected");

    }
    else if (state.level1 && state.level2 && state.level3) {

        Serial.println("All three beams blocked");
        Serial.println("Large cup detected");

    }
    else if (!state.level1 && !state.level2 && !state.level3) {

        Serial.println("No cup detected");

    }
    else {

        Serial.println("Unknown sensor pattern");
    }

    Serial.println("----------------------------------");
}

void setup() {
    Serial.begin(115200);

    pinMode(IR_SENSOR_1, INPUT);
    pinMode(IR_SENSOR_2, INPUT);
    pinMode(IR_SENSOR_3, INPUT);

    Serial.println();
    Serial.println("IR Cup Detection Started");
}

void loop() {
    IRLadder state = readIRLadder();

    printCupState(state);

    delay(300);
}
