/* ***********************************************************************************************************************************************************
Este archivo ha sido modificado de manera considerable para implementar el sensor ultrasónico de distancia JSN-SR04T en vez del original BME280.
El enlace para consultar el proyecto original del usuario de GitHub "rwanrooy" es el siguiente:
https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.git
*********************************************************************************************************************************************************** */
#include <QuickMedianLib.h>                                 // Librería para obtener la mediana de un array

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// JSN-SR04T config
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
int obten_distancia(){
  long duracion;
  int distancia;
  
  digitalWrite(trigPin, LOW);                               // Clear the trigPin by setting it LOW:
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);                              // Trigger the sensor by setting the trigPin high for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH);                        // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds
  distancia = duracion * 0.034 / 2;                         // Calculate the distance:
  return distancia;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para calcular la mediana de un numero n de muestras de distancia para hacer el dato del nivel del agua más robusto
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
int lista_medidas[5];

uint8_t obten_nivel_mediano(uint8_t muestras){
  int distancia_sonar, distancia_mediana;
  uint8_t nivel_mediana;

  for(uint8_t i = 0; i < muestras; i++){
    distancia_sonar = obten_distancia();

    if(distancia_sonar == 0){                               // Si distancia es 0, implica que superamos el umbral superior. Sin embargo, ésto a veces ocurre sin estar en esta condición, es decir, el sensor tiene fallos físicos
      Serial.print("En el umbral superior: ");
      Serial.println(distancia_sonar);
      uint8_t index = 0;
      while(distancia_sonar == 0 && index < 10){            // "&& i < 'valor'", así puedo evitar pasarme la vida aquí, pero reducir el error
        Serial.print("Umbral superior, corregiendo...       ");
        Serial.println(index);
        distancia_sonar = obten_distancia();
        index++;                                            
        mi_timer(250);                                      // Por ello, en este 'if', itero cada 250ms hasta que de una medida que no sea 0
      }
      Serial.print("Umbral superior corregido: ");
    }

    else if(distancia_sonar <= 24 && distancia_sonar >= 1){ // Si estoy entre 1 y 24, el sensor no tiene resolución y siempre da "24"
      Serial.print("En el umbral inferior: ");
      Serial.println(distancia_sonar);
      uint8_t index = 0;
      while((distancia_sonar <= 24 && distancia_sonar >= 1) && index < 10){ // Itero 10 veces, cada intento en franjas de 250ms
        Serial.print("Umbral inferior, corregiendo...       ");
        Serial.println(index);
        distancia_sonar = obten_distancia();
        index++;
        mi_timer(250); 
      }
      
      if(index == 10){                                      // Si 10 veces seguidas da un "24", tendrá razón y lo acepto
        Serial.println("UMBRAL INFERIOR");
        distancia_sonar = MIN_DISTANCE;
      }
      else{
        Serial.print("Umbral inferior corregido: ");        // Si no, es que consiguió una medida "sana" y es con la que me quedo en el array
      }
    }

    else{
      Serial.print("La muestra es: ");
    }

    Serial.println(distancia_sonar);
    lista_medidas[i] = distancia_sonar;
    mi_timer(1000);
  }
  distancia_mediana = QuickMedian<int>::GetMedian(lista_medidas, muestras);
  nivel_mediana = -((100*(distancia_mediana - 24))/376)+100; // Fórmula para calcular de forma lineal el porcentaje de nivel de agua
  return nivel_mediana;
}

// ===========================================================================================================================================================
// FUNCION PRINCIPAL DE "sensor.ino" - Construir el paquete de datos que se enviara por LoRa
// ===========================================================================================================================================================
void buildPacket(uint8_t txBuffer[3]){                      // Uso 'uint8_t' para que todos los datos sean del tamaño de 1byte (8bits)
  //
  // Distancia -----------------------------------------------------------------------------------------------------------------------------------------------
  //
  uint8_t nivel_mediano = obten_nivel_mediano(5);
  Serial.print("Nivel de agua: ");
  Serial.print(nivel_mediano);
  Serial.println("%");

  txBuffer[0] = lowByte(nivel_mediano);                       // Uso únicamente el lowByte ya que estoy hablando de un porcentaje, del 0% al 100%, valores que no superan 255 y caben en un byte

  //
  // Batería -------------------------------------------------------------------------------------------------------------------------------------------------
  //
  float VBAT;
  VBAT = (float)(analogRead(VBATPIN)) / 4095*2*3.3*1.1;     // Conversión del valor analógico del pin a su voltaje correspondiente
  uint8_t nivel_bateria = 50*(VBAT - 2.2);                  // Relacion lineal (muy simplificada) donde asocio el rango 3.1V - 4.2V al 0% - 100%

  Serial.print("Nivel de batería: ");
  Serial.print(nivel_bateria);
  Serial.println("%");

  txBuffer[1] = lowByte(nivel_bateria);
}