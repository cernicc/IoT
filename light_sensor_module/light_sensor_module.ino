#define ANALOG_SENSOR_PIN  A0 

#define LEDR1 D0
#define LEDR2 D1
#define LEDR3 D2
#define LEDY1 D3
#define LEDY2 D4
#define LEDY3 D5
#define LEDG1 D6
#define LEDG2 D7
#define LEDG3 D9

int  LightAnalogValue;
int range = 114; // 1024 max value

void setup() 
{
  Serial.begin(9600);  
  
  pinMode(LEDR1, OUTPUT);
  pinMode(LEDR2, OUTPUT);
  pinMode(LEDR3, OUTPUT);
  pinMode(LEDY1, OUTPUT);
  pinMode(LEDY2, OUTPUT);
  pinMode(LEDY3, OUTPUT);
  pinMode(LEDG1, OUTPUT);
  pinMode(LEDG2, OUTPUT);
  pinMode(LEDG3, OUTPUT);
}

void loop()   
{
  LightAnalogValue = analogRead(ANALOG_SENSOR_PIN);

  if (LightAnalogValue >= range*8)
  {
    digitalWrite(LEDR1, HIGH);
  }
  if (LightAnalogValue >= range*7)
  {
    digitalWrite(LEDR2, HIGH);
  }
  if (LightAnalogValue >= range*6)
  {
    digitalWrite(LEDR3, HIGH);
  }
  if (LightAnalogValue >= range*5)
  {
    digitalWrite(LEDY1, HIGH);
  }
  if (LightAnalogValue >= range*4)
  {
    digitalWrite(LEDY2, HIGH);
  }
  if (LightAnalogValue >= range*3)
  {
    digitalWrite(LEDY3, HIGH);
  }
  if (LightAnalogValue >= range*2)
  {
    digitalWrite(LEDG1, HIGH);
  }
  if (LightAnalogValue >= range)
  {
    digitalWrite(LEDG2, HIGH);
  }
  if (LightAnalogValue >= 0)
  {
    digitalWrite(LEDG3, HIGH);
  }

    digitalWrite(LEDG3, HIGH);
  off_all();
}

void off_all() {
  digitalWrite(LEDR1, LOW);
  digitalWrite(LEDR2, LOW);
  digitalWrite(LEDR3, LOW);
  digitalWrite(LEDY1, LOW);
  digitalWrite(LEDY2, LOW);
  digitalWrite(LEDY3, LOW);
  digitalWrite(LEDG1, LOW);
  digitalWrite(LEDG2, LOW);
  digitalWrite(LEDG3, LOW);
}

