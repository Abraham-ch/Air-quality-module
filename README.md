# Documentation
## Introduction
To develop a smart city, good air quality is essential, as it is fundamental for the health and well-being of citizens. High levels of air pollution can have negative effects on health, such as respiratory problems, cardiovascular diseases, cancer, and other chronic conditions. The Breath proposal was designed to take measures to reduce air pollution and improve the quality of life for citizens by promoting the use of renewable energy, and encouraging public transportation and sustainable mobility.
## Description
Breath is a project dedicated to air quality monitoring. It consists of an IoT device that contains sensors such as PMS, BME280, and SCD40, capable of measuring humidity, temperature, PM10 and PM2.5 particle concentrations, and various gases that, at high concentrations, could be harmful to humans or cause irritation and respiratory difficulties. The project was developed to be scalable and compact. Due to its low cost, this device can be deployed in various settings, covering crowded places, industrial facilities, and indoor environments. It only requires a power source and WiFi, making it portable if needed. Once deployed, the data will be displayed on an LCD screen or, if required, virtually, showing concentrations through graphs and storing data in the cloud for later use, such as research, monitoring, and forecasting.

## Breath Device
The project's goal is to provide real-time information on air quality. This need arose due to the significant pollution gap in Peru, along with the poor awareness of this issue in Lima.

### Technology Selection
For the project, we will include sensors in addition to a microcontroller and an LCD screen.


<!-- TABLES -->

<table class="tg">
<thead>
  <tr>
    <th class="tg-0pky"></th>
    <th class="tg-9wq8">Module</th>
    <th class="tg-9wq8">Input Voltage</th>
    <th class="tg-9wq8">Output Voltage</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-0pky"><img src="https://grobotronics.com/images/detailed/123/esp32-4-1_grobo.jpg" alt="ESP32 DevKit V1" width="100" height="100"></td>
    <td class="tg-9wq8">Esp32</td>
    <td class="tg-9wq8">5.5 V</td>
    <td class="tg-9wq8">3.3 V</td>
  </tr>
  <tr>
    <td class="tg-0pky"><img src="https://robu.in/wp-content/uploads/2018/02/robu-1-29.jpg" alt="TFT" width="100" height="100"></td>
    <td class="tg-9wq8">TFT 4" LCD<br>SPI screen</td>
    <td class="tg-9wq8">3.3 V</td>
    <td class="tg-9wq8">-</td>
  </tr>
</tbody>
</table>

<table class="tg">
<thead>
  <tr>
    <th class="tg-0pky" colspan="2"></th>
    <th class="tg-9wq8">Sensor</th>
    <th class="tg-9wq8">Measures</th>
    <th class="tg-9wq8">Measurement Range</th>
    <th class="tg-nrix">Error</th>
    <th class="tg-nrix">Voltage Range</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-0lax" colspan="2" rowspan="3"><img src="https://ae01.alicdn.com/kf/S132ff2b5995b4bb89f2f9c61cbb32e29I/SCD40-M-dulo-de-sensor-de-gas-detecta-CO2-di-xido-de-carbono-temperatura-y-humedad.jpg" alt="SCD40" width="100" height="100"></td>
    <td class="tg-nrix" rowspan="3">SCD40</td>
    <td class="tg-nrix">CO2</td>
    <td class="tg-nrix">[400, 2000] ppm</td>
    <td class="tg-nrix">± 50ppm</td>
    <td class="tg-nrix" rowspan="3">[2.4, 5.5] V</td>
  </tr>
  <tr>
    <td class="tg-nrix">Relative<br>Humidity</td>
    <td class="tg-nrix">[0,100] %RH</td>
    <td class="tg-nrix">± 9% RH</td>
  </tr>
  <tr>
    <td class="tg-nrix">Temperature</td>
    <td class="tg-nrix">[-10, 60]°C</td>
    <td class="tg-nrix">± 1.5°C</td>
  </tr>
  <tr>
    <td class="tg-0lax" colspan="2" rowspan="3"><img src="https://cdn.shopify.com/s/files/1/1509/1638/products/gy-bme280-barometrischer-sensor-fur-temperatur-luftfeuchtigkeit-und-luftdruck-438688_1024x.jpg?v=1679398687" alt="BME280" width="100" height="100"></td>
    <td class="tg-nrix" rowspan="3">BME280</td>
    <td class="tg-nrix">Atmospheric<br>pressure</td>
    <td class="tg-nrix">[300, 1100] hPa</td>
    <td class="tg-nrix">± 5% hPa</td>
    <td class="tg-nrix" rowspan="3">[1.71, 3.6] V</td>
  </tr>
  <tr>
    <td class="tg-9wq8">Relative<br>Humidity</td>
    <td class="tg-9wq8">[0,100] %RH</td>
    <td class="tg-nrix">± 9% RH</td>
  </tr>
  <tr>
    <td class="tg-nrix">Temperature</td>
    <td class="tg-nrix">[-40, 85]°C</td>
    <td class="tg-nrix">± 1.5°C</td>
  </tr>
  <tr>
    <td class="tg-0lax" colspan="2" rowspan="3"><img src="https://i5.walmartimages.com/asr/6ca0b606-5bca-45f2-a54a-bc1ccfa822b8.e011f45c7903ece3f99dfa569b178d53.jpeg" alt="PMS5003T" width="100" height="100"></td>
    <td class="tg-nrix" rowspan="3">PMS5003T</td>
    <td class="tg-nrix">PM 1.0</td>
    <td class="tg-nrix">[0, 1000] ug/m3</td>
    <td class="tg-nrix">± 10%ug/m3</td>
    <td class="tg-nrix" rowspan="3">[4.5, 5.5] V</td>
  </tr>
  <tr>
    <td class="tg-9wq8">PM 2.5</td>
    <td class="tg-9wq8">[0, 1000] ug/m3</td>
    <td class="tg-nrix">± 10%ug/m3</td>
  </tr>
  <tr>
    <td class="tg-9wq8">PM 10</td>
    <td class="tg-9wq8">[0, 1000] ug/m3</td>
    <td class="tg-nrix">± 10%ug/m3</td>
  </tr>
