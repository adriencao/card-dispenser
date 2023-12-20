void setup() {
  // put your setup code here, to run once:
  pinMode(13, INPUT); //en
  pinMode(12, OUTPUT); //in1
  pinMode(11, OUTPUT); //in2
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  analogWrite(13, 255);

  delay(1100);
  
  analogWrite(13, 0);

  delay(1000);

  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);

  analogWrite(13, 255);

  delay(1000);
}
