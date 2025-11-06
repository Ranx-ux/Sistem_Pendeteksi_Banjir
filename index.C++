#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === SENSOR ULTRASONIC ===
#define TRIG 26
#define ECHO 27
#define MAX_DISTANCE 400
NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

// === BUZZER ===
#define BUZZER_PIN 25

// === LED ===
#define LEDMERAH 14   
#define LEDHIJAU 12   

// === LCD I2C ===
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("I'M RANGGA");
  lcd.setCursor(0, 1);
  lcd.print("Loading...");
  delay(1500);
  lcd.clear();

  // Inisialisasi pin
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LEDMERAH, OUTPUT);
  pinMode(LEDHIJAU, OUTPUT);

  Serial.println("Sistem Monitoring Jarak Aktif");
}

void loop() {
  int jarak = sonar.ping_cm();

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak > 0 && jarak <= 200) {
    // Bahaya
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LEDMERAH, HIGH);
    digitalWrite(LEDHIJAU, LOW);
    Serial.println("Status: BAHAYA! -> LED MERAH ON, BUZZER ON");
  } 
  else if (jarak > 200) {
    // Aman
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LEDMERAH, LOW);
    digitalWrite(LEDHIJAU, HIGH);
    Serial.println("Status: AMAN -> LED HIJAU ON, BUZZER OFF");
  } 
  else {
    // Tidak terbaca
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LEDMERAH, LOW);
    digitalWrite(LEDHIJAU, LOW);
    Serial.println("Status: ERROR");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(jarak);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  if (jarak > 0 && jarak <= 200) {
    lcd.print("Status: BAHAYA!");
  } else if (jarak > 200) {
    lcd.print("Status: AMAN   ");
  } else {
    lcd.print("Status: ERROR  ");
  }

  delay(500);
}