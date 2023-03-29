void init_pin()
{
  DEBUG_LOG("init_pin()");
  pinMode(13, OUTPUT); //led
  pinMode(3, OUTPUT);  //esp_reset
  pinMode(4, OUTPUT);  //extra
  pinMode(5, OUTPUT);  //extra
  pinMode(6, OUTPUT);  //1 wire
  pinMode(23, OUTPUT); //r12
  pinMode(25, OUTPUT); //r11
  pinMode(27, OUTPUT); //r10
  pinMode(29, OUTPUT); //r9
  pinMode(31, OUTPUT); //r8
  pinMode(33, OUTPUT); //r7
  pinMode(35, OUTPUT); //r6
  pinMode(37, OUTPUT); //r5
  pinMode(39, OUTPUT); //r4
  pinMode(41, OUTPUT); //r3
  pinMode(43, OUTPUT); //r2
  pinMode(45, OUTPUT); //r1
  
  digitalWrite(13, HIGH); //led
  digitalWrite(3,  LOW); //esp_reset beim starten noch aus, nach setup starten lassen
  digitalWrite(4,  HIGH); //extra
  digitalWrite(5,  HIGH); //extra
  digitalWrite(6,  LOW);  //1 wire
  digitalWrite(23, HIGH); //r12
  digitalWrite(25, HIGH); //r11
  digitalWrite(27, HIGH); //r10
  digitalWrite(29, HIGH); //r9
  digitalWrite(31, HIGH); //r8
  digitalWrite(33, HIGH); //r7
  digitalWrite(35, HIGH); //r6
  digitalWrite(37, HIGH); //r5
  digitalWrite(39, HIGH); //r4
  digitalWrite(41, HIGH); //r3
  digitalWrite(43, HIGH); //r2
  digitalWrite(45, HIGH); //r1
  
  delay(100);
  DEBUG_LOG("init_pin() ende");
}

void relay() {
  DEBUG_LOG("relay()");
  if(r12z == 0){ digitalWrite(23, HIGH); }else{ digitalWrite(23, LOW); }
  if(r11z == 0){ digitalWrite(25, HIGH); }else{ digitalWrite(25, LOW); }
  if(r10z == 0){ digitalWrite(27, HIGH); }else{ digitalWrite(27, LOW); }
  if(r9z  == 0){ digitalWrite(29, HIGH); }else{ digitalWrite(29, LOW); }
  if(r8z  == 0){ digitalWrite(31, HIGH); }else{ digitalWrite(31, LOW); }
  if(r7z  == 0){ digitalWrite(33, HIGH); }else{ digitalWrite(33, LOW); }
  if(r6z  == 0){ digitalWrite(35, HIGH); }else{ digitalWrite(35, LOW); }
  if(r5z  == 0){ digitalWrite(37, HIGH); }else{ digitalWrite(37, LOW); }
  if(r4z  == 0){ digitalWrite(39, HIGH); }else{ digitalWrite(39, LOW); }
  if(r3z  == 0){ digitalWrite(41, HIGH); }else{ digitalWrite(41, LOW); }
  if(r2z  == 0){ digitalWrite(43, HIGH); }else{ digitalWrite(43, LOW); }
  if(r1z  == 0){ digitalWrite(45, HIGH); }else{ digitalWrite(45, LOW); }
  DEBUG_LOG("relay() ende");
}

void laufzeit() {
  DEBUG_LOG("laufzeit()");
  if(led == 0){ digitalWrite(13, HIGH); led = 1; }else{ digitalWrite(13, LOW); led = 0; }
  sec_z++;
  
  if(sec_z >= 60){ sec_z = 0; min_z++; }
  if(min_z >= 60){ min_z = 0; stu_z++; }
  if(stu_z >= 24){ stu_z = 0; tag_z++; }
  DEBUG_LOG("laufzeit() ende");
}

void esp_reset_f()
{
  DEBUG_LOG("esp_reset_f()");
  if(neu_esp_reset == 0){
    digitalWrite(3, LOW);
    delay(300);
    digitalWrite(3, HIGH);
    delay(700);
  }else{
    digitalWrite(3, HIGH);
    delay(300);
    digitalWrite(3, LOW);
    delay(700);
  }
  DEBUG_LOG("esp_reset_f() ende");
}

