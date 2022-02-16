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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  /*
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  */
}











