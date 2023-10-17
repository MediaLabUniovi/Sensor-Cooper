/*

SSD1306 - Screen module

Copyright (C) 2019 by Roel van Wanrooy (www.connectix.nl)


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "images.h"

// Define OLED function
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
unsigned long startTime = 0;

// BOTÓN
int buttonState = 0;

// SETUP OLED -------------------------------------------------------------------------------------------------------------------------------------------------
void screen_setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(5000);                                                             // Pause for 2 seconds to allow the display to initialize

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
}

// FUNCIÓN PROPIA --------------------------------------------------------------------------------------------------------------------------------------------
void muestra_informacion_OLED(int interval){
  
  buttonState = digitalRead(BUTTONPIN);                                    // Read the state of the button

  if(buttonState == LOW && startTime == 0){                                // If the button is pressed and it's the first press
    startTime = millis();                                                  // Record the start time
    int distancia = sonar.ping_cm(); // ==================================================================================================================================
    display.clearDisplay();                                                // Limpio el display a cada ejecución del bucle

    // Bloques de impresión de texto en el OLED y monitor serial

    // "Dist: "
    Serial.print("Dist: ");
    display.setTextSize(2);
    display.setCursor(0,20);
    display.print("Dist: ");

    // "distancia = sonar.ping_cm()"
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
    Serial.print(Vbat);
    display.setTextSize(2);
    display.setCursor(50,40);
    display.print(Vbat);

    // "V"
    Serial.println("V");
    display.setTextSize(2);
    display.setCursor(100,40);
    display.print("V");

    //Serial.println();
    display.display();                                                     // Display "Text" on the OLED screen
  }

  if(startTime > 0 && millis() - startTime >= interval){                   // If 2 seconds have passed
    display.clearDisplay();                                                // Clear the display 'display.clearDisplay()'
    display.setCursor(0,0);
    display.print("");                                                     // Imito que la pantalla está apagada (y lo está al ser OLED)
    display.display();                                                     // Turn off the LED
    startTime = 0;                                                         // Reset the start time for the next press
  }
}