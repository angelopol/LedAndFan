#include <NewPing.h>
 
#define TRIGGER_PIN  4
#define ECHO_PIN     2
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int LEDROJO = 7;    // pin 9 a anodo LED rojo
int LEDVERDE = 6;    // pin 10 a anodo LED verde
int LEDAZUL = 5;   // pin 11 a anodo LED azul

int relay = 13;
int fan;

long duracion;
int distancia;

int led = A2;
int ledst;

int aut = 0;

int fotoP = A0;
int fotoPD = 8;
int val = 0; //valores de la fotoresistencia
int i;
int t = 0;


void setup() {
  pinMode(fotoPD, OUTPUT);

  pinMode(relay, OUTPUT);

  pinMode(led, OUTPUT);

  pinMode(LEDROJO, OUTPUT); // todos los pines como salida
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  analogWrite(LEDROJO, 255);  // rojo
  analogWrite(LEDVERDE, 0);
  analogWrite(LEDAZUL, 0);

  digitalWrite(relay, HIGH);

  analogWrite(led, 0);

  digitalWrite(fotoPD, LOW);

  Serial.begin(9600);

}

void loop() {
  duracion = sonar.ping();
  val = analogRead(fotoP);  //leemos el puerto analogico de la fotop
  fan = digitalRead(relay);
  ledst = analogRead(led);

  delay(100);

if (val == 0) {
  
  if (duracion <= 250 && ledst < 100) {
      analogWrite(LEDROJO, 0);  // verde
      analogWrite(LEDVERDE, 255);
      analogWrite(LEDAZUL, 0);

      analogWrite(led, 255);
    
      Serial.println("Encendido manual");
      delay(500);
    }

  if (duracion <= 250 && ledst > 100) {
      analogWrite(LEDROJO, 255);  // rojo
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 0);

      analogWrite(led, 0);

      Serial.println("Apagado manual");
      delay(500);
    }
}

  if (duracion >= 450 && duracion <= 600 && val == 0) {
      i = 1;
      analogWrite(LEDROJO, 0);  // azul
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 255);
      digitalWrite(led, LOW);
      digitalWrite(fotoPD, HIGH);
      Serial.println("Modo Automatico Encendido");
      delay(500);
    }

  if (i == 1){
      Serial.println(analogRead(fotoP));
      
      if(analogRead(fotoP) > 0 && analogRead(fotoP) < 20){
        digitalWrite(led, HIGH);
        Serial.println("+");
        }
     if(analogRead(fotoP) > 60){
        t = t + 1;
        if (t >50) {
          digitalWrite(led, LOW);
          Serial.println("-");
          t = 0;
          }
      }
  }

  if (duracion >= 450 && duracion <= 600 && val > 0) {
      i = 0;
      analogWrite(LEDROJO, 255);  // rojo
      analogWrite(LEDVERDE, 0);
      analogWrite(LEDAZUL, 0);
      digitalWrite(led, LOW);
      digitalWrite(fotoPD, LOW);
      Serial.println("Modo Automatico Apagado");
      delay(500);
    }

  if (duracion >= 700 && duracion <= 900 && fan == 1) {
      digitalWrite(relay, LOW); //El relay enciende 
      Serial.println("Fan Encendido");
      delay(500);
    }

  if (duracion >= 700 && duracion <= 900 && fan == 0) {
      digitalWrite(relay, HIGH); //El relay apaga 
      Serial.println("Fan Apagado");
      delay(500);
    }

}
