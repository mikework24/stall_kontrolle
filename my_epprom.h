int silo_offen = 1;
int silo1x     = 0;
int silo2x     = 0;
int silo_kg    = 0;
int silo_T     = 0;
int wasser     = 0;
int wasser2    = 0;
int futter_sec = 590; //g
int licht_diff = 20; //20 min
int ti         = 0;
int to         = 0;
int t_jahr     = 2019;
int t_mon      = 11;
int t_tag      = 1;
int t1 = 1;
int t2 = 7;
int t3 = 14;
int t4 = 21;
int t5 = 28;
int u1 = 20;
int u2 = 20;
int u3 = 20;
int u4 = 20;
int u5 = 20;
int d1 = 1;
int d2 = 6;
int d3 = 8;
int d4 = 10;
int d5 = 10;
int m_lu = 60;
int lu_ak = 0;
int he_ak = 0;
int ku_ak = 0;
int li_op = 0;
int li_abg = 0;
int wa_im = 10;
int lu_2e_t = 7;
int lu_3e_t = 12;
int lu_tol = 50; //tolleranz zur normal temp 0,5 = 50
int lu_to2 = 150; //tolleranz zur normal temp 1,5 = 150  für 2 extractorgruppe
int lu_to3 = 250; //tolleranz zur normal temp 2,5 = 250  für 3 extractorgruppe
int te1_ka = 0; //analog kalibrierung
int te2_ka = 0; //analog kalibrierung
int he1_ka = 0; //digital feuchte kalibrierung
int he2_ka = 0; //digital feuchte kalibrierung

//epprom werte
const int EEPROM_MIN_ADDR = 0;
const int EEPROM_MAX_ADDR = 512;
const int BUFSIZE         = 6; 
char      buffer[BUFSIZE]; 


void eeprom_erase_all(byte b = 0xFF) {
  int i;
  for (i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++) {
    EEPROM.write(i, b);
  }
}

boolean eeprom_is_addr_ok(int addr) {
  return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}
 
void eeprom_serial_dump_table(int bytesPerRow = 16) {
  int i;
  int j;
  byte b;
  char buf[10];
  j = 0;
 
  for (i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++) {
    if (j == 0) {
      sprintf(buf, "%03X: ", i);
      Serial.print(buf);
    }
    b = EEPROM.read(i);
    sprintf(buf, "%02X ", b);
    j++;
    if (j == bytesPerRow) {
      j = 0;
      Serial.println(buf);
    } else  Serial.print(buf);
  }
}
 
boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) {
  int i;
 
  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) return false;
 
  for (i = 0; i < numBytes; i++) {
    EEPROM.write(startAddr + i, array[i]);
  }  return true;
}
 
boolean eeprom_write_int(int addr, int value) {
  byte *ptr;
 
  ptr = (byte*)&value;
  return eeprom_write_bytes(addr, ptr, sizeof(value));
}

boolean eeprom_read_bytes(int startAddr, byte array[], int numBytes) {
  int i;
 
  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) return false;
 
  for (i = 0; i < numBytes; i++) {
    array[i] = EEPROM.read(startAddr + i);
  } return true;
}
 
boolean eeprom_read_int(int addr, int* value) {
  return eeprom_read_bytes(addr, (byte*)value, sizeof(int));
}
 
boolean eeprom_write_string(int addr, const char* string) {
  int numBytes;
  numBytes = strlen(string) + 1;
 
  return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}
 
boolean eeprom_read_string(int addr, char* buffer, int bufSize) {
  byte ch;
  int bytesRead;
 
  if (!eeprom_is_addr_ok(addr)) return false;
  if (bufSize == 0) return false;
 
  if (bufSize == 1) {
    buffer[0] = 0;
    return true;
  }
 
  bytesRead = 0;
  ch = EEPROM.read(addr + bytesRead);
  buffer[bytesRead] = ch;
  bytesRead++;
 
  while ((ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= EEPROM_MAX_ADDR)) {
    ch = EEPROM.read(addr + bytesRead);
    buffer[bytesRead] = ch;
    bytesRead++;
  }
 
  if ((ch != 0x00) && (bytesRead >= 1)) buffer[bytesRead - 1] = 0;
 
  return true;
}

