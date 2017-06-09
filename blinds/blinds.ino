/*
  Open and close blinds based on specific time fetched from nrp
 */
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Motor config
#define DISTANCE            3200
#define MOTOR_PIN_STEP      D3
#define MOTOR_PIN_DIRECTION D4
#define BUTTON_PIN          D5

// Specify times
String open_blinds_time = "07:00:00";
String close_blinds_time = "19:00:00";

// WiFi parameters
const char* ssid = "MSI";
const char* password = "ursus2000";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.europe.pool.ntp.org", 7200, 86400);

int is_blind_open = true;
int step_counter = 0;
int stepping = false;

void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_PIN_STEP, OUTPUT);     
  pinMode(MOTOR_PIN_DIRECTION, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  digitalWrite(MOTOR_PIN_STEP, LOW);
  digitalWrite(MOTOR_PIN_DIRECTION, LOW);
  digitalWrite(BUTTON_PIN, LOW);
  
  
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());

  if (
      (
        (open_blinds_time == timeClient.getFormattedTime() && is_blind_open == false) 
        || 
        (close_blinds_time == timeClient.getFormattedTime() && is_blind_open == true) 
        || 
        digitalRead(BUTTON_PIN) == LOW
      )
      &&
      stepping == false
     ) {
    stepping = true;
  }

  if (is_blind_open == true) {
    digitalWrite(MOTOR_PIN_DIRECTION, HIGH);
  } else {
    digitalWrite(MOTOR_PIN_DIRECTION, LOW);
  }

  if (stepping == true) {
    step(1000);

    step_counter = step_counter + 1;

    if (step_counter == DISTANCE)
    {
      step_counter = 0;
      stepping = false;
      is_blind_open = !is_blind_open;
    }
  }
}

void step(long stepDelay) {
  digitalWrite(MOTOR_PIN_STEP, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(MOTOR_PIN_STEP, LOW);
  delayMicroseconds(stepDelay);
}

