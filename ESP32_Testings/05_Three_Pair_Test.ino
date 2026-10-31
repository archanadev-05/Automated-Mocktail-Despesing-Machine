// Three-Pair IR Input Test

#define IR_SENSOR_1 4
#define IR_SENSOR_2 16
#define IR_SENSOR_3 18

void setup() {
    Serial.begin(115200);

    pinMode(IR_SENSOR_1, INPUT);
    pinMode(IR_SENSOR_2, INPUT);
    pinMode(IR_SENSOR_3, INPUT);

    Serial.println();
    Serial.println("Three-Pair IR Input Test Started");
    Serial.println("Reading the three receiver outputs.");
}

void loop() {
    int sensor1 = digitalRead(IR_SENSOR_1);
    int sensor2 = digitalRead(IR_SENSOR_2);
    int sensor3 = digitalRead(IR_SENSOR_3);

    Serial.print("IR 1: ");
    Serial.print(sensor1);

    Serial.print(" | IR 2: ");
    Serial.print(sensor2);

    Serial.print(" | IR 3: ");
    Serial.println(sensor3);

    delay(200);
}