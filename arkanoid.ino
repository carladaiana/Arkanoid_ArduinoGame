#include <Arduino.h>
#include <MaxMatrix.h>
#include <avr/pgmspace.h>

#define NO_OF_LEVELS 3 

const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;

char smile[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10010101,
                  B10100001,
                  B10100001,
                  B10010101,
                  B01000010,
                  B00111100
                 };

PROGMEM const unsigned char LEVELS[] = {
                //level 1
                  B00000000,
                  B01111110,
                  B01111110,
                  B00000000,
                  B00000000,
                  B00000000,
                  B00000000,
                  B00000000,
                //level 2
                  B10101010,
                  B01010101,
                  B10101010,
                  B00000000,
                  B00000000,
                  B00000000,
                  B00000000,
                  B00000000,
                //level 3
                  B10001111,
                  B11000111,
                  B11100011,
                  B11110001,
                  B00000000,
                  B00000000,
                  B00000000,
                  B00000000
};

PROGMEM const unsigned char CH[] = {
  3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
  1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
  3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
  5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
  4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
  5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
  5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
  1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
  3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
  3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
  5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
  5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
  2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
  4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
  2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
  4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
  3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
  4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
  4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
  4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
  4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
  4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
  4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
  4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
  4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
  2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
  2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
  3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
  3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
  3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
  4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
  5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
  4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
  4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
  4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
  4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
  4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
  4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
  4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
  4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
  3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
  4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
  4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
  4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
  5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
  5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
  4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
  4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
  4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
  4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
  5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
  4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
  5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
  5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
  5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
  5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
  4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
  2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
  4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
  2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
  3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
  4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
  2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
  4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
  4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
  4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
  4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
  4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
  3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
  4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
  4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
  3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
  4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
  4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
  3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
  5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
  4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
  4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
  4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
  4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
  4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
  4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
  3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
  4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
  5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
  5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
  5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
  4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
  3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
  3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
  1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
  3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
  4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};

int DIN = 7;   // DIN pin of MAX7219 module
int CLK = 6;   // CLK pin of MAX7219 module
int CS = 5;    // CS pin of MAX7219 module
int maxInUse = 1;

MaxMatrix m(DIN, CS, CLK, maxInUse);

byte buffer[10];
unsigned long previousMillis = 0; 
const long interval = 200; 
void(*resetFunc)(void) = 0;

typedef struct {
  int x, y;
} point_t;

point_t ball;
point_t pad[2];
char bricks[8][8];
enum Direction {U, U_R, R_D, D, D_L, L_U};
Direction currentDirection;
int level;
int activeBricks;

void activateBrick(int x, int y);
void deactivateBrick(int x, int y);
void bricksSetup(int level);
void setBall(int x, int y);
void setPad(int x, int y);
void movePadRight();
void movePadLeft();
void moveBall(Direction direction);
void gameOver();
point_t getNextPosition();
Direction getNextDirection(point_t nextPosition);
void victory();
void nextLevel();
void setup();
void loop();
void serialEvent();

void activateBrick(int x, int y) {
  bricks[x][y] = '1';
  m.setDot(y, x, true);
  ++activeBricks;
}

void deactivateBrick(int x, int y) {
  bricks[x][y] = '0';
  m.setDot(y, x, false);
  --activeBricks;
}

void bricksSetup(int level) {
  int i, j;
  memcpy_P(buffer, LEVELS + 8*(level - 1), 8);
  m.clear();
  activeBricks = 0;
  for(i = 0; i < 8; ++i) {
    for(j = 0; j < 8; ++j)
      if((buffer[i] & (1 << j)) != 0) 
        activateBrick(i, 7 - j);                
      else 
        bricks[i][7 - j] = '0';     
  }
}

void setBall(int x, int y) {
  if(x >= 0 && x <= 7 && y >= 0 && y <= 7) {
    //erase current ball
    m.setDot(ball.y,ball.x,false);
    //set new coordinates
    ball.x = x; 
    ball.y = y;
    m.setDot(ball.y,ball.x,true);
  }
}

void setPad(int x, int y) {
  if(x >= 0 && x <= 7 && y >= 0 && y < 7) {
    //erase current pad
    m.setDot(pad[0].y,pad[0].x,false);
    m.setDot(pad[1].y,pad[1].x,false);
    
    //set new coordinates
    pad[0].x = x; pad[1].x = x; 
    pad[0].y = y; pad[1].y = y + 1; 
    m.setDot(pad[0].y,pad[0].x,true);
    m.setDot(pad[1].y,pad[1].x,true);
    
  }
}

void movePadRight() {
  setPad(pad[0].x, pad[0].y + 1);
}

void movePadLeft() {
  setPad(pad[0].x, pad[0].y - 1);
}

