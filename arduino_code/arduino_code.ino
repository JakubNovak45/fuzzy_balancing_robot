void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  float val = Serial.parseFloat();
  //apply val to motors
  //Serial.println(val);
}
