#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 8, 2);  // 8 columns, 2 rows

#define BUZZER  8   // buzzer on D8
#define RED     2  // RGB Red   on D9
#define GREEN   3  // RGB Green on D10
#define BLUE    4   // RGB Blue  on D6

// Common Cathode: HIGH = ON, LOW = OFF
void setRGB(bool r, bool g, bool b) {
  digitalWrite(RED,   r);
  digitalWrite(GREEN, g);
  digitalWrite(BLUE,  b);
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(BUZZER, OUTPUT);
  pinMode(RED,    OUTPUT);
  pinMode(GREEN,  OUTPUT);
  pinMode(BLUE,   OUTPUT);

  digitalWrite(BUZZER, LOW);
  setRGB(0, 0, 0);  // all off
}

void loop() {
  int value = analogRead(A0);

  // Row 0 — raw value
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(value);
  lcd.print("    ");

  // Row 1 — water level + RGB + buzzer
  lcd.setCursor(0, 1);
  if (value == 0) {
    lcd.print("EMPTY   ");
    setRGB(1, 0, 0);         // Red
    digitalWrite(BUZZER, LOW);
  } else if (value > 1 && value < 250) {
    lcd.print("LOW     ");
    setRGB(1, 0, 0);         // Red
    digitalWrite(BUZZER, LOW);
  } else if (value >= 350 && value < 520) {
    lcd.print("MEDIUM  ");
    setRGB(0, 0, 1);         // Blue
    digitalWrite(BUZZER, LOW);
  } else if (value >= 600) {
    lcd.print("HIGH    ");
    setRGB(0, 1, 0);         // Green
    digitalWrite(BUZZER, HIGH);  // beep!
  }

  Serial.println(value);
  delay(300);
}
