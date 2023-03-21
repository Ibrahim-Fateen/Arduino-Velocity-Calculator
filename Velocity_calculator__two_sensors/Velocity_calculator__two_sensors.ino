#include <NewPing.h>

#define echo1Pin 2 
#define trig1Pin 3
#define echo2Pin 13
#define trig2Pin 10
#define led1 5
#define led2 6
#define dist_bet_sensors 11.8 // cm
#define maxDistance 15

NewPing sonar1(trig1Pin, echo1Pin, maxDistance);
NewPing sonar2(trig2Pin, echo2Pin, maxDistance);

double duration1;
double duration2;
double velocity;
double distance1;
double distance2;
double time1;
double time2;
bool condition;


void setup()
{
  Serial.begin(9600); 
  pinMode(trig1Pin,OUTPUT);
  pinMode(echo1Pin,INPUT); 
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop(){
  distance1 = sonar1.ping_cm();
  if (distance1 <= 10 && distance1 != 0) {
    
    time1 = millis();
    digitalWrite(led1, HIGH);

    duration2 = 0;
    while(duration2 > 583.09 || duration2 == 0) {
      digitalWrite(trig2Pin, LOW);
      delayMicroseconds(2);
      digitalWrite(trig2Pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig2Pin, LOW);
      duration2 = pulseIn(echo2Pin, HIGH);
    }
    distance2 = 0.0343 * duration2 / 2;
    
    if (distance2 <= 10 && distance2 != 0) {
      digitalWrite(led2, HIGH);
      time2 = millis();
      
      velocity = dist_bet_sensors / abs(time1 - time2) * 1000;
      condition = true;
    }
  }
  if (condition) {
    Serial.print("velocity = ");
    Serial.print(velocity);
    Serial.println(" cm/s");

    delay(10000);
  }
  condition = false;
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  distance1 = 0;
  distance2 = 0;
  time1 = 0;
  time2 = 0;
  delay(100);
}
