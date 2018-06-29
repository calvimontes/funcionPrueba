//#include "DHT.h"
//#define DHTPIN 7
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h> /*Librería que permite establecer comunicación serie en otros pins*/
/*Aquí conectamos los pins RXD,TDX del módulo Bluetooth.*/
SoftwareSerial BT(10,11); //5 RX, 6 TX.*/
#define PIN_TRIG 12
#define PIN_ECO  13 
#include <DHT11.h>
const int buzzer = 8; //pin de activacion del buzzer
int led = 6; //led Rojo de prueba de conexión
char inbyte = 0; //Char para leer el led
 
void setup() {
  // initialise serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  //dht.begin();
  BT.begin(9600);
  pinMode(buzzer, OUTPUT); //buzzer como salida de audio
}
 
void loop() { 
  if (BT.available() > 0)
  {
    inbyte = BT.read();
    BT.println(inbyte);
    Serial.println(inbyte);
    //Serial.write(BT.read());  
  }
  getProximidad();
  getBuzzer();
  getDHT11();
  getLed();
  getLedRGB();
  sendAndroidValues();
  delay(2000); 
}

//enviar los valores por el dipositivo android por el modulo Bluetooth
void sendAndroidValues()
{
  BT.println("");
}

void getProximidad(){
   /*desde aqui es el de proximidad*/
  long duracion, distancia;  // Variables
    /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);  // Flanco ascendente
  delayMicroseconds(10);        // Duracion del pulso
  digitalWrite(PIN_TRIG, LOW);  // Flanco descendente
    /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);
    /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29;
/* Imprimir resultados a la terminal serial */
 if (distancia >= 5000 || distancia <= 0){
    Serial.println(distancia);
    }
  else {
    Serial.print(distancia);
    Serial.println(" cm");   
  }  /* Retardo para disminuir la frecuencia de las lecturas*/
  //delay(500);   
}

void getBuzzer(){
  if (inbyte == '1'){
  digitalWrite(buzzer, LOW); //buzzer off
  }
  if (inbyte == '2'){
  digitalWrite(buzzer, HIGH); //buzzer on
  }
}

void getDHT11(){
  int pin=7;
  DHT11 dht11(pin);
    int err;
       float temp, hum;
       if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
          {
             Serial.print("Temperatura: ");
             Serial.print(temp);
             Serial.print(" Humedad: ");
             Serial.print(hum);
             Serial.println();
             BT.println(temp);    
             BT.println(hum);    
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
             BT.println(err);
          }
}

void getLed(){
    if (inbyte == '3'){
      digitalWrite(led, HIGH); //LED on
    }
    if (inbyte == '4'){
      digitalWrite(led, LOW); //LED off
    }
}
// aqui es con control de deslizamiento...barra
void getLedRGB(){
  
  
}
