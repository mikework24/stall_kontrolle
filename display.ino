void displayX() {
  DEBUG_LOG("displayX()");
  char stringbuf[6];
  if ( dt <= secund ) {
    dm = 0;
    futtermenge = "0";
  }

  disp++;
  if (disp >= 30 && dm == 0) {//jede 2 minuten display neu verbinden
    lcd.init();
    lcd.backlight();
    disp = 0;
  }

  if (dm == 0) { //Startseite
    neue_zeit = (time_rtc + secund);
    int si_offen;
    int h1_int = float(h1 / 100);
    int te1_int = float(te1 / 100);
    if (silo_offen == 0) {
      si_offen = 100;
    } else {
      si_offen = 10;
    }
    if (menu_t(si_offen, 20, 30, 40)) {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GALPON: ");
      if (h1_int < 10) { lcd.print(" "); }
      lcd.print(h1_int);
      if (h1_int == 100) { lcd.print("%  "); } else { lcd.print(" %  "); }
      lcd.setCursor(13, 0);
      if (te1_int < 10) { lcd.print(" "); }
      lcd.print(float(te1 / 10) / 10, 1);
      lcd.setCursor(17, 0);
      lcd.print(" " + String((char)223) + "C");

      lcd.setCursor(0, 1);
      lcd.print("MUERTO: " + String(to) + "     ");
      lcd.setCursor(14, 1);
      lcd.print((100.00 * (float)to / ((float)ti * 2.00)));
      lcd.setCursor(18, 1);
      lcd.print(" %");

      lcd.setCursor(0, 2);
      if (silo_offen == 0)
      {
        //falls nur 1 Silo vorhanden ist
        lcd.print("SILO 1:     ");
        lcd.print(stellen(silo1));
        lcd.setCursor(17, 2);
        lcd.print(" KG");
      } else {
        //bei 2 Silos
        if (silo_offen == 2) { lcd.print("SILO 2: "); } else { lcd.print("SILO 1:>"); }
        int silo_m = (int)(silo1 / 100);
        if (silo_m <= 99) { lcd.print(" "); }
        lcd.print(float(silo1 / 100) / 10, 1);
        lcd.print("T   ");

        lcd.setCursor(14, 2);
        if (silo_offen == 2) { lcd.print(">"); } else { lcd.print(" "); }
        silo_m = (int)(silo2 / 100);
        if (silo_m <= 99) { lcd.print(" "); }
        lcd.print(float(silo2 / 100) / 10, 1);
        lcd.print("T");
      }

      //zeile 3
      int turt_dis = turtag;
      if(turt_dis > 99){ turt_dis = 99; }
      lcd.setCursor(0, 3);
      lcd.print("DIA: ");
      lcd.print(turt_dis);
      lcd.print("  ");

      lcd.setCursor(8, 3);
      if ( future.hour() < 10 ) { lcd.print("0"); }
      lcd.print(future.hour());
      lcd.print(":");
      if ( future.minute() < 10 ) { lcd.print("0"); }
      lcd.print(future.minute());

      lcd.print("  ");
      if ( future.day() < 10 ) { lcd.print("0"); }
      lcd.print(future.day());
      lcd.print(".");
      if ( future.month() < 10 ) { lcd.print("0"); }
      lcd.print(future.month());
    }
  }

  if (dm == 10 || dm == 11) { //A 10 und 11 Silo ändern
    if (menu_t(dm * 10, 10, 11, 0)) {
      lcd.setCursor(0, 0);
      lcd.print("Elegir Silo         ");

      lcd.setCursor(0, 1);
      if (dm == 10) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Silo 1:   ");
      lcd.print(stellen(silo1));
      //lcd.setCursor(18, 1);
      lcd.print(" KG");

      lcd.setCursor(0, 2);
      if (dm == 11) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Silo 2:   ");
      lcd.print(stellen(silo2));
      //lcd.setCursor(18, 2);
      lcd.print(" KG");

      lcd.setCursor(0, 3);
      lcd.print("                    ");
    }
  }

  if (dm == 100 || dm == 101 || dm == 102 || dm == 110 || dm == 111 || dm == 112) { //A 100 und 110 Silo ändern
    int za1 = 0;
    int za2 = 0;
    int za3 = 0;
    if (silo_offen == 0) {
      if (dm == 100 || dm == 101) {//falls nur ein silo existiert wird das menü 10 übersprungen
        za1 = 0;
      }
      if (dm == 100 || dm == 110) {
        za2 = dm;
        za3 = dm + 1;
      }
      if (dm == 101 || dm == 111) {
        za2 = dm - 1;
        za3 = dm;
      }
    } else {
      if (dm == 100 || dm == 101 || dm == 102) {
        za1 = 10;
      } else {
        za1 = 11;
      }
      if (dm == 100 || dm == 110) {
        za2 = dm;
        za3 = dm + 1;
      }
      if (dm == 101 || dm == 111) {
        za2 = dm - 1;
        za3 = dm;
        if (silo_offen == 1 && dm == 111) { za3 = dm + 1; }
        if (silo_offen == 2 && dm == 101) { za3 = dm + 1; }
      }
      if (dm == 102 || dm == 112) {
        za2 = dm - 1;
        za3 = dm;
      }
    }
    if (menu_t(dm * 10, za2, za3, za1)) {
      futtermenge = "";
      lcd.setCursor(0, 0);
      if (dm == 100 || dm == 101 || dm == 102) {
        lcd.print("Silo 1      ");
        lcd.print(stellen(silo1));
      }
      else {
        lcd.print("Silo 2      ");
        lcd.print(stellen(silo2));
      }
      
      lcd.print(" KG");

      lcd.setCursor(0, 1);
      if (dm == 100 || dm == 110) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Nueva recepcion   ");

      lcd.setCursor(0, 2);
      if (dm == 101 || dm == 111) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Modificar stock   ");

      lcd.setCursor(0, 3);
      if (silo_offen != 0)
      {
        if (dm == 102 || dm == 112) { lcd.print("> "); } else { lcd.print("  "); }
        if ( dm == 110 || dm == 111 || dm == 112 ) {
          if (silo_offen != 1) {
            //lcd.print("Silo elegido");
          } else {
            lcd.print("Elegir Silo       ");
          }
        }
        else {
          if (silo_offen != 2) {
            //lcd.print("Silo elegido");
          } else {
            lcd.print("Elegir Silo       ");
          }
        }
      }else{
        lcd.print("                    ");
      }
    }
  }


  if (dm == 1000 || dm == 1100) { //A 1010 und 1110 Silo Liferung
    if (menu_t(dm * 10, dm, dm, dm / 10)) {
      if(futtermenge.toInt() > 32000){ futtermenge = ""; }
      lcd.setCursor(0, 0);
      lcd.print("Nueva recepcion:    ");

      lcd.setCursor(0, 1);
      if (dm == 1000) {
        lcd.print("Silo 1:     ");
      }
      else {
        lcd.print("Silo 2:     ");
      }
      lcd.print(stellen(futtermenge.toInt()));
      lcd.print(" KG");

      lcd.setCursor(0, 2);
      lcd.print("Stock actual:       ");
      lcd.setCursor(0, 3);
      lcd.print("            ");
      if (dm == 1000) { lcd.print(stellen((int)silo1)); } else { lcd.print(stellen((int)silo2)); }
      lcd.print(" KG");
    }
  }

  if (dm == 10000 || dm == 11000) { //A 1010 und 1110 Silo ändern
    lcd.setCursor(0, 0);
    lcd.print("Recepcion aceptada  ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    if (dm == 10000) {
      eep_bearbeiten("silo1x", futtermenge.toInt() + silo1); //speichern
      silo1x = futtermenge.toInt() + silo1;
      silo1  = futtermenge.toInt() + silo1;
    } else {
      eep_bearbeiten("silo2x", futtermenge.toInt() + silo2); //speichern
      silo2x = futtermenge.toInt() + silo2;
      silo2  = futtermenge.toInt() + silo2;
    }
    futtermenge = "";
    dm = 0;
    dt = secund + 1;
  }


  if (dm == 1010 || dm == 1110) { //A 1010 und 1110 Silo ändern
    if (menu_t(dm * 10, dm, dm, dm / 10)) {
      if(futtermenge.toInt() > 32000){ futtermenge = ""; }
      lcd.setCursor(0, 0);
      lcd.print("Modificar stock     ");

      lcd.setCursor(0, 1);
      if (dm == 1010) { lcd.print("Silo 1:     "); } else { lcd.print("Silo 2:     "); }
      lcd.print(stellen(futtermenge.toInt()));
      lcd.print(" KG");

      lcd.setCursor(0, 2);
      lcd.print("Stock anterior:     ");
      lcd.setCursor(0, 3);
      lcd.print("            ");
      if (dm == 1010) { lcd.print(stellen((int)silo1)); } else { lcd.print(stellen((int)silo2)); }
      lcd.print(" KG");
    }
  }

  if (dm == 10100 || dm == 11100) { //A 1010 und 1110 Silo ändern
    lcd.setCursor(0, 0);
    lcd.print("Stock aceptado!     ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    if (dm == 10100) {
      eep_bearbeiten("silo1x", futtermenge.toInt()); //speichern
      silo1x = futtermenge.toInt();
      silo1  = futtermenge.toInt();
    } else {
      eep_bearbeiten("silo2x", futtermenge.toInt()); //speichern
      silo2x = futtermenge.toInt();
      silo2  = futtermenge.toInt();
    }
    futtermenge = "";
    dm = 0;
    dt = secund + 1;
  }


  if (dm == 1020 || dm == 1120) { //A 1010 und 1110 Silo ändern
    lcd.setCursor(0, 0);
    lcd.print("Silo elegido        ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    if (dm == 1120 && silo_offen == 1) {
      silo_offen = 2;
      eep_bearbeiten("silo_offen", 2);
    }

    if (dm == 1020 && silo_offen == 2) {
      silo_offen = 1;
      eep_bearbeiten("silo_offen", 1);
    }

    dm = 0;
    dt = secund + 1;
  }
  //silo ende

  if (dm == 20) { //B
    if (menu_t(20, 20, 20, 0)) {
      lcd.setCursor(0, 0);
      lcd.print("Serie: ");
      lcd.print(serien_nr);
      lcd.print("    V: ");
      lcd.print(versionNr);
      lcd.print(" ");
      
      lcd.setCursor(16, 1);
      lcd.print("    ");

      lcd.setCursor(0, 1);
      lcd.print("Inic.:");
      lcd.print(tag_z);
      lcd.print(" dias ");
      lcd.print(stu_z);
      lcd.print(":");
      lcd.print(min_z);

      lcd.setCursor(16, 2);
      lcd.print("    ");
      
      lcd.setCursor(0, 2);
      lcd.print("In :");
      if (analogRead(0) >= 200) { lcd.print("1"); } else { lcd.print("0"); }
      if (analogRead(1) >= 200) { lcd.print("1"); } else { lcd.print("0"); }
      if (analogRead(2) >= 200) { lcd.print("1"); } else { lcd.print("0"); }
      if (analogRead(3) >= 200) { lcd.print("1"); } else { lcd.print("0"); }
      lcd.print(" ");
      //lcd.print(temp1(4));
      //lcd.print(" ");
      //lcd.print(temp1(5));
      //lcd.print(" ");
      lcd.print(float(te1 / 10) / 10, 0);
      lcd.print(" ");
      lcd.print(float(te2 / 10) / 10, 0);
      


      lcd.setCursor(0, 3);
      lcd.print("Out:");
      lcd.print(r1z);
      lcd.print(r2z);
      lcd.print(r3z);
      lcd.print(r4z);
      lcd.print(" ");
      lcd.print(r5z);
      lcd.print(r6z);
      lcd.print(r7z);
      lcd.print(r8z);
      lcd.print(r9z);
      lcd.print(r10z);
      lcd.print(r11z);
      lcd.print(r12z);
      lcd.print("   ");
    }
  }

  if (dm == 30) { //C
    if (menu_t(30, 30, 30, 0)) {
      lcd.setCursor(0, 0);
      lcd.print("Consumo             ");

      lcd.setCursor(16, 1);
      lcd.print("    ");
      
      lcd.setCursor(0, 1);
      lcd.print("Agua:       ");
      lcd.print((float)wasser2 + ((float)wasser / 1000));

      lcd.setCursor(16, 2);
      lcd.print("    ");
      
      lcd.setCursor(0, 2);
      lcd.print("Balanceado: ");
      lcd.print( (float)silo_T + ( (float)silo_kg * (float)futter_sec / 1000000 ) );

      lcd.setCursor(0, 3);
      lcd.print("                    ");
      
      if(loop_esp_re >= 40){
        lcd.setCursor(0, 3);
        lcd.print("ESP TIMER: ");
        lcd.print( ((150-(int)loop_esp_re)*2) );
        lcd.print(" sec");
      }
      
    }
  }

  if (dm >= 40 && dm <= 43) { //D -> Einstellungen
    int menu_a, menu_b, menu_c, seite;
    seite = 1;
    if (dm == 40) {
      menu_a = 400;
      menu_b = 40;
      menu_c = 41;
    }
    if (dm == 41) {
      menu_a = 410;
      menu_b = 40;
      menu_c = 42;
    }
    if (dm == 42) {
      menu_a = 420;
      menu_b = 41;
      menu_c = 43;
    }
    if (dm == 43) {
      menu_a = 430;
      menu_b = 42;
      menu_c = 43;
    }

    if (menu_t(menu_a, menu_b, menu_c, 0)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ajustes:");

      if (dm >= 40 && dm <= 42) {
        lcd.setCursor(0, seite);
        if (dm == 40) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Cria");
        seite++;
      }
      if (dm >= 40 && dm <= 43) {
        lcd.setCursor(0, seite);
        if (dm == 41) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Clima");
        seite++;
      }
      if (dm >= 40 && dm <= 44) {
        lcd.setCursor(0, seite);
        if (dm == 42) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Iluminaci");
        lcd.print(ochar);
        lcd.print("n");
        seite++;
      }
      if (dm >= 43 && dm <= 45) {
        lcd.setCursor(0, seite);
        if (dm == 43) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Calibrar");
        seite++;
      }
    }
  }

  if (dm >= 400 && dm <= 402) { //D -> Einstellungen
    int menu_a, menu_b, menu_c, seite;
    seite = 1;
    if (dm == 400) {
      menu_a = 4000;
      menu_b = 400;
      menu_c = 401;
    }
    if (dm == 401) {
      menu_a = 4010;
      menu_b = 400;
      menu_c = 402;
    }
    if (dm == 402) {
      menu_a = 4020;
      menu_b = 401;
      menu_c = 402;
    }

    if (menu_t(menu_a, menu_b, menu_c, 40)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cria:");

      if (dm >= 400 && dm <= 402) {
        lcd.setCursor(0, seite);
        if (dm == 400) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Nueva cira");
        seite++;
      }
      if (dm >= 400 && dm <= 403) {
        lcd.setCursor(0, seite);
        if (dm == 401) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Cantidad de pollo");
        seite++;
      }
      if (dm >= 400 && dm <= 404) {
        lcd.setCursor(0, seite);
        if (dm == 402) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Inicio de cria");
        seite++;
      }
    }
  }

  if (dm >= 410 && dm <= 412) { //D -> Einstellungen
    int menu_a, menu_b, menu_c, seite;
    seite = 1;
    if (dm == 410) {
      menu_a = 4100;
      menu_b = 410;
      menu_c = 411;
    }
    if (dm == 411) {
      menu_a = 4110;
      menu_b = 410;
      menu_c = 412;
    }
    if (dm == 412) {
      menu_a = 4120;
      menu_b = 411;
      menu_c = 412;
    }

    if (menu_t(menu_a, menu_b, menu_c, 41)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Clima:");

      if (dm >= 410 && dm <= 412) {
        lcd.setCursor(0, seite);
        if (dm == 410) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Ventilaci");
        lcd.print(ochar);
        lcd.print("n");
        seite++;
      }
      if (dm >= 410 && dm <= 412) {
        lcd.setCursor(0, seite);
        if (dm == 411) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Calefacci");
        lcd.print(ochar);
        lcd.print("n");
        seite++;
      }
      if (dm >= 410 && dm <= 412) {
        lcd.setCursor(0, seite);
        if (dm == 412) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Refrigeraci");
        lcd.print(ochar);
        lcd.print("n");
        seite++;
      }
    }
  }

  if (dm >= 430 && dm <= 436) { //D -> Einstellungen
    int menu_a, menu_b, menu_c, seite;
    seite = 1;
    if (dm == 430) {
      menu_a = 4300;
      menu_b = 430;
      menu_c = 431;
    }
    if (dm == 431) {
      menu_a = 4310;
      menu_b = 430;
      menu_c = 432;
    }
    if (dm == 432) {
      menu_a = 4320;
      menu_b = 431;
      menu_c = 433;
    }
    if (dm == 433) {
      menu_a = 4990;//feutigkeit
      menu_b = 432;
      menu_c = 434;
    }
    if (dm == 434) {
      if (li_op == 0) {
        menu_a = 4330;
      } else {
        menu_a = 4331;
      }
      menu_b = 433;
      menu_c = 435;
    }
    if (dm == 435) {
      menu_a = 4340;
      menu_b = 434;
      menu_c = 436;
    }
    if (dm == 436) {
      menu_a = 4350;
      menu_b = 435;
      menu_c = 436;
    }

    if (menu_t(menu_a, menu_b, menu_c, 43)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Calibraci");
      lcd.print(ochar);
      lcd.print("n:");

      if (dm >= 430 && dm <= 432) {
        lcd.setCursor(0, seite);
        if (dm == 430) { lcd.print("> ");
          futtermenge = "";
          futtermenge += futter_sec;
        } else { lcd.print("  "); }
        lcd.print("Balanceado");
        seite++;
      }
      if (dm >= 430 && dm <= 433) {
        lcd.setCursor(0, seite);
        if (dm == 431){ lcd.print("> "); futtermenge = ""; futtermenge += wa_im; } else { lcd.print("  "); }
        lcd.print("Agua");
        seite++;
      }
      if (dm >= 430 && dm <= 434) {
        lcd.setCursor(0, seite);
        if (dm == 432) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Temperatura");
        seite++;
      }
      if (dm >= 433 && dm <= 435) {
        lcd.setCursor(0, seite);
        if (dm == 433) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Humedad");
        seite++;
      }
      if (dm >= 434 && dm <= 436) {
        lcd.setCursor(0, seite);
        if (dm == 434) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Iluminaci");
        lcd.print(ochar);
        lcd.print("n");
        seite++;
      }
      if (dm >= 435 && dm <= 436) {
        lcd.setCursor(0, seite);
        if (dm == 435) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Reloj");
        seite++;
      }
      if (dm >= 436 && dm <= 436) {
        lcd.setCursor(0, seite);
        if (dm == 436) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Reajustar");
        seite++;
      }
    }
  }

  if (dm == 4000) { //B
    if (menu_t(4001, 4000, 4000, 400)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Nueva cria?");

      lcd.setCursor(0, 1);
      lcd.print("Confirmar (A)");
      lcd.setCursor(0, 2);
      lcd.print("Abortar   (D)");
    }
  }

  if (dm == 4001) { //B
    if (menu_t(4002, 4001, 4001, 4000)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Cantidad de Pollo");

      lcd.setCursor(0, 1);
      lcd.print("Cantidad: ");
      if(futtermenge.toInt() > 60000){ futtermenge = ""; }
      if(futtermenge.toInt() < 0){ futtermenge = ""; }
      lcd.print(futtermenge.toInt());

      lcd.setCursor(0, 2);
      lcd.print("Confirmar (A)");
      lcd.setCursor(0, 3);
      lcd.print("Abortar   (D)");
    }
  }

  if (dm == 4002) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Iniciando nueva cria");

    eep_bearbeiten("silo_kg",    0); //speichern
    eep_bearbeiten("silo_T",     0); //speichern
    eep_bearbeiten("w",     0); //speichern
    eep_bearbeiten("w2",    0); //speichern
    long neu_ti = futtermenge.toInt() / 2;
    if(neu_ti < 0 || neu_ti > 30000){ neu_ti = 0; }
    eep_bearbeiten("ti", neu_ti); //speichern
    eep_bearbeiten("to",         0); //speichern

    eep_bearbeiten("t_tag", neue_zeit.day()); //speichern
    eep_bearbeiten("t_mon", neue_zeit.month()); //speichern
    eep_bearbeiten("t_jahr", neue_zeit.year()); //speichern

    silo1 = (float)silo1x;
    silo2 = (float)silo2x;

    dm = 0;
    dt = secund + 1;
  }

  if (dm == 4010) {
    if (menu_t(4011, 4010, 4010, 401)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Cantidad de Pollo");
      lcd.setCursor(0, 1);
      lcd.print("Antes: ");
      lcd.print((long)ti * 2);
      lcd.setCursor(0, 2);
      lcd.print("Ahora: ");
      lcd.print(futtermenge.toInt());
      lcd.setCursor(0, 3);
      lcd.print("Confirmar (A)");
    }
  }

  if (dm == 4011) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Guardado");
    int neu_ti = futtermenge.toInt() / 2;
    if(neu_ti < 0 || neu_ti > 30000){ neu_ti = 0; }
    eep_bearbeiten("ti", neu_ti); //speichern
    dm = 0;
    dt = secund + 1;
  }

  if (dm == 4020) {
    if (menu_t(4021, 4022, 4023, 402)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Inicio de cria");
      lcd.setCursor(0, 1);
      lcd.print("Antes:    ");
      if ( t_tag < 10 ) { lcd.print("0"); }
      lcd.print(t_tag);
      lcd.print(".");
      if ( t_mon < 10 ) { lcd.print("0"); }
      lcd.print(t_mon);
      lcd.print(".");
      lcd.print(t_jahr);
      lcd.setCursor(0, 2);
      lcd.print("Ahora:    ");
      if ( neue_zeit.day() < 10 ) { lcd.print("0"); }
      lcd.print(neue_zeit.day());
      lcd.print(".");
      if ( neue_zeit.month() < 10 ) { lcd.print("0"); }
      lcd.print(neue_zeit.month());
      lcd.print(".");
      lcd.print(neue_zeit.year());
    }
  }

  if (dm == 4021) { //*
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Guardado");
    eep_bearbeiten("t_tag", neue_zeit.day()); //speichern
    eep_bearbeiten("t_mon", neue_zeit.month()); //speichern
    eep_bearbeiten("t_jahr", neue_zeit.year()); //speichern
    dm = 0;
    dt = secund + 1;
  }

  if (dm == 4022) { //*
    neue_zeit = (neue_zeit.unixtime() + 86400);
    dm = 4020;
    //dt =  secund + 1;
    displayX();
    delay(100);
  }

  if (dm == 4023) { //*
    neue_zeit = (neue_zeit.unixtime() - 86400);
    dm = 4020;
    //dt =  secund + 1;
    displayX();
    delay(100);
  }

  if (dm >= 4100 && dm <= 4106) {
    int menu_b, menu_c;
    menu_b = dm - 1;
    menu_c = dm + 1;
    
    if (dm == 4100) { menu_b = 4100; }
    if (dm == 4106) { menu_c = 4106; }
    
    if (lu_ak == 0) { menu_b = 4100; menu_c = 4100; }

    if (menu_t(dm + 50, menu_b, menu_c, 410)) {
      int seite = 1;
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Ventilaci");
      lcd.print(ochar);
      lcd.print("n");

      if (dm <= 4102)
      {
        lcd.setCursor(0, seite);
        if (dm == 4100) { lcd.print("> "); } else { lcd.print("  "); }
        if (lu_ak == 0) { lcd.print("Apagado"); } else { lcd.print("Activado"); }
        seite++;
      }
      
      if (lu_ak == 1) {
        if (dm <= 4103)
        {
          lcd.setCursor(0, seite);
          if (dm == 4101) { lcd.print("> "); } else { lcd.print("  "); }
          lcd.print("Ventilaci");
          lcd.print(ochar);
          lcd.print("n Minima");
          //lcd.print( m_lu );
          seite++;
        }

        if (dm <= 4104)
        {
          lcd.setCursor(0, seite);
          if (dm == 4102) { lcd.print("> "); } else { lcd.print("  "); }
          lcd.print("2 Ext. des dia: ");
          lcd.print( lu_2e_t );
          seite++;
        }
        
        if (dm >= 4103 && dm <= 4105 && seite <= 3)
        {
          lcd.setCursor(0, seite);
          if (dm == 4103) { lcd.print("> "); } else { lcd.print("  "); }
          lcd.print("3 Ext. des dia: ");
          lcd.print( lu_3e_t );
          seite++;
        }

        if (dm >= 4104 && seite <= 3)
        {
          lcd.setCursor(0, seite);
          if (dm == 4104) { lcd.print("> "); } else { lcd.print("  "); }
          lcd.print("1 Ext. de ");
          lcd.print( (float)lu_tol / 100, 1 );
          lcd.print(" C");
          seite++;
        }

        if (dm >= 4105 && seite <= 3)
        {
          lcd.setCursor(0, seite);
          if (dm == 4105) { lcd.print("> "); } else { lcd.print("  "); }
          lcd.print("2 Ext. de ");
          lcd.print( (float)lu_to2 / 100, 1 );
          lcd.print(" C");
          seite++;
        }
        
        if (dm == 4106 && seite <= 3)
        {
          lcd.setCursor(0, seite);
          if (dm == 4106) { lcd.print("> "); } else { lcd.print("  "); }
          lcd.print("3 Ext. de ");
          lcd.print( (float)lu_to3 / 100, 1 );
          lcd.print(" C");
          seite++;
        }
      }
    }
  }

  if (dm == 4150) {
    if (lu_ak == 0)
    {
      eep_bearbeiten("lu_ak", 1); //speichern
    } else {
      eep_bearbeiten("lu_ak", 0); //speichern
    }

    dm = 4100;
    displayX();
    delay(100);
  }

  if (dm == 4151) {
    if (taste == "B")
    {
      m_lu = m_lu + 10;
      if (m_lu > 300) {
        m_lu = 300;
      }
      eep_bearbeiten("m_lu", m_lu);
    }

    if (taste == "C")
    {
      m_lu = m_lu - 10;
      if (m_lu < 0) {
        m_lu = 0;
      }
      eep_bearbeiten("m_lu", m_lu);
    }

    if (menu_t(4101, 4151, 4151, 4101)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Ventilaci");
      lcd.print(ochar);
      lcd.print("n minima");

      lcd.setCursor(0, 1);
      lcd.print("> ");
      lcd.print( m_lu );
      lcd.print(" Sec Activado");
      
      lcd.setCursor(0, 2);
      lcd.print("  ");
      lcd.print( (300 - m_lu) );
      lcd.print(" Sec Apagado");
    }
  }

  if (dm == 4152) {
    if (taste == "B")
    {
      lu_2e_t = lu_2e_t + 1;
      if (lu_2e_t > 14) {
        lu_2e_t = 14;
      }
      eep_bearbeiten("lu_2e_t", lu_2e_t);
    }

    if (taste == "C")
    {
      lu_2e_t = lu_2e_t - 1;
      if (lu_2e_t < 1) {
        lu_2e_t = 1;
      }
      eep_bearbeiten("lu_2e_t", lu_2e_t);
    }

    if (menu_t(4102, 4152, 4152, 4102)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("2 Extraktores desde");

      lcd.setCursor(0, 1);
      lcd.print("> ");
      lcd.print( lu_2e_t );
      lcd.print(" dia");
    }
  }
  
  if (dm == 4153) {
    if (taste == "B")
    {
      lu_3e_t = lu_3e_t + 1;
      if (lu_3e_t > 21) {
        lu_3e_t = 21;
      }
      eep_bearbeiten("lu_3e_t", lu_3e_t);
    }

    if (taste == "C")
    {
      lu_3e_t = lu_3e_t - 1;
      if (lu_3e_t < 1) {
        lu_3e_t = 1;
      }
      eep_bearbeiten("lu_3e_t", lu_3e_t);
    }

    if (menu_t(4103, 4153, 4153, 4103)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("3 Extraktores desde");

      lcd.setCursor(0, 1);
      lcd.print("> ");
      lcd.print( lu_3e_t );
      lcd.print(" dia");
    }
  }

  if (dm == 4154) {
    if (taste == "B")
    {
      lu_tol = lu_tol + 10;
      if (lu_tol > (lu_to2 - 10)) {
        lu_tol = (lu_to2 - 10);
      }
      eep_bearbeiten("lu_tol", lu_tol);
    }

    if (taste == "C")
    {
      lu_tol = lu_tol - 10;
      if (lu_tol < 0) {
        lu_tol = 0;
      }
      eep_bearbeiten("lu_tol", lu_tol);
    }

    if (menu_t(4104, 4154, 4154, 4104)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("1 Extraktor");

      lcd.setCursor(0, 1);
      lcd.print("Continuado desde");

      lcd.setCursor(0, 2);
      lcd.print("> +");
      lcd.print( (float)lu_tol / 100, 1 );
      lcd.print(" dia");

      lcd.setCursor(0, 3);
      lcd.print("Sobre temp. ideal");
    }
  }

  if (dm == 4155) {
    if (taste == "B")
    {
      lu_to2 = lu_to2 + 10;
      if (lu_to2 > (lu_to3 - 10)) {
        lu_to2 = (lu_to3 - 10);
      }
      eep_bearbeiten("lu_to2", lu_to2);
    }

    if (taste == "C")
    {
      lu_to2 = lu_to2 - 10;
      if (lu_to2 < (lu_tol + 10)) {
        lu_to2 = (lu_tol + 10);
      }
      eep_bearbeiten("lu_to2", lu_to2);
    }

    if (menu_t(4105, 4155, 4155, 4105)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("2 Extraktores");

      lcd.setCursor(0, 1);
      lcd.print("continuado desde");

      lcd.setCursor(0, 2);
      lcd.print("> +");
      lcd.print( (float)lu_to2 / 100, 1 );
      lcd.print(" dia");

      lcd.setCursor(0, 3);
      lcd.print("Sobre temp. ideal");
    }
  }
  
  if (dm == 4156) {
    if (taste == "B")
    {
      lu_to3 = lu_to3 + 10;
      if (lu_to3 > 400) {
        lu_to3 = 400;
      }
      eep_bearbeiten("lu_to3", lu_to3);
    }

    if (taste == "C")
    {
      lu_to3 = lu_to3 - 10;
      if (lu_to3 < (lu_to2 + 10)) {
        lu_to3 = (lu_to2 + 10);
      }
      eep_bearbeiten("lu_to3", lu_to3);
    }

    if (menu_t(4106, 4156, 4156, 4106)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("3 Extraktores");

      lcd.setCursor(0, 1);
      lcd.print("continuado desde");

      lcd.setCursor(0, 2);
      lcd.print("> +");
      lcd.print( (float)lu_to3 / 100, 1 );
      lcd.print(" dia");

      lcd.setCursor(0, 3);
      lcd.print("Sobre temp. ideal");
    }
  }

  if (dm == 4110) {
    if (menu_t(4111, 4110, 4110, 411)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Calefacti");
      lcd.print(ochar);
      lcd.print("n");

      lcd.setCursor(0, 1);
      if (he_ak == 0) { lcd.print("> Apagado"); } else { lcd.print("> Activado"); }
    }
  }

  if (dm == 4111) {
    if (he_ak == 0)
    {
      eep_bearbeiten("he_ak", 1); //speichern
    } else {
      eep_bearbeiten("he_ak", 0); //speichern
    }

    dm = 4110;
    displayX();
    delay(100);
  }

  if (dm == 4120) {
    if (menu_t(4121, 4120, 4120, 412)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Refrigeraci");
      lcd.print(ochar);
      lcd.print("n");

      lcd.setCursor(0, 1);
      if (ku_ak == 0) { lcd.print("> Apagado"); } else { lcd.print("> Activado"); }
    }

    //hier fehlen noch sachen
  }

  if (dm == 4121) {
    if (ku_ak == 0)
    {
      eep_bearbeiten("ku_ak", 1); //speichern
    } else {
      eep_bearbeiten("ku_ak", 0); //speichern
    }

    dm = 4120;
    displayX();
    delay(100);
  }

  if (dm >= 420 && dm <= 422) {
    int menu_b, menu_c;
    if (dm == 420) {
      menu_b = 420;
      menu_c = 421;
    }
    if (li_op == 1) {
      if (dm == 421) {
        menu_b = 420;
        menu_c = 422;
      }
      if (dm == 422) {
        menu_b = 421;
        menu_c = 422;
      }
    } else {
      if (dm == 421) {
        menu_b = 420;
        menu_c = 421;
      }
    }

    if (menu_t(dm + 3, menu_b, menu_c, 42)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Iluminaci");
      lcd.print(ochar);
      lcd.print("n:");
      
      lcd.setCursor(0, 1);
      if (dm == 420) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Entre grupos");
      
      lcd.setCursor(0, 2);
      if (dm == 421) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Activar manual");
      if (li_op == 1) {
        lcd.setCursor(0, 3);
        if (dm == 422) { lcd.print("> "); } else { lcd.print("  "); }
        lcd.print("Horario");
        //hier fehlen noch sachen
      }
    }
  }

  if (dm == 423) {
    if (menu_t(423, 4231, 4232, 420)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Entre grupos:");
      lcd.setCursor(0, 1);
      lcd.print("minutos: ");
      lcd.print(licht_diff);
    }
  }

  if (dm == 4231) {
    licht_diff++;
    if (licht_diff > 60) {
      licht_diff = 60;
    }
    eep_bearbeiten("licht_diff", licht_diff); //speichern
    dm = 423;
    displayX();
    delay(100);
  }

  if (dm == 4232) {
    licht_diff--;
    if (licht_diff < 0) {
      licht_diff = 0;
    }
    eep_bearbeiten("licht_diff", licht_diff); //speichern
    dm = 423;
    displayX();
    delay(100);
  }

  if (dm == 424) {
    if (menu_t(424, 4241, 4242, 421)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Activar manual:");
      lcd.setCursor(0, 1);
      if (li_abg == 0) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Apagado");

      lcd.setCursor(0, 2);
      if (li_abg == 1) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Activado");
    }
  }

  if (dm == 4241) {
    eep_bearbeiten("li_abg", 0); //speichern
    dm = 424;
    displayX();
    delay(100);
  }

  if (dm == 4242) {
    eep_bearbeiten("li_abg", 1); //speichern
    dm = 424;
    displayX();
    delay(100);
  }

  if (dm >= 425 && dm <= 429)
  {
    int menu_b, menu_c;
    if (dm == 425) {
      menu_b = 425;
      menu_c = 426;
    }
    if (dm == 426) {
      menu_b = 425;
      menu_c = 427;
    }
    if (dm == 427) {
      menu_b = 426;
      menu_c = 428;
    }
    if (dm == 428) {
      menu_b = 427;
      menu_c = 429;
    }
    if (dm == 429) {
      menu_b = 428;
      menu_c = 429;
    }

    if (menu_t(dm * 10, menu_b, menu_c, 42)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Horario");

      lcd.setCursor(0, 1);
      lcd.print("# | Dia | De | Horas");

      int zeile = 2;

      if (dm == 425) {
        lcd.setCursor(0, zeile);
        lcd.print("1");
        if (dm == 425) { lcd.print("<| "); } else { lcd.print(" | "); }
        lcd.print(t1);
        lcd.setCursor(8, zeile);
        lcd.print("| ");
        lcd.print(u1);
        lcd.setCursor(13, zeile);
        lcd.print("| ");
        lcd.print(d1);
        zeile++;
      }

      if (dm == 425 || dm == 426) {
        lcd.setCursor(0, zeile);
        lcd.print("2");
        if (dm == 426) { lcd.print("<| "); } else { lcd.print(" | "); }
        lcd.print(t2);
        lcd.setCursor(8, zeile);
        lcd.print("| ");
        lcd.print(u2);
        lcd.setCursor(13, zeile);
        lcd.print("| ");
        lcd.print(d2);
        zeile++;
      }

      if (dm == 426 || dm == 427) {
        lcd.setCursor(0, zeile);
        lcd.print("3");
        if (dm == 427) { lcd.print("<| "); } else { lcd.print(" | "); }
        lcd.print(t3);
        lcd.setCursor(8, zeile);
        lcd.print("| ");
        lcd.print(u3);
        lcd.setCursor(13, zeile);
        lcd.print("| ");
        lcd.print(d3);
        zeile++;
      }

      if (dm == 427 || dm == 428 || dm == 429) {
        lcd.setCursor(0, zeile);
        lcd.print("4");
        if (dm == 428) { lcd.print("<| "); } else { lcd.print(" | "); }
        lcd.print(t4);
        lcd.setCursor(8, zeile);
        lcd.print("| ");
        lcd.print(u4);
        lcd.setCursor(13, zeile);
        lcd.print("| ");
        lcd.print(d4);
        zeile++;
      }

      if (dm == 428 || dm == 429) {
        lcd.setCursor(0, zeile);
        lcd.print("5");
        if (dm == 429) { lcd.print("<| "); } else { lcd.print(" | "); }
        lcd.print(t5);
        lcd.setCursor(8, zeile);
        lcd.print("| ");
        lcd.print(u5);
        lcd.setCursor(13, zeile);
        lcd.print("| ");
        lcd.print(d5);
        zeile++;
      }
    }
  }

  if (dm >= 4250 && dm <= 4293)
  {
    int pfeil, li_pro, li_t, li_u, li_d , menu_a, menu_d, li_lim;
    String sp_na = "";
    menu_a = dm + 1;
    menu_d = dm / 10;

    if (dm == 4250 || dm == 4260 || dm == 4270 || dm == 4280 || dm == 4290) {
      li_lim = 40;
      menu_a = dm + 1;
      pfeil = 1;
    }
    if (dm == 4251 || dm == 4261 || dm == 4271 || dm == 4281 || dm == 4291) {
      li_lim = 23;
      menu_a = dm + 1;
      pfeil = 2;
    }
    if (dm == 4252 || dm == 4262 || dm == 4272 || dm == 4282 || dm == 4292) {
      li_lim = 12;
      menu_a = dm / 10;
      pfeil = 3;
    }

    if (dm == 4250) {
      li_pro = t1;
      sp_na = "t1";
    }
    if (dm == 4251) {
      li_pro = u1;
      sp_na = "u1";
    }
    if (dm == 4252) {
      li_pro = d1;
      sp_na = "d1";
    }
    if (dm >= 4250 && dm <= 4252) {
      li_t = t1;
      li_u = u1;
      li_d = d1;
    }

    if (dm >= 4260) {
      li_pro = t2;
      sp_na = "t2";
    }
    if (dm >= 4261) {
      li_pro = u2;
      sp_na = "u2";
    }
    if (dm >= 4262) {
      li_pro = d2;
      sp_na = "d2";
    }
    if (dm >= 4260 && dm <= 4262) {
      li_t = t2;
      li_u = u2;
      li_d = d2;
    }

    if (dm >= 4270) {
      li_pro = t3;
      sp_na = "t3";
    }
    if (dm >= 4271) {
      li_pro = u3;
      sp_na = "u3";
    }
    if (dm >= 4272) {
      li_pro = d3;
      sp_na = "d3";
    }
    if (dm >= 4270 && dm <= 4272) {
      li_t = t3;
      li_u = u3;
      li_d = d3;
    }

    if (dm >= 4280) {
      li_pro = t4;
      sp_na = "t4";
    }
    if (dm >= 4281) {
      li_pro = u4;
      sp_na = "u4";
    }
    if (dm >= 4282) {
      li_pro = d4;
      sp_na = "d4";
    }
    if (dm >= 4280 && dm <= 4282) {
      li_t = t4;
      li_u = u4;
      li_d = d4;
    }

    if (dm >= 4290) {
      li_pro = t5;
      sp_na = "t5";
    }
    if (dm >= 4291) {
      li_pro = u5;
      sp_na = "u5";
    }
    if (dm >= 4292) {
      li_pro = d5;
      sp_na = "d5";
    }
    if (dm >= 4290 && dm <= 4292) {
      li_t = t5;
      li_u = u5;
      li_d = d5;
    }

    if (taste_r == "B") {
      li_pro++;
      if (li_pro > li_lim) {
        li_pro = li_lim;
      } eep_bearbeiten(sp_na, li_pro);
    }
    if (taste_r == "C") {
      li_pro--;
      if (li_pro < 0     ) {
        li_pro = 0;
      } eep_bearbeiten(sp_na, li_pro);
    }
    taste_r = "";

    if (menu_t(menu_a, dm, dm, menu_d)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Horario");

      lcd.setCursor(0, 1);
      lcd.print("# | Dia | De | Horas");

      lcd.setCursor(0, 2);
      lcd.print(sp_na.substring(1, 2));
      lcd.print(" |");
      if (pfeil == 1) { lcd.print(">"); li_t = li_pro; } else { lcd.print(" "); }
      lcd.print(li_t);
      lcd.setCursor(8, 2);
      lcd.print("|");
      if (pfeil == 2) { lcd.print(">"); li_u = li_pro; } else { lcd.print(" "); }
      lcd.print(li_u);
      lcd.setCursor(13, 2);
      lcd.print("|");
      if (pfeil == 3) { lcd.print(">"); li_d = li_pro; } else { lcd.print(" "); }
      lcd.print(li_d);
    }
  }

  if (dm == 4300) {
    if (taste == "C") {
      futtermenge = "";
      if (silo_offen == 0)
      {
        futtermenge += 1;
      } else {
        futtermenge += 2;
      }
    }
    if (menu_t(4301, 4300, 4302, 430)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Balanceado");
      lcd.setCursor(0, 1);
      lcd.print("> Pro Sec.: ");
      lcd.print(futtermenge.toInt());
      lcd.setCursor(0, 2);
      lcd.print("Cantidad de Silos");
      lcd.setCursor(0, 3);
      lcd.print("  ");
      if (silo_offen == 0) { lcd.print("1"); } else { lcd.print("2"); }
    }
  }

  if (dm == 4301) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Guardado");
    eep_bearbeiten("futter_sec", futtermenge.toInt()); //speichern
    dm = 4300;
    dt = secund + 1;
  }

  if (dm == 4302) {
    if (taste == "B") {
      futtermenge = "";
      futtermenge += futter_sec;
    }
    if (menu_t(4303, 4300, 4302, 430)) {
      if (futtermenge.toInt() >= 3)
      {
        futtermenge = "";
      }
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Balanceado");
      lcd.setCursor(0, 1);
      lcd.print("  Pro Sec.: ");
      lcd.print(futter_sec);
      lcd.setCursor(0, 2);
      lcd.print("Cantidad de Silos");
      lcd.setCursor(0, 3);
      lcd.print("> ");
      lcd.print(futtermenge.toInt());
    }
  }

  if (dm == 4303) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Guardado");
    if (futtermenge.toInt() == 1)
    {
      eep_bearbeiten("silo_offen", 0);
      eep_bearbeiten("silo2x", 0);
      silo2x = 0;
      silo2  = 0;
    }
    if (futtermenge.toInt() == 2) {
      eep_bearbeiten("silo_offen", 1);
    }
    dm = 4300;
    dt = secund + 1;
  }

  if (dm == 4310) {
    if (menu_t(4311, 4310, 4310, 431)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Medidor de agua");
      lcd.setCursor(0, 1);
      lcd.print("Litros por pulso:");

      lcd.setCursor(0, 2);
      lcd.print("> ");
      lcd.print(futtermenge.toInt());

      lcd.setCursor(0, 3);
      lcd.print("Entre 1 - 100 L");
    }
  }

  if (dm == 4311) {
    lcd.clear();

    lcd.setCursor(0, 0);
    if (futtermenge.toInt() > 0 && futtermenge.toInt() <= 100)
    {
      lcd.print("Guardado");
      eep_bearbeiten("wa_im", futtermenge.toInt()); //speichern
      dm = 0;
      dt = secund + 1;
    } else {
      lcd.print("Debe que estar");
      lcd.setCursor(0, 1);
      lcd.print("entre 1 - 100 L");
      dm = 4310;
    }
  }

  if (dm >= 4320 && dm <= 4322) {
    if (menu_t(dm + 5, 4320, 4321, 432)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Calibrar Sensoes:");

      lcd.setCursor(0, 1);
      lcd.print("de Temperatura:");

      lcd.setCursor(0, 2);
      if (dm == 4320) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print( (float)te1_ka / 100, 1 );
      lcd.print(String((char)223) + "C Galpon");

      lcd.setCursor(0, 3);
      if (dm == 4321) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print( (float)te2_ka / 100, 1 );
      lcd.print(String((char)223) + "C Afuera");
    }
  }

  if (dm == 4325) {
    if (taste == "B")
    {
      te1_ka = te1_ka + 10;
      if (te1_ka > 400) {
        te1_ka = 400;
      }
      eep_bearbeiten("te1_ka", te1_ka);
    }

    if (taste == "C")
    {
      te1_ka = te1_ka - 10;
      if (te1_ka < -400) {
        te1_ka = -400;
      }
      eep_bearbeiten("te1_ka", te1_ka);
    }

    int analog4 = temp2(4);
    if (analog4 != 9999)
    {
      analog4 = analog4 + te1_ka;
    }

    if (menu_t(dm - 5, dm, dm, dm - 5)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Sensor de Temp.");

      lcd.setCursor(0, 1);
      lcd.print("Galpon:");

      lcd.setCursor(0, 2);
      lcd.print("> ");
      lcd.print( (float)te1_ka / 100, 1 );
      lcd.print(String((char)223) + "C -> ");
      lcd.setCursor(13, 2);
      lcd.print( (float)analog4 / 100, 1 );
      lcd.print(String((char)223) + "C");

      lcd.setCursor(0, 3);
      lcd.print("  Digial:");
      lcd.setCursor(13, 3);
      lcd.print(float(te1 / 10) / 10, 1);
      lcd.print(String((char)223) + "C");
    }
  }

  if (dm == 4326) {
    if (taste == "B")
    {
      te2_ka = te2_ka + 10;
      if (te2_ka > 400) {
        te2_ka = 400;
      }
      eep_bearbeiten("te2_ka", te2_ka);
    }

    if (taste == "C")
    {
      te2_ka = te2_ka - 10;
      if (te2_ka < -400) {
        te2_ka = -400;
      }
      eep_bearbeiten("te2_ka", te2_ka);
    }

    int analog5 = temp2(5);
    if (analog5 != 9999)
    {
      analog5 = analog5 + te2_ka;
    }

    if (menu_t(dm - 5, dm, dm, dm - 5)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Sensor de Temp.");

      lcd.setCursor(0, 1);
      lcd.print("Afuera:");

      lcd.setCursor(0, 2);
      lcd.print("> ");
      lcd.print( (float)te2_ka / 100, 1 );
      lcd.print(String((char)223) + "C -> ");
      lcd.setCursor(13, 2);
      lcd.print( (float)analog5 / 100, 1 );
      lcd.print(String((char)223) + "C");

      lcd.setCursor(0, 3);
      lcd.print("  Digial:");
      lcd.setCursor(13, 3);
      lcd.print(float(te2 / 10) / 10, 1);
      lcd.print(String((char)223) + "C");
    }
  }
  
  //hier noch die feuchtigkeit
  if (dm >= 4990 && dm <= 4992) {
    temp_dht1();
    if (menu_t(dm + 5, 4990, 4991, 433)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Calibrar Sensoes:");

      lcd.setCursor(0, 1);
      lcd.print("de Humedad:");

      lcd.setCursor(0, 2);
      if (dm == 4990) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print( he1_ka );
      lcd.print("% Galpon");

      lcd.setCursor(0, 3);
      if (dm == 4991) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print( he2_ka );
      lcd.print("% Afuera");
    }
  }

  if (dm == 4995) {
    if (taste == "B")
    {
      he1_ka = he1_ka + 1;
      if (he1_ka > 50) {
        he1_ka = 50;
      }
      eep_bearbeiten("he1_ka", he1_ka);
    }

    if (taste == "C")
    {
      he1_ka = he1_ka - 1;
      if (he1_ka < -50) {
        he1_ka = -50;
      }
      eep_bearbeiten("he1_ka", he1_ka);
    }

    if (menu_t(dm - 5, dm, dm, dm - 5)) {
      temp_dht1();
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Sensor de");

      lcd.setCursor(0, 1);
      lcd.print("Humedad -> Galpon");

      lcd.setCursor(0, 2);
      lcd.print("> ");
      lcd.print(he1_ka);
      lcd.print("% -> ");
      lcd.setCursor(13, 2);
      int he1_re = h1/100;
      if(he1_re > 100){ he1_re = 100; }
      if(he1_re < 0){ he1_re = 0; }
      lcd.print( he1_re );
      lcd.print("%");
    }
  }

  if (dm == 4996) {
    if (taste == "B")
    {
      he2_ka = he2_ka + 1;
      if (he2_ka > 50) {
        he2_ka = 50;
      }
      eep_bearbeiten("he2_ka", he2_ka);
    }

    if (taste == "C")
    {
      he2_ka = he2_ka - 1;
      if (he2_ka < -50) {
        he2_ka = -50;
      }
      eep_bearbeiten("he2_ka", he2_ka);
    }

    if (menu_t(dm - 5, dm, dm, dm - 5)) {
      temp_dht1();
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Sensor de");

      lcd.setCursor(0, 1);
      lcd.print("Humedad -> Afuera");

      lcd.setCursor(0, 2);
      lcd.print("> ");
      lcd.print(he2_ka);
      lcd.print("% -> ");
      lcd.setCursor(13, 2);
      int he2_re = h2/100;
      if(he2_re > 100){ he2_re = 100; }
      if(he2_re < 0){ he2_re = 0; }
      lcd.print( he2_re );
      lcd.print("%");
    }
  }
  //ende der feuchtigkeit

  if (dm == 4330 || dm == 4331) {
    if (menu_t(dm + 2, 4330, 4331, 434)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Iluminaci");
      lcd.print(ochar);
      lcd.print("n");
      lcd.setCursor(0, 1);
      lcd.print("segun:");
      lcd.setCursor(0, 2);
      if (dm == 4330) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Signal");
      lcd.setCursor(0, 3);
      if (dm == 4331) { lcd.print("> "); } else { lcd.print("  "); }
      lcd.print("Horario");
    }
  }

  if (dm == 4332 || dm == 4333) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Guardado");
    if (dm == 4332) {
      eep_bearbeiten("li_op", 0);
    } else {
      eep_bearbeiten("li_op", 1);
    }
    dm = 0;
    dt = secund + 1;
  }

  if (dm >= 4340 && dm <= 4344) {
    unsigned long time_rechner = 0;
    if (dm == 4340) {
      time_rechner = 3600;
    }
    if (dm == 4341) {
      time_rechner = 60;
    }
    if (dm == 4342) {
      time_rechner = 86400;
    }
    if (dm == 4343) {
      time_rechner = 2592000;
    }
    if (dm == 4344) {
      time_rechner = 31536000;
    }
    if (taste == "B") {
      neue_zeit = (neue_zeit.unixtime() + time_rechner);
    }
    if (taste == "C") {
      neue_zeit = (neue_zeit.unixtime() - time_rechner);
    }
    if (menu_t(dm + 1, dm, dm, 435)) {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Hora:  ");
      if ( neue_zeit.hour() < 10 ) { lcd.print(" "); }
      lcd.print(neue_zeit.hour());
      lcd.print(":");
      if ( neue_zeit.minute() < 10 ) { lcd.print("0"); }
      lcd.print(neue_zeit.minute());

      lcd.setCursor(7, 1);
      if (dm == 4340) { lcd.print("--"); } else { lcd.print("  "); }
      lcd.print(" ");
      if (dm == 4341) { lcd.print("--"); } else { lcd.print("  "); }

      lcd.setCursor(0, 2);
      lcd.print("Fecha: ");
      if ( neue_zeit.day() < 10 ) { lcd.print(" "); }
      lcd.print(neue_zeit.day());
      lcd.print(".");
      if ( neue_zeit.month() < 10 ) { lcd.print(" "); }
      lcd.print(neue_zeit.month());
      lcd.print(".");
      lcd.print(neue_zeit.year());

      lcd.setCursor(7, 3);
      if (dm == 4342) { lcd.print("--"); } else { lcd.print("  "); }
      lcd.print(" ");
      if (dm == 4343) { lcd.print("--"); } else { lcd.print("  "); }
      lcd.print(" ");
      if (dm == 4344) { lcd.print("----"); }
    }
  }

  if (dm == 4345) { //*
    lcd.setCursor(0, 0);
    lcd.print("Guardado            ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    rtc.adjust(neue_zeit.unixtime());
    DateTime now = rtc.now();
    time_rtc     = now.unixtime() - secund;

    dm = 0;
    dt = secund + 1;
  }

  if (dm == 4350) {
    if (menu_t(4351, 4350, 4350, 436)) {
      lcd.setCursor(0, 0);
      lcd.print("Atenci");
      lcd.print(ochar);
      lcd.print("n            ");
      lcd.setCursor(0, 1);
      lcd.print("Se perder");
      lcd.print(achar);
      lcd.print("n todos   ");
      lcd.setCursor(0, 2);
      lcd.print("todos los datos     ");
      lcd.setCursor(0, 3);
      lcd.print("Confirmar (A)       ");
    }
  }

  if (dm == 4351) {
    lcd.setCursor(0, 0);
    lcd.print("Borrando...         ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    eep_bearbeiten("reset", 1);
    initializeVariables();
    
    neue_zeit = (time_rtc + secund);
    eep_bearbeiten("t_tag", neue_zeit.day()); //speichern
    eep_bearbeiten("t_mon", neue_zeit.month()); //speichern
    eep_bearbeiten("t_jahr", neue_zeit.year()); //speichern

    silo1 = (float)silo1x;
    silo2 = (float)silo2x;

    dm = 0;
    dt = secund + 1;
  }

  if (dm == 50) { //*
    if (menu_t(51, 0, 52, 0)) {
      lcd.setCursor(9, 0);
      lcd.print("           ");
      
      lcd.setCursor(0, 0);
      lcd.print("Muerto: ");
      lcd.print(futtermenge.toInt());
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("Confirmar con A     ");
      lcd.setCursor(0, 3);
      lcd.print("Salir con D         ");
    }
  }

  if (dm == 51) { //*
    lcd.setCursor(0, 0);
    lcd.print("Guardando           ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    eep_bearbeiten("to", to + futtermenge.toInt()); //speichern
    dm = 0;
    dt =  secund + 1;
  }

  if (dm == 52) { //*
    lcd.setCursor(0, 0);
    lcd.print("Guardando           ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    eep_bearbeiten("to", to - futtermenge.toInt()); //speichern
    dm = 0;
    dt = secund + 1;
  }

  DEBUG_LOG("displayX() ende");
}

boolean menu_t(int a, int b, int c, int d)
{
  if (taste == "A") {
    dm = a;
  }
  if (taste == "B") {
    dm = b;
  }
  if (taste == "C") {
    dm = c;
  }
  if (taste == "D") {
    dm = d;
  }

  if (taste == "*") {
    futtermenge = "";
  }
  if (taste == "*" && dm == 0 ) {
    dm = 50;
  }

  if (taste != "") {
    if (taste == "0" || taste == "1" || taste == "2" || taste == "3" || taste == "4" || taste == "5" || taste == "6" || taste == "7" || taste == "8" || taste == "9") {
      futtermenge += taste;
    }

    taste = "";
    dt = secund + 10;
    displayX();
    return false;
  } else {
    return true;
  }
}

String stellen(int zahlX)
{
  String antw = "";
  if ((int)zahlX >= 10000) {
    antw = String(zahlX);
  }
  else if ((int)zahlX >= 1000) {
    antw = " " + String(zahlX);
  }
  else if ((int)zahlX >= 100) {
    antw = "  " + String(zahlX);
  }
  else if ((int)zahlX >= 10)  {
    antw = "   " + String(zahlX);
  }
  else if ((int)zahlX  < 10)  {
    antw = "    " + String(zahlX);
  }
  return antw;
}
