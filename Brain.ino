
#include "diagnostic.h"

/* Bit mask of active buttons  */
#define PLAYER1_FIRST  1
#define PLAYER2_FIRST  1 << 1
#define PLAYER3_FIRST  1 << 2
#define PLAYER4_FIRST  1 << 3

int wait_action ();
int detect_pushed_button (int);
void answer_wait (int);
void signalize (int);

/* Pins preinitialization and hardware diagnostics  */
void setup() {

  /* Set button pins as inputs */
  pinMode(PLAYER1, INPUT);
  pinMode(PLAYER2, INPUT);
  pinMode(PLAYER3, INPUT);
  pinMode(PLAYER4, INPUT);
  pinMode(MASTER, INPUT);

  /* Set diode pins as outputs */
  pinMode (VD1, OUTPUT);
  pinMode (VD2, OUTPUT);
  pinMode (VD3, OUTPUT);
  pinMode (VD4, OUTPUT);

  /* Put off diodes */
  analogWrite (VD1, 255);
  analogWrite (VD2, 255);
  analogWrite (VD3, 255);
  analogWrite (VD4, 255);

  /* Set speaker as output */
  pinMode (SPEAKER, OUTPUT);

  /* Open serial port for debug */
  Serial.begin (9600);
  
  /* Speaker and diodes testing */
  play_melody(SPEAKER);
}

/* Main loop function  */
void loop() {
  int buttons_state = 0;
  int current_led = 0;

  buttons_state = wait_action();
  current_led = detect_pushed_button(buttons_state);

  if (current_led != 0) {
    signalize (current_led);
    answer_wait (current_led);
  }
}

/* Read current buttons state. Returns state mask, when one of buttons
   has been pushed.
   Each bit of state_mask is a current player's button state, as example:
   0001 - player 1 pushed the button
   0010 - player 2 pushed the button
   0100 - player 3 pushed the button
   1000 - player 4 pushed the button
*/
int wait_action () {
  int state_mask = 0;
  int player1_state = LOW;
  int player2_state = LOW;
  int player3_state = LOW;
  int player4_state = LOW;

  while (true) {
    player1_state = digitalRead (PLAYER1);
    player2_state = digitalRead (PLAYER2);
    player3_state = digitalRead (PLAYER3);
    player4_state = digitalRead (PLAYER4);

    if (player1_state == HIGH)
      state_mask = state_mask | PLAYER1_FIRST;

    if (player2_state == HIGH)
      state_mask = state_mask | PLAYER2_FIRST;

    if (player3_state == HIGH)
      state_mask = state_mask | PLAYER3_FIRST;

    if (player4_state == HIGH)
      state_mask = state_mask | PLAYER4_FIRST;

    if (state_mask != 0)
      break;
  }
  return state_mask;
}

/* Identify wich button has been pushed. Returns number of VD,
  corresponds to pushed button.
*/
int detect_pushed_button (int state_mask) {
  if (state_mask == PLAYER1_FIRST){
    Serial.println ("Button on pin 2 has been pushed");
    return VD1;
  }
  if (state_mask == PLAYER2_FIRST){
    Serial.println ("Button on pin 3 has been pushed");
    return VD2;
  }
  if (state_mask == PLAYER3_FIRST){
    Serial.println ("Button on pin 4 has been pushed");
    return VD3;
  }
    
  if (state_mask == PLAYER4_FIRST){
    Serial.println ("Button on pin 5 has been pushed");
    return VD4;
  }
  Serial.println ("No button has been pushed");  
  return 0;
}

/* Led diode, and beep
   @diode_pin - pin, correspinding to the pushed button
*/
void signalize (int diode_pin) {
  tone (SPEAKER, 400);
  delay(500);
  noTone (SPEAKER);
  analogWrite (diode_pin, 0);
}

/* Sycle for waiting answer
   @diode_pin - currently active diode
*/
void answer_wait (int diode_pin) {
  int master_state = LOW;

  while (true) {
    master_state = digitalRead (MASTER);
    if (master_state == HIGH) {
      Serial.println ("Master state is HIGH");
      analogWrite (diode_pin, 255);
      break;
    }
  }
}




