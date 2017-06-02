7f         =8                          ;/*  Lab 3 - DC Motor
    Created:     May 25, 2017
    Last edited: June 2, 2017
    Author:      Gavin Acquroff

    Description:
    Control speed and direction of a DC motor.

    Portions of code were borrowed from https://blog.adafruit.com/2009/10/20/example-code-for-multi-button-checker-with-debouncing/ ,
    written by user Ladyada

    To do:
    - Create Debounce function - https://www.arduino.cc/en/tutorial/debounce#toc5
    - checking for potentiometer input
    - checking for new button presses
*/

#define NUMBUTTONS sizeof(button_pins)
byte button_pins[] = {2, 3};
const int Q1 = 9;
const int Q2 = 10;
const int Q3 = 5;
const int Q4 = 6;
const int debounce_delay = 50;
const int potentiometer = A0;
volatile byte last_button_state[NUMBUTTONS], button[NUMBUTTONS], push_state, change_state;

void setup() {
  byte k;
  Serial.begin(9600);

  // Run timer2 interrupt every 15 ms
  TCCR2A = 0; //disable Compare Match interrupt
  TCCR2B = 1 << CS22 | 1 << CS21 | 1 << CS20; //Sets prescaler to 1024. These settings actually give interrupt of ~16ms = 16,000,000/1024/256

  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1 << TOIE2; //setting Overflow Interrupt Enable bit in TC2 Interrupt Mask Register

  for (k = 0; k < NUMBUTTONS; k++) { //if i was used instead of k, would it conflict with usage of i in debounce function?
    pinMode(button_pins[k], INPUT_PULLUP);
  }

  pinMode(Q1, OUTPUT);
  pinMode(Q2, OUTPUT);
  pinMode(Q3, OUTPUT);
  pinMode(Q4, OUTPUT);
}

void set_trans (int var) {
  int motor_speed;
  motor_speed = analogRead(potentiometer);
  motor_speed = map(motor_speed, 0, 1023, 0, 255);

  switch (var) {
    case 0:
      digitalWrite(Q1, HIGH); //OFF
      digitalWrite(Q4, LOW); //OFF
      digitalWrite(Q2, LOW); //OFF
      digitalWrite(Q3, HIGH); //OFF
      break;

    case 1:
      analogWrite(Q1, LOW); //PWM
      analogWrite(Q4, motor_speed); //MAX
      digitalWrite(Q2, LOW); //OFF
      digitalWrite(Q3, HIGH); //OFF
      break;

    case 2:
      digitalWrite(Q1, HIGH); //OFF
      digitalWrite(Q4, LOW); //OFF
      analogWrite(Q2, motor_speed); //MAX
      analogWrite(Q3, LOW); //PWM
      break;
  }
}

//debounce - ISR
//runs every 15ms
//sets debounced values of push_forw and push_backw
//sets change_state flag
void debounce() {
  static byte button_read[NUMBUTTONS], new_push_state;
  static unsigned long last_time_checked;
  byte i = 0;

//  Serial.print("time = ");
//  Serial.print(millis(), DEC);
//  Serial.println(" ms");

  //need seperate for loops because only want change_state = true when both buttons have been debounced
  for (i = 0; i < NUMBUTTONS; i++) {
    button_read[i] = !digitalRead(button_pins[i]);

    if (button_read[i] != last_button_state[i]) {
      last_time_checked = millis();
      last_button_state[i] = button_read[i];
    }
  }

  for (i = 0; i < NUMBUTTONS; i++) {
    if ((millis() - last_time_checked) >= debounce_delay) {
      button[i] = button_read[i];
    }
  }
  Serial.print(button[0]);
  Serial.print("  ");
  Serial.print(button[1]);
  Serial.print("  ");

  if (button[0] && !button[1])
    new_push_state = 1;
  else if (!button[0] && button[1])
    new_push_state = 2;
  else if (button[0] && button[1])
    new_push_state = 0;
  else 
    new_push_state = push_state;
  
  Serial.print(new_push_state);
  Serial.print("  ");

  if (push_state != new_push_state)
    change_state = 1;
  else
    change_state = 0;

  Serial.println(change_state); 
  
}

SIGNAL(TIMER2_OVF_vect) {
  debounce();
}

void loop() {
  
  change_state = 0;

  if (button[0] && !button[1]) {
    push_state = 1;

    while (!change_state) {
      set_trans(push_state); //goes inside while loop to be able to change motor speed during a certain push state
    }
  }

  else if (!button[0] && button[1]) {
    push_state = 2;

    while (!change_state) {
      set_trans(push_state);
    }
  }

  else {
    push_state = 0;

    while (!change_state) {
      set_trans(push_state);
    }

  }
}
