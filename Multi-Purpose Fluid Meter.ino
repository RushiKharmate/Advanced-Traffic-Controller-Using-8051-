#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

#define FLOW_SENSOR_PIN 2
#define SERVO_PIN 9
#define CS_PIN 10

Servo myservo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

volatile int pulseCount = 0;
float flowRate = 0.0;
float flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
unsigned long oldTime = 0;

File dataFile;

const unsigned long maxMilliLitres = 5000; // Set your desired maximum amount of water in milliliters

void setup() {
  lcd.begin(16, 2);
  lcd.print("Flow Meter");

  myservo.attach(SERVO_PIN);

  pinMode(FLOW_SENSOR_PIN, INPUT);
  digitalWrite(FLOW_SENSOR_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);

  if (!SD.begin(CS_PIN)) {
    lcd.setCursor(0, 1);
    lcd.print("SD Init Failed!");
    while (1);
  }

  dataFile = SD.open("flowData.txt", FILE_WRITE);
  if (!dataFile) {
    lcd.setCursor(0, 1);
    lcd.print("File Open Error!");
    while (1);
  }

  oldTime = millis();
  myservo.write(0); // Initialize servo to open position
}

void loop() {
  if ((millis() - oldTime) > 1000) {
    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN));

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / 7.5;
    oldTime = millis();

    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    lcd.clear();
    lcd.print("Flow: ");
    lcd.print(flowRate);
    lcd.print(" L/min");
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(totalMilliLitres);
    lcd.print(" mL");

    dataFile = SD.open("flowData.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.print("Flow Rate: ");
      dataFile.print(flowRate);
      dataFile.print(" L/min");
      dataFile.print(" Total: ");
      dataFile.print(totalMilliLitres);
      dataFile.println(" mL");
      dataFile.close();
    }

    // Control Servo Motor based on total amount of water passed
    if (totalMilliLitres >= maxMilliLitres) {
      myservo.write(90); // Turn servo to close position
    } else {
      myservo.write(0); // Keep servo in open position
    }

    pulseCount = 0;
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}
