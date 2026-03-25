#define MAX_SIZE 50
#define TILE_SIZE 30
#define WALL_WIDTH 2.35
#define BIG_WALL 5
#define IS_WALL 1
#define NUM_COMMANDS_FORWARD 8
#define NUM_COMMANDS_BACKWARD 2
#define NUM_COMMANDS_TURN 5
#define NUMBER_WAIT 5
#define SPEED 100
#define TRIGGER_PIN  13
#define ECHO_PIN     12

const int motorPinR1 = 4;    // Motor Right IN1
const int motorPinR2 = 5;    // Motor Right IN2
bool is_third_sensor = false

const int motorPinL1 = 6;    // Motor Left IN1
const int motorPinL2 = 7;   // Motor Left IN2
int LeftSensor = 8;
int MiddleSensor1 = 10;
int MiddleSensor2 = 9;
int RightSensor = 11;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distance;

typedef struct
{
  char speed_right;
  char speed_left;
} command;

struct point
{
  float x;
  float y;
};

int operation_now = 0;
struct point position = { MAX_SIZE * TILE_SIZE, MAX_SIZE * TILE_SIZE };
float degree = 0;
int has_wall_up[2 * MAX_SIZE][2 * MAX_SIZE] = { 0 };
int has_wall_right[2 * MAX_SIZE][2 * MAX_SIZE] = { 0 };

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
  moveMotor(motorPinR1, motorPinR2, -1, speed);  // Move right motor forward
  moveMotor(motorPinL1, motorPinL2, 1, speed);  // Move left motor forward
}

/*
Move the robot backward.
Accepts speed (0-255) to set motor speed.
*/
void moveBackward(int speed) {
  moveMotor(motorPinR1, motorPinR2, 1, speed);  // Move right motor backward
  moveMotor(motorPinL1, motorPinL2, -1, speed);  // Move left motor backward
}

/*
Rotate the robot to the right.
Right motor moves forward, left motor moves backward.
*/
void turnRight(int speed) {
  moveMotor(motorPinR1, motorPinR2, -1, speed);   // Right motor forward
  moveMotor(motorPinL1, motorPinL2, -1, speed);  // Left motor backward
}

/*
Rotate the robot to the left.
Right motor moves backward, left motor moves forward.
*/
void turnLeft(int speed) {
  moveMotor(motorPinR1, motorPinR2, 1, speed);  // Right motor backward
  moveMotor(motorPinL1, motorPinL2, 1, speed);   // Left motor forward
}

point* get_sensor_point_pos(float sensor_distance, float sensor_degree)
{
	float total_sensor_degree = degree + sensor_degree;
	point* new_point = malloc(sizeof(point));
	new_point->x = position.x + cos((M_PI * total_sensor_degree) / 180);
	new_point->y = position.y + sin((M_PI * total_sensor_degree) / 180);
	return new_point;
}

void update_walls_array(point position)
{

}

void gather_data_sensor(float degree_from_forward, int sensor_number, float distance_forward)
{
  if (digitalRead(sensor_number) == IS_WALL)
  {
    //update_walls_array(get_sensor_point_pos());
  }
}

// place in array of commands of currecnt operation
int ind = 0;
// array of commands in current operation
command* commands_waiting;
// number of commands in current operation
int number_commands = 0;


// initialize commands in commands_forward and return the number of commands
int get_command_forward(command** commands_forward)
{
  *commands_forward = malloc(sizeof(command) * (NUM_COMMANDS_FORWARD));
  for (int i = 0; i < NUM_COMMANDS_FORWARD; i++)
    commands_forward[0][i] = { 1, 1 };
  return NUM_COMMANDS_FORWARD;
}

// initialize commands in commands_right and return the number of commands
int get_command_right(command** commands_right)
{
  *commands_left = malloc(sizeof(command) * (NUM_COMMANDS_TURN + NUMBER_WAIT + NUM_COMMANDS_BACKWARD));
  for (int i = 0; i < NUM_COMMANDS_BACKWARD; i++)
    commands_left[0][i] = { -1, -1 };

  for (int i = 0; i < NUMBER_WAIT; i++)
    commands_left[0][i + NUM_COMMANDS_BACKWARD] = { 0, 0 };

  for (int i = 0; i < NUM_COMMANDS_TURN; i++)
    commands_left[0][i + NUM_COMMANDS_BACKWARD + NUMBER_WAIT] = { -1, 1 };
  return NUM_COMMANDS_TURN + NUMBER_WAIT + NUM_COMMANDS_BACKWARD;
}

// initialize commands in commands_left and return the number of commands
int get_command_left(command** commands_left)
{
  *commands_left = malloc(sizeof(command) * (NUM_COMMANDS_TURN + NUMBER_WAIT + NUM_COMMANDS_BACKWARD));
  for (int i = 0; i < NUM_COMMANDS_BACKWARD; i++)
    commands_left[0][i] = { -1, -1 };

  for (int i = 0; i < NUMBER_WAIT; i++)
    commands_left[0][i + NUM_COMMANDS_BACKWARD] = { 0, 0 };

  for (int i = 0; i < NUM_COMMANDS_TURN; i++)
    commands_left[0][i + NUM_COMMANDS_BACKWARD + NUMBER_WAIT] = { 1, -1 };
  return NUM_COMMANDS_TURN + NUMBER_WAIT + NUM_COMMANDS_BACKWARD;
}

