# SENSOR COOPER V3.2 - MEDIALAB LPWAN: ULTRASONIC SENSOR FOR MEASURING SAN MIGUEL'S CREEK WATER LEVEL

## Project based on: https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.

In honour of Martin Cooper and Arlene Harris and their vision of IoP, The Internet of People, in MediaLab_ LPWAN we wanted to develop an IoT device that could improve the quality of the Polytechnic School of Engineering of Gijón. As a result, the idea of the Cooper Sensor came in as a LoRa device that could be left without any need of mantainance measuring the water level of San Miguel's creek.

![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/4_Martin%20Cooper%20y%20Arlene%20Harris.jpg)

With these sensors, the aim is to monitor the possibility of the main building flood during the heavy rains season. Specifically, in 2018, a major flood took place turning useless many expensive equipment from the lower floors that were used by the students during the laboratory practices of many subjetcs:

![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(4).jpg)
![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(12).jpg)
![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(6).jpg)

**Component list:**

| Component | Model |
| ------------- | ------------- |
| Dev Module  | LilyGO LoRa32 OLED v2.1_1.6 |
| Distance sensor  | JSN-SR04T |
| Battery  | 18650 |
| Solar panel  | SYP-S0606 |
| PCB  | Custom (file included) |
| Housing  | Custom (file included) |

**Connection list:**

| JSN-SR04T | 18650 | SYP-S0606 | LilyGO |
| ------------- | ------------- | ------------- | ------------- |
| trigger | - | - | 13 |
| echo | - | - | 12 |
| 5v | - | - | 00 |
| GND | - | - | GND |
| - | Bat Conn | - | Bat Conn |
| - | - | USB | USB |

_The PCB offers the possibility to connect a button between GPIO23 and GND to be programmed as desired_

**Main features:**

- Developed using LilyGO LoRa32 OLED v2.1_1.6 (supports solar recharging and battery management)
![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/Screenshot%202023-11-13%20194151.png)

- Changes made for JSN-SR04T: ultrasonic distance sensor
![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/61rPJNXbuNL._AC_UF894%2C1000_QL80_.jpg)

- Dynamic Data Transmission Rate implementation: send interval dynamically changes its value depending on the typical deviation from the latest 5 distances sent to The Things Network (by OTAA)
![alt text](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-11-30%20182339.png)

The first unit has been deployed near the Polytechnic School of Engineering of Gijón:
![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/9_Sensor%20Cooper%20en%20Arroyo%20de%20San%20Miguel.jpg)

Access the Grafana panel via this QR code or the link below it:

![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/qrcode_4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com.png)

http://4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com:8080/d/vJhQNCZgz/sensores-jsn-sr04t-arroyo-de-san-miguel?from=now-24h&orgId=1&to=now&refresh=1m

Authors: Daniel Rodríguez Moya, Óscar Gijón, Ramón Rubio and MediaLab LPWAN Workgroup.