void initializeVariables()
{
  int lauf = 1;
  
  lauf++; // leer
  eeprom_read_int((BUFSIZE * lauf++),&silo1x     ); // silo1x
  eeprom_read_int((BUFSIZE * lauf++),&silo2x     ); // silo2x
  eeprom_read_int((BUFSIZE * lauf++),&silo_offen ); // silo_offen
  eeprom_read_int((BUFSIZE * lauf++),&silo_kg    ); // silo_kg
  eeprom_read_int((BUFSIZE * lauf++),&silo_T     ); // silo_T
  eeprom_read_int((BUFSIZE * lauf++),&wasser     ); // wasser
  eeprom_read_int((BUFSIZE * lauf++),&wasser2    ); // wasser2
  eeprom_read_int((BUFSIZE * lauf++),&licht_diff ); // licht_diff
  eeprom_read_int((BUFSIZE * lauf++),&ti         ); // ti
  eeprom_read_int((BUFSIZE * lauf++),&to         ); // to
  eeprom_read_int((BUFSIZE * lauf++),&futter_sec ); // futter_sec
  eeprom_read_int((BUFSIZE * lauf++),&t_jahr     ); // t_jahr
  eeprom_read_int((BUFSIZE * lauf++),&t_mon      ); // t_mon
  eeprom_read_int((BUFSIZE * lauf++),&t_tag      ); // t_tag
  eeprom_read_int((BUFSIZE * lauf++),&t1         ); // t1
  eeprom_read_int((BUFSIZE * lauf++),&t2         ); // t2
  eeprom_read_int((BUFSIZE * lauf++),&t3         ); // t3
  eeprom_read_int((BUFSIZE * lauf++),&t4         ); // t4
  eeprom_read_int((BUFSIZE * lauf++),&t5         ); // t5
  eeprom_read_int((BUFSIZE * lauf++),&u1         ); // u1
  eeprom_read_int((BUFSIZE * lauf++),&u2         ); // u2
  eeprom_read_int((BUFSIZE * lauf++),&u3         ); // u3
  eeprom_read_int((BUFSIZE * lauf++),&u4         ); // u4
  eeprom_read_int((BUFSIZE * lauf++),&u5         ); // u5
  eeprom_read_int((BUFSIZE * lauf++),&d1         ); // d1
  eeprom_read_int((BUFSIZE * lauf++),&d2         ); // d2
  eeprom_read_int((BUFSIZE * lauf++),&d3         ); // d3
  eeprom_read_int((BUFSIZE * lauf++),&d4         ); // d4
  eeprom_read_int((BUFSIZE * lauf++),&d5         ); // d5
  eeprom_read_int((BUFSIZE * lauf++),&m_lu       ); // m_lu
  eeprom_read_int((BUFSIZE * lauf++),&lu_ak      ); // lu_ak
  eeprom_read_int((BUFSIZE * lauf++),&he_ak      ); // he_ak
  eeprom_read_int((BUFSIZE * lauf++),&ku_ak      ); // ku_ak
  eeprom_read_int((BUFSIZE * lauf++),&li_op      ); // li_op
  eeprom_read_int((BUFSIZE * lauf++),&li_abg     ); // li_abg
  eeprom_read_int((BUFSIZE * lauf++),&wa_im      ); // wa_im
  eeprom_read_int((BUFSIZE * lauf++),&lu_2e_t    ); // lu_2e_t
  eeprom_read_int((BUFSIZE * lauf++),&lu_tol     ); // lu_tol
  eeprom_read_int((BUFSIZE * lauf++),&lu_to2     ); // lu_to2
  eeprom_read_int((BUFSIZE * lauf++),&te1_ka     ); // te1_ka
  eeprom_read_int((BUFSIZE * lauf++),&te2_ka     ); // te2_ka
  eeprom_read_int((BUFSIZE * lauf++),&lu_3e_t    ); // lu_3e_t
  eeprom_read_int((BUFSIZE * lauf++),&lu_to3     ); // lu_to3
  eeprom_read_int((BUFSIZE * lauf++),&he1_ka     ); // he1_ka
  eeprom_read_int((BUFSIZE * lauf++),&he2_ka     ); // he2_ka

}

