#define MAX_SIZE 50
#define TILE_SIZE 30
#define WALL_WIDTH 2.35
#define BIG_WALL 5
#define IS_WALL 1
#define NUM_COMMANDS_FORWARD 50
#define NUM_COMMANDS_TURN 50
#define NUMBER_WAIT 10

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
