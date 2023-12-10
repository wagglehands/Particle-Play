# Particle Argon
The Particle Argon is a development kit with Wi-Fi and Bluetooth radios for building connected projects and products.

 Projects in this Argon Repository:
 
1. [Argon Setup](https://github.com/wagglehands/Particle-Play/edit/main/readme#set-up-argon) 
2. Use of Temperature Humidity Sensor
3. Controlling a Chainable LED
4. Using the Light Sensor
5. Simple Parking Sensor
6. Couple's Light

## The Argon kit comes with the following things:
-Argon development kit
-Starter Project
-One micro-USB cable
-One mini breadboard
-Electronic components
-Two resistors (220 ohm)
-One light-emitting diode (LED)
-One phototransistor

# Set up Argon
Once you're ready to proceed, use the online setup application to configure your new Argon. The process includes the following:
Registration of your device with your Particle account
Connection of your device to the Particle Device Cloud
Once you've completed the setup you will be able to program your device and send over-the-air (OTA) updates to it.

#### NOTES:
1.) If you have already set up your Argon, skip to Step #2.
2.) We recommend setting up the Argon as stanadalone device, not as a part of a mesh network. See mesh deprecation for more information.

### Open the Web IDE
To program your Argon, open a new browser tab and go to the Web IDE. You will see a layout like the image below.
NOTE: The Web IDE is one of the ways you can write, compile, and deploy code to your Particle devices.
If you're looking for a more traditional embedded development experience, be sure to learn about Particle Workbench, a full toolchain integration with Microsoft Visual Studio Code.
### Load the Blink example
Click on Blink an LED on the left side of the page. As soon as you click the Blink and LED code will load and fill the screen as shown below.
The code is heavily commented to help you understand the general structure of the sketch: the first part of the code declares two variables, the setup() function configures two pins as outputs, and finally the loop() which turns the onboard LED on, then off, then loops continuously.
#### Target your device
The Web IDE can be used with multiple devices. As such, when you go to compile source code, it's a good idea to verify that the device you are intending to program has a gold star to the left of its name in the Devices tab (circle with 4 lines).
### Compile your code & flash
Click the lightning bolt icon on the top left of your screen to flash your code to your device.
As soon as you click, the Particle Device cloud will compile the program source code to a binary file and send it over-the-air (OTA) to your Argon.

# Measure Temperature & Humidity

The Particle Device OS provides a simple way to access sensor values and device local state through the variable primitive. Registering an item of firmware state as a variable enables you to retrieve that state from the Particle Device Cloud. Let's explore this now with the help of the Grove Temperature and Humidity sensor.

## Connect the temperature sensor
To connect the sensor, connect a Grove cable to the port on the sensor. Then, connect the other end of the cable to the D2 port on the Grove shield.

### Install the sensor firmware library
If you are using the Web IDE, click the Libraries icon on the left and select Grove_Temperature_And_Humidity_Sensor and add it to your project.

If you are using Particle Workbench, from the Command Palette (Ctrl+Shift+P on Windows and Linux, and Cmd+Shift+P on Mac) select Particle: Install Library and install the library Grove_Temperature_And_Humidity_Sensor.

### Read from the sensor
Once the library is installed, add it to your project via an #include statement at the top of your main project file (.ino or .cpp).
#include "Grove_Temperature_And_Humidity_Sensor.h"

#### Tip: Get any error message from Workbench?
From time-to-time, the IntelliSense engine in VS Code that Workbench depends on may report that it cannot find a library path and draw a red squiggly under your #include statement above. As long as your code compiles, (which you can verify by opening the command palette [CMD/CTRL+SHIFT+P] and choosing the Particle: compile application (local)) you can ignore this error.
You can also resolve the issue by trying one of the steps detailed in this community forum post, here.

### Next, initialize the sensor, just after the #include statement.
DHT dht(D2);

### In the setup function, you'll initialize the sensor and a serial monitor.
void setup()
{
Serial.begin(9600);
dht.begin();
}

