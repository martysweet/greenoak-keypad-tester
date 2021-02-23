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

void doReadColumn(int offset);
int* readColumn();
void resetAllColumns();
int* readColumnRows();

// Allow for switching between pullup/floating
int triggerColumnState = LOW; // LOW = everything is high unless evaluating | HIGH = everything is LOW/floating unless evaluating
int status[3][8] = {0}; // Row 0, 1, 2, // Column 0-7
int* switches;

/**
 * Setup the columns as outputs, we set these to HIGH or LOW
 * Setup the rows as inputs, we read the value of these.
 * 
 * The best operation mode is when all outputs by default are HIGH and inputs use the INPUT_PULLUP.
 * When evaluating, the column is set LOW. This results in the input pin going LOW when read. 
 * This avoids transient/floating voltages.
 */
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


/**
 * Main loop
 * Reads each column and the switches of them into status array
 * When a column is in a trigger state, we can read all the rows and thus infer if the button is pressed for that column
 * We do this for each column, evaluating all the buttons.
 * Clears the terminal and Displays the status
 **/
void loop() {

  // Column 1
  digitalWrite(COLUMN1, triggerColumnState);    // Set the Column typically low
  doReadColumn(0);                              // 0 specifies the row offset to put this column into the status array
  resetAllColumns();                            // Reset all columns

  // Column 2
  digitalWrite(COLUMN2, triggerColumnState);
  doReadColumn(2);
  resetAllColumns();

  // Column 3
  digitalWrite(COLUMN3, triggerColumnState);
  doReadColumn(4);
  resetAllColumns();

  // Column 4
  digitalWrite(COLUMN4, triggerColumnState);
  doReadColumn(6);
  resetAllColumns();

  // Clear screen and display the current status Array
  // Use minicom for this functionality: minicom -b115200 -D /dev/ttyACM0
  Serial.println("\033[0H\033[0J-------------------------");
  for(int r=0; r<3; r++){
    for(int c=0; c<8; c++){
      if(status[r][c] == triggerColumnState){ // The pin is the same as the relevant Column output
        Serial.print(" X ");
      }else{
        Serial.print(" O ");
      }
    }
    Serial.println("");
  }
  Serial.println("-------------------------");

}

/**
 * Reads the column, putting six switches into the status array
 **/
void doReadColumn(int offset){
  switches = readColumnRows();
  int switchInc = 0;
  for(int r = 0; r<3; r++){
    status[r][offset] = switches[switchInc++];
    status[r][offset+1] = switches[switchInc++];
  }
}

/**
 * Resets all the column power feeds
 **/
void resetAllColumns(){
  digitalWrite(COLUMN1, !triggerColumnState);
  digitalWrite(COLUMN2, !triggerColumnState);
  digitalWrite(COLUMN3, !triggerColumnState);
  digitalWrite(COLUMN4, !triggerColumnState);
  delay(10);
}

/**
 * Reads all the rows for the specifically powered column.
 * returning an array of LOW | HIGH
 **/
int* readColumnRows(){
  delay(10);
  static int resp[6];             // For the selected Column
  resp[0] = digitalRead(ROW1L);   // 0 1
  resp[1] = digitalRead(ROW1R);   // 2 3
  resp[2] = digitalRead(ROW2L);   // 4 5
  resp[3] = digitalRead(ROW2R);
  resp[4] = digitalRead(ROW3L);
  resp[5] = digitalRead(ROW3R);
  return resp;
}
