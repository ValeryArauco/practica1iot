const int PIN_GREEN = 12;
const int PIN_YELLOW = 14;
const int PIN_RED = 27;
const long MIN_DISTANCE = 2;
const long MAX_DISTANCE = 100;




class LED {
  private:
    int pin;




  public:
    LED(int pin) : pin(pin) {
      pinMode(pin, OUTPUT);
    }




    void turnOn() {
      digitalWrite(pin, HIGH);
    }




    void turnOff() {
      digitalWrite(pin, LOW);
    }




    void blink() {
      turnOn();
      delay(500);
      turnOff();
      delay(500);
    }
};




class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;




  public:
    UltrasonicSensor(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin) {}




    double readUltrasonicDistance() {
      pinMode(triggerPin, OUTPUT);  // Clear the trigger
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      // Sets the trigger pin to HIGH state for 10 microseconds
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      pinMode(echoPin, INPUT);
      // Reads the echo pin, and returns the sound wave travel time in microseconds
      return 0.01723 * pulseIn(echoPin, HIGH);
    }
};








void manageLEDs(long distance, LED& red, LED& yellow, LED& green) {
  if (distance >= MIN_DISTANCE &&  distance <= 15) {
    red.blink();
    yellow.turnOff();
    green.turnOff();
  } else if (distance > 15 && distance <= 43) {
    red.turnOn();
    yellow.turnOff();
    green.turnOff();
  } else if (distance > 43 && distance <= 71) {
    red.turnOff();
    yellow.turnOn();
    green.turnOff();
  } else if (distance > 71 && distance <= MAX_DISTANCE) {
    red.turnOff();
    yellow.turnOff();
    green.turnOn();
  }
  else
  {
    red.turnOff();
    yellow.turnOff();
    green.turnOff();
  }
}




void setup() {
  Serial.begin(9600);
}




void loop() {
  UltrasonicSensor sensor(25, 26);
  LED red(PIN_RED), yellow(PIN_YELLOW), green(PIN_GREEN);
  double distance = sensor.readUltrasonicDistance();
  Serial.print(distance);
  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
  manageLEDs(distance, red, yellow, green);
}