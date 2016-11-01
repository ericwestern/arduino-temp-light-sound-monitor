const int piezo = A0;
const int temp = A1;
const int photo = A2;

const unsigned long thirtyMinutes = 30 * 60 * 1000UL; //30 minutes in ms
const double photoVoltConversion = 0.0048828125; //5 volts / 1024 possible values from sensor

int piezoValue = 0;
float tempValue = 0;
double photoValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  piezoValue = analogRead(piezo);
  delay(10);
  tempValue = analogRead(temp);
  delay(10);
  photoValue = analogRead(photo);

  double photoVout = photoValue * photoVoltConversion;
  int lux = 500/(10 * ((5-photoVout) / photoVout)); //conversion to lux, assumes 10 kOhm resistor at bottom of voltage divider
    
  float voltage = (tempValue/1024.0) * 5.0;
  float temperature = ((voltage - 0.5) * 100) * (9.0/5.0) + 32.0;
  
  String currStatus = "Temp: " + (String)temperature + "F, Lights: " + (String)lux + "lx, Sound level: " + (String)piezoValue + ".";
  Serial.println(currStatus);

  delay(thirtyMinutes);  
}
