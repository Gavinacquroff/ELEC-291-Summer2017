#include <DRV8835MotorShield.h>

DRV8835MotorShield motors;

int left_IR = 1;
int right_IR = 2;
int sensorValue1, sensorValue2;
int time1 = 0, time2 = 0;
int setValue1 = 15000, setValue2 = 2500, setValue3 = 7500, setValue4 = 625;
int speed = 400;
int i = 0, k = 0;
int limit;
void setup() {

  Serial.begin(9600);
  pinMode(left_IR, INPUT);
  pinMode(right_IR, INPUT);
}

void loop() {
  time1 = millis();

  while (i < 1) {

    while (time1 < setValue1) {
      sensorValue1 = digitalRead(left_IR);
      sensorValue2 = digitalRead(right_IR);

      if (sensorValue1 == LOW && sensorValue2 == HIGH) {
        motors.setM1Speed(speed);
        motors.setM2Speed(-speed);
      }
      else if (sensorValue1 == HIGH && sensorValue2 == LOW) {
        motors.setM1Speed(-speed);
        motors.setM2Speed(speed);
      }
      else if (sensorValue1 == HIGH && sensorValue2 == HIGH) {
        motors.setM1Speed(speed);
        motors.setM2Speed(speed);
      }
      else {
        motors.setM1Speed(0);
        motors.setM2Speed(0);
      }

      time1 = millis();
    }

    motors.setM1Speed(speed);
    motors.setM2Speed(-speed);
    delay(setValue2);

    time2 = millis();
    limit = millis() + setValue3;

    while (time2 < limit) {
      sensorValue1 = digitalRead(left_IR);
      sensorValue2 = digitalRead(right_IR);

      if (sensorValue1 == LOW && sensorValue2 == HIGH) {
        motors.setM1Speed(speed);
        motors.setM2Speed(-speed);
      }
      else if (sensorValue1 == HIGH && sensorValue2 == LOW) {
        motors.setM1Speed(-speed);
        motors.setM2Speed(speed);
      }
      else if (sensorValue1 == HIGH && sensorValue2 == HIGH) {
        motors.setM1Speed(speed);
        motors.setM2Speed(speed);
      }
      else {
        motors.setM1Speed(0);
        motors.setM2Speed(0);
      }

      time2 = millis();
    }

    delay(2000);

    for (k = 0, k < 4, k++) {
      motors.setM1Speed(speed);
      motors.setM2Speed(-speed);

      delay(setValue4);
    }

    motors.setM1Speed(0);
    motors.setM2Speed(0);

    i++;

  }
}

