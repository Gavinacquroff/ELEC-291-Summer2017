#include <DRV8835MotorShield.h>

DRV8835MotorShield motors;
int left_IR=1;
int right_IR=2;
int sensorValue1,sensorValue2;
int time1=0,time2=0;
int setValue1,setValue2,setValue3,setValue4;
int speed=400;
void setup() {
  
  Serial.begin(9600);
  pinMode(left_IR,INPUT);
}
 
void loop() {

  while(time1<setValue1){
  sensorValue1 = digitalRead(left_IR);
  sensorValue2 = digitalRead(right_IR);
  
 if(sensorValue1==LOW && sensorValue2==HIGH){
  motors.setM1Speed(speed);
  motors.setM2Speed(-speed);
 }
else{
  if(sensorValue1==HIGH && sensorValue2==LOW){
    motors.setM1Speed(-speed);
    motors.setM2Speed(speed);
  }
  else{
    if(sensorValue1==HIGH && sensorValue2==HIGH){
      motors.setM1Speed(speed);
      motors.setM2Speed(speed);
    }
    else{
      motors.setM1Speed(-speed);
      motors.setM2Speed(-speed);
    }
  }
    
  }

time1=millis();

  }
  }
  
  motors.setM1Speed(speed);
  motors.setM2Speed(-speed);
  delay(setValue2);

  
  while(time2<setValue2){
    sensorValue1 = digitalRead(left_IR);
  sensorValue2 = digitalRead(right_IR);
  
 if(sensorValue1==LOW && sensorValue2==HIGH){
  motors.setM1Speed(-speed);
  motors.setM2Speed(speed);
else{
  if(sensorValue1==HIGH && sensorValue2==LOW){
    motors.setM1Speed(speed);
    motors.setM2Speed(-speed);
  }
  else{
    if(sensorValue1==HIGH && sensorValue2==HIGH){
      motors.setM1Speed(-speed);
      motors.setM2Speed(-speed);
    }
    else{
      motors.setM1Speed(speed);
      motors.setM2Speed(speed);
    }
  }
    
  }
}
time2=millis()-time1;

    
  }
  
  delay(2000);

   motors.setM1Speed(speed);
  motors.setM2Speed(-speed);
  delay(setValue4);


  
       
}
