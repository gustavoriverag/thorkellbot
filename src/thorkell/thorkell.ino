// Thorkell-bot
// ME4705 Fabricación Digital
// Joseph Jowell Sabin, Joan Núñez, Gustavo Rivera

#include<Button.h>

//Se definen los pines de motores y sensores
int pin_mot_1 = 5;
int pin_mot_1_r = 6;

int pin_mot_2 = 10;
int pin_mot_2_r = 11;

int pin_tracker = 7;
int pin_trig = 3;
int pin_echo = 4;
int pin_button = 2;

long pulso = 0;
// Variable que indica el estado del robot (batalla o estacionario)
bool batalla = false;

//Variable que indica si el robot busca o avanza
bool busca = true;
bool bstate = false;

Button  boton(pin_button);
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
  
  boton.begin();
  
  Serial.begin(9600);
  delay(2000);
  Serial.println("Ready");
}

int getDist() {
  //https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  digitalWrite(pin_trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pin_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  pulso = pulseIn(pin_echo, HIGH);
  // Calculating the distance
  return int(pulso * 0.034 / 2);
}

void batallar() {
  if (batalla) {
    dist = getDist();
    //Hay 2 estados, búsqueda y ataque
    if (busca) {
      analogWrite(pin_mot_1, 180);
      analogWrite(pin_mot_1_r, 0);
      analogWrite(pin_mot_2, 0);
      analogWrite(pin_mot_2_r, 180);
    
      if (dist < 30) {
        Serial.println("Detectado");
        busca = false;
      }
    } else {
      analogWrite(pin_mot_1, 255);
      analogWrite(pin_mot_1_r, 0);
      analogWrite(pin_mot_2, 255);
      analogWrite(pin_mot_2_r, 0);
      if (dist >=30) {
        busca = true; 
      }
    }
    
  } else {
    analogWrite(pin_mot_1, 0); 
    analogWrite(pin_mot_1_r, 0);
    analogWrite(pin_mot_2, 0);
    analogWrite(pin_mot_2_r, 0);
  }
}
void loop()
{

  // Si hay lectura en el botón, se inicia o se acaba la batalla, y se dejan pasar 5 segundos
  if (boton.toggled() && boton.read() != Button::PRESSED) {
    Serial.println(batalla);
    if (!batalla) {
        Serial.println("Lesgoo");
        
    }
    batalla = !batalla;
    delay(5000);   
  }
//   if (boton.toggled()) {
//        if (boton.read() == Button::PRESSED)
//            Serial.println("Button 3 has been pressed");
//        else
//            Serial.println("Button 3 has been released");
//    }
//  Serial.println(digitalRead(pin_tracker));
}
