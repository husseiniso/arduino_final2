#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int inputPin = 6;
int val = 0; 
int pirState = LOW;
int motorState = 0;
int ledPin = 13;
const int motorPin = 9;
int pinSpeaker = 10; 





void setup()
{
    pinMode(ledPin, OUTPUT);
          pinMode(pinSpeaker, OUTPUT);
  pinMode(inputPin, INPUT); 
  lcd.begin(16, 2);

  lcd.clear();
 
  lcd.print("STATE");
  
  pinMode(motorPin, OUTPUT);
Serial.begin(9600);
}
int counter = 0;





void loop()
{
    lcd.setCursor(0,1);

  val = digitalRead(inputPin);
    Serial.println(val);
  if (val == HIGH){
    lcd.print("AATTTTAAACCCKKKk");
    if( motorState  == 0 ) 
    {      motorOn();
          motorState = 1;
    }
    digitalWrite(ledPin, HIGH);
    playTone(300, 160);
  }
  
  if (val == LOW) {
    counter++;
    lcd.print("chill its safe  ");
    if(motorState == 1 && counter > 500)
    {
        motorOff();
        motorState= 0;
        counter = 0;
    }
       digitalWrite(ledPin, LOW);
        playTone(0, 0);

  }

}

void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}


void motorOn(){
   int speeds;
    int delayTime = 1; 
    for(speeds = 0; speeds <= 255; speeds++)
  {
    analogWrite(motorPin,speeds);	
    delay(delayTime);           	
  }

}

void motorOff(){
  digitalWrite(motorPin, LOW); 

}
// This function turns the motor on and off like the blinking LED.
// Try different values to affect the timing.

void motorOnThenOff()
{
  int onTime = 3000;  // milliseconds to turn the motor on
  int offTime = 3000; // milliseconds to turn the motor off
  
  digitalWrite(motorPin, HIGH); // turn the motor on (full speed)
  delay(onTime);                // delay for onTime milliseconds
  digitalWrite(motorPin, LOW);  // turn the motor off
  delay(offTime);               // delay for offTime milliseconds
}


// This function alternates between two speeds.
// Try different values to affect the timing and speed.

void motorOnThenOffWithSpeed()
{
  int Speed1 = 200;  // between 0 (stopped) and 255 (full speed)
  int Time1 = 3000;  // milliseconds for speed 1
  
  int Speed2 = 50;   // between 0 (stopped) and 255 (full speed)
  int Time2 = 3000;  // milliseconds to turn the motor off
  
  analogWrite(motorPin, Speed1);  // turns the motor On
  delay(Time1);                   // delay for onTime milliseconds
  analogWrite(motorPin, Speed2);  // turns the motor Off
  delay(Time2);                   // delay for offTime milliseconds
}


// This function slowly accelerates the motor to full speed,
// then back down to zero.

void motorAcceleration()
{
  int speed;
  int delayTime = 20; // milliseconds between each speed step
  
  // accelerate the motor

  for(speed = 0; speed <= 255; speed++)
  {
    analogWrite(motorPin,speed);	// set the new speed
    delay(delayTime);           	// delay between speed steps
  }
  
  // decelerate the motor

  for(speed = 255; speed >= 0; speed--)
  {
    analogWrite(motorPin,speed);	// set the new speed
    delay(delayTime);           	// delay between speed steps
  }
}


// This function will let you type a speed into the serial
// monitor window. Open the serial monitor using the magnifying-
// glass icon at the top right of the Arduino window. Then
// type your desired speed into the small text entry bar at the
// top of the window and click "Send" or press return. The motor
// will then operate at that speed. The valid range is 0 to 255.

void serialSpeed()
{
  int speed;
  
  Serial.println("Type a speed (0-255) into the box above,");
  Serial.println("then click [send] or press [return]");
  Serial.println();  // Print a blank line

  // In order to type out the above message only once,
  // we'll run the rest of this function in an infinite loop:

  while(true)  // "true" is always true, so this will loop forever.
  {
    // First we check to see if incoming data is available:
  
    while (Serial.available() > 0)
    {
      // If it is, we'll use parseInt() to pull out any numbers:
      
      speed = Serial.parseInt();
  
      // Because analogWrite() only works with numbers from
      // 0 to 255, we'll be sure the input is in that range:
  
      speed = constrain(speed, 0, 255);
      
      // We'll print out a message to let you know that the
      // number was received:
      
      Serial.print("Setting speed to ");
      Serial.println(speed);
  
      // And finally, we'll set the speed of the motor!
      
      analogWrite(motorPin, speed);
    }
  }
}

