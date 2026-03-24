#define MAX_SIZE 50
#define IS_WALL 1

struct command
{
  bool active_command;
  char speed_right;
  char speed_left;
};

int LeftSensor = 8;
int MiddleSensor1 = 9;
int MiddleSensor2 = 10;
int RightSensor = 11;
int mazeLevel = 0;

struct point
{
  float x;
  float y;
}

struct total_state
{
  struct point position;
  float degree;
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



void gather_data_sensor(float degree_from_forward, int sensor_number, float distance_forward)
{
  if (digitalRead(sensor_number) == IS_WALL)
  {
    
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
int operations[10];


// initialize commands in commands_forward and return the number of commands
int get_command_forward(command** commands_forward)
{

}

// initialize commands in commands_right and return the number of commands
int get_command_right(command** commands_right)
{

}

// initialize commands in commands_left and return the number of commands
int get_command_left(command** commands_left)
{

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

void setup() {
  // put your setup code here, to run once:
  pinMode(LeftSensor, INPUT);
  pinMode(MiddleSensor1, INPUT);
  pinMode(MiddleSensor2, INPUT);
  pinMode(RightSensor, INPUT);
  Serial.begin(9600);

  if (mazeLevel == 0)
  {
    operations = [1, 1, 3, 1];
  }
  else if (mazeLevel == 1)
  {
    operations = [1, 2, 1, 3, 1, 2, 1, 2, 1, 1, 2, 1];
  }
  else
  {
    operations = [1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 1];
  }



}

void loop() {
  // put your main code here, to run repeatedly:
  gather_data_sensor(, LeftSensor, );
  gather_data_sensor(, MiddleSensor1, );
  gather_data_sensor(, MiddleSensor2, );
  gather_data_sensor(, RightSensor, );
  Serial.print(state_left, HEX);
  if (ind == number_commands)
  {
    stage++;
    ind = 0
    number_commands = get_next_commands(commands_waiting, operations[stage]);
  }
  if (commands_waiting != NULL)
  {
    do_command(commands_waiting[ind]);
    ind++;
  }
  
  Serial.println();
}
