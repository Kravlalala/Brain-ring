
/* Diodes put out  */
void diodes_off(){
  analogWrite(VD1, 255);
  analogWrite(VD1, 255);
  analogWrite(VD1, 255);
  analogWrite(VD1, 255);
}

/* Light diodes  */
void diodes_on(){
  analogWrite(VD1, 0);
  analogWrite(VD1, 0);
  analogWrite(VD1, 0);
  analogWrite(VD1, 0);
}


/* Plays melody with blinking diodes
*  @speaker_pin - pin number, where speaker is connected
*/
void play_melody (int speaker_pin){
 int melody[] = { NOTE_A2, NOTE_G2, NOTE_FS2, NOTE_E2, NOTE_FS2, 
                  NOTE_E2, NOTE_D2, NOTE_B1, NOTE_D2, NOTE_FS2};
 int noteDurations[] = { 8, 8, 2, 8, 8, 4, 8, 4, 8, 2 };
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    /* Start diodes lighting */
    diodes_on ();
      
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speaker_pin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;

    /* Stop diodes lighting */
    diodes_off();
    delay(pauseBetweenNotes);
    
    // stop the tone playing:
    noTone(speaker_pin);
  }
}

