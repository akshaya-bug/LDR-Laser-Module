#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int laserPin = 8;
const int buttonPin = 2;

bool laserState = LOW;
bool buttonState;
bool lastButtonState = HIGH;

int switchCount = 0;

void setup() {
  pinMode(laserPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(laserPin, LOW);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {

  buttonState = digitalRead(buttonPin);

  // Toggle only once per press
  if (lastButtonState == HIGH && buttonState == LOW) {

    laserState = !laserState;
    digitalWrite(laserPin, laserState);

    switchCount++;

    updateDisplay();

    delay(250);   // Debounce
  }

  lastButtonState = buttonState;
}

void updateDisplay() {

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println("Laser");

  display.setTextSize(1);

  display.setCursor(0, 28);
  display.print("Status : ");
  if (laserState)
    display.println("ON");
  else
    display.println("OFF");

  display.setCursor(0, 48);
  display.print("Count  : ");
  if (switchCount < 10)
    display.print("0");
  display.println(switchCount);

  display.display();
}