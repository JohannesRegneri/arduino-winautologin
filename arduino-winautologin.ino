/* Schaltung:
    Taster an Pin 2 und 3
    wir nutzen die Keypad Libary um auf Pulldown Widerstände zu verzichten.
    So kann der Taster direkt an zwei digitale Pins angeschlossen werden.

https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/





*/
#include "Keyboard.h"
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
//Benutze die folgenden Input Pins für die Taster
byte rowPins[ROWS] = {2, 4, 6, 8}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {3, 5, 7}; //connect to the column pinouts of the kpd

//Erstelle ein neues Keyboard
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String msg;


void setup() {
  Serial.begin(9600);

  msg = "";
  // initialize control over the keyboard:
  Keyboard.begin();
}

void keypress() {
  // Wird beim Drücken aufgerufen
  Keyboard.press(KEY_LEFT_CTRL);  // press and hold Shift
  Keyboard.press(KEY_LEFT_ALT);  // press and hold Alt
  Keyboard.press(KEY_DELETE);          // press and hold Enf

}

void keyrelease() {
  // Wird beim Loslassen aufgerufen
  Keyboard.releaseAll();           // release all
}


void loop() {
  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (kpd.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
      {
        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
          case PRESSED:
            msg = " PRESSED.";
            keypress();
            break;
          case HOLD:
            msg = " HOLD.";
            break;
          case RELEASED:
            msg = " RELEASED.";
            keyrelease();
            break;
          case IDLE:
            msg = " IDLE.";
        }
        //Keyboard.print(kpd.key[i].kchar);
      }
    }
  }
}  // End loop
