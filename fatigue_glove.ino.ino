#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
//  TELEGRAM BOT CREDENTIALS
const char* ssid = "Redmi 12 5G";
const char* password = "12345678";

String botToken = "8710132465:AAGzYJOKxHeFMHfKfHBMCCttuGbij0c3nmk";   
String chatID   = "8711708120";     

// Function to send a Telegram alert
void sendTelegramAlert(String msg) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + botToken +
                 "/sendMessage?chat_id=" + chatID +
                 "&text=" + msg;
    http.begin(url);
    http.GET();
    http.end();
  }
}
//  SENSOR & FATIGUE SYSTEM
#define MPU_THUMB 0x68
#define MPU_WRIST 0x69
#define FSR_PIN 34

#define GRIP_THRESHOLD 200
#define THUMB_MOVEMENT_TH 20.0
#define WRIST_STATIC_TH 2.0

float prevThumbGyro = 0;
float prevWristGyro = 0;

float thumbVar = 0;
float wristVar = 0;

int fatigueScore = 0;
unsigned long usageStart = 0;

int16_t read16(uint8_t addr, uint8_t reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, 2);
  return (Wire.read() << 8) | Wire.read();
}

void wakeMPU(uint8_t addr) {
  Wire.beginTransmission(addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  // Wake sensors
  wakeMPU(MPU_THUMB);
  wakeMPU(MPU_WRIST);

  usageStart = millis();
  Serial.println("Fatigue Monitoring Started");
  //  CONNECT TO WIFI
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {

  // ===== Read FSR =====
  int gripValue = analogRead(FSR_PIN);
  bool highGrip = (gripValue > GRIP_THRESHOLD);

  // ===== Read Thumb MPU =====
  float thumbGyro = read16(MPU_THUMB, 0x45) / 131.0;
  thumbVar = 0.8 * thumbVar + 0.2 * abs(thumbGyro - prevThumbGyro);
  prevThumbGyro = thumbGyro;
  bool repetitiveThumb = (thumbVar > THUMB_MOVEMENT_TH);

  // ===== Read Wrist MPU =====
  float wristGyro = read16(MPU_WRIST, 0x45) / 131.0;
  wristVar = 0.8 * wristVar + 0.2 * abs(wristGyro - prevWristGyro);
  prevWristGyro = wristGyro;
  bool wristStatic = (wristVar < WRIST_STATIC_TH);

  // ===== Usage Time =====
  unsigned long usageMinutes = (millis() - usageStart) / 60000;

  // ===== Fatigue Score Calculation =====
  fatigueScore = 0;

  if (highGrip) fatigueScore += 30;
  if (repetitiveThumb) fatigueScore += 30;
  if (wristStatic) fatigueScore += 20;
  if (usageMinutes > 5) fatigueScore += 20;

  // ===== Print Data =====
  Serial.print("Grip: "); Serial.print(gripValue);
  Serial.print(" | ThumbVar: "); Serial.print(thumbVar, 1);
  Serial.print(" | WristVar: "); Serial.print(wristVar, 1);
  Serial.print(" | Score: "); Serial.print(fatigueScore);

  // ===== Alert with Telegram Notification =====
  if (fatigueScore >= 50) {
    Serial.println("  ⚠ FATIGUE ALERT - Relax Grip / Move Wrist / Take Break");

    //  SEND TELEGRAM MESSAGE
    sendTelegramAlert("⚠ FATIGUE ALERT! Relax your grip / Move your wrist / Take a short break.");

  } else {
    Serial.println("  OK");
  }

  delay(200);
}