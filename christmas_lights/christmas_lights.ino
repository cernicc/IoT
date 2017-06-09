#include <Arduino.h>
#include <ESP8266TrueRandom.h>

const int buttonPin = 1;
const int myPins[] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3};

void wave(int delayBetween)
{
  for (int j = 0; j < (sizeof(myPins) / sizeof(myPins[0])); j++)
  {
    digitalWrite(myPins[j], HIGH);
    delay(delayBetween);
  }
  for (int j = (sizeof(myPins) / sizeof(myPins[0])) - 1; j > 0; j--)
  {
    digitalWrite(myPins[j], LOW);
    delay(delayBetween);
  }
}

void random(int delayBetween) {
  int j = 0;
  while (j < 500)
  {
    digitalWrite(myPins[ESP8266TrueRandom.random(sizeof(myPins))], HIGH);
    delay(delayBetween);
    digitalWrite(myPins[ESP8266TrueRandom.random(sizeof(myPins))], LOW);
    delay(delayBetween);

    j++;
  }
}

void flash(int delayBetween)
{
  for (int k = 0; k <= 1; k++)
  {
    for (int j = 0;j < (sizeof(myPins) / sizeof(myPins[0])); j++)
      digitalWrite(myPins[j], HIGH);
    delay(delayBetween);
    for (int j = 0;j < (sizeof(myPins) / sizeof(myPins[0])); j++)
      digitalWrite(myPins[j], LOW);
    delay(delayBetween);
  }
}

//----- Setup function. ------------------------
void setup()
{
  pinMode(buttonPin, INPUT);

  for (int i = 0; i < sizeof(myPins); i++) {
    pinMode(myPins[i], OUTPUT);
  }
}

//----- Loop routine. --------------------------
void loop()
{
  wave(100);
  flash(200);
  random(5);
  flash(200);
}

