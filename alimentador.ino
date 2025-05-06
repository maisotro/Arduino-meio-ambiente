// Alimentador automático com Arduino Uno, 2 motores 28BYJ-48 e RTC DS3231
// Movimento em 45 graus e 22,5 graus alternadamente com pausa de 5 minutos entre
// Motores acionados em horários fixos todos os dias
#include <Wire.h>
#include <RTClib.h>
#include <Stepper.h>
// Motor de passo 28BYJ-48 com driver ULN2003 tem 2048 passos por volta
#define STEPS_PER_REV 2048

// Inicializa os dois motores
Stepper motor1(STEPS_PER_REV, 8, 10, 9, 11); // PinosIN1, IN3, IN2, IN4 do driver 1

Stepper motor2(STEPS_PER_REV, 4, 6, 5, 7); // Pinos IN1, IN3, IN2, IN4 do driver 2
RTC_DS3231 rtc;

// Flags de controle para não repetir ações
bool motor1ExecutadoHoje = false;
bool motor2ExecutadoHoje = false;

void setup() {
    Serial.begin(9600);
    Wire.begin();
if (!rtc.begin()){
      Serial.println("RTC não encontrado!"); 
      while (1);  } 
// rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Use uma vez para ajustar o RTC  

motor1.setSpeed(10); // velocidade em RPM  
motor2.setSpeed(10);
}

void loop() {
DateTime now = rtc.now();
// Reset das flags à meia-noite
if (now.hour() == 0 && now.minute() == 0) 
{
      motor1ExecutadoHoje = false;
      motor2ExecutadoHoje = false;  }  

// Motor 1: 08h00
if (now.hour() == 8 && now.minute() == 0 && !motor1ExecutadoHoje)
{ 
alimentarMotor(motor1);
motor1ExecutadoHoje = true;
}

// Motor 2: 08h10
if (now.hour() == 8 && now.minute() == 10 && !motor2ExecutadoHoje) {
alimentarMotor(motor2);
motor2ExecutadoHoje = true;
}
delay(30000);
// Verifica a cada 30 segundos
}
void alimentarMotor(Stepper& motor) 
{  // Gira 45 graus 
(STEPS_PER_REV * 45 / 360 = 256 passos)  motor.step(256);  
delay(300000); 
// Aguarda 5 minutos (300.000 ms) 
 // Gira mais 22.5 graus 
 (STEPS_PER_REV * 22.5 / 360 = 128 passos)  motor.step(128);}

            
          
          
          
        
        
      
    