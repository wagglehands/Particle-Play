### connect the light sensor to the analog A0/A1 port on the grove shield

double currentLightLevel;

void setup() {
pinMode(A0, INPUT);
}

void loop() {
    
double lightAnalogVal = analogRead(A0);
currentLightLevel = map(lightAnalogVal, 0.0, 4095.0, 0.0, 100.0);

if (currentLightLevel > 50) {
    Particle.publish("light-meter/level", String(currentLightLevel),
    PRIVATE);
}

}