#define MAX_SIZE 50

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

class total_state
{
  float position_x;
  float position_y;
  float degree;
  int has_wall_up[2 * MAX_SIZE][2 * MAX_SIZE] = { 0 };
  int has_wall_right[2 * MAX_SIZE][2 * MAX_SIZE] = { 0 };
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
  int state_left = digitalRead(LeftSensor);
  int state_middle1 = digitalRead(MiddleSensor1);
  int state_middle2 = digitalRead(MiddleSensor2);
  int state_right = digitalRead(RightSensor);
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