void initializeEEPROM()
{
  int i;
  int statusFlag = EEPROM.read(0);
 
  if(WRITE_EEPROM || statusFlag != 49)
  {
    eeprom_erase_all();
    delay(500);
    eeprom_serial_dump_table();
    delay(500);
    strcpy(buffer, "1");
    eeprom_write_string(0, buffer);
    int lauf = 1;
    
    //Variablen ab hier 
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  leer
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  silo1x
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  silo2x
    eeprom_write_int((BUFSIZE * lauf++), 1);    //  silo_offen
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  silo_kg
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  silo_T
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  wasser
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  wasser2

    eeprom_write_int((BUFSIZE * lauf++), 20);  //  licht_diff
    eeprom_write_int((BUFSIZE * lauf++), 18000);//  ti
    eeprom_write_int((BUFSIZE * lauf++), 0);    //  to
    eeprom_write_int((BUFSIZE * lauf++), 590);  //  futter_sec
    eeprom_write_int((BUFSIZE * lauf++), 2015);  //  futter_sec
    eeprom_write_int((BUFSIZE * lauf++), 12);    //  futter_sec
    eeprom_write_int((BUFSIZE * lauf++), 3);     //  futter_sec
    
    eeprom_write_int((BUFSIZE * lauf++), 1);     //  t1
    eeprom_write_int((BUFSIZE * lauf++), 7);     //  t2
    eeprom_write_int((BUFSIZE * lauf++), 14);     //  t3
    eeprom_write_int((BUFSIZE * lauf++), 21);     //  t4
    eeprom_write_int((BUFSIZE * lauf++), 28);     //  t5
    
    eeprom_write_int((BUFSIZE * lauf++), 20);     //  u1
    eeprom_write_int((BUFSIZE * lauf++), 20);     //  u2
    eeprom_write_int((BUFSIZE * lauf++), 20);     //  u3
    eeprom_write_int((BUFSIZE * lauf++), 20);     //  u4
    eeprom_write_int((BUFSIZE * lauf++), 20);     //  u5
    
    eeprom_write_int((BUFSIZE * lauf++), 1);     //  u1
    eeprom_write_int((BUFSIZE * lauf++), 6);     //  u2
    eeprom_write_int((BUFSIZE * lauf++), 8);     //  u3
    eeprom_write_int((BUFSIZE * lauf++), 10);     //  u4
    eeprom_write_int((BUFSIZE * lauf++), 10);     //  u5
    
    eeprom_write_int((BUFSIZE * lauf++), 60);     //  m_lu
    eeprom_write_int((BUFSIZE * lauf++), 0);     //  lu_ak
    eeprom_write_int((BUFSIZE * lauf++), 0);     //  he_ak
    eeprom_write_int((BUFSIZE * lauf++), 0);     //  ku_ak
    eeprom_write_int((BUFSIZE * lauf++), 0);     //  li_op
    eeprom_write_int((BUFSIZE * lauf++), 0);     //  li_abg
    eeprom_write_int((BUFSIZE * lauf++), 10);    //  wa_im
    eeprom_write_int((BUFSIZE * lauf++), 7);     //lu_2e_t
    eeprom_write_int((BUFSIZE * lauf++), 50);     //lu_tol
    eeprom_write_int((BUFSIZE * lauf++), 150);     //lu_to2
    eeprom_write_int((BUFSIZE * lauf++), 0);     //te1_ka
    eeprom_write_int((BUFSIZE * lauf++), 0);     //te2_ka
    eeprom_write_int((BUFSIZE * lauf++), 12);     //lu_3e_t
    eeprom_write_int((BUFSIZE * lauf++), 250);     //lu_to3
    eeprom_write_int((BUFSIZE * lauf++), 0);     //he1_ka
    eeprom_write_int((BUFSIZE * lauf++), 0);     //he2_ka
    //ende der standardeinstellungen

    delay(200);
    eeprom_serial_dump_table();
    for (i = 0; i < BUFSIZE; i++) 
    {
      buffer[i] = 0;
    }
  }
}

