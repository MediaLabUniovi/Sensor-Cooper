# SENSOR COOPER V3.2 - MEDIALAB LPWAN: ULTRASONIC SENSOR FOR MEASURING SAN MIGUEL'S CREEK WATER LEVEL

Project based on: https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.

Component list:

| Component  | Model |
| ------------- | ------------- |
| Dev Module  | LilyGO LoRa32 OLED v2.1_1.6  |
| Distance sensor  | JSN-SR04T  |
| Battery  | 18650  |
| Solar panel  | SYP-S0606  |
| PCB  | Custom (file included)  |
| Housing  | Custom (file included)  |

Main features:

- Developed with LilyGO LoRa32 OLED v2.1_1.6 (supports solar recharging and battery management)
![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/Screenshot%202023-11-13%20194151.png)

- Changes made for JSN-SR04T: ultrasonic distance sensor
![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/61rPJNXbuNL._AC_UF894%2C1000_QL80_.jpg)

- Dynamic Data Transmission Rate implementation: send interval dynamically changes its value depending on the typical deviation from the latest 5 distances sent to TTN
![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/Screenshot%202023-11-06%20131622.png)

The first unit has been deployed near the Polytechnic School of Engineering of Gijón:
![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/9_Sensor%20Cooper%20en%20Arroyo%20de%20San%20Miguel.jpg)

Access the Grafana panel via this QR code:

![alt text](https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/qrcode_4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com.png)

Authors: Daniel Rodríguez Moya, Óscar Gijón, Ramón Rubio and MediaLab LPWAN Workgroup.
