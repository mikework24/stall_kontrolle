void licht()
{
  DEBUG_LOG("licht()");
  r12z = 1;
  r11z = 1;
  r10z = 1;
  r9z = 0;
    
  if(li_op == 0)
  {
    //licht schaltet nach eingangs Signal
    li_ang_timer++;
    long li_di = (long)licht_diff * 60;
    if(li_di <= 60){ li_di = 5; }
    int a3 = analogRead(3);
    if(a3 > 200)
    {
      if(li_z_alt == 0){ li_z_alt = 1; li_ang_timer = 0; }
      
      if(li_ang_timer < (li_di * 1)) { r11z = 0; }
      if(li_ang_timer < (li_di * 2)) { r10z = 0; }
      if(li_ang_timer < (li_di * 3)){ r9z = 1; }
    }else{
      if(li_z_alt == 1){ li_z_alt = 0; li_ang_timer = 0; }
      
      r12z = 0;
      if(li_ang_timer >= (li_di * 1)) { r11z = 0; }
      if(li_ang_timer >= (li_di * 2)) { r10z = 0; }
      if(li_ang_timer < (li_di * 3)){ r9z = 1; }
    }
  }else{
    //licht soll nach uhrzeiten schalten
    li_ang_timer = 3600;

    if(licht_typ == 2){ r9z = 1; } //läßt sich vieleicht in die nächste funktion verschieben
  
    for(int x= t1; x < t2; x++){ licht_f(x, u1, d1); }
    for(int x= t2; x < t3; x++){ licht_f(x, u2, d2); }
    for(int x= t3; x < t4; x++){ licht_f(x, u3, d3); }
    for(int x= t4; x < t5; x++){ licht_f(x, u4, d4); }
    for(int x= t5; x < 50; x++){ licht_f(x, u5, d5); }
  }
  
  if(li_abg == 1){
    r12z = 1;
    r11z = 1;
    r10z = 1;
    r9z = 1;
  }
  DEBUG_LOG("licht() ende");
}

void licht_f(long t, long u, long d)
{
  DEBUG_LOG("licht_f()");
  //if(licht_halbzeit != 0){  }
  long li_di = (long)licht_diff * 60; //in minuten umwandeln
  unsigned long an  = (t * 86400) + (u * 3600);
  unsigned long aus = an + (d * 3600);

  //ab 4 stunden aus darf geteilt werden
  //Serial.print("d = ");
  //Serial.println(d);
  //Serial.print("lhz = ");
  //Serial.println(licht_halbzeit);
  if(d >= 4 && licht_halbzeit != 0){
    //Serial.print("alte auszeit = ");
    //Serial.println(aus);
    aus = an + ((d + (long)licht_halbzeit) * 3600); //annschaltzeit wird um die pausenzeit verlängert
    //Serial.print("neue auszeit = ");
    //Serial.println(aus);
  }

  //lichtgruppen
  if(turzeit >= an && turzeit <= aus)                                 { r12z = 0; }
  if(turzeit >= (an + (li_di * 1)) && turzeit <= (aus + (li_di * 1))) { r11z = 0; }
  if(turzeit >= (an + (li_di * 2)) && turzeit <= (aus + (li_di * 2))) { r10z = 0; }

  //notlicht
  if(licht_typ == 0){ //3 Lichtgruppen Stall 2
    if(turzeit >= (an - 300) && turzeit <= (an + (li_di * 3))) { r9z = 1; } //startet (5 min vorher) mit dem ersten ausgehen + 3 * diff(Mike stall 1)
    if(turzeit >= (aus - (li_di * 1)) && turzeit <= (aus + (li_di * 2))){ r9z = 1; } //startet vorher bleibt nocht an bis alle lampen an sind(Mike)
  }

  if(licht_typ == 1){ //nur eine lichtgruppe Stall 1 und bei Anatoli
    
    if(turzeit >= (an - li_di) && turzeit <= (an + li_di)) { r9z = 1; } //notlicht beim ausschalten
    if(turzeit >= (aus - li_di) && turzeit <= (aus + li_di)) { r9z = 1; } //notlicht bevor licht an gehen soll
  }
  
  if(licht_typ == 2){ //notlicht bleibt tagsüber an (anatoli neu)
    if(turzeit >= (an + (li_di * 1)) && turzeit <= (aus - (li_di * 1))) { r9z = 0; }
  }

  //falls geteilt werden soll geht das licht wieder an bei der hälfte
  if(d >= 4 && licht_halbzeit != 0){
    if(turzeit >= (an + (d * 1800)) && turzeit <= (an + (d * 1800) + ((long)licht_halbzeit * 3600))){ r10z = 1; r11z = 1; r12z = 1; }
  }
  DEBUG_LOG("licht_f() ende");
}

