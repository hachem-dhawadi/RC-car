#include <PS4Controller.h>

// Left side motors
#define IN1 12
#define IN2 13
#define ENA 25

// Right side motors
#define IN3 14
#define IN4 27
#define ENB 26

void setup() {
  Serial.begin(115200);
  PS4.begin("5c:61:99:9b:bb:b2"); 
  Serial.println("Waiting for PS4 controller...");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void setMotor(int in1, int in2, int en, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(en, speed);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(en, -speed);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, 0);
  }
}

void loop() {
  if (PS4.isConnected()) {
    int leftY = -PS4.LStickY();  // Invert for natural forward control
    int rightY = -PS4.RStickY();

    int leftSpeed = map(leftY, -128, 127, -255, 255);
    int rightSpeed = map(rightY, -128, 127, -255, 255);

    setMotor(IN1, IN2, ENA, leftSpeed);
    setMotor(IN3, IN4, ENB, rightSpeed);

    // Debug
    Serial.print("LeftSpeed: ");
    Serial.print(leftSpeed);
    Serial.print(" | RightSpeed: ");
    Serial.println(rightSpeed);
  }
}