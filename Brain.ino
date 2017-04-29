#include "diagnostic.h"

/* Bit mask of active buttons  */
#define PLAYER1_FIRST  1
#define PLAYER2_FIRST  1 << 1
#define PLAYER3_FIRST  1 << 2
#define PLAYER4_FIRST  1 << 3

void answer_wait (int);
int check_button_pushed ();
int read_buttons ();

/* Pins preinitialization and hardware diagnostics  */
void setup() {

  /* Set button pins as inputs */
  pinMode(PLAYER1, INPUT);    
  pinMode(PLAYER2, INPUT);
  pinMode(PLAYER3, INPUT);
  pinMode(PLAYER4, INPUT);

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
  pinMode (SPEAKER, OUTPUT);

  /* Speaker and diodes testing */
  play_melody(SPEAKER);
}

/* Main loop function  */
void loop() {
  int buttons_state_mask = 0;
  int pressed_button = 0;
  
  buttons_state_mask = read_buttons();
  pressed_button = check_button_pushed(buttons_state_mask);
  
  if (pressed_button != 0)
    answer_wait (pressed_button);
}

/* Read current buttons state. Returns state mask, where
* each bit is current player's button state, as example: 
* 0001 - player 1 pushed the button
* 0010 - player 2 pushed the button 
* 0100 - player 3 pushed the button
* 1000 - player 4 pushed the button 
*/
int read_buttons (){
  int state_mask = 0;
  int player1_state = digitalRead (PLAYER1);
  int player2_state = digitalRead (PLAYER2);
  int player3_state = digitalRead (PLAYER3);
  int player4_state = digitalRead (PLAYER4);
  
  if (player1_state == HIGH)
    state_mask = state_mask | PLAYER1_FIRST;
  
  if (player2_state == HIGH)
    state_mask = state_mask | PLAYER2_FIRST;
  
  if (player3_state == HIGH)
    state_mask = state_mask | PLAYER3_FIRST;
  
  if (player4_state == HIGH)
    state_mask = state_mask | PLAYER4_FIRST;
    
   return state_mask;
}

/* Identify wich button has been pushed. Returns number of VD, 
* corresponds to pushed button. 
*/
int check_button_pushed (int state_mask){
  if (state_mask == PLAYER1_FIRST)
    return VD1;
  if (state_mask == PLAYER2_FIRST)
    return VD2;
  if (state_mask == PLAYER3_FIRST)
    return VD3;
  if (state_mask == PLAYER4_FIRST)
    return VD4;
  return 0;   
}

/* Sycle for waiting answer  */
void answer_wait (int diode_pin){
  int master_state = LOW;
  tone (SPEAKER, 400);
  delay(500);
  noTone (SPEAKER);
  analogWrite (diode_pin, 0);
  while (true){
    master_state = digitalRead (MASTER); 
    if (master_state == HIGH){
      analogWrite (diode_pin, 255);
      break;
    }
  } 
}




