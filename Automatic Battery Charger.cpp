// Automatic Battery Charger
// Arduino UNO
// Battery voltage measured through a voltage divider

int batteryPin = A0;
int relayPin = 8;

// Voltage divider
float R1 = 30000.0;
float R2 = 7500.0;

// Charging limits for a typical 12V lead-acid battery
float startCharging = 11.5;
float stopCharging = 12.7;

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);

  // Relay OFF initially
  digitalWrite(relayPin, LOW);
}

void loop() {

  int sensorValue = analogRead(batteryPin);

  // Convert ADC value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Calculate actual battery voltage
  float batteryVoltage = voltage * ((R1 + R2) / R2);

  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage, 2);
  Serial.println(" V");

  // Automatic charging control
  if (batteryVoltage < startCharging) {

    digitalWrite(relayPin, HIGH);

    Serial.println("Battery LOW");
    Serial.println("Charger: ON");
  }

  else if (batteryVoltage >= stopCharging) {

    digitalWrite(relayPin, LOW);

    Serial.println("Battery FULL");
    Serial.println("Charger: OFF");
  }

  delay(1000);
}
