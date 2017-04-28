
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


/* Plays melody with blinking diodes  */
void play_melody (int speaker_pin){
 int melody[] = { NOTE_C4, NOTE_G3, NOTE_G3, 
                  NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
 int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    diodes_on ();
      
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speaker_pin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    
    diodes_off();
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speaker_pin);
  }
}