// initialize commands in commands_left and return the number of commands
int get_command_back_to_right(command** commands_left)
{
  *commands_left = malloc(sizeof(command) * (NUM_COMMANDS_TURN + NUM_COMMANDS_BACKWARD + NUMBER_WAIT * 2));
  for (int i = 0; i < NUM_COMMANDS_BACKWARD; i++)
    commands_left[0][i] = { -1, -1 };
  for (int i = 0; i < NUMBER_WAIT; i++)
    commands_left[0][i + NUM_COMMANDS_BACKWARD] = { 0, 0 };
  for (int i = 0; i < NUM_COMMANDS_TURN; i++)
    commands_left[0][i + NUM_COMMANDS_BACKWARD + NUMBER_WAIT] = { -1, -1 };
  for (int i = 0; i < NUMBER_WAIT; i++)
    commands_left[0][i + NUM_COMMANDS_TURN + NUM_COMMANDS_BACKWARD + NUMBER_WAIT] = { 0, 0 };
  return NUM_COMMANDS_TURN + NUMBER_WAIT;
}

int get_next_commands(command** commands_waiting, int command_number)
{
  if (command_number == 1)
  {
    return get_command_forward(commands_waiting);
  }
  if (command_number == 2)
  {
    return get_command_left(commands_waiting);
  }
  if (command_number == 3)
  {
    return get_command_right(commands_waiting);
  }
  if (command_number == 4)
  {
    return get_command_back_to_right(commands_waiting);
  }
}

void do_command(command command_now)
{
    if(command_now.speed_right == -1) {
        moveMotor(motorPinR1, motorPinR2, 1, SPEED);
    }
    if(command_now.speed_right == 1) {
        moveMotor(motorPinR1, motorPinR2, -1, SPEED);
    }
    if(command_now.speed_right == 0) {
        moveMotor(motorPinR1, motorPinR2, 0, SPEED);
    }
    if(command_now.speed_left == -1) {
        moveMotor(motorPinL1, motorPinL2, -1, SPEED);
    }
    if(command_now.speed_left == 1) {
      moveMotor(motorPinL1, motorPinL2, 1, SPEED);
    }
    if(command_now.speed_right == 0) {
        moveMotor(motorPinL1, motorPinL2, 0, SPEED);
    }
}

// 0 - do nothing
// 1 - move forward one step
// 2 - rotate x degrees left
// 3 - rotate x degrees right
// 4 - go back and after rotate x degrees right
int get_next_operation()
{
  if (is_third_sensor && digitalRead(MiddleSensor1) == 0 && digitalRead(MiddleSensor2) == 0 && digitalRead(RightSensor) == 0)
  {
    return 3;
  }
  else if (digitalRead(MiddleSensor1) == 0 && digitalRead(MiddleSensor2) == 0)
  {
    return 1;
  }
  else if (digitalRead(MiddleSensor1) == 0 && digitalRead(MiddleSensor2) != 0)
  {
    return 2;
  }
  else if (digitalRead(MiddleSensor1) != 0 && digitalRead(MiddleSensor2) == 0)
  {
    return 3;
  }
  else if (digitalRead(MiddleSensor1) != 0 && digitalRead(MiddleSensor2) != 0)
  {
    return 3; // 4
  }
}

void setup()
{
  Serial.begin(9600);
  //pinMode(LeftSensor, INPUT);
  pinMode(MiddleSensor1, INPUT);
  pinMode(MiddleSensor2, INPUT);
  pinMode(RightSensor, INPUT);
}

void loop()
{
  //gather_data_sensor(, LeftSensor, );
  //gather_data_sensor(, MiddleSensor1, );
  //gather_data_sensor(, MiddleSensor2, );
  //gather_data_sensor(, RightSensor, );

  distance = sonar.ping_cm();
  
  // Send results to Serial Monitor
  Serial.print("Distance = ");
  if (distance <= 10) {
    Serial.println("Out of range");
    terminate();
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  int next_operation = get_next_operation();

  if ((operation_now == 1 && operation_now != next_operation) || ind == number_commands)
  {
    free(commands_waiting);
    if (operation_now != next_operation)
    {
      command command_stop = { 0, 0 };
      do_command(command_stop);
      delay(NUMBER_WAIT);
    }
    ind = 0;
    Serial.print("Next op: ");
    operation_now = next_operation;
    Serial.println(operation_now);
    number_commands = get_next_commands(&commands_waiting, operation_now);
  }
  if (commands_waiting != NULL)
  {
    Serial.print("In commands waiting");
    do_command(commands_waiting[ind]);
    ind++;
  }
  
}
