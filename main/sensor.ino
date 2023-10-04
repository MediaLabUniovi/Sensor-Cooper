/***************************************************************************
  Este archivo ha sido modificado de manera considerable para implementar el
  sensor ultrasónico de distancia JSN-SR04T en vez del original BME280.

  El enlace para consultar el proyecto original del usuario de GitHub
  "rwanrooy" es el siguiente:
  https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.git
***************************************************************************/

#include <NewPing.h>                                       // Librería para usar el sensor JSN-SR04T de forma más sencilla. No va ni por I2C ni SPI, por lo que no hace falta 'wire.h' u otras

//
// Declaración de pines para JSN-SR04T y batería ------------------------------------------------------------------------------------------------------------
//

//
// Declaración de variables ---------------------------------------------------------------------------------------------------------------------------------
//

char LoRa_char[32];                                        // 'char' para imprimir por serial los valores del sensor y batería

#define MAX_DISTANCE 400                                   // En 'MAX_DISTANCE' guardaré de forma inmutable la máxima distancia a la que funciona el sensor, unos 400 a 500cm

NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE);   // 'NewPing' setup para pines y distancia máxima

float Vbat;                                                // Voltaje de la batería del conversor AD del ESP32

//
// Funciones ------------------------------------------------------------------------------------------------------------------------------------------------
//

void LoRa_setup(){
  Serial.begin(115200);
  pinMode(VBAT, INPUT);
}

int distance(){
  return sonar.ping_cm();
}

//
// 'loop()' - COGER CON PINZAS QUE SEA EL LOOP, PERO SE ASEMEJA EN CONCEPTO PARA ESTE FICHERO ----------------------------------------------------------------
//

void buildPacket(uint8_t txBuffer[4]){
  char buffer[40];

  //
  // Distancia -----------------------------------------------------------------------------------------------------------------------------------------------
  //

  delay(50); // Esperar 50ms, sobre 20pings/s. El mínimo razonable serían 29ms

  int distance = sonar.ping_cm();
  sprintf(LoRa_char, "Distancia: %d", distance);
  Serial.println(LoRa_char);

  snprintf(buffer, sizeof(buffer), "Distancia: %d\n", distance);
  screen_print(buffer);

  txBuffer[1] = lowByte(distance);
  txBuffer[0] = highByte(distance);

  //
  // Batería -------------------------------------------------------------------------------------------------------------------------------------------------
  //

  Vbat = (float)(analogRead(VBAT)) / 4095*2*3.3*1.1;
  sprintf(LoRa_char, "Voltaje: %f", Vbat);
  Serial.println(LoRa_char);

  snprintf(buffer, sizeof(buffer), "Voltaje: %.3f\n", Vbat);
  screen_print(buffer);

  // float -> int
  // int payloadVbat = (int)Vbat * 1000;

  // int -> bytes
  // byte VbatLow = lowByte(payloadVbat);
  // byte VbatHigh = highByte(payloadVbat);
  int dec = (Vbat - floor(Vbat))*100;
  txBuffer[2] = lowByte((int)Vbat);
  txBuffer[3] = lowByte(dec);
  Serial.println(dec);
}
