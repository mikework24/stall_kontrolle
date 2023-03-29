//Arduino Mega

#include <avr/wdt.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <EEPROM.h>
//#include <SoftwareSerial.h>
#include <OneWire.h>
#include "DHT.h"
#include <stdlib.h>

//meine Funktionen
#define WRITE_EEPROM false
#define DEBUG_SERIAL false
#include "my_epprom.h"

int serien_nr    = 10;
String versionNr = "1.6";
//licht_typ  G1 = 2; G2 = 0
int licht_typ    = 2; // 0 = 3 lichtgruppen, 1 = nur eine lichtgruppe, 2 = 1 lichtgruppe + notlicht bleibt tagsüber an
int licht_halbzeit = 0; //soll bei der hälfe eine pause gemacht werden, wie lange in stunden?
//neu_esp_reset  G1 = 1; G2 = 0;
int neu_esp_reset = 1;


#define Serial_esp Serial1
RTC_DS1307 rtc;
DHT dht1(7, DHT22);
DHT dht2(2, DHT22);
LiquidCrystal_I2C lcd(0x27,20,4); //startbildschirm
LiquidCrystal_I2C lcd1(0x3F,20,4); //korrekturadresse
LiquidCrystal_I2C lcd2(0x27,20,4); //alte adresse

//Char
char myWa[10];
char myFu[10];

char ochar    = 0; //ó
char achar    = 1; //a
byte obyte[8] = { B01100,B00000,B01110,B10001,B10001,B10001,B01110,B00000 };
byte abyte[8] = { B01100,B00000,B01110,B00001,B01111,B10001,B01111,B00000 };

//String
String futtermenge = "0";
String xbeeSend    = "";
String espSend     = "";

int neuan = 0;

//durchschnitt der temperatur nutzen
int tempR = 0;
int tempD[6];
//end

//Feste Variablen
int turtag    = 0;
int te1       = 2500;
int te2       = 2500;
int h1        = 6500;
int h2        = 6500;
int li_z_alt  = 0;
int licht_z   = 2;
int daten_w   = 0;
int sec_z     = 0;
int min_z     = 0;
int stu_z     = 0;
int tag_z     = 0;
int silo_save = 0;
int wasserN   = 0;
float wasserZ = 0;
float silo1   = 0;
float silo2   = 0;
float waT     = 0;
float fuT     = 0;
int led       = 0;
int info      = 0;
int disp      = 0;
int luftak    = 0;
int luftak_n  = 0;

//Variablen
String taste   = "";
String taste_r = "";
String taste_a = "";
int r1z        = 0;
int r2z        = 0;
int r3z        = 0;
int r4z        = 0;
int r5z        = 0;
int r6z        = 0;
int r7z        = 0;
int r8z        = 0;
int r9z        = 0;
int r10z       = 0;
int r11z       = 0;
int r12z       = 0;

int value;
String sp;

//Schleifen und pausen
int loop_temp   = 999;
int loop_esp   = 0;
int loop_disp   = 999;
int loop_silo   = 0;
int loop_daten  = 0;
int loop_rtc    = 0;
int loop_luft   = 0;
int loop_ku     = 0;
int loop_esp_nr = 0; //in esp
int loop_esp_re = 0; //startet den esp neu
long dt = 0;
long dm = 0;

unsigned long tur_anfang   = 0;
unsigned long time_rtc     = 0;
unsigned long secund       = 0;
unsigned long turzeit      = 0;
unsigned long tage         = 0;
unsigned long mtimerms     = 0;
unsigned long licht_timer  = 0;
unsigned long li_ang_timer = 0;
unsigned long loop_milisec = 0;
unsigned long vergleich_time = 0;

DateTime future;
DateTime turanfang;
DateTime neue_zeit;

void setup()
{
  Serial.begin(115200);
  
  DEBUG_LOG("Setup");
  
  Wire.begin();
  rtc.begin();
  
  dht1.begin();
  dht2.begin();
  
  Serial_esp.begin(115200);
  
  init_pin();
  
  DateTime now = rtc.now();
  time_rtc     = now.unixtime();
  neue_zeit    = (time_rtc);
  if (! rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2019, 4, 14, 11, 56, 0));
  }
  //rtc.adjust(DateTime(2017, 12, 25, 9, 32, 0));
  DEBUG_LOG("initializeEEPROM()");
  initializeEEPROM();
  DEBUG_LOG("initializeEEPROM() ende");
  DEBUG_LOG("initializeVariables()");
  initializeVariables();
  DEBUG_LOG("initializeVariables() ende");
  //eep_bearbeiten("reset", 1);
  
  silo1 = (float)silo1x;
  silo2 = (float)silo2x;
  
  init_lcd();
  lcd.setCursor(0,0);
  lcd.print("Cargando...");
  lcd.createChar(ochar, obyte);
  lcd.createChar(achar, abyte);
  esp_reset_f();
  //digitalWrite(3, HIGH); //ESP Starten
  wdt_enable(WDTO_8S);

  DEBUG_LOG("Setup ende");
}

void loop()
{
  tastatur();
  //langsame funktionen
  if( secund != (millis() / 1000)) {
    secund = millis() / 1000;  
    
    laufzeit();
    silo();
    licht();
    lueften();
    heizen();
    kuhlen();

    //relay2(neuan);
    //neuan++;
    
    relay();
    turzeitfunktion();
    temperatur();
    datenpaket();
    datensenden();
    aktdisplay();
    rtclesen();
  }
  
  //schnelle funktionen
  if( loop_milisec != (millis() / 100) ) {
    loop_milisec = (millis()/100);
    
    wasser_f();
  }
  
  wdt_reset();
}

void DEBUG_LOG(String ausg_log){
  if(DEBUG_SERIAL){
    Serial.println(ausg_log);
  }
}
