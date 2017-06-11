/*
  Open and close blinds based on specific time fetched from nrp
 */
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Motor config
#define DISTANCE            30000
#define MOTOR_PIN_STEP      D3
#define MOTOR_PIN_DIRECTION D4
#define MOTOR_PIN_SLEEP     D5
#define BUTTON_PIN          D7

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
  pinMode(MOTOR_PIN_SLEEP, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  digitalWrite(MOTOR_PIN_STEP, LOW);
  digitalWrite(MOTOR_PIN_DIRECTION, LOW);
  digitalWrite(MOTOR_PIN_SLEEP, LOW);
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

  if (((open_blinds_time == timeClient.getFormattedTime() && is_blind_open == false) || 
       (close_blinds_time == timeClient.getFormattedTime() && is_blind_open == true) || 
        digitalRead(BUTTON_PIN) == LOW))
  {
    // Wake up driver
    digitalWrite(MOTOR_PIN_SLEEP, HIGH);

    // Check direction
    if (is_blind_open == true)
    {
      digitalWrite(MOTOR_PIN_DIRECTION, HIGH);
    }
    else
    {
      digitalWrite(MOTOR_PIN_DIRECTION, LOW);
    }

    // Turn motor
    // TODO: Make non blocking
    while (step_counter != DISTANCE)
    {
      step(200);
      yield();
      step_counter = step_counter + 1;
    }

    // Reset and sleep
    is_blind_open = !is_blind_open;
    step_counter = 0;
    digitalWrite(MOTOR_PIN_SLEEP, LOW);
  }
}

void step(long stepDelay) {
  digitalWrite(MOTOR_PIN_STEP, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(MOTOR_PIN_STEP, LOW);
  delayMicroseconds(stepDelay);
}

