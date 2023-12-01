# SENSOR COOPER V3.2 - MEDIALAB LPWAN: ULTRASONIC SENSOR FOR MEASURING SAN MIGUEL'S CREEK WATER LEVEL

## Project based on: https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN

In honour of Martin Cooper, Princesa de Asturias Award 2009, and Arlene Harris and their vision of IoP, The Internet of People, in MediaLab_ LPWAN, we wanted to develop an IoT device that could improve the quality of the Polytechnic School of Engineering of Gijón. As a result, the idea of the Cooper Sensor came in as a LoRa device that could be left without any need of mantainance measuring the water level of San Miguel's creek.

![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/4_Martin%20Cooper%20y%20Arlene%20Harris.jpg)

With these sensors, the aim is to monitor the possibility of a flood in the main building during the heavy rains season. Specifically, in 2018, a major flood took place turning useless many expensive equipment from the lower floors that were used by the students during the laboratory practices of many subjetcs:

![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(4).jpg)
![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(12).jpg)
![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(6).jpg)

In this repo, you will find all the files and teaching guides required to understand and even take the creative freedom to improve this project.

___

### Component list:

| Component | Model |
| ------------- | ------------- |
| Dev Module  | LilyGO LoRa32 OLED v2.1_1.6 |
| Distance sensor  | JSN-SR04T |
| Battery  | 18650 |
| Solar panel  | SYP-S0606 |
| PCB  | Custom (file included) |
| Housing  | Custom (file included) |

___

### Connection list:

| JSN-SR04T | 18650 | SYP-S0606 | LilyGO |
| ------------- | ------------- | ------------- | ------------- |
| `trigger` | - | - | `13` |
| `echo` | - | - | `12` |
| `5v` | - | - | `00` |
| `GND` | - | - | `GND` |
| - | `Bat Conn` | - | `Bat Conn` |
| - | - | `USB` | `USB` |

> [!TIP]
> The PCB (More info coming below) offers the possibility to connect a button between GPIO23 and GND to be programmed as desired

___

### Flowchart (Simplified!)

```mermaid
graph TD;
  A[Turn on] -->|1| B(Wake up if in deep sleep)
  B -->|2| C(Get distance and battery measurement)
  C -->|3| D(Send bytes to TTN)
  D -->|4| E(Time 20 minutes)
  E -->|5| F(Go to deep sleep)
  F -->|6| B
```

> [!TIP]
> Inside of folder `lorawaterlevelmonitorin/main`, the code is available and ready to flash or edit. The most important files to edit are `sensor.ino`, where any sensor can be implemented, and `configuration.h`, where the peripherals' macros are declared

> [!CAUTION]
> Additional code may be needed if implementing I2C I/O. The functions to make them work are in the original project in `TTGO-PAXCOUNTER-LoRa32-V2.1-TTN/main/main.ino`

___

### Libraries:

- LilyGO board library (Paste the link on the `Preferences` tab and choose `Board` as `TTGO LoRa32 OLED` in Arduino IDE): https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series/blob/master/boards/t3_s3_v1_x.json

- LMIC (Copy the contents of the project file `main/lmic_project_config.h` to the library file `arduino-lmic/project_config/lmic_project_config.h` and uncomment the proper frequency for your region. The sketch does always look at the library folder for the configured region!): https://github.com/mcci-catena/arduino-lmic

- QuickMedianLib (To obtain more solid distance values): https://github.com/luisllamasbinaburo/Arduino-QuickMedian

- ESP sleep (To reduce battery consumption): https://github.com/pycom/pycom-esp-idf/blob/master/components/esp32/include/esp_sleep.h

> [!NOTE]
> Other libraries, like SPI library, are easily downloadable from Arduino IDE

___

### Main features:

- Developed using LilyGO LoRa32 OLED v2.1_1.6 (Supports solar recharging and battery management)

  ![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/Screenshot%202023-11-13%20194151.png)

- Changes made for JSN-SR04T (Ultrasonic distance sensor)

  ![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/61rPJNXbuNL._AC_UF894%2C1000_QL80_.jpg)

- Dynamic Data Transmission Rate implementation: send interval dynamically changes its value between 20 and 40 minutes depending on the typical deviation from the latest 5 distances sent to The Things Network (By OTAA; file "payload_formatter.json" is a suggestion on how to decode the sent bytes)

  ![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-11-30%20182339.png)

- Custom PCB

  ![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-10-04%20142016.png)

> [!TIP]
> Consider soldering female pin connectors so the electronic components can simply be plugged in and unplugged if a repair has to be done

- Custom housing to fit all the elements in the most efficient way

  ![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-12-01%20175741.png)
  ![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-12-01%20175633.png)

> [!WARNING]
> Clear colour PETG 3D printing filament is recommended to survive sun radiation and plastic deformations. An O-ring is also a good choice to fix and stabilize the sensor inside of the bell

___

The first unit has been deployed near the Polytechnic School of Engineering of Gijón:

![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/9_Sensor%20Cooper%20en%20Arroyo%20de%20San%20Miguel.jpg)
![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/map.png)

___

Access the Grafana panel[^1] via this QR code or the link below it:

![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/qrcode_4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com.png)

http://4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com:8080/d/vJhQNCZgz/sensores-jsn-sr04t-arroyo-de-san-miguel?from=now-24h&orgId=1&to=now&refresh=1m

> [!IMPORTANT]
> We will kindly answer doubts and read suggestions via e-mail: medialablpwan@gmail.com :shipit:

_Authors: Daniel Rodríguez Moya, Óscar Gijón, Ramón Rubio and MediaLab LPWAN Workgroup_

[^1]: Instructions on how to deploy Grafana panels are given on the repo `medialablpwan/documentacion`.