//move ball one step in a certain direction
void moveBall(Direction direction) {
  switch(direction) {
    case U: setBall(ball.x - 1, ball.y); break;
    case U_R: setBall(ball.x - 1, ball.y + 1); break;
    case R_D: setBall(ball.x + 1, ball.y + 1); break;
    case D: setBall(ball.x + 1, ball.y); break;
    case D_L: setBall(ball.x + 1, ball.y - 1); break;
    case L_U: setBall(ball.x - 1, ball.y - 1); break;
  }
}

void gameOver() {
  int i;
  m.writeSprite(0, 0, smile);
  delay(2000);
  resetFunc();
}

point_t getNextPosition() {
  point_t nextPosition;
  nextPosition.x = ball.x;
  nextPosition.y = ball.y;
  
  switch(currentDirection) {
    case U: --nextPosition.x; break;
    case U_R: --nextPosition.x; ++nextPosition.y; break;
    case R_D: ++nextPosition.x; ++nextPosition.y; break;
    case D: ++nextPosition.x; break;
    case D_L: ++nextPosition.x; --nextPosition.y; break;    
    case L_U: --nextPosition.x; --nextPosition.y; break;
  }
  
  return nextPosition;
}

Direction getNextDirection(point_t nextPosition) {
  if(nextPosition.x > 7)
    gameOver();
  if(nextPosition.y < 0) {
    switch(currentDirection) {
      case D_L: return R_D; 
      case L_U: return U_R; 
    }
  }
  else
  if(nextPosition.y > 7) {
    switch(currentDirection) {
      case R_D: return D_L; 
      case U_R: return L_U; 
    }
  }
  else
  if(nextPosition.x < 0) {
    switch(currentDirection) {
      case U: return D; 
      case U_R: return R_D; 
      case L_U: return D_L; 
    }  
  }
  else
  if(nextPosition.x == pad[0].x && nextPosition.y == pad[0].y) {
    switch(currentDirection) {
      case R_D: return L_U; 
      case D: return L_U; 
      case D_L: return L_U; 
    }
  }
  else
  if(nextPosition.x == pad[0].x && nextPosition.y == pad[0].y - 1) {
    switch(currentDirection) {
      case R_D: gameOver(); 
      case D: gameOver(); 
      case D_L: return L_U; 
    }
  }
  else
  if(nextPosition.x == pad[1].x && nextPosition.y == pad[1].y) {
    switch(currentDirection) {
      case R_D: return U_R; 
      case D: return U_R; 
      case D_L: return U_R;
    }
  }
  if(nextPosition.x == pad[1].x && nextPosition.y == pad[1].y + 1) {
    switch(currentDirection) {
      case R_D: return U_R; 
      case D: gameOver(); 
      case D_L: gameOver(); 
    }
  }
  
  else {
    switch(currentDirection) {
      case U:
        if(bricks[nextPosition.x][nextPosition.y] == '0')
          return currentDirection;
        deactivateBrick(nextPosition.x, nextPosition.y);
        return D;
      case U_R:
          if(bricks[nextPosition.x][nextPosition.y] == '0' && bricks[nextPosition.x][nextPosition.y - 1] == '0' && bricks[nextPosition.x + 1][nextPosition.y] == '0')
            return currentDirection;        
            
          if(bricks[nextPosition.x + 1][nextPosition.y] == '1') {
          
            if(bricks[nextPosition.x][nextPosition.y - 1] == '1') {
              deactivateBrick(nextPosition.x + 1, nextPosition.y);
              deactivateBrick(nextPosition.x, nextPosition.y - 1);
              return D_L;
            }
            else {
              deactivateBrick(nextPosition.x + 1, nextPosition.y);
              return L_U;
            }
          }  
          else {
            
            if(bricks[nextPosition.x][nextPosition.y - 1] == '1') {
              deactivateBrick(nextPosition.x, nextPosition.y - 1);
              return R_D;
            }
            else {
              deactivateBrick(nextPosition.x, nextPosition.y);
              return D_L;
            }
         }
      case R_D: 
          if(bricks[nextPosition.x][nextPosition.y] == '0' && bricks[nextPosition.x][nextPosition.y - 1] == '0' && bricks[nextPosition.x - 1][nextPosition.y] == '0')
            return currentDirection;
            
          if(bricks[nextPosition.x - 1][nextPosition.y] == '1') {
          
            if(bricks[nextPosition.x][nextPosition.y - 1] == '1') {
              deactivateBrick(nextPosition.x - 1, nextPosition.y);
              deactivateBrick(nextPosition.x, nextPosition.y - 1);
              return L_U;
            }
            else {
              deactivateBrick(nextPosition.x - 1, nextPosition.y);
              return D_L;
            }
          }
          else {
          
            if(bricks[nextPosition.x][nextPosition.y - 1] == '1') {
              deactivateBrick(nextPosition.x, nextPosition.y - 1);
              return U_R;
            }
            else {
              deactivateBrick(nextPosition.x, nextPosition.y);
              return L_U;
            }
         }
            
      case D: 
        if(bricks[nextPosition.x][nextPosition.y] == '0')
          return currentDirection;
        deactivateBrick(nextPosition.x, nextPosition.y);
        return U; break;
      
      case D_L: 
          if(bricks[nextPosition.x][nextPosition.y] == '0' && bricks[nextPosition.x][nextPosition.y + 1] == '0' && bricks[nextPosition.x - 1][nextPosition.y] == '0')
            return currentDirection;
            
          if(bricks[nextPosition.x - 1][nextPosition.y] == '1') {
            
            if(bricks[nextPosition.x][nextPosition.y + 1] == '1') {
              deactivateBrick(nextPosition.x - 1, nextPosition.y);
              deactivateBrick(nextPosition.x, nextPosition.y + 1);
              return U_R;
            }
            else {
              deactivateBrick(nextPosition.x - 1, nextPosition.y);
              return R_D;
            }
          }
          else {
            
            if(bricks[nextPosition.x][nextPosition.y + 1] == '1') {
              deactivateBrick(nextPosition.x, nextPosition.y + 1);
              return L_U;
            }
            else {
              deactivateBrick(nextPosition.x, nextPosition.y);
              return U_R;
            }
          }
               
      case L_U: 
          if(bricks[nextPosition.x][nextPosition.y] == '0' && bricks[nextPosition.x][nextPosition.y + 1] == '0' && bricks[nextPosition.x + 1][nextPosition.y] == '0')
            return currentDirection;
            
          if(bricks[nextPosition.x + 1][nextPosition.y] == '1') {
            
            if(bricks[nextPosition.x][nextPosition.y + 1] == '1') {
              deactivateBrick(nextPosition.x + 1, nextPosition.y);
              deactivateBrick(nextPosition.x, nextPosition.y + 1);
              return R_D;
            }
            else {
              deactivateBrick(nextPosition.x + 1, nextPosition.y);
              return U_R;
            }
          }
          else 
            if(bricks[nextPosition.x][nextPosition.y + 1] == '1') {
              deactivateBrick(nextPosition.x, nextPosition.y + 1);
              return D_L;
            }
            else {
              deactivateBrick(nextPosition.x, nextPosition.y);
              return R_D;
            }  
    }
  }
}

