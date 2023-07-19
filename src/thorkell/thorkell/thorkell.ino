// Thorkell-bot
// ME4705 Fabricación Digital
// Joseph Jowell Sabin, Joan Núñez, Gustavo Rivera

#include<Button.h>

//Se definen los pines de motores y sensores
int pin_mot_1 = 5;
int pin_mot_1_r = 6;

int pin_mot_2 = 10;
int pin_mot_2_r = 11;

int pin_tracker = 12;
int pin_trig = 3;
int pin_echo = 4;
int pin_button = 2;

long pulso = 0;
// Variable que indica el estado del robot (batalla o estacionario)
bool batalla = false;

//Variable que indica si el robot busca o avanza
bool busca = true;
//Variable que indica detección de línea
bool linea = false;

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
//  Serial.println("Ready");
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

bool detectLine(bool lastVal) {
  //Sólo revisar si es que no se está actualmente sobre la línea
  if (!lastVal) {
    bool newVal = digitalRead(pin_tracker);  
    if (newVal) {
      return true;
    }
  }
  
}
void turn_left(double pot) {
  analogWrite(pin_mot_1, pot * (double) 255);
  analogWrite(pin_mot_1_r, 0);
  analogWrite(pin_mot_2, 0);
  analogWrite(pin_mot_2_r, pot * (double) 255);
}

void turn_right(double pot) {
  analogWrite(pin_mot_1_r, pot * (double) 255);
  analogWrite(pin_mot_1, 0);
  analogWrite(pin_mot_2_r, 0);
  analogWrite(pin_mot_2, pot * (double) 255);
}

void forward(double pot) {
  analogWrite(pin_mot_1, pot * (double) 255);
  analogWrite(pin_mot_1_r, 0);
  analogWrite(pin_mot_2_r, 0);
  analogWrite(pin_mot_2, pot * (double) 255);
}

void backwards(double pot) {
  analogWrite(pin_mot_1_r, pot * (double) 255);
  analogWrite(pin_mot_1, 0);
  analogWrite(pin_mot_2, 0);
  analogWrite(pin_mot_2_r, pot * (double) 255);
}

void stop() {
  analogWrite(pin_mot_1, 0);
  analogWrite(pin_mot_2, 0);
  analogWrite(pin_mot_1_r, 0);
  analogWrite(pin_mot_2_r, 0);
}

void batallar() {
  if (batalla) {
    dist = getDist();
    //Hay 2 estados, búsqueda y ataque
    if (busca) {
      turn_left((double)180/255);
      if (dist < 35) {
//        Serial.println("Detectado");
        busca = false;
      }
    } else {
      forward(1);
      if (dist >=35) {
        busca = true; 
      }
    }
    
  } else {
    stop();
  }
}
void loop()
{
  // true si el tracker lee 0 (blanco)
  linea = !digitalRead(pin_tracker);
  
  // Si hay lectura en el botón, se inicia o se acaba la batalla, y se dejan pasar 5 segundos
  if (boton.toggled() && boton.read() != Button::PRESSED) {
    Serial.println(batalla);
    if (!batalla) {
        Serial.println("Lesgoo");
        
    }
    batalla = !batalla;
    delay(5000);   
  }
  if (batalla) {
    if (linea) {
//      Serial.println("Se cae");
      backwards(1);
    } else {
      dist = getDist();
//      Serial.println(dist);
      //Hay 2 estados, búsqueda y ataque
      if (busca) {
        turn_left((double)180/255);
        if (dist < 30) {
//          Serial.println("Detectado");
          busca = false;
        }
      } else {
        forward(1);
        if (dist >=30) {
          busca = true; 
        }
      }
    }
  } else {
    stop();
  }
}