### Finally, take the readings in the loop function and write them to the serial monitor.
void loop()
{
float temp, humidity;
temp = dht.getTempFarenheit();
humidity = dht.getHumidity();
Serial.printlnf("Temp: %f", temp);
Serial.printlnf("Humidity: %f", humidity);
delay(10000);
}

**Now, flash this code to your device. Open the command palette (CMD/CTRL+SHIFT+P) and select the Particle: Cloud Flash option.**
Finally, open a terminal window and run the particle serial monitor command. Once your Argon comes back online, it will start logging environment readings to the serial console.
Now that you've connected the sensor, let's sprinkle in some Particle goodness.

**Store sensor data in Particle variables**
To use the Particle variable primitive, you need global variables to access.
Start by moving the first line of your loop which declares the two environment variables (temp and humidity) to the top of your project, outside of the setup and loop functions.
Then, add two more variables of type double. We'll need these because the Particle Cloud expects numeric variables to be of type int or double.

#include "Grove_Temperature_And_Humidity_Sensor.h"
DHT dht(D2);
float temp, humidity;
double temp_dbl, humidity_dbl;
void setup() {
 // Existing setup code here
}
void loop() {
 // Existing loop code here
}

With global variables in hand, you can add Particle variables using the Particle.variable() method, which takes two parameters: the first is a string representing the name of the variable, and the second is the firmware variable to track.

**Add the following lines to the end of your setup function:**
Particle.variable("temp", temp_dbl);
Particle.variable("humidity", humidity_dbl);

**Next, in the loop function, just after you read the temp and humidity values from the sensor, add the following two lines, which will implicitly cast the raw float values into double for the Device Cloud.**
temp_dbl = temp;
humidity_dbl = humidity;

Flash this code to your device and, when the Argon comes back online, move on to the next step.
Accessing Particle variables from the console
To view the variables you just created, open the Particle Console by navigating to console.particle.io and clicking on your device.

On the device detail page, your variables will be listed on the right side, under Device Vitals and Functions.

Click the Get button next to each variable to see its value.
Now that you've mastered Particle variables for reading sensor data, let's look at how you can use the function primitive to trigger an action on the device.

# Particle Functions: Controlling a Chainable LED
As with Particle variables, the function primitive exposes our device to the Particle Device Cloud. Where variables expose state, functions expose actions.

In this section, you'll use the Grove Chainable LED and the Particle.function command to take a heart-rate reading, on demand.

