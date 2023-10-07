#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

// Define Trig and Echo pin:
#define trigPin 13
#define echoPin 12
#define MAX_DISTANCE 400 // Max safe distance for the sensor

// Define OLED params
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

// Define button pin
#define BUTTONPIN 23

// Define OLED function
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define sensor function
NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// Define "delay" function without stopping the program's execution
void mi_timer(int milisegundos){
  unsigned long startTime = millis(); // Get the current time in milliseconds
  while (millis() - startTime < milisegundos){
  }
}

int buttonState = 0;     // Variable for reading the button state

// Variables used for reading the voltage
const uint8_t vbatPin = 35;
float VBAT;

// setup -----------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  // Serial monitor init
  Serial.begin(9600);

  // OLED init
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);  // Pause for 2 seconds to allow the display to initialize

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);

  // I/O init
  pinMode(BUTTONPIN, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
  pinMode(vbatPin, INPUT);
}

// loop ------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  mide_distancia(5000);
  muestra_informacion_OLED(2000);
}

// Funciones del usuario -------------------------------------------------------------------------------------------------------------------------------------

// Función para detectar distancia cada 5 segundos
void mide_distancia(int interval){
  static long prevMill = 0;
  if((millis() - prevMill) >= interval){
    int distancia = sonar.ping_cm();
    prevMill = millis();
    Serial.println(distancia);
  }
}

// Funcion para mostrar la información del OLED durante un tiempo de 2 segundos
void muestra_informacion_OLED(int interval){
  static long startTime = 0;
  
  buttonState = digitalRead(BUTTONPIN); // Read the state of the button
  VBAT = (float)(analogRead(vbatPin)) / 4095*2*3.3*1.1;

  if(buttonState == LOW && startTime == 0){ // If the button is pressed and it's the first press
    startTime = millis(); // Record the start time
    int distancia = sonar.ping_cm();
    display.clearDisplay(); // Limpio el display a cada ejecución del bucle

    // Bloques de impresión de texto en el OLED y monitor serial

    // "Dist: "
    Serial.print("Dist: ");
    display.setTextSize(2);
    display.setCursor(0,20);
    display.print("Dist: ");

    // "distancia = sonar.pingcm()"
    Serial.print(sonar.ping_cm());
    if(distancia > 24){
      display.setTextSize(2);
      display.setCursor(60,20);
      distancia = sonar.ping_cm();
      display.print(distancia);
      display.display();
    }
    else if(distancia <= 24){
      display.setTextSize(2);
      display.setCursor(60,20);
      display.print("NOT");
      display.display();
    }
    
      // "cm"
    Serial.println("cm");
    display.setTextSize(2);
    display.setCursor(100,20);
    display.print("cm");

    // "Bat: "
    Serial.print("Bat: ");
    display.setTextSize(2);
    display.setCursor(0,40);
    display.print("Bat: ");

    // "VBAT"
    Serial.print(VBAT);
    display.setTextSize(2);
    display.setCursor(50,40);
    display.print(VBAT);

    // "V"
    Serial.println("V");
    display.setTextSize(2);
    display.setCursor(100,40);
    display.print("V");

    Serial.println();
    display.display(); // Display "Text" on the OLED screen
  }

  if(startTime > 0 && millis() - startTime >= interval){ // If 2 seconds have passed
    display.clearDisplay(); // Clear the display 'display.clearDisplay()'
    display.setCursor(0,0);
    display.print("");      // Imito que la pantalla está apagada (y lo está al ser OLED)
    display.display(); // Turn off the LED
    startTime = 0; // Reset the start time for the next press
  }
}