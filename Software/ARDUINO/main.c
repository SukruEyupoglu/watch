// HC-SR04 trig pin
// 10us high

#define echoPin_L 14 // attach pin D14 Arduino to pin Echo_L of HC-SR04
#define trigPin_L 15 //attach pin D15 Arduino to pin Trig_L of HC-SR04
#define echoPin_R 16 // attach pin D16 Arduino to pin Echo_R of HC-SR04
#define trigPin_R 17 //attach pin D17 Arduino to pin Trig_R of HC-SR04
#define In_1 10 // attach pin D10 Arduino to pin In_1 of DRV8833
#define In_2 9 // attach pin D9 Arduino to pin In_2 of DRV8833
#define In_3 6 // attach pin D6 Arduino to pin In_3 of DRV8833
#define In_4 5 // attach pin D5 Arduino to pin In_4 of DRV8833
#define Fault 7 // attach pin D7 Arduino to pin Fault of DRV8833
#define Sleep 4 // attach pin D4 Arduino to pin Sleep of DRV8833
unsigned long duration_L = 0; // variable for the duration of sound wave travel
unsigned long duration_R = 0; // variable for the duration of sound wave travel
void motor_geri(unsigned char mtr_hz_L , unsigned char mtr_hz_R)
{
  analogWrite(In_1, mtr_hz_R); // max 255
  digitalWrite(In_2, LOW);
  analogWrite(In_3, mtr_hz_L); // max 255
  digitalWrite(In_4, LOW);
}
void motor_ileri(unsigned char mtr_hz_L , unsigned char mtr_hz_R)
{
  analogWrite(In_2, mtr_hz_R); // max 255
  digitalWrite(In_1, LOW);
  analogWrite(In_4, mtr_hz_L); // max 255
  digitalWrite(In_3, LOW);
}
void setup()
{
  pinMode(trigPin_L, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin_L, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin_R, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin_R, INPUT); // Sets the echoPin as an INPUT
  pinMode(In_1, OUTPUT);pinMode(In_2, OUTPUT);pinMode(In_3, OUTPUT);pinMode(In_4, OUTPUT);
  pinMode(Fault, INPUT);pinMode(Sleep, OUTPUT);digitalWrite(Sleep, HIGH);
  digitalWrite(In_1, LOW);digitalWrite(In_2, LOW);digitalWrite(In_3, LOW);digitalWrite(In_4, LOW);
  digitalWrite(trigPin_L, LOW);digitalWrite(trigPin_R, LOW);
  /*
  Serial.begin(115200); // // Serial Communication is starting with 115200 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("ARDUINO NANO");
  */
}
void loop() {
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //distance_L = 0;
  duration_L = pulseIn(echoPin_L, HIGH); // 5800 per meter
  // Calculating the distance
  // distance_L = duration_L * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // delay(1);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  // distance_R = 0;
   duration_R = pulseIn(echoPin_R, HIGH); // 5800 per meter
  // Calculating the distance
  // distance_L = duration_L * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // delay(60); // recomended from datasheet
  if( duration_L > 17400) // if distance bigger than 3 meter set max value to 3 meter
  {
    duration_L = 17400; // 3 * 5800 = 17400
  }
  if( duration_R > 17400) // if distance bigger than 3 meter set max value to 3 meter
  {
    duration_R = 17400; // 3 * 5800 = 17400
  }
  if( duration_L < 1160 ) // if distance smaller than 20 cm go back 20 * 58 = 1160
  {
    motor_geri( 80 , 150 );
    delay(400); // 500ms go back
  }
  if( duration_R < 1160 ) // if distance smaller than 20 cm go back 20 * 58 = 1160
  {
    motor_geri( 180 , 50 );
    delay(400); // 500ms go back
  }
  if( ( !(duration_L < 1160) ) |  ( !(duration_R < 1160) ) ) // if every sensor return value bigger than 20 cm go through
  {
    //motor_ileri( (duration_L / 70) , (duration_R / 70) );
    motor_ileri( 130 , 100 );
    delay(60); // 1sn go go go
  }
}
/*  
  // her iki gözde 0 - 20cm de engel algıladı , minimum 20cm
  // sadece 1 gözde 0 - 20cm de engel algıladı , minimum 20cm
  // her iki gözde 20 - 50cm de engel algıladı
  // sadece 1 gözde 20 - 50cm de engel algıladı
  // her iki gözde 50 - 100cm de engel algıladı
  // sadece 1 gözde 50 - 100cm de engel algıladı
  // her iki gözde 100 - 200cm de engel algıladı
  // sadece 1 gözde 100 - 200cm de engel algıladı
  // her iki gözde 200 + da engel algıladı veya engel algılanmadı
  // sadece 1 gözde 200 + da engel algıladı veya engel algılanmadı
  
    // her iki gözde 0 - 20cm de engel algıladı , minimum 20cm
  if( (distance_R < 20) &
      (distance_L < 20)
    )
  {
    motor_geri(10 , 10);
  }
  // sadece 1 gözde 0 - 20cm de engel algıladı , minimum 20cm
  if( (distance_R < 20) &
      (distance_L >= 20)
    )
  {
    motor_ileri(10 , 20);
  }
  if( (distance_R >= 20) &
      (distance_L < 20)
    )
  {
    motor_ileri(20 , 10);
  }
  // her iki gözde 20 - 50cm de engel algıladı
  if( ( (distance_R >= 20) & (distance_R < 50) ) &
      ( (distance_L >= 20) & (distance_L < 50) )
    )
  {
    if(distance_R > distance_L)
    {
      motor_ileri(50 , 20);
    }
    else
    {
      motor_ileri(20 , 50);
    }
  }
  // sadece 1 gözde 20 - 50cm de engel algıladı
  if( (distance_R < 50) &
      (distance_L >= 50)
    )
  {
    motor_ileri(20 , 50);
  }
  if( (distance_R >= 50) &
      (distance_L < 50)
    )
  {
    motor_ileri(50 , 20);
  }
  // her iki gözde 50 - 100cm de engel algıladı
  if( ( (distance_R >= 50) & (distance_R < 100) ) &
      ( (distance_L >= 50) & (distance_L < 100) )
    )
  {
    if(distance_R > distance_L)
    {
      motor_ileri(75 , 50);
    }
    else
    {
      motor_ileri(50 , 75);
    }
  }
  // sadece 1 gözde 50 - 100cm de engel algıladı
  if( (distance_R < 100) &
      (distance_L >= 100)
    )
  {
    motor_ileri(50 , 75);
  }
  if( (distance_R >= 100) &
      (distance_L < 100)
    )
  {
    motor_ileri(75 , 50);
  }
  // her iki gözde 100 - 200cm de engel algıladı
  if( ( (distance_R >= 100) & (distance_R < 200) ) &
      ( (distance_L >= 100) & (distance_L < 200) )
    )
  {
    if(distance_R > distance_L)
    {
      motor_ileri(90 , 75);
    }
    else
    {
      motor_ileri(75 , 90);
    }
  }
  // sadece 1 gözde 100 - 200cm de engel algıladı
  if( (distance_R < 200) &
      (distance_L >= 200)
    )
  {
    motor_ileri(75 , 90);
  }
  if( (distance_R >= 200) &
      (distance_L < 200)
    )
  {
    motor_ileri(50 , 75);
  }
  // her iki gözde 200 + da engel algıladı veya engel algılanmadı
  if( (distance_R >= 200) &
      (distance_L >= 200)
    )
  {
    motor_ileri(90 , 90);
  }
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  */
















