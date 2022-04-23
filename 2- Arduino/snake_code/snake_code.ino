const int Button_Up = 7;
const int Button_Down = 5;
const int Button_Left = 6;
const int Button_Right = 8;

const int Buzzer = 9;

const int Matrix_CLK = 4;
const int Matrix_CS = 3;
const int Matrix_DIN = 2;

const int Matrix_Brightness = 8;
const int initialSnakeLength = 3;

int snakeLength = initialSnakeLength;
int snakeSpeed = 200;
int snakeDirection = 0;

#include "LedControl.h"

int gameboard[8][8] = {};

LedControl matrix(Matrix_DIN,Matrix_CLK,Matrix_CS,1);

bool win = false;
bool gameOver = false;

int snake_row = -1;
int snake_col = -1;
int food_row = -1;
int food_col = -1;

const int up = 1;
const int right = 2;
const int down = 3;
const int left = 4;

void setup() 
{
  initialize();
  sound_device_initialize();
  
}

void initialize() {
  pinMode(Button_Up, INPUT_PULLUP);
  pinMode(Button_Down, INPUT_PULLUP);
  pinMode(Button_Right, INPUT_PULLUP);
  pinMode(Button_Left, INPUT_PULLUP);

  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);

  matrix.shutdown(0, false);
  matrix.setIntensity(0, Matrix_Brightness);
  matrix.clearDisplay(0);

  randomSeed(analogRead(A5));
  snake_row = random(8);
  snake_col = random(8);
}

void generateFood() {
  if (food_row == -1 || food_col == -1) {
    if (snakeLength >= 64) {
      win = true;
      return;
    }
    while (gameboard[food_row][food_col] > 0) {
      food_col = random(8);
      food_row = random(8);
    }
  }
}

void scanButtons() {
  int previousDirection = snakeDirection;
  long timestamp = millis();
  while (millis() < timestamp + snakeSpeed) {
    if (digitalRead(Button_Up) == false) snakeDirection = up;
    else if (digitalRead(Button_Right) == false) snakeDirection = right;
    else if (digitalRead(Button_Down) == false) snakeDirection = down;
    else if (digitalRead(Button_Left) == false) snakeDirection = left; 
    
    if (snakeDirection + 2 == previousDirection && previousDirection != 0)
    snakeDirection = previousDirection;
    if (snakeDirection - 2 == previousDirection && previousDirection != 0)
    snakeDirection = previousDirection;

    if (millis() % 100 < 50)
    matrix.setLed(0, food_row, food_col, 1);
    else
    matrix.setLed(0, food_row, food_col, 0);
  }
    
}

void calculateSnake() {
  switch (snakeDirection) {
    
    case up:
    snake_row--;
    fixEdge();
    matrix.setLed(0, snake_row, snake_col, 1);
    break;

    case right:
    snake_col++;
    fixEdge();
    matrix.setLed(0, snake_row, snake_col, 1);
    break;

    case down:
    snake_row++;
    fixEdge();
    matrix.setLed(0, snake_row, snake_col, 1);
    break;

    case left:
    snake_col--;
    fixEdge();
    matrix.setLed(0, snake_row, snake_col, 1);
    break;

    default:
    return;
  }
  
  if (gameboard[snake_row][snake_col] > 1 && snakeDirection != 0) {
    gameOver = true;
    return;
  }

  if (snake_row == food_row && snake_col == food_col) {
    food_row = -1;
    food_col = -1;
    snakeLength++;
    gameboard[snake_row][snake_col] = snakeLength;
  }
  else{ // bütün sayıları bir sıra kaydır
    gameboard[snake_row][snake_col] = snakeLength +1; //

    //reduce previous numbers  
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        //reduce previous numbers
        if (gameboard[row][col] > 0 ) gameboard[row][col]--;

        //display the current pixel
        if (gameboard[row][col] == 0) matrix.setLed(0, row, col, 0);
      }
           
    }
  }
}



void fixEdge() {
  if (snake_col < 0) snake_col += 8;
  if (snake_col > 7) snake_col -= 8;
  if (snake_row < 0) snake_row += 8;
  if (snake_row > 7) snake_row -= 8;
}

void sound_win() {
    tone(Buzzer,200,400); //buzzer, kaç Hz, ne kadar çalsın
    delay(200); // gecikme
    tone(Buzzer,400,400);
    delay(200);
    tone(Buzzer,600,400);
    delay(200);
}

void sound_device_initialize() {
    tone(Buzzer,200,400); //buzzer, kaç Hz, ne kadar çalsın
    delay(200); // gecikme
    tone(Buzzer,400,400);
    delay(200);
    tone(Buzzer,600,400);
    delay(200);
}

void sound_game_over() {
    tone(Buzzer,200,400); //buzzer, kaç Hz, ne kadar çalsın
    delay(200); // gecikme
    tone(Buzzer,400,400);
    delay(200);
    tone(Buzzer,600,400);
    delay(200);
}

void sound_start_again() {
    tone(Buzzer,200,400); //buzzer, kaç Hz, ne kadar çalsın
    delay(200); // gecikme
    tone(Buzzer,400,400);
    delay(200);
    tone(Buzzer,600,400);
    delay(200);
}

void handleGameStates() {
  if (gameOver) {
    sound_game_over();

    win = false;
    gameOver = false;
    snake_row = -1;
    snake_col = -1;
    snakeLength = initialSnakeLength;
    snakeDirection = 0;
    memset(gameboard, 0, sizeof(gameboard));
    matrix.clearDisplay(0);
    sound_start_again;

    if (win) {
    sound_win();

    win = false;
    gameOver = false;
    snake_row = -1;
    snake_col = -1;
    snakeLength = initialSnakeLength;
    snakeDirection = 0;
    memset(gameboard, 0, sizeof(gameboard));
    matrix.clearDisplay(0);
    sound_start_again;

  }
 }
}


void loop() {
  // put your main code here, to run repeatedly:
  generateFood();
  scanButtons();
  calculateSnake();
  handleGameStates();
}