**Connect the Chainable LED**
Open the bag containing the chainable LED and take one connector out of the bag.
Connect one end of the Grove connector to the chainable LED on the side marked IN (the left side if you're looking at the device in a correct orientation).
Plug the other end of the connector into the Shield port labeled A4.
As with the Temp and Humidity sensor, you'll need a library to help us program the chainable LED. Using the same process you followed in the last module, add the Grove_ChainableLED library to your project in Particle Workbench.
Once the library has been added, add an include and create an object for the ChainableLED class at the top of your code file. The first two parameters specify which pin the LED is wired to, and the third is the number of LEDs you have chained together, just one in your case.
#include "Grove_ChainableLED.h"
ChainableLED leds(A4, A5, 1);

Now, initialize the object in your setup function. You'll also set the LED color to off after initialization.
leds.init();
leds.setColorHSB(0, 0.0, 0.0, 0.0);

With our new device set-up, you can turn it on in response to Particle function calls!
Illuminating the Chainable LED
Start by creating an empty function to toggle the LED. Place the following before the setup function. Note the function signature, which returns an int and takes a single String argument.
int toggleLed(String args) {
}

**In the toggleLED function, add a few lines turn the LED red, delay for half a second, and then turn it off again.**
int toggleLed(String args) {
leds.setColorHSB(0, 0.0, 1.0, 0.5);
delay(500);
leds.setColorHSB(0, 0.0, 0.0, 0.0);
delay(500);
return 1;
}

Now, let's call this from the loop to test things out. Add the following line before the delay.
toggleLed("");

The last step is to flash this new code to your Argon. Once it's updated, the LED will blink red.
Setting-up Particle functions for remote execution
Now, let's modify our firmware to make the LED function a Particle Cloud function.

### Add a Particle.function to the setup function.
Particle.function("toggleLed", toggleLed);
Particle.function takes two parameters, the name of the function for display in the console and remote execution, and a reference to the firmware function to call.

### Remove the call to toggleLed from the loop.
Calling Particle functions from the console
Flash the latest firmware and navigate to the device dashboard for your Argon at console.particle.io. On the right side, you should now see your new function.

Click the Call button and watch the chainable LED light up at your command!
Particle publish & subscribe with the light sensor
For the final section of this lab, you're going to explore the Particle pub/sub primitives, which allows inter-device (and app!) messaging through the Particle Device Cloud. You'll use the light sensor and publish messages to all listeners when light is detected.

### Connect the light sensor
To connect the light sensor, connect a Grove cable to the port of the sensor. Then, connect the other end of the cable to the Analog A0/A1 port on the Grove shield.

# Particle Functions: Using the light sensor
Let's set-up the sensor on the firmware side so that you can use it in our project. The light sensor is an analog device, so configuring it is easy, no library needed.

You'll need to specify that the light sensor is an input using the pinMode function. Add the following line to your setup function:
pinMode(A0, INPUT);

**Let's also add a global variable to hold the current light level detected by the sensor. Add the following before the setup and loop functions:**
double currentLightLevel;

Now, in the loop function, let's read from the sensor and use the map function to translate the analog reading to a value between 0 and 100 that you can work with.
double lightAnalogVal = analogRead(A0);
currentLightLevel = map(lightAnalogVal, 0.0, 4095.0, 0.0, 100.0);

Now, let's add a conditional to check the level and to publish an event using Particle.publish if the value goes over a certain threshold.
if (currentLightLevel > 50) {
Particle.publish("light-meter/level", String(currentLightLevel), PRIVATE);
}

Flash the device and open the Particle Console dashboard for your device. Shine a light on the sensor and you'll start seeing values show up in the event log.

**Subscribe to published messages from the Particle CLI**
In addition to viewing published messages from the console, you can subscribe to them using Particle.subscribe on another device, or use the Device Cloud API to subscribe to messages in an app. Let's use the Particle CLI to view messages as they come across.

Open a new terminal window and type particle subscribe light-meter mine.

Shine a light on the light sensor and wait for readings. You should see events stream across your terminal. Notice that the light-meter string is all you need to specify to get the light-meter/latest events. By using the forward slash in events, can subscribe via greedy prefix filters.
Congratulations! You've made it through our first IoT Starter Kit project. This is just the beginning of what's possible with the hardware in front of you.

# Couples Light

## OVERVIEW
This project includes two Particle Argon IoT devices. The goal of this project is to achieve communication via LEDs that light up to heart beat pulses and can send signals over any distance. The only requirement is that both of the Particle Argon IOT devices must be connected to WIFI so the signal is sent successfully. When the button is pressed on an Argon, three LEDs flash and when the heartbeat sensor is held, LED connected to D6 flashes. This can be configured to use any colored LED without needing to code anything. If more or less LEDs are wanted that can be configured with a simple addition of another LED into a code. The time delay between the LEDs lighting up can also be configured simply in the code.

## WIRING
The Button is connected to ground, positive and D4, the LED's are connected to D6, D5, and D3 and also to the ground strip. The heart beat sensor is connected to positive, ground, and A1. There is also a couple jumper wires going from 3v3 to positive strip and ground to the negative strip. The both of the ground strips are being powered by a jumper wire.

## Simple Parking Sensor
This code checks if there is something less than 25 centimeters near the sensor and if there is, this means that there is a car. You can change this number to anything that you want as long as it's less than 400cm, the max distance of the sensor.

## **STEP 1 SETUP WIRING**
Connect Vcc to VUSB
Connect Trig to D2.
Connect Echo to D6.
Connect Gnd to Gnd.
Note: make sure the sensor is not tilted in any way because this will skew the results

## STEP 2 Create the Spreadsheet
Create a spreadsheet and give it a name.
The first column will be the device ID, followed by date and parking status. 
**change the default spreadsheet script**
click on extensions and apps script
replace the default code with the following, to publish device's ID, , the date and time the event was run in the second column, and the data (parked or not) in the third column.
If you don't want your device ID to be a column in your spreadsheet, you can go to the line that starts with var row and delete e.parameter.coreid.

function doPost(e) {

  var publishedAt = new Date(e.parameter.published_at);

  var dataArray = [];
  try {
    dataArray = JSON.parse(e.parameter.data);
  }
  catch(e) {
  }

  var sheet = SpreadsheetApp.getActiveSheet();

  var row = [e.parameter.coreid, publishedAt, e.parameter.data];

  row = row.concat(dataArray);

  sheet.appendRow(row);

  var result = {};
  result.ok = true;

  return ContentService.createTextOutput(JSON.stringify(result))
    .setMimeType(ContentService.MimeType.JSON);
}

**Publishing the Script**
In order for this code to actually work you have to publish and deploy the script.

In the upper right hand corner, click on Deploy and select New deployment.

Execute as: Set this option to me.
Who has access: set this option to Anyone.

**Click Deploy**
Web app URL: This link will be used in the next step when creating the webhook. Make sure to copy it for later use but keep it a secret, because anyone with this link will be able to make changes to your spreadsheet.

## **STEP 3 CREATE WEBHOOKS**
You are going to be making two webhooks, one that will communicate with the spreadsheet and one that will communicate with IFTTT to send the text to your phone.

**The Spreadsheet Webhook**
Go to https://console.particle.io/integrations, the Integrations tab on Particle's homepage.
Click on create new integration and select Webhook, then give the event a name.
Paste the link you copied into the URL field.
Set Request Type to Post.
Set Request Format to Web Form.

**The Text Webhook**
Follow the previous steps to create a new webhook and give the event a name. This webhook will be for triggering the text to send.
Leave the URL field blank for now, we will come back to this in the next step.

## **STEP 4 IFTTT**
Go to https://ifttt.com/create and click Add on If This.
Search up webhooks and select it.

Click on Receive a web request with a JSON payload and type in the name of your event (What you named your text webhook).

Next, click on Then That and search ClickSend Sms and select it. 
ClickSend gives you about $2 for free to begin with but then after that you have to fund your own texts. I sent exactly 70 texts before running out of money.

Click on the Send Sms action and fill out the To and From fields.
In the message field copy and paste this: Parked: {{ {{OccurredAt}}}}.
This will send a text message to your phone when the event was triggered (a parked car) as well as the date and time of when it occurred.

Go to https://ifttt.com/maker_webhooks/settings and copy the IFTTT API key which is directly after use/ in the URL.
Replace TestEvent with the name of your event and paste your API key after /key/

https://maker.ifttt.com/trigger/TestEvent/json/with/key/bCYXXXXXXXX_YfdXXXXXeV

Go back to the text webhook you created and paste your newly created link into the URL field

**Note:**
The sensor will return -1 if it reads a distance that is less than 10 centimeters because that is the minimum possible distance that the sensor can recognize (or greater than 400cm). Another reason that it could either be reading -1 or reading very inaccurate numbers is if you plugged your VCC wire into 3V instead of 5V, which is something that I am guilty of doing myself. Also make sure that you are using something solid to test with and not your hand because the ultrasonic sensor uses soundwaves to measure distance so you want something that the soundwaves can easily bounce off of. To test the sensor use something like cardboard and slide it in front of the sensor with the serial monitor up and running to see if the distance seems accurate or not. You can also measure the distance yourself with a ruler if you aren't sure if it's entirely accurate.

Appendix: Grove sensors
Grove sensors included in the IoT Starter Kit.

-Button
    Sensor Type: Digital
-Rotary angle sensor
    Sensor Type: Analog
-Ultrasonic ranger
Sensor Type: Digital
-Temperature and humidity sensor
Sensor Type: Digital
-Light sensor
Sensor Type: Analog
-Chainable LED
Sensor Type: Serial
-Buzzer
Sensor Type: Digital

-4-Digit Display
Sensor Type: Digital

