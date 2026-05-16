

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BT(2, 3);

// Motor Pins
#define IN1 4
#define IN2 5
#define IN3 8
#define IN4 13

// Ultrasonic
#define F_TRIG 6
#define F_ECHO 7
#define L_TRIG 9
#define L_ECHO 10
#define R_TRIG 11
#define R_ECHO 12

// Relays
#define PUMP A1
#define CLEAN A2

char command;
char mode = 'M';

bool pumpState = false;
bool cleanState = false;

// Distance Function
int getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  return duration * 0.034 / 2;
}

// Movement Functions
void forward() {
  lcd.setCursor(0,1);
  lcd.print("Forward       ");
  Serial.println("Move: FORWARD");

  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
}

void backward() {
  lcd.setCursor(0,1);
  lcd.print("Backward      ");
  Serial.println("Move: BACKWARD");

  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
}

void left() {
  lcd.setCursor(0,1);
  lcd.print("Left          ");
  Serial.println("Move: LEFT");

  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
}

void right() {
  lcd.setCursor(0,1);
  lcd.print("Right         ");
  Serial.println("Move: RIGHT");

  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
}

void stopRobot() {
  lcd.setCursor(0,1);
  lcd.print("Stop          ");
  Serial.println("Move: STOP");

  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,LOW);
}

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Floor Cleaner");
  lcd.setCursor(0,1);
  lcd.print("Connecting...");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
  BT.begin(9600);

  pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT); pinMode(IN4,OUTPUT);
++
  pinMode(F_TRIG,OUTPUT); pinMode(F_ECHO,INPUT);
  pinMode(L_TRIG,OUTPUT); pinMode(L_ECHO,INPUT);
  pinMode(R_TRIG,OUTPUT); pinMode(R_ECHO,INPUT);

  pinMode(PUMP, OUTPUT);
  pinMode(CLEAN, OUTPUT);

  stopRobot();
}

void loop() {

  // 🔹 Bluetooth Commands
  if (BT.available()) {
    command = BT.read();

    Serial.print("Received: ");
    Serial.println(command);

    // Mode Selection
    if (command == 'A') {
      mode = 'A';
      Serial.println("Mode: AUTO");
    }
    if (command == 'M') {
      mode = 'M';
      Serial.println("Mode: MANUAL");
    }

    // Pump Toggle
    if (command == 'P') {
      pumpState = !pumpState;
      digitalWrite(PUMP, pumpState);

      Serial.print("Pump: ");
      Serial.println(pumpState ? "ON" : "OFF");

      lcd.setCursor(0,1);
      lcd.print(pumpState ? "Pump ON       " : "Pump OFF      ");
      delay(500);
    }

    // Cleaning Toggle
    if (command == 'C') {
      cleanState = !cleanState;
      digitalWrite(CLEAN, cleanState);

      Serial.print("Cleaning: ");
      Serial.println(cleanState ? "ON" : "OFF");

      lcd.setCursor(0,1);
      lcd.print(cleanState ? "Clean ON      " : "Clean OFF     ");
      delay(500);
    }

    // Manual Control
    if (mode == 'M') {
      if (command == 'F') forward();
      else if (command == 'B') backward();
      else if (command == 'L') left();
      else if (command == 'R') right();
      else if (command == 'S') stopRobot();
    }
  }

  // 🔹 Display Mode
  lcd.setCursor(0,0);
  if (mode == 'M') lcd.print("Manual Mode   ");
  else lcd.print("Auto Mode     ");

  // 🔹 AUTO MODE
  if (mode == 'A') {

    int front = getDistance(F_TRIG, F_ECHO);
    int leftD = getDistance(L_TRIG, L_ECHO);
    int rightD = getDistance(R_TRIG, R_ECHO);

    Serial.print("F:"); Serial.print(front);
    Serial.print(" L:"); Serial.print(leftD);
    Serial.print(" R:"); Serial.println(rightD);

    if (front < 20) {
      Serial.println("Obstacle");

      stopRobot();
      delay(200);

      if (leftD > rightD) {
        Serial.println("Turning LEFT");
        left();
        delay(400);
      } else {
        Serial.println("Turning RIGHT");
        right();
        delay(400);
      }
    } 
    else {
      Serial.println("Forward");
      forward();
    }

    // Auto ON
    digitalWrite(PUMP, HIGH);
    digitalWrite(CLEAN, HIGH);
  }
}