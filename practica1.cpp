const int PIN_GREEN = 12;
const int PIN_YELLOW = 14;
const int PIN_RED = 27;
const long MIN_DISTANCE = 2;
const long MAX_DISTANCE = 400;

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

    long readUltrasonicDistance() {
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
  red.turnOff();
  yellow.turnOff();
  green.turnOff();

  if (distance >= MIN_DISTANCE &&  distance <= 20) {
    red.blink();
  } else if (distance > 20 && distance <= 132) {
    red.turnOn();
  } else if (distance > 132 && distance <= 265) {
    yellow.turnOn();
  } else if (distance > 265 && distance <= MAX_DISTANCE) {
    green.turnOn();
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  UltrasonicSensor sensor(25, 26);
  LED red(PIN_RED), yellow(PIN_YELLOW), green(PIN_GREEN);
  long distance = sensor.readUltrasonicDistance();

  manageLEDs(distance, red, yellow, green);

  delay(400);
}
