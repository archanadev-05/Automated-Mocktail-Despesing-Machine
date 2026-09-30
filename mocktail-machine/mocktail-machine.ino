#include <Keypad.h>

// ----------------------
// Keypad Setup
// ----------------------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ----------------------
// Motor Pins
// ----------------------

// Motor 1
const int M1_IN1 = 22;
const int M1_IN2 = 23;

// Motor 2
const int M2_IN1 = 24;
const int M2_IN2 = 25;

// Motor 3
const int M3_IN1 = 26;
const int M3_IN2 = 27;

// Motor 4
const int M4_IN1 = 28;
const int M4_IN2 = 29;

// Motor 5
const int M5_IN1 = 30;
const int M5_IN2 = 31;

// Motor 6
const int M6_IN1 = 32;
const int M6_IN2 = 33;

// Rotation Times (milliseconds)
unsigned long motorTime[6] = {
  2000,   // Motor 1
  3000,   // Motor 2
  5000,   // Motor 3
  1000,   // Motor 4
  4000,   // Motor 5
  6000    // Motor 6
};

void setup() {
  Serial.begin(9600);

  for(int i=22;i<=33;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }

  Serial.println("Press 1-6");
}

void loop() {

  char key = keypad.getKey();

  if(key){

    Serial.print("Key Pressed: ");
    Serial.println(key);

    switch(key){

      case '1':
        runMotor(M1_IN1, M1_IN2, motorTime[0]);
        break;

      case '2':
        runMotor(M2_IN1, M2_IN2, motorTime[1]);
        break;

      case '3':
        runMotor(M3_IN1, M3_IN2, motorTime[2]);
        break;

      case '4':
        runMotor(M4_IN1, M4_IN2, motorTime[3]);
        break;

      case '5':
        runMotor(M5_IN1, M5_IN2, motorTime[4]);
        break;

      case '6':
        runMotor(M6_IN1, M6_IN2, motorTime[5]);
        break;

      default:
        Serial.println("No motor assigned.");
    }
  }
}

// ----------------------
// Motor Function
// ----------------------
void runMotor(int in1, int in2, unsigned long runtime){

  // Forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  delay(runtime);

  // Stop
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  Serial.println("Motor Finished");
}