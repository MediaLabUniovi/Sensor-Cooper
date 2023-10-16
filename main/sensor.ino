/***************************************************************************
  Este archivo ha sido modificado de manera considerable para implementar el
  sensor ultrasónico de distancia JSN-SR04T en vez del original BME280.

  El enlace para consultar el proyecto original del usuario de GitHub
  "rwanrooy" es el siguiente:
  https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.git
***************************************************************************/

#include <NewPing.h>

// Define sensor function
NewPing sonar_sensor = NewPing(trigPin, echoPin, MAX_DISTANCE);

//
// Declaración de variables ---------------------------------------------------------------------------------------------------------------------------------
//

char LoRa_char[32];                                        // 'char' para imprimir por serial los valores del sensor y batería

float Vbat_sensor;                                                // Voltaje de la batería del conversor AD del ESP32

//
// Funciones ------------------------------------------------------------------------------------------------------------------------------------------------
//

void LoRa_setup(){
  Serial.begin(115200);
  pinMode(VBAT, INPUT);                                    // Defino VBAT, asociado al pin 35, como input. Es el "sensor" de voltaje de la batería
}

//
// 'loop()' - COGER CON PINZAS QUE SEA EL LOOP, PERO SE ASEMEJA EN CONCEPTO PARA ESTE FICHERO ----------------------------------------------------------------
//

void buildPacket(uint8_t txBuffer[4]){
  char buffer[40];

  //
  // Distancia -----------------------------------------------------------------------------------------------------------------------------------------------
  //
  int distance = sonar_sensor.ping_cm();
  sprintf(LoRa_char, "Distancia: %d", distance);
  Serial.println(LoRa_char);

  snprintf(buffer, sizeof(buffer), "Distancia: %d\n", distance);

  txBuffer[0] = highByte(distance);                       // Si la distancia supera los 255, entonces se acumula en 'highByte()' una unidad por cada vez que pase
  txBuffer[1] = lowByte(distance);                        // Para distancia, que puede estar entre 0 y 400, 'lowByte()' me da valores de 0 a 255. Si 'distance' supera n*256, entonces 'distance' = highByte()*256 + lowByte()
                                                          // Por ello, en el Payload formatters de TTN, la misma fórmula en .json se representa ---------------------------------> data.distancia = ((bytes[0] << 8) | bytes[1])
  //
  // Batería -------------------------------------------------------------------------------------------------------------------------------------------------
  //

  Vbat_sensor = (float)(analogRead(VBAT)) / 4095*2*3.3*1.1;
  sprintf(LoRa_char, "Voltaje: %f", Vbat_sensor);
  Serial.println(LoRa_char);

  snprintf(buffer, sizeof(buffer), "Voltaje: %.3f\n", Vbat_sensor);

  int ent = (int)Vbat_sensor;                                     // Parte entera del porcentaje de batería. Si obtengo 3.45, me quedo con 3
  int dec = (Vbat_sensor - floor(Vbat_sensor))*100;                      // Extracción de 2 decimales y conversión a entero. Si obtengo 3.45, 3.45 - 3 = 0.45 y, luego, 0.45 * 100 = 45

  txBuffer[2] = lowByte(ent);                              // Como la parte entera de batería nunca será más de 255, solo envío su 'lowByte()'
  txBuffer[3] = lowByte(dec);                              // Como voy a coger sólo 2 decimales e hice el truco de multiplicarlo para que sea un entero, cojo el 'lowByte()' ya que el rango de valores es 0 - 99, nunca superando 255
                                                           // En el Payload formatters de TTN, Vbat = ent + dec/100, es decir, data.Vbat = lowByte(ent) + lowByte(dec)/100
}
