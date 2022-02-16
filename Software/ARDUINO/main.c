// HC-SR04 trig pin
// 10us high

#define echoPin_L 14 // attach pin D14 Arduino to pin Echo_L of HC-SR04
#define trigPin_L 15 //attach pin D15 Arduino to pin Trig_L of HC-SR04

#define echoPin_R 16 // attach pin D16 Arduino to pin Echo_R of HC-SR04
#define trigPin_R 17 //attach pin D17 Arduino to pin Trig_R of HC-SR04

long duration_L; // variable for the duration of sound wave travel
int distance_L; // variable for the distance measurement

long duration_R; // variable for the duration of sound wave travel
int distance_R; // variable for the distance measurement

void setup ()
{
  pinMode(trigPin_L, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin_L, INPUT); // Sets the echoPin as an INPUT
  
  pinMode(trigPin_R, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin_R, INPUT); // Sets the echoPin as an INPUT
  /*
  Serial.begin(115200); // // Serial Communication is starting with 115200 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("ARDUINO NANO");
  */
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_L = pulseIn(echoPin_L, HIGH);
  // Calculating the distance
  // distance_L = duration_L * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  distance_L = (duration_L * ( (34 / 1000) / 2) ); // Speed of sound wave divided by 2 (go and back)
  
  
  // Clears the trigPin condition
  digitalWrite(trigPin_R, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_R = pulseIn(echoPin_R, HIGH);
  // Calculating the distance
  // distance_L = duration_L * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // distance = (duration-10) * 0.034 / 2 // maybe more clear
  distance_R = (duration_R * ( (34 / 1000) / 2) ); // Speed of sound wave divided by 2 (go and back)  
  if( (distance_R < 50) |
      (distance_L < 50) )
  {
    if(distance_L < distance_R)
    {
      motor_L_faster();
      motor_R_slower();
    }
  
    if(distance_R < distance_L)
    {
      motor_R_faster();
      motor_L_slower();
    }
  }
  /*
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  */
}











