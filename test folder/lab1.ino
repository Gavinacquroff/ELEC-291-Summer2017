const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 4;
const int LED4 = 5;
const int button_100 = 2;
const int button_500 = 3;
const int time_step_low = 500;
const int time_step_high = 100;

int low_speed = 0;
int high_speed = 0;
volatile int time_step = 0;
volatile int leds_on = 0;
volatile int test1 = 0;

void button_ISR() {
  time_step = 0;
  leds_on = 0;
}


void LED_flash (int time_s, int leds_on) {
  time_step = time_s;
  if (leds_on) {
    digitalWrite(LED1, leds_on);
    delay (time_step);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, leds_on);
    delay (time_step);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, leds_on);
    delay (time_step);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, leds_on);
    delay (time_step);
    digitalWrite(LED4, LOW);
  }
  else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(button_100, INPUT);
  pinMode(button_500, INPUT);

//  attachInterrupt(digitalPinToInterrupt(button_100), button_ISR, RISING);
//  attachInterrupt(digitalPinToInterrupt(button_500), button_ISR, RISING);

  attachInterrupt(1, button_ISR, RISING);
  attachInterrupt(0, button_ISR, RISING);

  Serial.begin(9600);
  
}

void loop() {
beginning:
  low_speed = !digitalRead(button_500);
  high_speed = !digitalRead(button_100);

  if (low_speed && !high_speed) {
    leds_on = 1;
    LED_flash(time_step_low, leds_on);
  }
  else if (high_speed && !low_speed) {
    leds_on = 1;
    LED_flash (time_step_high, leds_on);
  }
  else {
    leds_on = 0;
    LED_flash (time_step_high, leds_on);
  }
}



