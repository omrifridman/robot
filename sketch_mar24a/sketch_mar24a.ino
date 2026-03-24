/*
Arduino Motor Control Code: Forward, Backward, Turn, and Stop with PWM

This code allows you to control a robot's motors to move forward, backward, turn left, turn right, and stop.
The speed of the motors is controlled using PWM (Pulse Width Modulation).

Each motor has two pins for direction control and one pin for speed control.

*/

const int motorPinR1 = 4;    // Motor Right IN1
const int motorPinR2 = 5;    // Motor Right IN2

const int motorPinL1 = 6;    // Motor Left IN1
const int motorPinL2 = 7;   // Motor Left IN2


/*
Function to control the movement of a motor (Left or Right).
direction: 1 for forward, -1 for backward, 0 to stop.
speed: The speed value (0-255) for PWM control.
*/
void moveMotor(int motorPin1, int motorPin2, int direction, int speed) {
  if (direction == 1) {  // Move forward
    digitalWrite(motorPin1, HIGH);  // Set IN1 HIGH
    digitalWrite(motorPin2, LOW);   // Set IN2 LOW
  } else if (direction == -1) {  // Move backward
    digitalWrite(motorPin1, LOW);   // Set IN1 LOW
    digitalWrite(motorPin2, HIGH);  // Set IN2 HIGH
  } else {  // Stop (direction == 0)
    digitalWrite(motorPin1, LOW);   // Set both IN1 and IN2 to LOW
    digitalWrite(motorPin2, LOW);
  }
}

/*
Move the robot forward.
Accepts speed (0-255) to set motor speed.
*/
void moveForward(int speed) {
  moveMotor(motorPinR1, motorPinR2, 1, speed);  // Move right motor forward
  moveMotor(motorPinL1, motorPinL2, 1, speed);  // Move left motor forward
}

/*
Move the robot backward.
Accepts speed (0-255) to set motor speed.
*/
void moveBackward(int speed) {
  moveMotor(motorPinR1, motorPinR2, -1, speed);  // Move right motor backward
  moveMotor(motorPinL1, motorPinL2, -1, speed);  // Move left motor backward
}

/*
Rotate the robot to the right.
Right motor moves forward, left motor moves backward.
*/
void turnRight(int speed) {
  moveMotor(motorPinR1, motorPinR2, 1, speed);   // Right motor forward
  moveMotor(motorPinL1, motorPinL2, -1, speed);  // Left motor backward
}

/*
Rotate the robot to the left.
Right motor moves backward, left motor moves forward.
*/
void turnLeft(int speed) {
  moveMotor(motorPinR1, motorPinR2, -1, speed);  // Right motor backward
  moveMotor(motorPinL1, motorPinL2, 1, speed);   // Left motor forward
}

/*
Stop both motors.
*/
void stopMotors() {
  moveMotor(motorPinR1, motorPinR2, 0, 0);  // Stop right motor (set direction to stop and speed to 0)
  moveMotor(motorPinL1, motorPinL2, 0, 0);  // Stop left motor (set direction to stop and speed to 0)
}

/*
Setup function runs once at the beginning to initialize motor pins.
*/
void setup() {
  // Initialize motor pins as OUTPUT
  pinMode(motorPinR1, OUTPUT);
  pinMode(motorPinR2, OUTPUT);

  pinMode(motorPinL1, OUTPUT);
  pinMode(motorPinL2, OUTPUT);
}

/*
Main loop function runs repeatedly to perform the robot movements.
*/
void loop() {
  // Move forward with speed 100
  moveForward(100);
  delay(2000);  // Keep moving forward for 2 seconds

  // Move backward with speed 100
  moveBackward(100);
  delay(2000);  // Keep moving backward for 2 seconds

  // Turn right with speed 100
  turnRight(100);
  delay(2000);  // Keep turning right for 2 seconds

  // Turn left with speed 100
  turnLeft(100);
  delay(2000);  // Keep turning left for 2 seconds

  // Stop both motors after completing all movements
  stopMotors();
  delay(1000);  // Wait for 1 second before starting the next iteration
}

