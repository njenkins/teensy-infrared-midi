int proximitySensorValue;
int proximitySensorLag;

void setup() {
  pinMode(0, INPUT_PULLUP); // Switch for bank
  pinMode(3, INPUT_PULLUP); // Lock for channel 0
  pinMode(8, INPUT_PULLUP); //Lock for channel 1
  
  // MIDI rate
  Serial.begin(31250);
}

void loop() {
  //read current proximity sensor value
  proximitySensorValue = analogRead(0);
if(digitalRead(0) == HIGH){
  Serial.println("Bank Switch is OFF");//For debugging
  if(digitalRead(3) == LOW){
    playCCMode(proximitySensorValue, 0);
  }
}
else {
    Serial.println("Bank Switch is ONN"); //For debugging
    if(digitalRead(8) == LOW){
      playCCMode(proximitySensorValue, 1);  
    }
  }
  
}


void playCCMode(int sensorValue, int control){
  int ccValue;
  // if difference is greater than 5...//Magic figure that seems to ignore unintended noise
  //from proximity sensor. Change to whatever works for you
  if (abs(sensorValue - proximitySensorLag) > 5){
    
    // calc the CC value based on the raw value
    ccValue = sensorValue/8; // 1023 / 8 to create midi value between 0 - 127
    
    Serial.println(ccValue);//For debugging
    usbMIDI.sendControlChange(control, ccValue, 1);
    proximitySensorLag = sensorValue;
  }
  delay(10); // limits MIDI messages to reasonable number
}
