
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Servo indicator;

const int buttonPin = 2;
const int greenLED = 7;
const int redLED = 8;
const int buzzer = 9;
const int servoPin = 10;

// Use 15 seconds for testing; change to 25 minutes later.
const unsigned long studyTime = 15000UL;

bool running = false;
bool finished = false;
unsigned long startTime = 0;
unsigned long lastUpdate = 0;

void showMessage(const char* a, const char* b) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 15);
  display.println(a);
  display.setCursor(0, 35);
  display.println(b);
  display.display();
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  indicator.attach(servoPin);
  indicator.write(0);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {}
  }

  showMessage("STUDY TIMER", "Press to start");
}

void loop() {
  static bool previousButton = HIGH;
  bool button = digitalRead(buttonPin);

  if (previousButton == HIGH && button == LOW) {
    if (finished) {
      finished = false;
      digitalWrite(redLED, LOW);
      noTone(buzzer);
      indicator.write(0);
      showMessage("STUDY TIMER", "Press to start");
    } else if (running) {
      running = false;
      digitalWrite(greenLED, LOW);
      showMessage("STUDY TIMER", "Paused");
    } else {
      running = true;
      startTime = millis();
      digitalWrite(greenLED, HIGH);
      showMessage("STUDY TIMER", "Session started");
    }
    delay(180);
  }
  previousButton = button;

  if (running && millis() - lastUpdate >= 200) {
    lastUpdate = millis();
    unsigned long elapsed = millis() - startTime;

    if (elapsed >= studyTime) {
      running = false;
      finished = true;
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      tone(buzzer, 1000, 700);
      indicator.write(90);
      showMessage("TIME IS UP!", "Great work!");
    } else {
      unsigned long remaining = (studyTime - elapsed) / 1000;
      display.clearDisplay();
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1);
      display.setCursor(0, 8);
      display.println("FOCUS SESSION");
      display.setTextSize(2);
      display.setCursor(10, 28);
      display.print(remaining / 60);
      display.print(":");
      if (remaining % 60 < 10) display.print("0");
      display.print(remaining % 60);
      display.display();
