void tastatur() {
  DEBUG_LOG("tastatur()");
  int tas1, tas2, tas3, tas4;
  int tastatur1 = analogRead(8);
  int tastatur2 = analogRead(9);
  int tastatur3 = analogRead(10);
  int tastatur4 = analogRead(11);
  
  if(tastatur1 != 0)
  {
    delay(10);
    tas1 = analogRead(8);
    if(tastatur1 < tas1){ tastatur1 = tas1; }
    delay(10);
    tas1 = analogRead(8);
    if(tastatur1 < tas1){ tastatur1 = tas1; }
    delay(10);
    tas1 = analogRead(8);
    if(tastatur1 < tas1){ tastatur1 = tas1; }
  }
  
  if(tastatur2 != 0)
  {
    delay(10);
    tas2 = analogRead(9);
    if(tastatur2 < tas2){ tastatur2 = tas2; }
    delay(10);
    tas2 = analogRead(9);
    if(tastatur2 < tas2){ tastatur2 = tas2; }
    delay(10);
    tas2 = analogRead(9);
    if(tastatur2 < tas2){ tastatur2 = tas2; }
  }
  
  if(tastatur3 != 0)
  {
    delay(10);
    tas3 = analogRead(10);
    if(tastatur3 < tas3){ tastatur3 = tas3; }
    delay(10);
    tas3 = analogRead(10);
    if(tastatur3 < tas3){ tastatur3 = tas3; }
    delay(10);
    tas3 = analogRead(10);
    if(tastatur3 < tas3){ tastatur3 = tas3; }
  }
  
  if(tastatur4 != 0)
  {
    delay(10);
    tas4 = analogRead(11);
    if(tastatur4 < tas4){ tastatur4 = tas4; }
    delay(10);
    tas4 = analogRead(11);
    if(tastatur4 < tas4){ tastatur4 = tas4; }
    delay(10);
    tas4 = analogRead(11);
    if(tastatur4 < tas4){ tastatur4 = tas4; }
  }

  
  String tasteX         = "";
  
  if(tastatur1 > 180 && tastatur1 < 280)  { tasteX = "D"; }
  if(tastatur1 > 280 && tastatur1 < 400)  { tasteX = "C"; }
  if(tastatur1 > 400 && tastatur1 < 750)  { tasteX = "B"; }
  if(tastatur1 > 900 && tastatur1 < 1025) { tasteX = "A"; }
  
  if(tastatur2 > 180 && tastatur2 < 280)  { tasteX = "#"; }
  if(tastatur2 > 280 && tastatur2 < 400)  { tasteX = "9"; }
  if(tastatur2 > 400 && tastatur2 < 750)  { tasteX = "6"; }
  if(tastatur2 > 900 && tastatur2 < 1025) { tasteX = "3"; }
  
  if(tastatur3 > 180 && tastatur3 < 280)  { tasteX = "0"; }
  if(tastatur3 > 280 && tastatur3 < 400)  { tasteX = "8"; }
  if(tastatur3 > 400 && tastatur3 < 750)  { tasteX = "5"; }
  if(tastatur3 > 900 && tastatur3 < 1025) { tasteX = "2"; }
  
  if(tastatur4 > 180 && tastatur4 < 280)  { tasteX = "*"; }
  if(tastatur4 > 280 && tastatur4 < 400)  { tasteX = "7"; }
  if(tastatur4 > 400 && tastatur4 < 750)  { tasteX = "4"; }
  if(tastatur4 > 900 && tastatur4 < 1025) { tasteX = "1"; }
  
  if(tasteX == ""){
    taste   = "";
    taste_a = "";
    taste_r = "";
  }
  
  if(taste_a != tasteX){
    taste_a = tasteX;
    taste   = tasteX;
    taste_r = tasteX;
    
    displayX();
    delay(200);
  }
  DEBUG_LOG("tastatur() ende");
}

void wasser_f() {
  DEBUG_LOG("wasser_f()");
  int aW = analogRead(1);
  
  if(aW > 200 && wasserN == 0){
    wasser = wasser + wa_im;
    if(wasser >= 1000){
      wasser = 0;
      wasser2++;
      eep_bearbeiten("w2", wasser2);
    }
    
    eep_bearbeiten("w", wasser); //speichern
    wasserN = 1;
  }
  
  if(aW < 200 && wasserN == 1){
    wasserN = 0;
  }
  
  waT     = (float)wasser2+((float)wasser/1000);
  dtostrf(waT,1,2,myWa);
  DEBUG_LOG("wasser_f() ende");
}


