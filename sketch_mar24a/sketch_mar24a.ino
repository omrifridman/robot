#define MAX_SIZE 50
#define TILE_SIZE 30
#define WALL_WIDTH 2.35
#define BIG_WALL 5
#define IS_WALL 1
#define NUM_COMMANDS_FORWARD 50
#define NUM_COMMANDS_TURN 50
#define NUMBER_WAIT 10

const int motorPinR1 = 4;    // Motor Right IN1
const int motorPinR2 = 5;    // Motor Right IN2

const int motorPinL1 = 6;    // Motor Left IN1
const int motorPinL2 = 7;   // Motor Left IN2
int maze_level = 1;

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

void do_command(int code) {
  if(code == -1) {
    moveBackword(100)
  }
  if(code == 1) {
    moveForward(100)
  }
  else {
    moveForward(0)
  }
}

typedef struct
{
  char speed_right;
  char speed_left;
} command;

int LeftSensor = 8;
int MiddleSensor1 = 9;
int MiddleSensor2 = 10;
int RightSensor = 11;

struct point
{
  float x;
  float y;
}

struct total_state
{
  struct point position = { MAX_SIZE * TILE_SIZE, MAX_SIZE * TILE_SIZE };
  float degree = 0;
  int has_wall_up[2 * MAX_SIZE][2 * MAX_SIZE] = { 0 };
  int has_wall_right[2 * MAX_SIZE][2 * MAX_SIZE] = { 0 };
}

point* get_sensor_point_pos(total_state* my_state, float sensor_distance, float sensor_degree)
{
	float total_sensor_degree = my_state->degree + sensor_degree;
	point* new_point = malloc(sizeof(point))
	new_point->x = my_state->point.x + cos((M_PI * total_sensor_degree) / 180)
	new_point->y = my_state->point.y + sin((M_PI * total_sensor_degree) / 180)
	return new_point
}

void update_walls_array(point position)
{

}

void gather_data_sensor(float degree_from_forward, int sensor_number, float distance_forward)
{
  if (digitalRead(sensor_number) == IS_WALL)
  {
    update_walls_array(get_sensor_point_pos());
  }
}

// place in array of operations
int stage = -1;
// place in array of commands of currecnt operation
int ind = -1;
// array of commands in current operation
command* commands_waiting;
// number of commands in current operation
int number_commands = 0;
// 0 - do nothing
// 1 - move forward one step
// 2 - rotate 90 degrees left
// 3 - rotate 90 degrees right
struct total_state my_state;


// initialize commands in commands_forward and return the number of commands
int get_command_forward(command** commands_forward)
{
  *commands_forward = malloc(sizeof(command) * (NUM_COMMANDS_FORWARD + NUMBER_WAIT));
  for (int i = 0; i < NUM_COMMANDS_FORWARD; i++)
    commands_forward[0][i] = { 1, 1 };
  for (int i = 0; i < NUMBER_WAIT; i++)
    commands_forward[0][i + NUM_COMMANDS_FORWARD] = { 0, 0 };
  return NUM_COMMANDS_FORWARD + NUMBER_WAIT;
}

// initialize commands in commands_right and return the number of commands
int get_command_right(command** commands_right)
{
  *commands_forward = malloc(sizeof(command) * (NUM_COMMANDS_TURN + NUMBER_WAIT));
  for (int i = 0; i < NUM_COMMANDS_TURN; i++)
    commands_forward[0][i] = { -1, 1 };
  for (int i = 0; i < NUMBER_WAIT; i++)
    commands_forward[0][i + NUM_COMMANDS_TURN] = { 0, 0 };
  return NUM_COMMANDS_TURN + NUMBER_WAIT;
}

// initialize commands in commands_left and return the number of commands
int get_command_left(command** commands_left)
{
  *commands_forward = malloc(sizeof(command) * (NUM_COMMANDS_TURN + NUMBER_WAIT));
  for (int i = 0; i < NUM_COMMANDS_TURN; i++)
    commands_forward[0][i] = { 1, -1 };
  for (int i = 0; i < NUMBER_WAIT; i++)
    commands_forward[0][i + NUM_COMMANDS_TURN] = { 0, 0 };
  return NUM_COMMANDS_TURN + NUMBER_WAIT;
}

int get_next_commands(command** commands_waiting, int command_number)
{
  if (command_number == 1)
  {
    return get_command_forward(&commands_waiting);
  }
  if (command_number == 2)
  {
    return get_command_left(&commands_waiting);
  }
  if (command_number == 3)
  {
    return get_command_right(&commands_waiting);
  }
}

void do_command(command command_now)
{

}

void setup()
{
  my_state = struct total_state;
  pinMode(LeftSensor, INPUT);
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
  if (ind == number_commands)
  {
    stage++;
    ind = 0;

    number_commands = get_next_commands(&commands_waiting, operations[stage]);
  }
  if (commands_waiting != NULL)
  {
    do_command(commands_waiting[ind]);
    ind++;
  }
  
}
