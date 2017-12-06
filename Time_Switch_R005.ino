#include "ESP8266WiFi.h"
#include <WiFiClient.h>
#include <EEPROM.h>



#define systemVersion "1.0.0 BETA"
String lastURL;
WiFiServer httpServer(0);
String httpPort = "80";
String APssid;
String APpass = "appletree";
String localSSID;
String localPASS;

String HTTPuser;
String HTTPpass;
String HTTPAdminpass = "0892";
boolean Adminloggedin = false;




int localIPaddress[4];
String deviceName;

long int resetLastMillis;
long int logoutLastMillis;

// NTP >>
#include <WiFiUdp.h>
#include <Time.h>
//IPAddress timeServer(132, 163, 4, 101);
int ntpPort;// = 2390;
IPAddress timeServerIP;
String ntpServerName;// = "time.nist.gov";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];
WiFiUDP udp;
int timeZone; //= 10;
time_t prevDisplay = 0;
long int uptimeLastUpdate;
// NTP <<

// PINs >>
const int LEDpin = 13;
const int FANpin = 12;
// PINs <<

String logFile;
boolean restartCountdown = false;
long int timetosave;



int relayPins[] = {16, 14, 12, 13};
int memoryStartAddress = 200;
int relayMemory[4][13];  /* 0=Sun - 6=Sat, 7=onHour, 8=onMin, 9=offHour, 10=offMin, 11=Power, 12=State/trigger  */
//int relayMemory[4][12] =  { {1, 0, 0, 0, 0, 0, 1, 12, 30, 13, 0, 1, 1}, {0, 1, 0, 0, 0, 1, 0, 9, 15, 14, 45, 0}, {0, 0, 1, 0, 1, 0, 0, 9, 15, 14, 45, 1} , {1, 0, 1, 0, 1, 0, 1, 9, 15, 14, 45, 0}  };
long int relayTrigger[4][1]; /* 0=mills */

WiFiClient client;


void setup() {
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   display.setTextColor(WHITE);
  Serial.begin(115200);
  Serial.println("\r\n\r\n");
  Serial.println("\r\n\r\n");

  logprint(false, "POWER ON");
  logprint(false, "Reading EPROM..");
  refreshEprom();


  if(((httpPort.toInt()) > 9999) || ((httpPort.toInt()) <= 0)){
  	factoryRestore();
  }


  logprint(false, "Reading EPROM SUCCESS!");
  delay(10);
  httpServer = httpPort.toInt();

  WiFi.begin(localSSID.c_str(), localPASS.c_str());
  if (testWifi() ) {
    setupSTA();
  }
  else {
    setupAP();
  }

  // PIN >>
  //  pinMode(LEDpin, OUTPUT);
  //  pinMode(FANpin, OUTPUT);
  //  analogWrite(FANpin, FANmaxSpeed);
  //  digitalWrite(LEDpin, HIGH);
  // PIN <<

  for (int chCount = 0; chCount < (sizeof(relayPins) / sizeof(int)); chCount++) {
    pinMode(relayPins[chCount], OUTPUT);
    switchRelay(chCount, false);// off
  }

  logprint(true, "System ready!");
   display.clearDisplay();
  display.display();
}


void loop() {

  mdns1();
  uptimeUpdate();

  if (restartCountdown) {
    if (millis() - resetLastMillis >= 1000 ) {
      ESP.restart();
      restartCountdown = false;
    }
  }
  else {
    resetLastMillis = millis();
  }

  if ( Adminloggedin) {
    if (millis() - logoutLastMillis >= 20000 ) {
      logprint(true, "ADMIN TIMEOUT");
      Adminloggedin = false;
    }
  }
  else {
    logoutLastMillis = millis();
  }


  // on  hh:mm  7:8
  // off hh:mm  9:10
  // state 11

  for (int chCount = 0; chCount < (sizeof(relayPins) / sizeof(int)); chCount++) {
    if (relayTrigger[chCount][0] > 0) {	
      if ((millis() - relayTrigger[chCount][0]) >= ((timeDif(relayMemory[chCount][7], relayMemory[chCount][8], relayMemory[chCount][9], relayMemory[chCount][10], 1)).toInt() * 60000) ) {
        relayTrigger[chCount][0] = 0;
        switchRelay(chCount, false);// off     
      }
      else {
        switchRelay(chCount, true);// on      
      }
    }
    else {

      if ((relayMemory[chCount][(weekday() - 1)]) && (relayMemory[chCount][11])) { // if it's the right day of the week
        if ((hour() == relayMemory[chCount][7]) && (hour() == relayMemory[chCount][9])) {
          if (minute() < relayMemory[chCount][8]) {
            switchRelay(chCount, false);// off
          }
          else if (minute() >= relayMemory[chCount][10]) {
            switchRelay(chCount, false); // off
          }
          else {
            switchRelay(chCount, true);// on
          }
        }
        else {

          if (hour() == relayMemory[chCount][7]) {
            if (minute() < relayMemory[chCount][8]) {
              switchRelay(chCount, false);// off
            }
            else {
              switchRelay(chCount, true);// ON
            }
          }
          else if (hour() == relayMemory[chCount][9]) {
            if (minute() >= relayMemory[chCount][10]) {
              switchRelay(chCount, false);// off
            }
            else {
              switchRelay(chCount, true);// on
            }
          }
          else if ((relayMemory[chCount][7] < hour()) && (relayMemory[chCount][9]) > hour()) {
            switchRelay(chCount, true);// on
          }
          else {    // may cause issues!!!!, untested!!!!
        switchRelay(chCount, false);// off
      }

        }
      }
      else {
        switchRelay(chCount, false);// off
      }

    }

  }



}


void switchRelay(int chToUse, boolean StateToUse) {
  if (StateToUse) {
    relayMemory[chToUse][12] = 1;
    digitalWrite(relayPins[chToUse], LOW);
  }
  else {
    relayMemory[chToUse][12] = 0;
    digitalWrite(relayPins[chToUse], HIGH);
  }
}










