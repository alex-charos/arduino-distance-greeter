/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 7 
 Trig to Arduino pin 8
 
 This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
 Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
 And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
 And even further notified by Alex here :https://github.com/alex-charos/arduino-distance-greeter
 */


#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED

int maximumRange = 2000; // Maximum range needed
int minimumRange = 0; // Minimum range needed

long getDistance(long duration) {
  //Calculate the distance (in cm) based on the speed of sound.
  return duration/58.2;
}

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}


void displayReading(long distance, long duration) {

  String message = getMessageByDistance(distance);
  
  Serial.print("{distanceInCms: '");
  Serial.print(distance);
  Serial.print("', durationInMicros :'");
  Serial.print(duration);
  Serial.print("', message:'");
  Serial.print(message);
  Serial.println("}");
  
}

String getMessageByDistance(long distance) {
  if (distance <10) {
    return "KISS ME!";
   }
   if (distance <50) {
    return "A little bit closer...";
   }
   
   if (distance <100) {
    return "Come closer...";
   }
   if (distance <200) {
    return "Hey! You! Come here!!!";
   }
   return "Where are you..?";
  
  
 }

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
    
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
   
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = getDistance(duration);
  
  displayReading(distance, duration);
  //Delay 50ms before next reading.
  delay(400);
}