void victory() {
  int i;
  char text[]= "Congratulations! :)   "; 
  printStringWithShift(text, 100); 
  delay(1000);
  //resetFunc();
}

void nextLevel() {
  ++level;
  if(level == NO_OF_LEVELS + 1)
    victory();
  m.clear();  
  memcpy_P(buffer, CH + 7 * (16 + level), 7);
  m.writeSprite(2, 1, buffer); // (text, scrolling speed)
  delay(1000);

  bricksSetup(level);
  
  setPad(7, 1);
  setBall(pad[0].x - 2, pad[0].y);
  currentDirection = D;
  delay(1000);
}

void setup() {
  m.init(); // MAX7219 initialization
  m.setIntensity(4); // initial led matrix intensity, 0-15
  //Serial.begin(9600); 
  
  pinMode(buttonPin1, INPUT); // the pushbutton pin is initialized as an input
  pinMode(buttonPin2, INPUT);

  level = 0;
  activeBricks = 0;
}

void loop() {
  unsigned long currentMillis = millis();
  //move ball after each interval
  if(activeBricks == 0)
    nextLevel();
    
  if(currentMillis - previousMillis >= interval) {
    //change ball direction based on its next position
    point_t nextPosition;
    Direction nextDirection;

    while(1) {
      nextPosition = getNextPosition();
      nextDirection = getNextDirection(nextPosition);
      if(nextDirection == currentDirection)
        break;
      currentDirection = nextDirection;
    }
    
    moveBall(currentDirection);
 
    previousMillis = currentMillis;
  }

   // read the state of the pushbutton value
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH
    if (buttonState1 == HIGH) {
      delay(150);
      movePadRight();
    } 
    
    if (buttonState2 == HIGH) {
      delay(150);
      movePadLeft();
    }  

  
}

void printCharWithShift(char c, int shift_speed) {
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7 * c, 7);
  m.writeSprite(32, 0, buffer);
  m.setColumn(32 + buffer[0], 0);
  for (int i = 0; i < buffer[0] + 1; i++)
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}
// Extract the characters from the text string
void printStringWithShift(char* s, int shift_speed) {
  while (*s != 0) {
    printCharWithShift(*s, shift_speed);
    s++;
  }
}


// Function used if commands are sent from the computer
/*void serialEvent()
{
   while(Serial.available()) 
   {
      char ch = Serial.read();
      Serial.write(ch);

      if (ch == '/')       
        movePadRight();
      else
      if (ch == 'z')
        movePadLeft();
      else 
      if (ch == 'r')
         resetFunc();
   }
}*/


