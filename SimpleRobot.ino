/* David Gamache 7/12/2016 */
const int motor_l = 2;
const int motor_r = 4;
const int bumper = 12;
const int left_directional = 7;
const int right_directional = 8;

const int stop = 0;
const int forward = 1;
const int left = 2;
const int right = 3;

void directional (int direction)
{
  switch (direction) {
    case left:
      for (int i = 0; i < 5; i++) {
        digitalWrite(left_directional, HIGH);
        delay (1000);
        digitalWrite(left_directional, LOW);
        delay (1000);
      }
      break;
    case right:
      for (int i = 0; i < 5; i++) {
        digitalWrite(right_directional, HIGH);
        delay (500);
        digitalWrite(right_directional, LOW);
        delay (500);
      }
      break;
    default:
      Serial.println("not allowed");
      return;
  }
}

// Command the motors
void go (int direction)
{
  switch (direction) {
    case stop:
      Serial.println("stop");
      digitalWrite(motor_l, LOW);
      digitalWrite(motor_r, LOW);
      break;
    case forward:
      // Serial.println("forward");
      digitalWrite(motor_l, HIGH);
      digitalWrite(motor_r, HIGH);
      break;
    case left:
      Serial.println("left");
      digitalWrite(motor_l, LOW);
      digitalWrite(motor_r, HIGH);
      // Should turn in half a second
      directional(left);
      break;
    case right:
      Serial.println("right");
      digitalWrite(motor_l, HIGH);
      digitalWrite(motor_r, LOW);
      // Should turn in half a second
      directional(left);
      break;
    default:
      Serial.println("not allowed");
      return;
  }
}

// Check for an obstacle
bool obstacle_detected()
{
  int result = digitalRead(bumper);
  if (result == HIGH) {
    return (true);
  }

  return (false);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(motor_l, OUTPUT);
  pinMode(motor_r, OUTPUT);
  pinMode(bumper, INPUT);
  pinMode(left_directional, OUTPUT);
  pinMode(right_directional, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!obstacle_detected()) {
    // If the route is clear, roll forward
    go (forward);
  }
  else {
    // If route is not clear, stop and go left
    go (stop);
    go (left);
  }
}
