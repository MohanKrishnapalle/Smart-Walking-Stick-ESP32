#include <TinyGPS++.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "BluetoothSerial.h"

// -------- OBJECTS --------
BluetoothSerial SerialBT;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);

// -------- WiFi --------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// -------- PINS --------
#define buttonPin 4
#define SOIL_SENSOR 34
#define buzzer 27

#define trigFront 19
#define echoFront 21
#define trigLeft 5
#define echoLeft 18
#define trigRight 25
#define echoRight 26
#define trigDown 22
#define echoDown 23

long duration;

// -------- VARIABLES --------
float latitude = 0.0, longitude = 0.0;
bool sent = false;

// -------- DISTANCE FUNCTION --------
int getDistance(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 20000);
  return duration * 0.034 / 2;
}

// -------- EMERGENCY FUNCTION --------
void sendEmergency() {

  Serial.println("Emergency button is pressed");

  SerialBT.end();
  delay(300);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  client.setInsecure();

  unsigned long start = millis();
  while (millis() - start < 3000) {
    while (gpsSerial.available()) {
      gps.encode(gpsSerial.read());
    }
  }

  if (gps.location.isValid()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }

  char msg[150];
  snprintf(msg, sizeof(msg),
           "EMERGENCY\nhttps://maps.google.com/?q=%.6f,%.6f",
           latitude, longitude);

  delay(500);

  bool success = bot.sendMessage(CHAT_ID, msg, "");

  if (success) {
    Serial.println("Message successfully sent to Telegram bot");
  } else {
    Serial.println("Message sending failed");
  }

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  SerialBT.begin("SMART_STICK");
}

// -------- SETUP --------
void setup() {

  Serial.begin(115200);

  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(SOIL_SENSOR, INPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
  pinMode(trigLeft, OUTPUT);  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT); pinMode(echoRight, INPUT);
  pinMode(trigDown, OUTPUT);  pinMode(echoDown, INPUT);

  SerialBT.begin("SMART_STICK");

  WiFi.mode(WIFI_OFF);
}

// -------- LOOP --------
void loop() {

  // -------- BUTTON --------
  if (digitalRead(buttonPin) == LOW && !sent) {
    sent = true;
    SerialBT.println("Emergency button is pressed");
    delay(200);
    sendEmergency();
  }

  if (digitalRead(buttonPin) == HIGH) {
    sent = false;
  }

  // -------- NORMAL MODE --------
  int soil = analogRead(SOIL_SENSOR);

  int front = getDistance(trigFront, echoFront);
  int left  = getDistance(trigLeft, echoLeft);
  int right = getDistance(trigRight, echoRight);
  int down  = getDistance(trigDown, echoDown);

  // -------- WATER --------
  if (soil < 3500) {
    Serial.println("Water detected");
    SerialBT.println("Water detected");

    tone(buzzer, 2000);
    delay(300);
    noTone(buzzer);
  }

  // -------- HOLE (DOWN SENSOR) --------
  if (down > 0 && down < 25) {
    Serial.println("Hole detected");
    SerialBT.println("Hole detected");

    for(int i=0; i<3; i++){
      tone(buzzer, 2000);
      delay(100);
      noTone(buzzer);
      delay(100);
    }
    delay(200);
    return;
  }

  // -------- OBSTACLE DETECTION --------
  char msg[200] = "";
  int minDist = 1000;
  bool first = true;

  if(front > 0 && front <= 30){
    Serial.println("Front obstacle detected");

    if(!first) strcat(msg, " and ");
    sprintf(msg + strlen(msg), "Obstacle is detected at front %d cm", front);

    minDist = min(minDist, front);
    first = false;
  }

  if(left > 0 && left <= 30){
    Serial.println("Left obstacle detected");

    if(!first) strcat(msg, " and ");
    sprintf(msg + strlen(msg), "Obstacle is detected at left %d cm", left);

    minDist = min(minDist, left);
    first = false;
  }

  if(right > 0 && right <= 30){
    Serial.println("Right obstacle detected");

    if(!first) strcat(msg, " and ");
    sprintf(msg + strlen(msg), "Obstacle is detected at right %d cm", right);

    minDist = min(minDist, right);
    first = false;
  }

  if(strlen(msg) > 0){

    SerialBT.println(msg);

    // -------- BUZZER (ONLY FRONT, LEFT, RIGHT) --------
    if(minDist >= 20){
      tone(buzzer, 1200);
      delay(150);
      noTone(buzzer);
    }
    else if(minDist >= 10){
      tone(buzzer, 1800);
      delay(120);
      noTone(buzzer);
    }
    else{
      for(int i=0; i<3; i++){
        tone(buzzer, 2000);
        delay(80);
        noTone(buzzer);
        delay(80);
      }
    }
  } 
  else {
    noTone(buzzer);
  }

  delay(50);
}