void wire_reset_f()
{
  DEBUG_LOG("wire_reset_f()");
  digitalWrite(6, HIGH);
  delay(300);
  digitalWrite(6, LOW);
  delay(300);
  DEBUG_LOG("wire_reset_f() ende");
}

void init_lcd()
{
  DEBUG_LOG("init_lcd()");
  byte error;
  Wire.beginTransmission(39);
  error = Wire.endTransmission();
  if (error == 0)
  {
    lcd = lcd2;
  }
  Wire.beginTransmission(63);
  error = Wire.endTransmission();
  if (error == 0)
  {
    lcd = lcd1;
  }
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  DEBUG_LOG("init_lcd() ende");
}

void turzeitfunktion()
{
  DEBUG_LOG("turzeitfunktion()");
  future = (time_rtc + secund);
  DateTime turanfang (t_jahr, t_mon, t_tag, 0, 0, 0);
  turzeit = future.unixtime() - turanfang.unixtime();
  turtag  = (int)((turzeit/86400));
  DEBUG_LOG("turzeitfunktion() ende");
}

void temperatur()
{
  DEBUG_LOG("temperatur()");
  if( loop_temp >= 3 && dm == 0) {
    //temp();
    //int ver_tem = temp1(5);
    //if(ver_tem != 9999){ te1 = ver_tem + temp_korrektur; }
    temp_dht1();
      
    loop_temp = 0;
  }
  loop_temp++;
  DEBUG_LOG("temperatur() ende");
}

void datenpaket()
{
  DEBUG_LOG("datenpaket()");
  if( loop_daten >= 30 && dm == 0) {
    daten_esp(); //esp8266
    loop_daten = 0;
  }
  loop_daten++;
  DEBUG_LOG("datenpaket() ende");
}

void datensenden()
{
  DEBUG_LOG("datensende()");
  if( loop_esp >= 2 && dm == 0) {
    esp8266();
    loop_esp = 0;
  }
  loop_esp++;
  DEBUG_LOG("datensenden() ende");
}

void aktdisplay()
{
  DEBUG_LOG("aktdisplay()");
  if( loop_disp >= 2 ) {
    displayX();
    loop_disp = 0;
  }
  loop_disp++;
  DEBUG_LOG("aktdisplay() ende");
}

void rtclesen()
{
  DEBUG_LOG("rtclesen()");
  if( loop_rtc >= 1800 ) { // jede 30 min zeit korregieren
    DateTime now = rtc.now();
    vergleich_time = time_rtc + secund;
    if(vergleich_time >= (now.unixtime() + 60) || vergleich_time <= (now.unixtime() - 60)){
      time_rtc = now.unixtime() - secund;
    }
    loop_rtc = 0;
  }
  loop_rtc++;
  DEBUG_LOG("rtclesen() ende");
}

void relay2(int neuan) { //nur zum belastung messen
  DEBUG_LOG("relay2()");
  if(neuan > 0){ digitalWrite(23, HIGH); }else{ digitalWrite(23, LOW); }
  if(neuan > 1){ digitalWrite(25, HIGH); }else{ digitalWrite(25, LOW); }
  if(neuan > 2){ digitalWrite(27, HIGH); }else{ digitalWrite(27, LOW); }
  if(neuan > 3){ digitalWrite(29, HIGH); }else{ digitalWrite(29, LOW); }
  if(neuan > 4){ digitalWrite(31, HIGH); }else{ digitalWrite(31, LOW); }
  if(neuan > 5){ digitalWrite(33, HIGH); }else{ digitalWrite(33, LOW); }
  if(neuan > 6){ digitalWrite(35, HIGH); }else{ digitalWrite(35, LOW); }
  if(neuan > 7){ digitalWrite(37, HIGH); }else{ digitalWrite(37, LOW); }
  if(neuan > 8){ digitalWrite(39, HIGH); }else{ digitalWrite(39, LOW); }
  if(neuan > 9){ digitalWrite(41, HIGH); }else{ digitalWrite(41, LOW); }
  if(neuan > 10){ digitalWrite(43, HIGH); }else{ digitalWrite(43, LOW); }
  if(neuan > 11){ digitalWrite(45, HIGH); }else{ digitalWrite(45, LOW); }
  if(neuan > 12){ digitalWrite(45, HIGH); }else{ digitalWrite(45, LOW); }
  if(neuan > 15){ neuan = 0; }
  DEBUG_LOG("relay2() ende");
}
