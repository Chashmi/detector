const int soundPin = A0;      // MAX9814 analog output
const int buzzerPin = 8;      // Buzzer
const int threshold = 600;    // Sensitivity threshold (adjust based on real readings)
const int checkCount = 10;    // How many readings to average
const int triggerCount = 6;   // How many readings must exceed threshold to activate

bool droneDetected = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int countAboveThreshold = 0;

  for (int i = 0; i < checkCount; i++) {
    int soundLevel = analogRead(soundPin);
    if (soundLevel > threshold) {
      countAboveThreshold++;
    }
    delay(10);
  }

  if (countAboveThreshold >= triggerCount) {
    if (!droneDetected) {
      Serial.println("Drone is detected!");
      droneDetected = true;
    }
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
    droneDetected = false;
  }
}
