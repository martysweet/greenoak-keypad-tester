#include <Arduino.h>

#define COLUMN1 2
#define COLUMN2 3
#define COLUMN3 4
#define COLUMN4 5

#define ROW3R A0
#define ROW3L A1
#define ROW2R A2
#define ROW2L A3
#define ROW1R A4
#define ROW1L A5

void readRow(char*, int);
int* readColumn();
void resetAllColumns();

// Allow for switching between pullup/floating
int triggerColumnState = LOW;
int unusedColumnState = HIGH;
int pressedState = LOW;


void setup() {
  Serial.begin(115200);

  // Setup the column pins as outputs
  pinMode(COLUMN1, OUTPUT);
  pinMode(COLUMN2, OUTPUT);
  pinMode(COLUMN3, OUTPUT);
  pinMode(COLUMN4, OUTPUT);

  // Setup the row pins as inputs
  int pullupToggle = INPUT;
  if(triggerColumnState == LOW){
    pullupToggle = INPUT_PULLUP;
  }

  pinMode(ROW1L, pullupToggle);
  pinMode(ROW1R, pullupToggle);
  pinMode(ROW2L, pullupToggle);
  pinMode(ROW2R, pullupToggle);
  pinMode(ROW3L, pullupToggle);
  pinMode(ROW3R, pullupToggle);


  resetAllColumns();

  Serial.println("Startup Complete");
}



int count = 0;
int status[3][8] = {0}; // Row 0, 1, 2, // Column 0-7
int* switches;

void loop() {
  count++;


  int offset = 0;
  int switchInc = 0;

  // Column 1
  digitalWrite(COLUMN1, triggerColumnState);
  switches = readColumn();
  offset = 0;
  switchInc = 0;
  for(int r = 0; r<3; r++){
    status[r][offset] = switches[switchInc++];
    status[r][offset+1] = switches[switchInc++];
  }
  resetAllColumns();


  // Column 2
  digitalWrite(COLUMN2, triggerColumnState);
  switches = readColumn();
  offset = 2;
  switchInc = 0;
  for(int r = 0; r<3; r++){
    status[r][offset] = switches[switchInc++];
    status[r][offset+1] = switches[switchInc++];
  }
  resetAllColumns();


  // Column 3
  digitalWrite(COLUMN3, triggerColumnState);
  switches = readColumn();
  offset = 4;
  switchInc = 0;
  for(int r = 0; r<3; r++){
    status[r][offset] = switches[switchInc++];
    status[r][offset+1] = switches[switchInc++];
  }
  resetAllColumns();


  // Column 4
  digitalWrite(COLUMN4, triggerColumnState);
  switches = readColumn();
  offset = 6;
  switchInc = 0;
  for(int r = 0; r<3; r++){
    status[r][offset] = switches[switchInc++];
    status[r][offset+1] = switches[switchInc++];
  }
  resetAllColumns();



  // Clear screen and display the current status Array
  // Use minicom for this functionality: minicom -b115200 -D /dev/ttyACM0
  Serial.println("\033[0H\033[0J-------------------------");
  for(int r=0; r<3; r++){
    for(int c=0; c<8; c++){
      if(status[r][c] == LOW){
        Serial.print(" X ");
      }else{
        Serial.print(" O ");
      }
    }
    Serial.println("");
  }
  Serial.println("-------------------------");

}

void resetAllColumns(){
  digitalWrite(COLUMN1, unusedColumnState);
  digitalWrite(COLUMN2, unusedColumnState);
  digitalWrite(COLUMN3, unusedColumnState);
  digitalWrite(COLUMN4, unusedColumnState);
  delay(10);
}

int* readColumn(){
    delay(10);
    static int resp[6];                    // For the selected Column
    resp[0] = digitalRead(ROW1L);   // 0 1
    resp[1] = digitalRead(ROW1R);   // 2 3
    resp[2] = digitalRead(ROW2L);   // 4 5
    resp[3] = digitalRead(ROW2R);
    resp[4] = digitalRead(ROW3L);
    resp[5] = digitalRead(ROW3R);
    return resp;
}

void readPin(char *s, int pinn){
  int reading = digitalRead(pinn);
  if(reading == HIGH){
    Serial.print(count);
    Serial.print(" ON ");
    Serial.println(s);
  }
}