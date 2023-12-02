# <p align="justify"> SENSOR COOPER V3.2 - MEDIALAB LPWAN: ULTRASONIC SENSOR FOR MEASURING SAN MIGUEL'S CREEK WATER LEVEL </p>

## <p align="justify"> Project based on: https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN </p>

<p align="justify"> In honour of Martin Cooper, Princesa de Asturias Award 2009, and Arlene Harris and their vision of IoP, The Internet of People, in MediaLab_ LPWAN, we wanted to develop an IoT device that could improve the quality of the Polytechnic School of Engineering of Gijón. As a result, the idea of the Cooper Sensor came in as a LoRa device that could be left without any need of mantainance measuring the water level of San Miguel's creek. </p>

<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/4_Martin%20Cooper%20y%20Arlene%20Harris.jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>

<p align="justify"> With these sensors, the aim is to monitor the possibility of a flood in the main building during the heavy rains season. Specifically, in 2018, a major flood took place turning useless many expensive equipment from the lower floors that were used by the students during the laboratory practices of many subjetcs: </p>

<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(4).jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>
<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(12).jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>
<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(6).jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>

<p align="justify"> In this repo, you will find all the files and teaching guides required to understand and even take the creative freedom to improve this project. </p>

___

### <p align="justify"> Component list: </p>

<div align="center">

| Component | Model |
| ------------- | ------------- |
| Dev Module  | LilyGO LoRa32 OLED v2.1_1.6 |
| Distance sensor  | JSN-SR04T |
| Battery  | 18650 |
| Solar panel  | SYP-S0606 |
| PCB  | Custom (file included) |
| Housing  | Custom (file included) |

</div>

___

### <p align="justify"> Connection list: </p>

<div align="center">

| JSN-SR04T | 18650 | SYP-S0606 | LilyGO |
| ------------- | ------------- | ------------- | ------------- |
| `trigger` | - | - | `13` |
| `echo` | - | - | `12` |
| `5v` | - | - | `00` |
| `GND` | - | - | `GND` |
| - | `Bat Conn` | - | `Bat Conn` |
| - | - | `USB` | `USB` |

</div>

> [!TIP]
> The PCB (More info coming below) offers the possibility to connect a button between GPIO23 and GND to be programmed as desired

___

### <p align="justify"> Flowchart (Simplified!) </p>

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
> Inside of folder `lorawaterlevelmonitoring/main`, the code is available and ready to flash or edit. The most important files to edit are `sensor.ino`, where any sensor can be implemented, and `configuration.h`, where the peripherals' macros are declared

> [!CAUTION]
> Additional code may be needed if implementing I2C I/O. The functions to make them work are in the original project in `TTGO-PAXCOUNTER-LoRa32-V2.1-TTN/main/main.ino`

___

### <p align="justify"> Libraries: </p>

- <p align="justify"> LilyGO board library (Paste the link on the [Preferences] tab and choose [TTGO LoRa32 OLED] as [Board] in Arduino IDE): https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series/blob/master/boards/t3_s3_v1_x.json

- <p align="justify"> LMIC (Copy the contents of the project file [main/lmic_project_config.h] to the library file [arduino-lmic/project_config/lmic_project_config.h] and uncomment the proper frequency for your region. The sketch does always look at the library folder for the configured region!): https://github.com/mcci-catena/arduino-lmic </p>

- <p align="justify"> QuickMedianLib (To obtain more solid distance values): https://github.com/luisllamasbinaburo/Arduino-QuickMedian </p>

- <p align="justify"> ESP sleep (To reduce battery consumption): https://github.com/pycom/pycom-esp-idf/blob/master/components/esp32/include/esp_sleep.h </p>

> [!NOTE]
> Other libraries, like SPI library, are easily downloadable from Arduino IDE

___

### <p align="justify"> Main features: </p>

- <p align="justify"> Developed using LilyGO LoRa32 OLED v2.1_1.6 (Supports solar recharging and battery management) </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/Screenshot%202023-11-13%20194151.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

- <p align="justify"> Changes made for JSN-SR04T (Ultrasonic distance sensor) </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/61rPJNXbuNL._AC_UF894%2C1000_QL80_.jpg" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

- <p align="justify"> Dynamic Data Transmission Rate implementation: send interval dynamically changes its value between 20 and 40 minutes depending on the typical deviation from the latest 5 distances sent to The Things Network (By OTAA; file [payload_formatter.json] is a suggestion on how to decode the sent bytes) </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-11-30%20182339.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

- <p align="justify"> Custom PCB </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-10-04%20142016.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

> [!TIP]
> Consider soldering female pin connectors so the electronic components can simply be plugged in and unplugged if a repair has to be done

- <p align="justify"> Custom housing to fit all the elements in the most efficient way </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-12-01%20175741.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>
  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-12-01%20175633.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

> [!WARNING]
> Clear colour PETG 3D printing filament is recommended to survive sun radiation and plastic deformations. An O-ring is also a good choice to fix and stabilize the sensor inside of the bell. Four M3 screws are needed to fix the assembly

___

<p align="justify"> The first unit has been deployed near the Polytechnic School of Engineering of Gijón: </p>

<div align="center">
  <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/9_Sensor%20Cooper%20en%20Arroyo%20de%20San%20Miguel.jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>
<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/map.png" width="600"  style="margin: 10px;"/>
</div>
<br/>

___

Access the Grafana panel[^1] via this QR code or the link below it:

<div align="center">
  <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/qrcode_4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com.png" width="600"  style="margin: 10px;"/>
</div>
<br/>

<p align="justify"> Link: http://4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com:8080/d/vJhQNCZgz/sensores-jsn-sr04t-arroyo-de-san-miguel?from=now-24h&orgId=1&to=now&refresh=1m </p>

> [!IMPORTANT]
> We will kindly answer doubts and read suggestions via e-mail: medialablpwan@gmail.com :shipit:

_<p align="justify"> Authors: Daniel Rodríguez Moya, Óscar Gijón, Ramón Rubio and MediaLab LPWAN Workgroup </p>_

[^1]: Instructions on how to deploy Grafana panels are given on the repo `medialablpwan/documentacion`.