int eep_bearbeiten(String name, int wert) {
  int zuruck;
  int stelle;
  int lehr = -1;
  if (wert == lehr){
    //Allgemein
    if (name == "lehr1"      ){ zuruck = 0;                  }
    if (name == "silo1x"     ){ zuruck = silo1x;             }
    if (name == "silo2x"     ){ zuruck = silo2x;             }
    if (name == "silo_offen" ){ zuruck = silo_offen;         }
    if (name == "silo_kg"    ){ zuruck = silo_kg;            }
    if (name == "silo_T"     ){ zuruck = silo_T;             }
    if (name == "w"          ){ zuruck = wasser;             }
    if (name == "w2"         ){ zuruck = wasser2;            }
    if (name == "licht_diff" ){ zuruck = licht_diff;         }
    if (name == "ti"         ){ zuruck = ti;                 }
    if (name == "to"         ){ zuruck = to;                 }
    if (name == "futter_sec" ){ zuruck = futter_sec;         }
    if (name == "t_jahr"     ){ zuruck = t_jahr;             }
    if (name == "t_mon"      ){ zuruck = t_mon;              }
    if (name == "t_tag"      ){ zuruck = t_tag;              }
    if (name == "t1"         ){ zuruck = t1;                 }
    if (name == "t2"         ){ zuruck = t2;                 }
    if (name == "t3"         ){ zuruck = t3;                 }
    if (name == "t4"         ){ zuruck = t4;                 }
    if (name == "t5"         ){ zuruck = t5;                 }
    if (name == "u1"         ){ zuruck = u1;                 }
    if (name == "u2"         ){ zuruck = u2;                 }
    if (name == "u3"         ){ zuruck = u3;                 }
    if (name == "u4"         ){ zuruck = u4;                 }
    if (name == "u5"         ){ zuruck = u5;                 }
    if (name == "d1"         ){ zuruck = d1;                 }
    if (name == "d2"         ){ zuruck = d2;                 }
    if (name == "d3"         ){ zuruck = d3;                 }
    if (name == "d4"         ){ zuruck = d4;                 }
    if (name == "d5"         ){ zuruck = d5;                 }
    if (name == "m_lu"       ){ zuruck = m_lu;               }
    if (name == "lu_ak"      ){ zuruck = lu_ak;              }
    if (name == "he_ak"      ){ zuruck = he_ak;              }
    if (name == "ku_ak"      ){ zuruck = ku_ak;              }
    if (name == "li_op"      ){ zuruck = li_op;              }
    if (name == "li_abg"     ){ zuruck = li_abg;             }
    if (name == "wa_im"      ){ zuruck = wa_im;              }
    if (name == "lu_2e_t"    ){ zuruck = lu_2e_t;            }
    if (name == "lu_tol"     ){ zuruck = lu_tol;             }
    if (name == "lu_to2"     ){ zuruck = lu_to2;             }
    if (name == "te1_ka"     ){ zuruck = te1_ka;             }
    if (name == "te2_ka"     ){ zuruck = te2_ka;             }
    if (name == "lu_3e_t"    ){ zuruck = lu_3e_t;            }
    if (name == "lu_to3"     ){ zuruck = lu_to3;             }
    if (name == "he1_ka"     ){ zuruck = he1_ka;             }
    if (name == "he2_ka"     ){ zuruck = he2_ka;             }
    
  }else{
    if (name == "reset" && wert == 1 ){//Neuschreiben des EEPROM
      strcpy(buffer, "0");
      eeprom_write_string(0, buffer);
      initializeEEPROM();
      initializeVariables();
    }

    if (name == "lehr1"      ){ stelle = (BUFSIZE * 1); }  
    if (name == "silo1x"     ){ stelle = (BUFSIZE * 2);  silo1x       = wert; }
    if (name == "silo2x"     ){ stelle = (BUFSIZE * 3);  silo2x       = wert; }
    if (name == "silo_offen" ){ stelle = (BUFSIZE * 4);  silo_offen   = wert; }
    if (name == "silo_kg"    ){ stelle = (BUFSIZE * 5);  silo_kg      = wert; }
    if (name == "silo_T"     ){ stelle = (BUFSIZE * 6);  silo_T       = wert; }
    if (name == "w"          ){ stelle = (BUFSIZE * 7);  wasser       = wert; }
    if (name == "w2"         ){ stelle = (BUFSIZE * 8);  wasser2      = wert; }
    if (name == "licht_diff" ){ stelle = (BUFSIZE * 9); licht_diff   = wert; }
    if (name == "ti"         ){ stelle = (BUFSIZE * 10); ti           = wert; }
    if (name == "to"         ){ stelle = (BUFSIZE * 11); to           = wert; }
    if (name == "futter_sec" ){ stelle = (BUFSIZE * 12); futter_sec   = wert; }
    if (name == "t_jahr"     ){ stelle = (BUFSIZE * 13); t_jahr       = wert; }
    if (name == "t_mon"      ){ stelle = (BUFSIZE * 14); t_mon        = wert; }
    if (name == "t_tag"      ){ stelle = (BUFSIZE * 15); t_tag        = wert; }
    if (name == "t1"         ){ stelle = (BUFSIZE * 16); t1           = wert; }
    if (name == "t2"         ){ stelle = (BUFSIZE * 17); t2           = wert; }
    if (name == "t3"         ){ stelle = (BUFSIZE * 18); t3           = wert; }
    if (name == "t4"         ){ stelle = (BUFSIZE * 19); t4           = wert; }
    if (name == "t5"         ){ stelle = (BUFSIZE * 20); t5           = wert; }
    if (name == "u1"         ){ stelle = (BUFSIZE * 21); u1           = wert; }
    if (name == "u2"         ){ stelle = (BUFSIZE * 22); u2           = wert; }
    if (name == "u3"         ){ stelle = (BUFSIZE * 23); u3           = wert; }
    if (name == "u4"         ){ stelle = (BUFSIZE * 24); u4           = wert; }
    if (name == "u5"         ){ stelle = (BUFSIZE * 25); u5           = wert; }
    if (name == "d1"         ){ stelle = (BUFSIZE * 26); d1           = wert; }
    if (name == "d2"         ){ stelle = (BUFSIZE * 27); d2           = wert; }
    if (name == "d3"         ){ stelle = (BUFSIZE * 28); d3           = wert; }
    if (name == "d4"         ){ stelle = (BUFSIZE * 29); d4           = wert; }
    if (name == "d5"         ){ stelle = (BUFSIZE * 30); d5           = wert; }   
    if (name == "m_lu"       ){ stelle = (BUFSIZE * 31); m_lu         = wert; }
    if (name == "lu_ak"      ){ stelle = (BUFSIZE * 32); lu_ak        = wert; }
    if (name == "he_ak"      ){ stelle = (BUFSIZE * 33); he_ak        = wert; }
    if (name == "ku_ak"      ){ stelle = (BUFSIZE * 34); ku_ak        = wert; }
    if (name == "li_op"      ){ stelle = (BUFSIZE * 35); li_op        = wert; }
    if (name == "li_abg"     ){ stelle = (BUFSIZE * 36); li_abg       = wert; }
    if (name == "wa_im"      ){ stelle = (BUFSIZE * 37); wa_im        = wert; }
    if (name == "lu_2e_t"    ){ stelle = (BUFSIZE * 38); lu_2e_t      = wert; }
    if (name == "lu_tol"     ){ stelle = (BUFSIZE * 39); lu_tol       = wert; }
    if (name == "lu_to2"     ){ stelle = (BUFSIZE * 40); lu_to2       = wert; }
    if (name == "te1_ka"     ){ stelle = (BUFSIZE * 41); te1_ka       = wert; }
    if (name == "te2_ka"     ){ stelle = (BUFSIZE * 42); te2_ka       = wert; }
    if (name == "lu_3e_t"    ){ stelle = (BUFSIZE * 43); lu_3e_t      = wert; }
    if (name == "lu_to3"     ){ stelle = (BUFSIZE * 44); lu_to3       = wert; }
    if (name == "he1_ka"     ){ stelle = (BUFSIZE * 45); he1_ka       = wert; }
    if (name == "he2_ka"     ){ stelle = (BUFSIZE * 46); he2_ka       = wert; }

    if(stelle != lehr){
      eeprom_write_int(stelle, wert);
      zuruck = 1;
    }
    
    //rückmeldung an server bei nächster übertragung
    //EthernetData+="&";
    //EthernetData+=name;
    //EthernetData+="=";
    //EthernetData+=wert;

  }
  return zuruck;
}



