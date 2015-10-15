/*
SAID -- Serial Arduino Input Device
---------------------------------
Arduino section

Reads inputs from joystick microswitches and sends the data out over serial as a two digit number. See "SAIDprotocol.txt" or the README
for more information on the data sent over serial.
 */


// Pin numbers for each switch
// NOTE THAT THE NAMES ARE ACTUALLY WRONG RIGHT NOW. WILL BE FIXED LATER
const int down = 6; 
const int up = 7;
const int left = 4;
const int right = 5;
const int trigger = 3;


int output = 0; //Stores the input data for transmission
int addzero = 0; //Does a leading zero need to be added?

void setup() {
Serial.begin(9600);
// The switches are wired to ground, so we need the pullup resistors active.
pinMode(down, INPUT_PULLUP);
pinMode(right, INPUT_PULLUP);
pinMode(left, INPUT_PULLUP);
pinMode(up, INPUT_PULLUP);
pinMode(trigger, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(up) == LOW) {
    output = 1 + output;
  } 
  if (digitalRead(right) == LOW) {
    output = 7 + output;
  } 
  if (digitalRead(down) == LOW) {
    output = 11 + output;
  }
  if (digitalRead(left) == LOW) {
    output = 15 + output;
  } 
  if (digitalRead(trigger) == LOW) {
    output = 19 + output;
  }
  if (output < 10) { //If final input tallies to a single digit number, add a leading zero.
    addzero = 1;
  }
  if (output > 0) {
    if (addzero == 0) {
      Serial.println(output);
    }
    if (addzero == 1) {
      Serial.print("0");
      Serial.println(output);

    }
    output = 0; 
    addzero = 0;

  } 
}
