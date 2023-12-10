/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs

##connect the sensor via grove cable to the D2 port on the Grove shield
##install firmware library Grove_Temperature_And_Humidity_Sensor, add

#include "Grove_Temperature_And_Humidity_Sensor.h"

##initialize the sensor
DHT dht(D2);
float temp, humidity;
double temp_dbl, humidity_dbl;

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  // Put initialization like pinMode and begin functions here
Serial.begin(9600);
dht.begin();

Particle.variable("temp", temp_dbl);
Particle.variable("humidity", humidity_dbl);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
float temp, humidity;
temp = dht.getTempFarenheit();
humidity = dht.getHumidity();
temp_dbl = temp;
humidity_dbl = humidity;
Serial.printlnf("Temp: %f", temp);
Serial.printlnf("Humidity: %f" humidity);
delay(10000);

}
