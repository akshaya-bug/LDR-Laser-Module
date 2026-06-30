#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int ldrPin = A0;
const int ledPin = 8;

const int threshold = 600;

void setup() {

  pinMode(ledPin, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  int ldrValue = analogRead(ldrPin);

  int signal = map(ldrValue, 0, 1023, 0, 100);
  signal = constrain(signal, 0, 100);

  bool beamDetected = (ldrValue > threshold);

  digitalWrite(ledPin, beamDetected);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 0);
  display.println("Beam");

  display.setTextSize(1);
  display.setCursor(0, 24);
  display.println("Status");

  display.setTextSize(2);
  display.setCursor(0, 38);

  if (beamDetected)
    display.println("DETECTED");
  else
    display.println("LOST!");

  display.setTextSize(1);
  display.setCursor(0, 56);
  display.print("Signal: ");
  display.print(signal);
  display.print("%");

  display.display();

  delay(100);
}