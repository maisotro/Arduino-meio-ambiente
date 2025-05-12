#include <NTPClient.h>          
// Biblioteca https://github.com/arduino-libraries/NTPClient
#include <ESP8266WiFi.h>        
// Biblioteca https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
#include <WiFiUdp.h>           
// Biblioteca https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
#include "Wire.h"
#include "RTClib.h"

//Objeto rtc da classe DS3231
RTC_DS3231 rtc; 

const char *ssid     = "maisotro";       // nome do seu roteador WIFI (SSID)
const char *password = "Pi314quinze";       // senha do roteador WIFI

WiFiUDP ntpUDP;
// Definindo o Servidor de relogio NTP Brasil, ajusta relogio UTC -3 horas, intervalo de atualizacao em milisegundos
NTPClient timeClient(ntpUDP, "gps.ntp.br", -3 * 3600, 60000);


char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"}; //Dias da semana

void setup()
{
Serial.begin(115200);                     // print no Serial Monitor da IDE
WiFi.begin(ssid, password);               // acessando a rede WIFI

while ( WiFi.status() != WL_CONNECTED )   // aguardando a conexão WEB
{
delay ( 500 );                          // aguarda 0,5 segundos
Serial.print ( "." );
}
timeClient.begin();
// void setup () {
//   Serial.begin(9600);                          //Inicializa a comunicacao serial
//   if (! rtc.begin()) {                         //Se o RTC nao for inicializado, faz
//     Serial.println("RTC NAO INICIALIZADO");    //Imprime o texto
//     while (1);                                 //Trava o programa
//   }
//   //rtc.adjust(DateTime(2019, 3, 6, 15, 24, 00));//Ajusta o tempo do RTC para a data e hora definida pelo usuario.
//   delay(100);                                  // 100 Milissegundos
// }
}


void loop()
{
 
  displayTime(); // display the real-time clock data on the Serial Monitor,
  delay(1000); // every second

  timeClient.update();                              // atualiza o relogio
  Serial.println(timeClient.getFormattedTime());    // print do relogio da WEB
  delay(1000);                                      // atraso de um segundo
}