String readSerial() {
  String inData = "";
  if (Serial.available() > 0) {
    delay(500); 
    int h = Serial.available();
    for (int i = 0; i < h; i++) {
      inData += (char)Serial.read();
    }
    return inData;
  } else {
    return "-1";
  }
}

void empfang() {
  int    doppelpunktPosition;
  int    gleichPosition;
  int    simikPosition;
  String geladen = readSerial();
  if(geladen != "-1") {
    String message = geladen;
    doppelpunktPosition = message.indexOf(':');
    gleichPosition      = message.indexOf('=');
    simikPosition       = message.indexOf(';');
    if(simikPosition != -1 && doppelpunktPosition != -1)
    {
      if(gleichPosition != -1)
      {
        String sp = message.substring(1,gleichPosition);
        message = message.substring(gleichPosition+1, message.length());
        String sp2 = message.substring(0,message.length()-1);
        int value = sp2.toInt();
        if(eep_bearbeiten(sp, value) == 1){
          Serial.print( sp );
          Serial.print( "=" );
          Serial.println( sp2 );
        }
      } else {
        String sp = message.substring(1,message.length()-1);
        Serial.print( sp );
        Serial.print( "=" );
        Serial.print( eep_bearbeiten(sp, -1) );
        Serial.println( ";" );
      }
    }
  }
  geladen = "";
}
