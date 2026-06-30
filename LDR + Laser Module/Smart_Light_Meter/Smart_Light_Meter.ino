#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create OLED object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// LDR Pin
const int ldrPin = A0;

int ldrValue = 0;

void setup() {

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (true);
  }

  display.clearDisplay();
}

void loop() {

  // Read LDR
  ldrValue = analogRead(ldrPin);

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.println("eARgle Labs");

  display.setCursor(0,20);
  display.print("LDR : ");
  display.println(ldrValue);

  display.setCursor(0,45);
  display.print("Status : ");

  // Light Status
  if (ldrValue > 700) {
    display.println("Bright");
  }
  else if (ldrValue > 300) {
    display.println("Normal");
  }
  else {
    display.println("Dark");
  }

  display.display();

  delay(200);
}