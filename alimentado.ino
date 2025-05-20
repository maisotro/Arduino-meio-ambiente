// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <Stepper.h>

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = { "Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado" };

uint8_t DAILY_EVENT_START_HH = 15;  // event start time: hour
uint8_t DAILY_EVENT_START_MM = 01;  // event start time: minute

//Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  Serial.begin(57600);

#ifndef ESP8266
  while (!Serial)
    ;  // wait for serial port to connect. Needed for native USB
#endif

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

   // myStepper.setSpeed(60);  //Determina a velocidade do motor
  }
}

//
// void alimentarMotor(){
  
//   myStepper.step(256); 
//   motor.step(128);
//   delay(300000); 

// }


void loop() {
  DateTime now = rtc.now();
  
  if (now.hour() == DAILY_EVENT_START_HH && now.minute() == DAILY_EVENT_START_MM){
   // alimentarMotor();
  Serial.println("A");
  } 
  else {
    Serial.println("não Agendado");
  }

  delay(1000);
}