int it(int tag) {
  DEBUG_LOG("it()");
  int idealtemp = 3200;
  if(tag >= 3){ idealtemp = 3100; }
  if(tag >= 7){ idealtemp = 3000; }
  if(tag >= 9){ idealtemp = 2900; }
  if(tag >= 11){ idealtemp = 2800; }
  if(tag >= 14){ idealtemp = 2700; }
  if(tag >= 16){ idealtemp = 2600; }
  if(tag >= 18){ idealtemp = 2500; }
  if(tag >= 21){ idealtemp = 2400; }
  if(tag >= 28){ idealtemp = 2300; }
  DEBUG_LOG("it() ende");
  return idealtemp;
}

void lueften() {
  DEBUG_LOG("lueften()");
  r5z=0; //gruppe 1 aus
  r6z=0; //gruppe 2 aus
  luftak=0;
  if(lu_ak == 1) //soll gelüftet werden
  {
    if(te1 >= (it(turtag) + lu_tol)) //über ideal temperatur für 1 ex dauerhaft
    {
      if(te1 >= (it(turtag) + lu_to2) && lu_2e_t <= turtag) //wenn der 2 ex an sein darf und die tolleranz ok ist dürfen 2 ex an sein
      {
        if(te1 >= (it(turtag) + lu_to3) && lu_3e_t <= turtag) //wenn der 3 ex an sein darf und die tolleranz ok ist dürfen 3 ex an sein
        { luftak = 3; }else{ luftak = 2; }
      }else{ luftak = 1; }
    }
    
    //läst nur eine änderung pro min zu
    if(luftak_n != luftak && loop_luft >= 60)
    {
      luftak_n = luftak;
      loop_luft = 0;
      if(luftak_n == 0){ loop_luft = m_lu + 1; }
    }
    
    if(luftak_n == 0){ if(loop_luft < m_lu){ r5z=1; }else{ r5z=0; } }
    
    if(luftak_n == 1){ r5z=1; r6z=0; }
    if(luftak_n == 2){ r5z=0; r6z=1; }
    if(luftak_n == 3){ r5z=1; r6z=1; }
    
    //zählt jede sec
    loop_luft++;
    if(loop_luft >= 300){ loop_luft = 0; }//jeder durchlauf dauert 5 min
  }
  DEBUG_LOG("luften() ende");
}

void kuhlen()
{
  DEBUG_LOG("kuehlen()");
  if(ku_ak == 1)
  {
    int ku_temp = 3000;              //nicht vor 30°C kühlen
    int ku_it   = it(turtag) + 200;
    
    if(ku_temp < ku_it){ ku_temp = ku_it; } //sorgt dafür das die sprühanlage nicht zu früh an geht
    
    if(te1 >= ku_temp) //zu heiß
    {
      int du_ku = (te1 - ku_temp) / 10;  
      if(du_ku < 2 ){ du_ku = 2;  }
      if(du_ku > 14){ du_ku = 18; }
      
      loop_ku++; //zählt die sec der kühlung
      
      if(loop_ku > 18){ loop_ku = 0; }
      if(loop_ku <= du_ku){ r7z=1; }else{ r7z=0; }
      
      
    }else{
      r7z=0;
      loop_ku = 0;
    }
  }else{
    r7z=0;
    loop_ku = 0;
  }
  DEBUG_LOG("kuehlen() ende");
}

void heizen()
{
  DEBUG_LOG("heizen()");
  if(he_ak == 1)
  {
    int hei_tol = 50; //tolleranz zwischen an und aus 0,5°C
    int hei_an  = it(turtag) - hei_tol;
    int hei_aus = it(turtag);
  
    if(te1 >= hei_aus)
    {
      r8z=0;
    }else{
      if(te1 <= hei_an && turtag <= 14)
      {
        r8z=1;
      }
    }
  }else{
    r8z=0;
  }
  DEBUG_LOG("heizen() ende");
}
