#define SENSORPIN 30

int sensorState = 0, lastState=0;

void setup() {    
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT_PULLUP);     
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorState = digitalRead(SENSORPIN);

  if (sensorState && !lastState) {
    Serial.println(sensorState);

    Serial.println("Unbroken");
  } 
  if (!sensorState && lastState) {
    Serial.println(sensorState);
    Serial.println("Broken");
  }
  lastState = sensorState;
}