void silo() {
  DEBUG_LOG("silo()");
  int a1 = analogRead(0);
  
  if(a1 > 200)
  {
    if(silo_offen == 0)
    {
      if((int)silo2 != 0)
      {
        eep_bearbeiten("silo2x", 0); //speichern
        silo2x = 0;
        silo2  = 0;
      }
    }else{
      if((int)silo1 == 0 && (int)silo2 != 0 && silo_offen == 1) { silo_offen = 2; eep_bearbeiten("silo_offen", 2); }
      if((int)silo2 == 0 && (int)silo1 != 0 && silo_offen == 2) { silo_offen = 1; eep_bearbeiten("silo_offen", 1); }
    }
    //fehler vermeiden
    if( silo_kg < 0){ eep_bearbeiten("silo_kg", 0); }
    if( silo_T > 300 || silo_T < 0){ eep_bearbeiten("silo_T", 0); }
    
    //berechnen des gesamtverbrauch
    silo_kg = silo_kg + 1;
    if( (1000000 / futter_sec) <= silo_kg ){
      silo_kg = 0;
      silo_T++;
      eep_bearbeiten("silo_T", silo_T); //speichern
      eep_bearbeiten("silo_kg", silo_kg); //speichern
    }
    
    if(silo_offen == 2)
    {
      silo2 = silo2 - ( (float)futter_sec / 1000 );
      if(silo2 < 0) { silo2 = 0; }
    }else{
      silo1 = silo1 - ( (float)futter_sec / 1000 );
      if(silo1 < 0) { silo1 = 0; }
    }
  }
  
  silo_save++;
  if(silo_save >= 60){
    
    if((int)silo1 != silo1x){
      eep_bearbeiten("silo_kg", silo_kg); //speichern
      eep_bearbeiten("silo1x", (int)silo1); //speichern
      silo1x = (int)silo1;
    }
    
    if((int)silo2 != silo2x){
      eep_bearbeiten("silo_kg", silo_kg); //speichern
      eep_bearbeiten("silo2x", (int)silo2); //speichern
      silo2x = (int)silo2;
    }

    silo_save = 0;
  }
  
  fuT     = (float)silo_T+( (float)silo_kg * (float)futter_sec / 1000000 );
  dtostrf(fuT,1,2,myFu);
  DEBUG_LOG("silo() ende");
}


int temp2(int nummer) {
  DEBUG_LOG("temp2()");
  //eingang 4 und 5
  uint8_t i;
  float average;
  float THERMISTORNOMINAL = 10000;
  float TEMPERATURENOMINAL = 25.0;
  float NUMSAMPLES = 5;
  float BCOEFFICIENT = 3435;
  float SERIESRESISTOR = 10000;
  int samples[5];
 
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(nummer);
  }
 
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
 
  float steinhart;
  steinhart = THERMISTORNOMINAL / average;          // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // convert to C
  
  if(steinhart <= -10 || steinhart >= 65)
  {
    DEBUG_LOG("temp2() ende");
    return 9999;
  }else{
    //Widerstand=THERMISTORNOMINAL*(Messwert/(1023.0-Messwert));
    
    if(tempR == 0)
    {
       tempD[1] = int(steinhart*100);
       tempD[2] = int(steinhart*100);
       tempD[3] = int(steinhart*100);
       tempD[4] = int(steinhart*100);
       tempD[5] = int(steinhart*100);
       tempR    = 1;
       DEBUG_LOG("temp2() ende");
       return int(steinhart*100);
    }else{
      if(tempR > 5){ tempR = 1;}
      tempD[tempR] = int(steinhart*100);
      tempR++;
      
      int dur_temp = 0;
      for (i=1; i< 6; i++) {
         dur_temp += tempD[i];
      }
      dur_temp /= 5;

      DEBUG_LOG("temp2() ende");
      return dur_temp;
    }
  }
  
}


void temp_dht1() {
  DEBUG_LOG("temp_dht1()");
  
  int te1akt = 0;
  int wi_re = 0;
  float h3x = dht1.readHumidity();
  float t3x = dht1.readTemperature();
  if (isnan(t3x) || isnan(h3x))
  {
      //was soll geschehen wenn keine digitalen daten da sind (analog daten nutzen)
      wi_re = 1;
      int analog4 = temp2(4);
      if(analog4 != 9999)
      {
        te1akt = analog4 + te1_ka;
      }
  }
  else 
  {
    //digitale daten
    if(t3x >= -5 && t3x <= 60 && h3x != 0)
    {
      //h1 = (int)(h3x*100);
      h1 = (he1_ka*100) + (int)(h3x*100);
      if(h1 > 10000){ h1 = 10000; }
      if(h1 < 0){ h1 = 0; }
      te1akt = (int)(t3x*100);
    }
  }
  if( te1 == 2500){ te1 = te1akt; }
  if( te1 < te1akt ){ te1 = te1 + 10; }
  if( te1 > te1akt ){ te1 = te1 - 10; }
  
  
  //nachster sensor
  int te2akt = 0;
  float h2x = dht2.readHumidity();
  float t2x = dht2.readTemperature();
  if (isnan(t2x) || isnan(h2x))
  {
      //was soll geschehen wenn keine daten kommen
      wi_re = 1;
      int analog5 = temp2(5);
      if(analog5 != 9999)
      {
        te2akt = analog5 + te2_ka;
      }
  } 
  else 
  {
    if(t2x >= -5 && t2x <= 60 && h2x != 0)
    {
      h2 = (he2_ka*100) + (int)(h2x*100);
      if(h2 > 10000){ h2 = 10000; }
      if(h2 < 0){ h2 = 0; }
      te2akt = (int)(t2x*100);
    }
  }
  if( te2 == 2500){ te2 = te2akt; }
  if( te2 < te2akt ){ te2 = te2 + 10; }
  if( te2 > te2akt ){ te2 = te2 - 10; }
  
  
  if(wi_re == 1)
  {
    wire_reset_f();
  }
  DEBUG_LOG("temp_dht1() ende");
}
