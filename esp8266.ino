void esp8266() {
  DEBUG_LOG("esp8266()");
  loop_esp_re++;
  if(loop_esp_re >= 150){ esp_reset_f(); loop_esp_re = 0; } //falls 5 min keine daten empfangen wurden startet der esp neu
  
  if(espSend != ""){
    Serial_esp.println(espSend);
    espSend = "";
  }else{
  
  if (Serial_esp.available()) { //Wenn daten empfangen wurden
    //loop_esp_re = 0;
    delay(50);
    String inData = "";
    
    while (Serial_esp.available() > 0) {
      inData += (char)Serial_esp.read();
    }
    
    String message     = inData;
    if(message.indexOf('ok') != -1){ //neustart zögern bei korrekter antwort
      loop_esp_re = 0;
    }
    
    int anfangPos      = message.indexOf('#');
    int gleichPos      = message.indexOf('=');
    int endePos        = message.indexOf(';');
    int sternPos       = message.indexOf('*');
    
    if(anfangPos != -1 && sternPos != -1) // wenn alle daten angekommen sind
    {
      int zeile = message.indexOf('\n');
      while (zeile != -1) {
        //anfangPos      = message.indexOf('#');
        anfangPos      = message.indexOf('#'+String(serien_nr)+':');
        gleichPos      = message.indexOf('=');
        endePos        = message.indexOf(';');
        
        if(anfangPos != -1) // wenn er richtige empfänger
        {
          empfang(message.substring(anfangPos+4,endePos));
        }
        
        message = message.substring(zeile+1, message.length());
        zeile = message.indexOf('\n');
      }
    }
  }
  }
  DEBUG_LOG("esp8266() ende");
}

void empfang(String geladen) {
  DEBUG_LOG("empfang()");
  int    gleichPos;

  if(geladen != "-1") {
    String message = geladen;
    gleichPos      = message.indexOf('=');
    if(gleichPos != -1)
    {
      sp = message.substring(0,gleichPos);
      String sp2 = message.substring(gleichPos+1,message.length());
      value = sp2.toInt();
      if(eep_bearbeiten(sp, value) == 1){
        Serial.print( "*" );
        Serial.print( serien_nr );
        Serial.print( ":" );
        Serial.print( sp );
        Serial.print( "=" );
        Serial.print( sp2 );
        Serial.println( ";" );
      }
    } 
    else
    {
      String sp = message.substring(0,message.length());

      Serial.print( "*" );
      Serial.print( serien_nr );
      Serial.print( ":" );
      Serial.print( sp );
      Serial.print( "=" );
      Serial.print( eep_bearbeiten(sp, -1) );
      Serial.println( ";" );
    }
  }
  geladen = "";
  DEBUG_LOG("empfang() ende");
}

void daten_esp() {
  DEBUG_LOG("daten_esp()");
  espSend = "s=";
  espSend += serien_nr;

  espSend += "&i=";
  espSend += te1;
  espSend += "_";
  
  espSend += te2;
  espSend += "_";
  
  espSend += h1;
  espSend += "_";
  
  espSend += h2;
  espSend += "_";
  
  espSend += ti;
  espSend += "_";
  
  espSend += to;
  espSend += "_";
  
  espSend += silo_offen;
  espSend += "_";
  
  espSend += (int)silo1;
  espSend += "_";
  
  espSend += (int)silo2;
  espSend += "_";
  
  espSend += myFu;
  espSend += "_";
  
  espSend += myWa;
  espSend += "_";
  
  espSend += loop_esp_nr;
  espSend += ";";
  
  loop_esp_nr++;
  if(loop_esp_nr >= 100){ loop_esp_nr = 0; }
  DEBUG_LOG("daten_esp() ende");
}

