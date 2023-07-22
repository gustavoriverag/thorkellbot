// Thorkell-bot
// ME4705 Fabricación Digital
// Joseph Jowell Sabin, Joan Núñez, Gustavo Rivera

#include<Button.h>

//We set variables for pins.
int pin_mot_1 = 5;
int pin_mot_1_r = 6;

int pin_mot_2 = 8;
int pin_mot_2_r = 9;

int pin_pwm_1 = 10;
int pin_pwm_2 = 11;

int pin_tracker = 12;
int pin_trig = 3;
int pin_echo = 4;
int pin_button = 2;

long pulse = 0;
// Auxiliary variable that indicates battle state (true) or idle state (false)
bool battle = false;

// Auxiliary variable that indicates if robot is on search mode (true) or chase mode (false)
bool search = true;
// Variable that indicates when the robot is over the arena border line

bool line = false;

Button  button(pin_button);
//Variable que guarda la distancia del sensor ultrasónico)
int dist = 0;

void setup()
{
  pinMode(pin_mot_1, OUTPUT);
  pinMode(pin_mot_1_r, OUTPUT);
  pinMode(pin_mot_2, OUTPUT);
  pinMode(pin_mot_2_r, OUTPUT);
  
  pinMode(pin_tracker, INPUT);
  pinMode(pin_trig, OUTPUT);
  pinMode(pin_echo, INPUT);
  
  button.begin();
  
  Serial.begin(9600);
  delay(2000);
//  Serial.println("Ready");
}

//Reads distance from the ultrasonic sensor
int getDist() {
  //https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  digitalWrite(pin_trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pin_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  pulse = pulseIn(pin_echo, HIGH);
  // Calculating the distance
  return int(pulse * 0.034 / 2);
}

// activates motors so the robot turns left. Pot parameter (0 to 1) sets power level percentage.
void turn_left(double pot) {
  digitalWrite(pin_mot_1, HIGH);
  digitalWrite(pin_mot_1_r, LOW);
  digitalWrite(pin_mot_2, LOW);
  digitalWrite(pin_mot_2_r, HIGH);
  analogWrite(pin_pwm_1, pot*255);
  analogWrite(pin_pwm_2, pot*255);  
}

// activates motors so the robot turns left. Pot parameter (0 to 1) sets power level percentage.
void turn_right(double pot) {
  digitalWrite(pin_mot_1_r, HIGH);
  digitalWrite(pin_mot_1, LOW);
  digitalWrite(pin_mot_2_r, LOW);
  digitalWrite(pin_mot_2, HIGH);
  analogWrite(pin_pwm_1, pot*255);
  analogWrite(pin_pwm_2, pot*255);
}

// activates motors so the robot goes forward. Pot parameter (0 to 1) sets power level percentage.
void forward(double pot) {
  digitalWrite(pin_mot_1, HIGH);
  digitalWrite(pin_mot_1_r, 0);
  digitalWrite(pin_mot_2_r, 0);
  digitalWrite(pin_mot_2, HIGH);
  analogWrite(pin_pwm_1, pot*255);
  analogWrite(pin_pwm_2, pot*255);
}

// activates motors so the robot goes backward. Pot parameter (0 to 1) sets power level percentage.
void backwards(double pot) {
  digitalWrite(pin_mot_1_r, HIGH);
  digitalWrite(pin_mot_1, LOW);
  digitalWrite(pin_mot_2, LOW);
  digitalWrite(pin_mot_2_r, HIGH);
  analogWrite(pin_pwm_1, pot*255);
  analogWrite(pin_pwm_2, pot*255);
}

// stops motors
void stop() {
  analogWrite(pin_mot_1, 0);
  analogWrite(pin_mot_2, 0);
  analogWrite(pin_mot_1_r, 0);
  analogWrite(pin_mot_2_r, 0);
}

void loop()
{
  // true if tracker sensor reads 0 (white)
  line = !digitalRead(pin_tracker);
  
  // If the button is pushed, toggles the battle state and waits five seconds.
  if (button.toggled() && button.read() != Button::PRESSED) {
    battle = !battle;
    delay(5000);   
  }
  // Only if the battle state is active
  if (battle) {
    // First check is if we are over the line (overrides everything)
    if (line) {
      // if we are falling of the arena, go backward at full power
      backwards(1);
      break;
    } else {
      // read the distance from the sensor
      dist = getDist();
      //If robot is in search mode, turn over its own axis at medium power, so it can detect easier.
      if (search) {
        turn_left((double)180/255);
        // if the distance measured is lower than 35, go into chase mode (search == false)
        if (dist < 35) {
          search = false;
        }
        break;
      } else {
        //if in chase mode, go forward at full power
        forward(1);
        // if the measured distance is higher than 35 cm, go back to search mode.
        if (dist >=35) {
          search = true; 
        }
        break;
      }
    }
  } else {
    // if we are in idle mode, just stop motors.
    stop();
  }
}