</tbody>
</table>

### Configuration and Connections

Schematic of connections between the sensors and modules created in Fritzing.

![Fritzing](./Fritzingconnections.jpeg "Conexiones Fritzing")

#### Connections TFT - ESP32
In case we do not want the device screen to be continuously on or want it to be managed routinely, disconnect the LED pin from the 3V3 of the ESP32 and assign a new pin.
We need to keep in mind that from SDO (MISO), the connections are made for the subsequent use of the device's touchscreen panel (which can be omitted).

|       4.0'' TFT     	  |   ESP32   	|
|:----------------------:	|:---------:	|
|           VCC          	|    3V3    	|
|           GND          	|    GND    	|
|           CS           	|    D15    	|
|          RESET         	|     D4    	|
|          DC/RS         	|     D2    	|
|        SDI(MOSI)       	|    D23    	|
|           SCK          	|    D18    	|
|           LED          	|    3V3    	|
|        SDO(MISO)       	|    D19    	|
|          T_CLK         	|    SCK    	|
|          T_CS          	|     D5    	|
|          T_DIN         	| SDI(MOSI) 	|
|          T_DO          	| SDO(MISO) 	|
|          T_IRQ         	|    D27    	|

#### Connections BME - SCD40 - ESP32
For configuring our device, we need to consider that the module we are using is the ESP32 DEVKIT V1, with only pins 21 and 22 available as SDA and SCL respectively for the I2C communication protocol.

| BME280 	| SCD40 	| ESP32 	|
|:-----:	|:-----:	|:-----:	|
|  GND  	|  GND  	|   GND   |
|  VCC  	|  VCC  	|   3V3   |
|  SCL  	|   SCL  	|   22    |
|  SDA  	|   SDA  	|   21    |

Since I2C communication is used for both sensors, they must be connected in parallel to the ESP32. If you need to change a sensor, remember to add its address as will be shown below.  

```c
void setup(void){
  Serial.begin(9600);
  ...
  BME280.begin(0x76); 
  SCD40.begin(0x62);
  ...
}
```

#### Connections PMS5003T - ESP32

If you have an additional 5V power source, it is preferable to connect it instead of the ESP32 power supply.

| PMS5003T 	|  ESP32  	|
|:--------:	|:-------:	|
|    GND   	|   GND   	|
|    VCC   	| VIN (5V) 	|
|    RX    	|   TX2   	|
|    TX    	|   RX2   	|

### Device Requirements:

* Internet connection to communicate with the HiveMQ MQTT platform.
* Power supply through a 5V micro USB connection.
* Not water-resistant and should not be submerged.

### Communication:

The HiveMQ MQTT platform will be used as the broker for device communications.

### Deployment
Once the connections are made, the project involves assembling the device and writing the code. Below is a sample of the raw product.

![Breath breadboard example](./muestrabreathbruto.jpg "Breadboard example")


